/******************************************************************************

 @File         occlusioncalculator.cpp

 @Title        Navigation

 @Version       @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  Calculates occlusion/visibility information using occlusion query
               facilities (or an image based fallback solution if hardware
               occlusion queries are not available).

******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <set>
#include <map>
using namespace std;

#include <stddef.h>
#include <float.h>

#include "PVRShell.h"
#include "OGLTools.h"

#include <GL/gl.h>

/******************************************************************************
 Defines
******************************************************************************/

#define OBJECT_TYPE_NONE     0
#define OBJECT_TYPE_BUILDING (1 << 0)
#define OBJECT_TYPE_LANDMARK (1 << 1)
#define OBJECT_TYPE_ROAD     (1 << 2)
#define OBJECT_TYPE_NODE     (1 << 3)
#define OBJECT_TYPE_LINK     (1 << 4)
#define OBJECT_TYPE_WATER    (1 << 5)
#define OBJECT_TYPE_LANDUSE  (1 << 6)
#define OBJECT_TYPE_TERRAIN  (1 << 7)
#define OBJECT_TYPE_ALL      ~0

// Constants required for alternate occlusion query mechanism
#ifndef GL_ANY_SAMPLES_PASSED_ARB
#define GL_ANY_SAMPLES_PASSED_ARB      0x8C2F
#endif
#ifndef GL_QUERY_RESULT_ARB
#define GL_QUERY_RESULT_ARB            0x8866
#endif
#ifndef GL_SAMPLES_PASSED_ARB
#define GL_SAMPLES_PASSED_ARB          0x8914
#endif
#ifndef GL_QUERY_RESULT_AVAILABLE_ARB
#define GL_QUERY_RESULT_AVAILABLE_ARB  0x8867
#endif

/******************************************************************************
 Constants
******************************************************************************/

const float c_fDefaultNearPlaneDistance = 0.1f;
const float c_fDefaultFarPlaneDistance = 500.0f;
const unsigned int c_iDefaultSubdivisions[3] = { 20, 20, 5 };
const unsigned int c_uiDefaultPathSubdivisions = 100;
// The following bitmask defines the types which will be always included in the occlusion test
// (they still have to pass the view frustum test though). 
const unsigned int c_uiEntityMask = OBJECT_TYPE_ROAD | OBJECT_TYPE_LINK | OBJECT_TYPE_NODE;

/****************************************************************************
** Structures
****************************************************************************/

/*!**************************************************************************
 *	@Struct PVRTBoundingBox2D
 *	@Brief  2D bounding box container.
 ****************************************************************************/
struct PVRTBoundingBox2D
{
	PVRTVec2 minCoords;
	PVRTVec2 maxCoords;
};

/*!**************************************************************************
 *	@Struct PVRTModelVertex
 *	@Brief  Vertex container including position, normal and texture coordinate.
 ****************************************************************************/
struct PVRTModelVertex
{
	PVRTVec3 position;
	PVRTVec3 normal;
	PVRTVec2 texcoord;
};

/*!**************************************************************************
 *	@Struct PVRTPositionColour
 *	@Brief  Vertex container including position and colour.
 ****************************************************************************/
struct PVRTPositionColour
{
	PVRTVec3 position;
	PVRTVec3 colour;
};

/*!**************************************************************************
 *	@Struct PVRTCompactModel
 *	@Brief  Compact model representation
 ****************************************************************************/
struct PVRTCompactModel
{
	// Vertex and index buffer objects for whole model (used for quick depth render)
	unsigned int numMeshes;
	unsigned int numIndices;
	GLuint vbo;
	GLuint ibo;

	// Per-object vertex and index buffers
	GLuint       *paObjectVbo;
	GLuint       *paIndexVbo;
	unsigned int *paNumIndices;
	unsigned int *paObjectTypes;

	PVRTBoundingBox2D boundingbox;
};

/*!**************************************************************************
 *	@Struct PVRTVisibilityRecord
 *	@Brief  Visibility record for a world-space position.
 ****************************************************************************/
struct PVRTVisibilityRecord
{
	PVRTVec3 position;
	map<unsigned int, set<unsigned int> > visible_tileobjects;
};

/*!**************************************************************************
 *	@Struct PVRTTileVisRecord
 *	@Brief  Visibility record for a whole city tile.
 ****************************************************************************/
struct PVRTTileVisRecord
{
	string filename;
	vector<string> tiles;
	vector<PVRTVisibilityRecord> visdata;
};

/*!**************************************************************************
 *	@Struct PVRTTileObjectSet
 *	@Brief  Stores an occlusion query object for a logical entity (e.g. a whole
 *          building, expressed as a parent node in the Collada file) and
 *          a vector of references into the POD node list for the physical
 *          representation of the child entities.
 ****************************************************************************/
struct PVRTTileObjectSet
{
	GLuint            occlusion_query;
	PVRTBoundingBox2D boundingbox;
	size_t            numSubObjects;
	unsigned int     *pNodeIdx;	
};

/*!**************************************************************************
 *	@Struct PVRTTileLod
 *	@Brief  Stores the filename of the city model tile and a description of the 
 *          objects it contains.
 ****************************************************************************/
struct PVRTTileLod
{
	char              *pszFilename;
	size_t             numObjects;
	PVRTTileObjectSet *paObjects;
};

/*!**************************************************************************
 *	@Struct PVRTTileContainer
 *	@Brief  Stores the bounding box of a city model tile and a list of the
 *          various levels of detail which represent the tile.
 ****************************************************************************/
struct PVRTTileContainer
{
	PVRTBoundingBox2D boundingbox;
	size_t            numLod;
	PVRTTileLod      *paLod;
};


/****************************************************************************
** Functions
****************************************************************************/

template<typename T>
void ConvertInchesToMeters(T &v)
{
	v *= 0.0254f;
}

bool PointInBoundingBox(PVRTVec2 pos, PVRTBoundingBox2D bbox)
{
	if (pos.x < bbox.minCoords.x || pos.y < bbox.minCoords.y || pos.x > bbox.maxCoords.x || pos.y > bbox.maxCoords.y)
		return false;
	else
		return true;
}

unsigned int DetermineObjectType(const char *pszName)
{
	if (strstr(pszName, "BUILDING")) return OBJECT_TYPE_BUILDING;
	if (strstr(pszName, "LANDMARK")) return OBJECT_TYPE_LANDMARK;
	if (strstr(pszName, "ROAD")) return OBJECT_TYPE_ROAD;
	if (strstr(pszName, "NODE")) return OBJECT_TYPE_NODE;
	if (strstr(pszName, "LINK")) return OBJECT_TYPE_LINK;
	if (strstr(pszName, "WATER")) return OBJECT_TYPE_WATER;
	if (strstr(pszName, "LANDUSE")) return OBJECT_TYPE_LANDUSE;
	if (strstr(pszName, "TERRAIN")) return OBJECT_TYPE_TERRAIN;
	return OBJECT_TYPE_NONE;
}

/*!****************************************************************************
 Class declaration
******************************************************************************/
class OcclusionCalculator : public PVRShell
{
	CPVRTglExt   m_Extensions;
	SPVRTContext m_PVRTContext;

	// Print3D class used to display text
	CPVRTPrint3D m_Print3D;

	// 3D Models		
	vector<string>            m_aszFilenames;
	vector<PVRTCompactModel>  m_aCityBlocks;
	vector<PVRTTileContainer> m_aModelIndex;
				
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	float        m_fAspectRatio;
	float        m_fFOV;
	float        m_fNearClipPlane;
	float        m_fFarClipPlane;
	bool         m_bRotate;

	unsigned int m_auiSubdivisions[3];
	unsigned int m_uiPathSubdivisions;

	PVRTMat4     m_mProjectionMatrix;
		
	string       m_szDefaultDirectory;
	string       m_szModelDirectory;
	string       m_szModelIndexFile;
	string       m_szOcclusionDataFilename;

	int          m_iProcessingCounter;
	int          m_iProcessingIterations;
	bool         m_bHWOcclusionQuery;
	GLenum       m_eOcclusionQueryMethod;

	unsigned long m_ulStartTime;
	unsigned long m_ulEndTime;

	CPVRTModelPOD m_Camera;
	bool m_bUseCameraPath;
	PVRTTileVisRecord m_CameraPathOcclusionData;
	
public:

	virtual bool InitApplication();
	virtual bool InitView();
	virtual bool ReleaseView();
	virtual bool QuitApplication();
	virtual bool RenderScene();
	
	bool Load3dModelIndex(const char *pszFilename);
	void Release3dModelIndex();
	bool LoadAndCompactModel(unsigned int idx, PVRTCompactModel &model);

	void GetViewFrustumPlanes(const PVRTMat4 &matrix, PVRTVec4 &left, PVRTVec4 &right, PVRTVec4 &front, PVRTVec4 &back) const;	
	void GetViewFrustumPlanes(const PVRTMat4 &matrix, PVRTVec4 &left, PVRTVec4 &right, PVRTVec4 &front, PVRTVec4 &back, PVRTVec4 &bottom, PVRTVec4 &top) const;
	bool BoundingBoxIntersectsFrustum(const PVRTBoundingBox2D &bbox, const PVRTVec4 planes[], const unsigned int numPlanes);

	void GenerateOcclusionDataTile(unsigned int modelindex, unsigned int subdivisions[3], float min_height, float max_height);
	void GenerateOcclusionDataCameraPath(CPVRTModelPOD &scene, unsigned int camera_idx, unsigned int subdivisions);

	void CalculateOcclusionFramebuffer(const PVRTVec3 &position, map<unsigned int, set<unsigned int> > &references);
	void CalculateOcclusionQuery(const PVRTVec3 &position, map<unsigned int, set<unsigned int> > &references, unsigned int objmask);

	bool WriteCameraPathOcclusionData(const char *pszFilename);
};



/*!****************************************************************************
 @Function		InitApplication
 @Return		bool		true if no error occured
 @Description	Code in InitApplication() will be called by PVRShell once per
				run, before the rendering context is created.
				Used to initialize variables that are not dependant on it
				(e.g. external modules, loading meshes, etc.)
				If the rendering context is lost, InitApplication() will
				not be called again.
******************************************************************************/
bool OcclusionCalculator::InitApplication()
{	
	m_iProcessingCounter = -1;
	m_iProcessingIterations = 0;
	m_bUseCameraPath = false;
	
	m_szDefaultDirectory = string((char*)PVRShellGet(prefReadPath)) + "..\\";	
	CPVRTResourceFile::SetReadPath(m_szDefaultDirectory.c_str());
	
	// Set defaults
	m_szModelDirectory = "models";
	m_szModelIndexFile = "hirarchy.n3d";
	m_szOcclusionDataFilename = "occlusiondata.nav";
	m_fNearClipPlane = c_fDefaultNearPlaneDistance;
	m_fFarClipPlane = c_fDefaultFarPlaneDistance;
	m_auiSubdivisions[0] = c_iDefaultSubdivisions[0];
	m_auiSubdivisions[1] = c_iDefaultSubdivisions[1];
	m_auiSubdivisions[2] = c_iDefaultSubdivisions[2];
	m_uiPathSubdivisions = c_uiDefaultPathSubdivisions;

	const SCmdLineOpt *pCmds = (const SCmdLineOpt*)PVRShellGet(prefCommandLineOpts);
	const int numCmds = PVRShellGet(prefCommandLineOptNum);
	for (int i=0; i < numCmds; i++)
	{
		if (strcmp(pCmds[i].pArg, "-help") == 0)
		{
			PVRShellOutputDebug("Available command line options:\n");
			PVRShellOutputDebug("  -models    Directory containing the city model files referenced by the index file\n");
			PVRShellOutputDebug("  -index     Hirarchical index file (generated by 3dSceneCompiler)\n");
			PVRShellOutputDebug("  -near      Camera near plane distance in meters\n");
			PVRShellOutputDebug("  -far       Camera far plane distance in meters\n");
			PVRShellOutputDebug("  -subdivx   Number of subdivision steps in x direction\n");
			PVRShellOutputDebug("  -subdivy   Number of subdivision steps in y direction\n");
			PVRShellOutputDebug("  -subdivz   Number of subdivision steps in z direction\n");
			PVRShellOutputDebug("  -camera    POD file containing camera paths to generate visibility data for\n");
			PVRShellOutputDebug("  -pathsteps Number of (equally spaced) subdivisions when following camera path\n");
			PVRShellOutputDebug("  -o         Output file containing occlusion data\n");
			
			return false;
		}
		if (strcmp(pCmds[i].pArg, "-o") == 0)
			m_szOcclusionDataFilename = pCmds[i].pVal;
		if (strcmp(pCmds[i].pArg, "-models") == 0)
			m_szModelDirectory = pCmds[i].pVal;		
		if (strcmp(pCmds[i].pArg, "-index") == 0)
			m_szModelIndexFile = pCmds[i].pVal;
		if (strcmp(pCmds[i].pArg, "-near") == 0)
			m_fNearClipPlane = (float)atoi(pCmds[i].pVal);
		if (strcmp(pCmds[i].pArg, "-far") == 0)
			m_fFarClipPlane = (float)atoi(pCmds[i].pVal);
		if (strcmp(pCmds[i].pArg, "-subdivx") == 0)
			m_auiSubdivisions[0] = atoi(pCmds[i].pVal);
		if (strcmp(pCmds[i].pArg, "-subdivy") == 0)
			m_auiSubdivisions[1] = atoi(pCmds[i].pVal);
		if (strcmp(pCmds[i].pArg, "-subdivz") == 0)
			m_auiSubdivisions[2] = atoi(pCmds[i].pVal);		
		if (strcmp(pCmds[i].pArg, "-camera") == 0)
		{
			if (m_Camera.ReadFromFile(pCmds[i].pVal) == PVR_SUCCESS)
				m_bUseCameraPath = true;
		}
		if (strcmp(pCmds[i].pArg, "-pathsteps") == 0)
			m_uiPathSubdivisions = atoi(pCmds[i].pVal);		
	}			
		
	return true;
}


/*!****************************************************************************
 @Function		QuitApplication
 @Return		bool		true if no error occured
 @Description	Code in QuitApplication() will be called by PVRShell once per
				run, just before exiting the program.
				If the rendering context is lost, QuitApplication() will
				not be called.
******************************************************************************/
bool OcclusionCalculator::QuitApplication()
{
	unsigned long delta = m_ulEndTime - m_ulStartTime;
	PVRShellOutputDebug("Time to process data: %f secs\n", delta * 0.001f);
	
    return true;
}

/*!****************************************************************************
 @Function		InitView
 @Return		bool		true if no error occured
 @Description	Code in InitView() will be called by PVRShell upon
				initialization or after a change in the rendering context.
				Used to initialize variables that are dependant on the rendering
				context (e.g. textures, vertex buffers, etc.)
******************************************************************************/
bool OcclusionCalculator::InitView()
{
	m_Extensions.LoadExtensions();
	m_PVRTContext.pglExt = &m_Extensions;

	CPVRTString ErrorStr;	
						
	// Is the screen rotated?
	m_bRotate = PVRShellGet(prefIsRotated) && PVRShellGet(prefFullScreen);
#ifdef _WIN32
	if (PVRShellGet(prefWidth) < PVRShellGet(prefHeight))
		m_bRotate = true;
#endif

	
	// Initialize Print3D
	if(m_Print3D.SetTextures(&m_PVRTContext, PVRShellGet(prefWidth), PVRShellGet(prefHeight), m_bRotate) != PVR_SUCCESS)
	{
		PVRShellSet(prefExitMessage, "ERROR: Cannot initialise Print3D\n");
		return false;
	}

	// Determine level of Occlusion query support
	if (CPVRTglExt::IsGLExtensionSupported("GL_ARB_occlusion_query2"))
	{
		m_bHWOcclusionQuery = true;
		m_eOcclusionQueryMethod = GL_ANY_SAMPLES_PASSED_ARB;
		PVRShellOutputDebug("Info: Using ANY_SAMPLES_PASSED occlusion query method.\n");
	}
	else if (CPVRTglExt::IsGLExtensionSupported("GL_ARB_occlusion_query"))
	{
		m_bHWOcclusionQuery = true;
		m_eOcclusionQueryMethod = GL_SAMPLES_PASSED_ARB;		
		PVRShellOutputDebug("Info: Using SAMPLES_PASSED occlusion query method.\n");
	}
	else
		m_bHWOcclusionQuery = false;

	if (!Load3dModelIndex(m_szModelIndexFile.c_str()))
	{
		PVRShellSet(prefExitMessage, "Failed to open model index file.\n");
		return false;
	}

	for (unsigned int i=0; i < m_aModelIndex.size(); i++)
		m_aszFilenames.push_back(m_aModelIndex[i].paLod[0].pszFilename);
	
	CPVRTResourceFile::SetReadPath(m_szModelDirectory.c_str());
	for (unsigned int i=0; i < m_aszFilenames.size(); i++)
	{
		PVRTCompactModel compmodel;
		if (!LoadAndCompactModel(i, compmodel))
		{
			PVRShellSet(prefExitMessage, "ERROR: Could not load models\n");
			return false;
		}
		m_aCityBlocks.push_back(compmodel);
	}

	if (m_bUseCameraPath)
		m_iProcessingIterations = m_Camera.nNumCamera;
	else
		m_iProcessingIterations = (int)m_aCityBlocks.size();

	m_uiWidth = PVRShellGet(prefWidth);
	m_uiHeight = PVRShellGet(prefHeight);
	m_fAspectRatio = (float)m_uiWidth/(float)m_uiHeight;
	// 90 degrees opening angle
	m_fFOV = PVRT_PI_OVER_TWO;
	
	m_mProjectionMatrix = PVRTMat4::PerspectiveFovRH(m_fFOV, m_fAspectRatio, m_fNearClipPlane, m_fFarClipPlane, PVRTMat4::OGL, m_bRotate); 

	m_ulStartTime = PVRShellGetTime();
				
	return true;
}

/*!****************************************************************************
 @Function		ReleaseView
 @Return		bool		true if no error occured
 @Description	Code in ReleaseView() will be called by PVRShell when the
				application quits or before a change in the rendering context.
******************************************************************************/
bool OcclusionCalculator::ReleaseView()
{		
	// Release Print3D Textures
	m_Print3D.ReleaseTextures();

	Release3dModelIndex();

	for (unsigned int i=0; i < m_aCityBlocks.size(); i++)
	{
		m_Extensions.glDeleteBuffersARB(m_aCityBlocks[i].numMeshes, m_aCityBlocks[i].paIndexVbo);
		m_Extensions.glDeleteBuffersARB(m_aCityBlocks[i].numMeshes, m_aCityBlocks[i].paObjectVbo);
		delete [] m_aCityBlocks[i].paIndexVbo;
		delete [] m_aCityBlocks[i].paNumIndices;
		delete [] m_aCityBlocks[i].paObjectVbo;
		delete [] m_aCityBlocks[i].paObjectTypes;
	}

	m_ulEndTime = PVRShellGetTime();

	return true;
}

/*!****************************************************************************
 @Function		RenderScene
 @Return		bool		true if no error occured
 @Description	Main rendering loop function of the program. The shell will
				call this function every frame.
				eglSwapBuffers() will be performed by PVRShell automatically.
				PVRShell will also manage important OS events.
				The user has access to these events through an abstraction 
				layer provided by PVRShell.
******************************************************************************/
bool OcclusionCalculator::RenderScene()
{
	if (m_iProcessingCounter >= m_iProcessingIterations)
	{
		if (m_bUseCameraPath)
			WriteCameraPathOcclusionData("occlusiondata.nav");
		return false;
	}

	// Setup the viewport for the whole window
	glViewport(0, 0, m_uiWidth, m_uiHeight);

	glDisable(GL_CULL_FACE);
	// No depth testing when rendering a plain 2D map
	glEnable(GL_DEPTH_TEST);
	// No stencil test required by default
	glDisable(GL_STENCIL_TEST);
	// Disable blending by default for now, but set proper blending mode
	glDisable(GL_BLEND);	

	if (m_iProcessingCounter == -1)
	{
		m_iProcessingCounter = 0;
		m_Print3D.DisplayDefaultTitle("Occlusion Data Calculator", NULL, ePVRTPrint3DLogoIMG);
		m_Print3D.Flush();
		return true;
	}

	unsigned long prevtime = PVRShellGetTime();

	if (m_bUseCameraPath)
		GenerateOcclusionDataCameraPath(m_Camera, m_iProcessingCounter, m_uiPathSubdivisions);
	else
		GenerateOcclusionDataTile(m_iProcessingCounter, m_auiSubdivisions, 8.0f, 100.0f);

	unsigned long posttime = PVRShellGetTime();	
				
	m_Print3D.DisplayDefaultTitle("Occlusion Data Calculator", NULL, ePVRTPrint3DLogoIMG);
	m_Print3D.Print3D(0.5f, 60.0f, 1.0f, 0xCDFFFFFF, "Time: %.2f seconds", (posttime - prevtime)*0.001f);
	if (m_bUseCameraPath)
	{
		m_Print3D.Print3D(0.5f, 50.0f, 1.0f, 0xCDFFFFFF, "Camera: %d / %d", m_iProcessingCounter+1, m_iProcessingIterations);	
		PVRShellOutputDebug("Processing of camera path took %.2f seconds.\n", (posttime - prevtime) * 0.001f);
	}
	else
	{
		m_Print3D.Print3D(0.5f, 50.0f, 1.0f, 0xCDFFFFFF, "Tile: %d / %d", m_iProcessingCounter+1, m_iProcessingIterations);	
		PVRShellOutputDebug("Processing of tile %s took %.2f seconds.\n", m_aszFilenames[m_iProcessingCounter].c_str(), (posttime - prevtime) * 0.001f);
	}
	m_Print3D.Flush();
	

	m_iProcessingCounter++;

	return true;
}


/*!****************************************************************************
 @Function		GenerateOcclusionDataTile 
 @Description	Calculates the occlusion data for a whole city tile at once.
                The reference positions are derived from the subdivision parameter.
******************************************************************************/
void OcclusionCalculator::GenerateOcclusionDataTile(unsigned int modelindex, unsigned int subdivisions[3], float min_height, float max_height)
{					
	PVRTTileVisRecord tilevisdata;
	tilevisdata.filename = m_aszFilenames[modelindex];
	tilevisdata.tiles = m_aszFilenames;

	PVRTBoundingBox2D bbox = m_aModelIndex[modelindex].boundingbox;
	PVRTVec2 dims = bbox.maxCoords - bbox.minCoords;
	PVRTVec3 position(bbox.minCoords.x, bbox.minCoords.y, min_height);
	PVRTVec3 stepwidth(dims.x / subdivisions[0], dims.y / subdivisions[1], (max_height - min_height) / subdivisions[2]);

	// For each grid cell
	for (unsigned int z=0; z < subdivisions[2]; z++)
	{
		for (unsigned int y=0; y < subdivisions[1]; y++)
		{
			for (unsigned int x=0; x < subdivisions[0]; x++)
			{
				PVRTVisibilityRecord posvisdata;
				posvisdata.position = position + PVRTVec3(stepwidth.x * x, stepwidth.y * y, stepwidth.z * z);
																
				if (m_bHWOcclusionQuery)				
					CalculateOcclusionQuery(posvisdata.position, posvisdata.visible_tileobjects, c_uiEntityMask);
				else
					CalculateOcclusionFramebuffer(posvisdata.position, posvisdata.visible_tileobjects);				
				
				tilevisdata.visdata.push_back(posvisdata);
			}
		}

		PVRShellOutputDebug("Finished cell row %d / %d\n", z, subdivisions[2]);
	}
	
	PVRShellOutputDebug("Finished processing tile %s\n", m_aszFilenames[modelindex].c_str());

	// File structure:
	//   #filenamelength filename
	//   #tiles 
	//   for_each(tile) { #tilenamelength tilename }
	//   #positions
	//   for_each(position) { #reftiles 
	//                        for_each(reftile) { #objects objectid } }
	//   
	
	string filename = "tilemap_" + m_aszFilenames[modelindex] + ".txt";	
	ofstream occfile(filename.c_str(), ios::binary);
	if (!occfile.is_open())
	{
		PVRShellOutputDebug("Error: Can't open %s\n", filename.c_str());
		return;
	}

	size_t namelen = m_aszFilenames[modelindex].length();
	occfile.write((const char*)&namelen, sizeof(size_t));
	occfile.write((const char*)m_aszFilenames[modelindex].c_str(), (std::streamsize)namelen);
	size_t numTiles = m_aszFilenames.size();
	occfile.write((const char*)&numTiles, sizeof(size_t));
	for (unsigned int i=0; i < numTiles; i++)
	{
		namelen = m_aszFilenames[i].length();
		occfile.write((const char*)&namelen, sizeof(size_t));
		occfile.write((const char*)m_aszFilenames[i].c_str(), (std::streamsize)namelen);
	}


	size_t numpositions = subdivisions[0] * subdivisions[1] * subdivisions[2];
	occfile.write((const char *)&numpositions, sizeof(size_t));

	for (unsigned int i=0; i < tilevisdata.visdata.size(); i++)
	{
		PVRTVisibilityRecord &posvisdata = tilevisdata.visdata[i];
		PVRTVec3 pos = posvisdata.position;
		occfile.write((const char*)pos.ptr(), sizeof(PVRTVec3));
		size_t reftiles = posvisdata.visible_tileobjects.size();
		occfile.write((const char*)&reftiles, sizeof(size_t));

		unsigned int refcounter = 0;

		map<unsigned int, set<unsigned int> >::iterator map_iter;
		for (map_iter = posvisdata.visible_tileobjects.begin(); map_iter != posvisdata.visible_tileobjects.end(); map_iter++)
		{					
			size_t tilenum = map_iter->first;
			occfile.write((const char*)&tilenum, sizeof(size_t));
					
			vector<unsigned int> tmp_vec;
			copy(map_iter->second.begin(), map_iter->second.end(), back_inserter(tmp_vec));
			size_t num_ref_models = tmp_vec.size();
			occfile.write((const char *)&num_ref_models, sizeof(size_t));
			occfile.write((const char *)&tmp_vec[0], (std::streamsize)(sizeof(unsigned int) * num_ref_models));
			refcounter += (unsigned int)num_ref_models;
		}								
	}

	occfile.close();
}


/*!****************************************************************************
 @Function		GenerateOcclusionDataCameraPath 
 @Description	Calculates the occlusion data for all cameras found in a POD file.
******************************************************************************/
void OcclusionCalculator::GenerateOcclusionDataCameraPath(CPVRTModelPOD &scene, unsigned int camera_idx, unsigned int subdivisions)
{		
	const float stepwidth = (scene.nNumFrame - 1) / (float)subdivisions;
	
	float time = 0.0f;

	for (unsigned int j=0; j < subdivisions; j++)
	{
		PVRTVec3 pos, to, up;
		scene.SetFrame(time);
		scene.GetCamera(pos, to, up, camera_idx);
		time += stepwidth;

		ConvertInchesToMeters(pos);
		pos = PVRTVec3(pos.x, -pos.z, pos.y);

		PVRTVisibilityRecord posvisdata;
		posvisdata.position = pos;

		if (m_bHWOcclusionQuery)				
			CalculateOcclusionQuery(pos, posvisdata.visible_tileobjects, c_uiEntityMask);
		else
			CalculateOcclusionFramebuffer(pos, posvisdata.visible_tileobjects);				

		m_CameraPathOcclusionData.visdata.push_back(posvisdata);			
	}
}


/*!****************************************************************************
 @Function		CalculateOcclusionFramebuffer 
 @Description	Fallback method to determine the visible buildings for a particular
                viewpoint. 
******************************************************************************/
void OcclusionCalculator::CalculateOcclusionFramebuffer(const PVRTVec3 &position, map<unsigned int, set<unsigned int> > &references)
{
	const unsigned int num_pixels = m_uiWidth * m_uiHeight;
	const unsigned int pixel_offset = num_pixels * 3;
	// Allocate a buffer big enough to store the framebuffer
	unsigned char *pPixels = new unsigned char[pixel_offset * 4];
	memset(pPixels, 0, pixel_offset * 4);

	PVRTVec3 viewdirs[6] = { PVRTVec3(0.0f, 1.0f, 0.0f), PVRTVec3(0.0f, -1.0f, 0.0f), PVRTVec3(-1.0f, 0.0f, 0.0f), PVRTVec3(1.0f, 0.0f, 0.0f), PVRTVec3(0.0f, 0.0f, -1.0f), PVRTVec3(0.0f, 0.0f, 1.0f) };
	PVRTVec3 updirs[6] = { PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(0.0f, 1.0f, 0.0f), PVRTVec3(0.0f, 1.0f, 0.0f) };

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_mProjectionMatrix.f);

	// For each of the four viewdirections
	for (unsigned int i=0; i < 6; i++)
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		PVRTMat4 viewmatrix = PVRTMat4::LookAtRH(position, position + viewdirs[i], updirs[i]);
		PVRTMat4 mvp = m_mProjectionMatrix * viewmatrix;

		PVRTVec4 planes[6];		
		GetViewFrustumPlanes(mvp, planes[0], planes[1], planes[2], planes[3], planes[4], planes[5]);
				
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(viewmatrix.f);		

		for (unsigned int j=0; j < m_aCityBlocks.size(); j++)
		{			
			// Gross culling of non-visible out-of-frustum objects
			if (!BoundingBoxIntersectsFrustum(m_aModelIndex[j].boundingbox, planes, 6))
				continue;

			m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_aCityBlocks[j].vbo);
			m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_aCityBlocks[j].ibo);		

			glVertexPointer(3, GL_FLOAT, sizeof(PVRTPositionColour), 0);
			glColorPointer(3, GL_FLOAT, sizeof(PVRTPositionColour), (const GLvoid*)offsetof(PVRTPositionColour, colour));

			glDrawElements(GL_TRIANGLES, (GLsizei)m_aCityBlocks[j].numIndices, GL_UNSIGNED_SHORT, 0);
		}

		glReadPixels(0, 0, m_uiWidth, m_uiHeight, GL_RGB, GL_UNSIGNED_BYTE, &pPixels[pixel_offset * i]);					
	}

	m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	for (unsigned int i=0; i < num_pixels * 4; i++)
	{						
		unsigned models_high = (unsigned int)(pPixels[i * 3 + 2]);
		unsigned models = (unsigned int)pPixels[i * 3 + 1];
		unsigned tile = (unsigned int)pPixels[i * 3];

		if (models_high == 255 && models == 255 && tile == 255)
			continue;

		references[tile].insert(models_high * 255 + models);						
	}

	delete [] pPixels;
}

/*!****************************************************************************
 @Function		CalculateOcclusionQuery
 @Description	Calculates visibility information based on hardware occlusion
                queries.
******************************************************************************/
void OcclusionCalculator::CalculateOcclusionQuery(const PVRTVec3 &position, map<unsigned int, set<unsigned int> > &references, unsigned int objmask)
{		
	PVRTVec3 viewdirs[6] = { PVRTVec3(0.0f, 1.0f, 0.0f), PVRTVec3(0.0f, -1.0f, 0.0f), PVRTVec3(-1.0f, 0.0f, 0.0f), PVRTVec3(1.0f, 0.0f, 0.0f), PVRTVec3(0.0f, 0.0f, -1.0f), PVRTVec3(0.0f, 0.0f, 1.0f) };
	PVRTVec3 updirs[6] = { PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(0.0f, 0.0f, 1.0f), PVRTVec3(1.0f, 0.0f, 0.0f), PVRTVec3(1.0f, 0.0f, 0.0f) };

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_mProjectionMatrix.f);

	// Enable the vertex attribute arrays	
	glEnableClientState(GL_VERTEX_ARRAY);

	// for each of the six viewdirections
	for (unsigned int i=0; i < 6; i++)
	{	
		// Clear the depth buffer, set the depth function and enable writing the depth values		
		glEnable(GL_DEPTH_TEST);		
		glDepthMask(GL_TRUE);		
		glClear(GL_DEPTH_BUFFER_BIT);
        
		PVRTMat4 viewmatrix = PVRTMat4::LookAtRH(position, position + viewdirs[i], updirs[i]);
		PVRTMat4 mvp = m_mProjectionMatrix * viewmatrix;

		PVRTVec4 planes[6];		
		GetViewFrustumPlanes(mvp, planes[0], planes[1], planes[2], planes[3], planes[4], planes[5]);
				
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(viewmatrix.f);		

		//
		// First render all occluders to the depth buffer
		//
		for (unsigned int j=0; j < m_aCityBlocks.size(); j++)
		{					
			m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_aCityBlocks[j].vbo);
			m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_aCityBlocks[j].ibo);				
			glVertexPointer(3, GL_FLOAT, sizeof(PVRTPositionColour), 0);

			glDrawElements(GL_TRIANGLES, (GLsizei)m_aCityBlocks[j].numIndices, GL_UNSIGNED_SHORT, 0);
		}
	
		//
		// Then each individual object
		//
		glDepthMask(GL_FALSE);		

		for (unsigned int j=0; j < m_aModelIndex.size(); j++)
		{			
			if (!BoundingBoxIntersectsFrustum(m_aModelIndex[j].boundingbox, planes, 6))
				continue;					

			const PVRTTileLod &pLod = m_aModelIndex[j].paLod[0];

			// Render each object, initiating the occlusion query before submitting the draw call			
			for (unsigned int k=0; k < pLod.numObjects; k++)
			{
				const PVRTTileObjectSet &object = pLod.paObjects[k];

				// If the current object is in the pass-through bitmask simply add it to the visible list
				// and continue with the next object
				if ((m_aCityBlocks[j].paObjectTypes[object.pNodeIdx[0]] & objmask) &&
					BoundingBoxIntersectsFrustum(object.boundingbox, planes, 6))
				{
					references[j].insert(k);
					continue;
				}
								
				m_Extensions.glBeginQueryARB(m_eOcclusionQueryMethod, object.occlusion_query); 
				
				for (unsigned int n=0; n < object.numSubObjects; n++)
				{					
					const unsigned int nodeidx = object.pNodeIdx[n];					

					m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_aCityBlocks[j].paObjectVbo[nodeidx]);
					m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, m_aCityBlocks[j].paIndexVbo[nodeidx]);		
					glVertexPointer(3, GL_FLOAT, sizeof(PVRTVec3), 0);
					
					glDrawElements(GL_TRIANGLES, (GLsizei)m_aCityBlocks[j].paNumIndices[nodeidx], GL_UNSIGNED_SHORT, 0);							
				}

				m_Extensions.glEndQueryARB(m_eOcclusionQueryMethod);
			}
		}

		glFlush();

		//
		// Iterate over all objects once again to get the results
		//
		for (unsigned int j=0; j < m_aModelIndex.size(); j++)
		{			
			// Gross culling of non-visible out-of-frustum objects			
			if (!BoundingBoxIntersectsFrustum(m_aModelIndex[j].boundingbox, planes, 6))
				continue;

			const PVRTTileLod &pLod = m_aModelIndex[j].paLod[0];

			for (unsigned int k=0; k < pLod.numObjects; k++)
			{
				const PVRTTileObjectSet &object = pLod.paObjects[k];

				// Skip objects that were skipped in the query again
				if ((m_aCityBlocks[j].paObjectTypes[object.pNodeIdx[0]] & objmask) &&
					BoundingBoxIntersectsFrustum(object.boundingbox, planes, 6))				
					continue;
								
				// Wait for the occlusion query to finish
				int available = 0;
				do
				{
					m_Extensions.glGetQueryObjectivARB(m_aModelIndex[j].paLod[0].paObjects[k].occlusion_query, GL_QUERY_RESULT_AVAILABLE_ARB, &available);					
				} while (!available);

				GLuint fragmentCount;
				m_Extensions.glGetQueryObjectuivARB(m_aModelIndex[j].paLod[0].paObjects[k].occlusion_query, GL_QUERY_RESULT_ARB, &fragmentCount);

				// If one fragment passed the test add it to the visible list
				if (fragmentCount > 0)
					references[j].insert(k);					
			}
		}		
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);

	m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	
	GLenum glerror = glGetError();
	if (GL_NO_ERROR != glerror)
		PVRShellOutputDebug("Error in GL: %d\n", glerror);
}

/*!****************************************************************************
 @Function		GetViewFrustumPlanes
 @Description	TODO
******************************************************************************/
void OcclusionCalculator::GetViewFrustumPlanes(const PVRTMat4 &matrix, PVRTVec4 &left, PVRTVec4 &right, PVRTVec4 &front, PVRTVec4 &back) const
{
	left.x = (matrix.f[3]  + matrix.f[0]);
    left.y = (matrix.f[7]  + matrix.f[4]);
    left.z = (matrix.f[11] + matrix.f[8]);
	left.w = (matrix.f[15] + matrix.f[12]);
	float inv_len = 1.0f / PVRTVec3(left).length();
	left *= inv_len;

	right.x = (matrix.f[3]  - matrix.f[0]);
    right.y = (matrix.f[7]  - matrix.f[4]);
    right.z = (matrix.f[11] - matrix.f[8]);
	right.w = (matrix.f[15] - matrix.f[12]);
	inv_len = 1.0f / PVRTVec3(right).length();
	right *= inv_len;

	front.x = (matrix.f[3]  + matrix.f[2]);
    front.y = (matrix.f[7]  + matrix.f[6]);
    front.z = (matrix.f[11] + matrix.f[10]);
	front.w = (matrix.f[15] + matrix.f[14]);
	inv_len = 1.0f / PVRTVec3(front).length();
	front *= inv_len;

	back.x = (matrix.f[3]  - matrix.f[2]);
    back.y = (matrix.f[7]  - matrix.f[6]);
    back.z = (matrix.f[11] - matrix.f[10]);
	back.w = (matrix.f[15] - matrix.f[14]);
	inv_len = 1.0f / PVRTVec3(back).length();
	back *= inv_len;
}


/*!****************************************************************************
 @Function		GetViewFrustumPlanes
 @Description	TODO
******************************************************************************/
void OcclusionCalculator::GetViewFrustumPlanes(const PVRTMat4 &matrix, PVRTVec4 &left, PVRTVec4 &right, PVRTVec4 &front, PVRTVec4 &back, PVRTVec4 &bottom, PVRTVec4 &top) const
{
	left.x = (matrix.f[3]  + matrix.f[0]);
    left.y = (matrix.f[7]  + matrix.f[4]);
    left.z = (matrix.f[11] + matrix.f[8]);
	left.w = (matrix.f[15] + matrix.f[12]);
	float inv_len = 1.0f / PVRTVec3(left).length();
	left *= inv_len;

	right.x = (matrix.f[3]  - matrix.f[0]);
    right.y = (matrix.f[7]  - matrix.f[4]);
    right.z = (matrix.f[11] - matrix.f[8]);
	right.w = (matrix.f[15] - matrix.f[12]);
	inv_len = 1.0f / PVRTVec3(right).length();
	right *= inv_len;

	front.x = (matrix.f[3]  + matrix.f[2]);
    front.y = (matrix.f[7]  + matrix.f[6]);
    front.z = (matrix.f[11] + matrix.f[10]);
	front.w = (matrix.f[15] + matrix.f[14]);
	inv_len = 1.0f / PVRTVec3(front).length();
	front *= inv_len;

	back.x = (matrix.f[3]  - matrix.f[2]);
    back.y = (matrix.f[7]  - matrix.f[6]);
    back.z = (matrix.f[11] - matrix.f[10]);
	back.w = (matrix.f[15] - matrix.f[14]);
	inv_len = 1.0f / PVRTVec3(back).length();
	back *= inv_len;

	bottom.x = (matrix.f[3]  + matrix.f[1]);
    bottom.y = (matrix.f[7]  + matrix.f[5]);
    bottom.z = (matrix.f[11] + matrix.f[9]);
	bottom.w = (matrix.f[15] + matrix.f[13]);
	inv_len = 1.0f / PVRTVec3(bottom).length();
	bottom *= inv_len;

	top.x = (matrix.f[3]  - matrix.f[1]);
    top.y = (matrix.f[7]  - matrix.f[5]);
    top.z = (matrix.f[11] - matrix.f[9]);
	top.w = (matrix.f[15] - matrix.f[13]);
	inv_len = 1.0f / PVRTVec3(top).length();
	top *= inv_len;
}

/*!****************************************************************************
 @Function		BoundingBoxIntersectsFrustum
 @Description	TODO
******************************************************************************/
bool OcclusionCalculator::BoundingBoxIntersectsFrustum(const PVRTBoundingBox2D &bbox, const PVRTVec4 planes[], const unsigned int numPlanes)
{
	PVRTVec3 points[4];
	points[0] = PVRTVec3(bbox.minCoords.x, bbox.minCoords.y, 0.0f);
	points[1] = PVRTVec3(bbox.maxCoords.x, bbox.minCoords.y, 0.0f);
	points[2] = PVRTVec3(bbox.maxCoords.x, bbox.maxCoords.y, 0.0f);
	points[3] = PVRTVec3(bbox.minCoords.x, bbox.maxCoords.y, 0.0f);

	bool bBoxVisible = true;

	// Test the axis-aligned bounding box against each plane;
	// only cull if all points are outside of one the view frustum planes
	for (unsigned int p=0; p < numPlanes; p++)
	{
		unsigned int pointsOut = 0;

		// Test the points against the plane
		for(unsigned int j=0; j < 4; j++)
			if ((planes[p].x * points[j].x + planes[p].y * points[j].y + planes[p].z * points[j].z + planes[p].w) < 0.0f)
				pointsOut++;

		// if all points are outside of a plane we can cull it
		if (pointsOut == 4)
			return false;
	}

	return true;
}


/*!****************************************************************************
 @Function		LoadAndCompactModel
 @Input         config
 @Input         pszOutfile
 @Return		bool		true if no error occured
 @Description	TODO
******************************************************************************/
bool OcclusionCalculator::LoadAndCompactModel(unsigned int idx, PVRTCompactModel &compressed_model)
{	
	PVRTTileLod *pModelLod = &m_aModelIndex[idx].paLod[0];

	CPVRTModelPOD model;
	if (PVR_SUCCESS != model.ReadFromFile(pModelLod->pszFilename))
	{
		cerr << "Failed loading POD file: " << pModelLod->pszFilename << endl;
		return false;
	}

	compressed_model.numMeshes = model.nNumMesh;
	compressed_model.paObjectTypes = new unsigned int[model.nNumMesh];

	for (unsigned int j=0; j < model.nNumMesh; j++)
		compressed_model.paObjectTypes[j] = DetermineObjectType(model.pNode[j].pszName);
	
	// Generate a VBO and IBO for every single element for hardware occlusion queries
	if (m_bHWOcclusionQuery)
	{		
		compressed_model.paIndexVbo = new GLuint[model.nNumMesh];		
		compressed_model.paObjectVbo = new GLuint[model.nNumMesh];		
		compressed_model.paNumIndices = new unsigned int[model.nNumMesh];

		m_Extensions.glGenBuffersARB(model.nNumMesh, compressed_model.paIndexVbo);
		m_Extensions.glGenBuffersARB(model.nNumMesh, compressed_model.paObjectVbo);

		// Copy data into flat array	
		for (unsigned int j=0; j < model.nNumMesh; j++)
		{		
			const SPODMesh &mesh = model.pMesh[model.pNode[j].nIdx];
			const PVRTModelVertex *pData = (const PVRTModelVertex *)mesh.pInterleaved;
			const unsigned short *pIData = (unsigned short*)mesh.sFaces.pData;

			vector<PVRTVec3> plain_vertices;
			plain_vertices.reserve(mesh.nNumVertex);

			// Swizzle the coordinates (z == up)
			for (unsigned int k=0; k < mesh.nNumVertex; k++)
			{
				PVRTVec3 position = pData[k].position;				
				plain_vertices.push_back(PVRTVec3(position.x, -position.z, position.y));			
			}

			m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, compressed_model.paObjectVbo[j]);
			m_Extensions.glBufferDataARB(GL_ARRAY_BUFFER_ARB, mesh.nNumVertex * sizeof(PVRTVec3), &plain_vertices[0], GL_STATIC_DRAW_ARB);

			compressed_model.paNumIndices[j] = PVRTModelPODCountIndices(mesh);
			m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, compressed_model.paIndexVbo[j]);
			m_Extensions.glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, compressed_model.paNumIndices[j] * sizeof(unsigned short), pIData, GL_STATIC_DRAW_ARB);			
		}
	}

	vector<PVRTPositionColour> vertices;
	vector<unsigned short> indices;

	unsigned int numVertices = 0;
	unsigned int numIndices = 0;	
	for (unsigned int j=0; j < model.nNumMesh; j++)
	{
		const SPODMesh &mesh = model.pMesh[model.pNode[j].nIdx];		
		numVertices += mesh.nNumVertex;
		numIndices += PVRTModelPODCountIndices(mesh);
	}

	vertices.reserve(numVertices);
	indices.reserve(numIndices);
	compressed_model.numIndices = numIndices;
	unsigned short indexoffset = 0;

	// Copy data into flat array	
	for (unsigned int j=0; j < pModelLod->numObjects; j++)
	{
		PVRTVec3 objcolour = PVRTVec3((float)idx, (float)(j % 255), (float)(j / 255)) * (1.0f / 255.0f);	

		for (unsigned int n=0; n < pModelLod->paObjects[j].numSubObjects; n++)
		{
			unsigned int nodeidx = pModelLod->paObjects[j].pNodeIdx[n];

			const SPODMesh &mesh = model.pMesh[model.pNode[nodeidx].nIdx];
			const PVRTModelVertex *pData = (const PVRTModelVertex *)mesh.pInterleaved;

			// Swizzle the coordinates (z == up)
			for (unsigned int k=0; k < mesh.nNumVertex; k++)
			{
				PVRTModelVertex vertex = pData[k];
				PVRTPositionColour poscol;				
				poscol.position = PVRTVec3(vertex.position.x, -vertex.position.z, vertex.position.y);	
				poscol.colour = objcolour;	
				vertices.push_back(poscol);
			}

			const unsigned short *pIData = (unsigned short*)mesh.sFaces.pData;
			const unsigned int numMeshIndices = PVRTModelPODCountIndices(mesh);
			for (unsigned int k=0; k < numMeshIndices; k++)
				indices.push_back(pIData[k] + indexoffset);
			indexoffset += mesh.nNumVertex;
		}								
	}
	
	m_Extensions.glGenBuffersARB(1, &compressed_model.vbo);
	m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, compressed_model.vbo);
	m_Extensions.glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices.size() * sizeof(PVRTPositionColour), &vertices[0], GL_STATIC_DRAW_ARB);
	m_Extensions.glGenBuffersARB(1, &compressed_model.ibo);
	m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, compressed_model.ibo);
	m_Extensions.glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW_ARB);			

	m_Extensions.glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	m_Extensions.glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

	return true;
}

/*!****************************************************************************
 @Function		Load3dModelIndex
 @Description	Loads the mesh data required for this training course into
				vertex buffer objects
******************************************************************************/
bool OcclusionCalculator::Load3dModelIndex(const char *pszFilename)
{
	ifstream file(pszFilename, ios::binary);
	if (!file.is_open())
		return false;

	size_t numTiles;
	file.read((char *)&numTiles, sizeof(numTiles));
	
	m_aModelIndex.resize(numTiles);

	for (unsigned int i=0; i < numTiles; i++)
	{
		file.read((char *)&m_aModelIndex[i].boundingbox, sizeof(PVRTBoundingBox2D));
		file.read((char *)&m_aModelIndex[i].numLod, sizeof(size_t));

		m_aModelIndex[i].paLod = new PVRTTileLod[m_aModelIndex[i].numLod];

		for (unsigned int j=0; j < m_aModelIndex[i].numLod; j++)
		{			
			size_t namelength;
			file.read((char *)&namelength, sizeof(size_t));
			
			m_aModelIndex[i].paLod[j].pszFilename = new char[namelength+1];
			file.read(m_aModelIndex[i].paLod[j].pszFilename, (std::streamsize)(sizeof(char) * namelength));
			m_aModelIndex[i].paLod[j].pszFilename[namelength] = '\0';
			
			file.read((char *)&m_aModelIndex[i].paLod[j].numObjects, sizeof(size_t));
			m_aModelIndex[i].paLod[j].paObjects = new PVRTTileObjectSet[m_aModelIndex[i].paLod[j].numObjects];
						
			for (unsigned int k=0; k < m_aModelIndex[i].paLod[j].numObjects; k++)
			{			
				file.read((char *)&m_aModelIndex[i].paLod[j].paObjects[k].boundingbox, sizeof(PVRTBoundingBox2D));
				file.read((char *)&m_aModelIndex[i].paLod[j].paObjects[k].numSubObjects, sizeof(size_t));
				m_aModelIndex[i].paLod[j].paObjects[k].pNodeIdx = new unsigned int[m_aModelIndex[i].paLod[j].paObjects[k].numSubObjects];
				file.read((char *)m_aModelIndex[i].paLod[j].paObjects[k].pNodeIdx, (std::streamsize)(sizeof(unsigned int) * m_aModelIndex[i].paLod[j].paObjects[k].numSubObjects));

				m_Extensions.glGenQueriesARB(1, &m_aModelIndex[i].paLod[j].paObjects[k].occlusion_query);
			}
		}
	}

	return true;
}

/*!****************************************************************************
 @Function		Release3dModelIndex
 @Description	Releases the 3d model index data
******************************************************************************/
void OcclusionCalculator::Release3dModelIndex()
{
	for (unsigned int i=0; i < m_aModelIndex.size(); i++)
	{
		for (unsigned int j=0; j < m_aModelIndex[i].numLod; j++)
		{
			for (unsigned int k=0; k < m_aModelIndex[i].paLod[j].numObjects; k++)
				delete [] m_aModelIndex[i].paLod[j].paObjects[k].pNodeIdx;				
			delete [] m_aModelIndex[i].paLod[j].paObjects;
			delete [] m_aModelIndex[i].paLod[j].pszFilename;						
		}
		delete [] m_aModelIndex[i].paLod;		
	}
}


/*!****************************************************************************
 @Function		WriteCameraPathOcclusionData
 @Description	TODO
******************************************************************************/
bool OcclusionCalculator::WriteCameraPathOcclusionData(const char *pszFilename)
{
	m_CameraPathOcclusionData.filename = "camerapaths";
	m_CameraPathOcclusionData.tiles = m_aszFilenames;
		
	// File structure:
	//   #filenamelength filename
	//   #tiles 
	//   for_each(tile) { #tilenamelength tilename }
	//   #positions
	//   for_each(position) { #reftiles 
	//                        for_each(reftile) { #objects objectid } }
	//   
	
	string filename = "camerapath_occlusion.txt";	
	ofstream occfile(pszFilename, ios::binary);
	if (!occfile.is_open())
	{
		PVRShellOutputDebug("Error: Can't open %s\n", filename.c_str());
		return false;
	}
	 
	size_t namelen = m_CameraPathOcclusionData.filename.length();
	occfile.write((const char*)&namelen, sizeof(size_t));
	occfile.write((const char*)m_CameraPathOcclusionData.filename.c_str(), (std::streamsize)namelen);
	size_t numTiles = m_aszFilenames.size();
	occfile.write((const char*)&numTiles, sizeof(size_t));
	for (unsigned int i=0; i < numTiles; i++)
	{
		namelen = m_aszFilenames[i].length();
		occfile.write((const char*)&namelen, sizeof(size_t));
		occfile.write((const char*)m_aszFilenames[i].c_str(), (std::streamsize)namelen);
	}


	size_t numpositions = m_uiPathSubdivisions * m_Camera.nNumCamera;
	occfile.write((const char *)&numpositions, sizeof(size_t));

	for (unsigned int i=0; i < m_CameraPathOcclusionData.visdata.size(); i++)
	{
		PVRTVisibilityRecord &posvisdata = m_CameraPathOcclusionData.visdata[i];
		PVRTVec3 pos = posvisdata.position;
		occfile.write((const char*)pos.ptr(), sizeof(PVRTVec3));
		size_t reftiles = posvisdata.visible_tileobjects.size();
		occfile.write((const char*)&reftiles, sizeof(size_t));

		unsigned int refcounter = 0;

		map<unsigned int, set<unsigned int> >::iterator map_iter;
		for (map_iter = posvisdata.visible_tileobjects.begin(); map_iter != posvisdata.visible_tileobjects.end(); map_iter++)
		{					
			size_t tilenum = map_iter->first;
			occfile.write((const char*)&tilenum, sizeof(size_t));
					
			vector<unsigned int> tmp_vec;
			copy(map_iter->second.begin(), map_iter->second.end(), back_inserter(tmp_vec));
			size_t num_ref_models = tmp_vec.size();
			occfile.write((const char *)&num_ref_models, sizeof(size_t));
			occfile.write((const char *)&tmp_vec[0], (std::streamsize)(sizeof(unsigned int) * num_ref_models));
			refcounter += (unsigned int)num_ref_models;
		}								
	}

	occfile.close();
	return true;
}


/*!****************************************************************************
 @Function		NewDemo
 @Return		PVRShell*		The demo supplied by the user
 @Description	This function must be implemented by the user of the shell.
				The user should return its PVRShell object defining the
				behaviour of the application.
******************************************************************************/
PVRShell* NewDemo()
{
	return new OcclusionCalculator();
}

/******************************************************************************
 End of file (OcclusionCalculator.cpp)
******************************************************************************/


