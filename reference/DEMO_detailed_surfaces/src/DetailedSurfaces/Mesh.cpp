#include "Mesh.h"

HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh )
{
	ID3DXMesh* pMesh = NULL;
	WCHAR str[MAX_PATH];
	HRESULT hr;

	//====================================================================//
	// Load the mesh with D3DX and get back a ID3DXMesh*.  For this       //
	// sample we'll ignore the X file's embedded materials since we know  //
	// exactly the model we're loading.  See the mesh samples such as     //
	// "OptimizedMesh" for a more generic mesh loading example.           //
	//====================================================================//
	V_RETURN( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, strFileName ) );
	V_RETURN( D3DXLoadMeshFromX( str, D3DXMESH_MANAGED, pd3dDevice, NULL, NULL, NULL, NULL, &pMesh ) );

	// Create a new vertex declaration to hold all the required data
	const D3DVERTEXELEMENT9 vertexDecl[] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0 },
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		D3DDECL_END()
	};

	LPD3DXMESH pTempMesh = NULL;

	// Clone mesh to match the specified declaration: 
	if ( FAILED( pMesh->CloneMesh( pMesh->GetOptions(), vertexDecl, pd3dDevice, &pTempMesh ) ))
	{
		SAFE_RELEASE( pTempMesh );
		return E_FAIL;
	}

	//====================================================================//
	// Check if the old declaration contains normals, tangents, binormals //
	//====================================================================//
	bool bHadNormal   = false;
	bool bHadTangent  = false;
	bool bHadBinormal = false; 

	D3DVERTEXELEMENT9 vertexOldDecl[ MAX_FVF_DECL_SIZE ];

	if ( pMesh && SUCCEEDED( pMesh->GetDeclaration( vertexOldDecl ) ) )
	{
		// Go through the declaration and look for the right channels, hoping for a match:
		for( UINT iChannelIndex = 0; iChannelIndex < D3DXGetDeclLength( vertexOldDecl ); iChannelIndex++ )
		{
			if( vertexOldDecl[iChannelIndex].Usage == D3DDECLUSAGE_NORMAL )
			{
				bHadNormal = true;
			}

			if( vertexOldDecl[iChannelIndex].Usage == D3DDECLUSAGE_TANGENT )
			{
				bHadTangent = true;
			}

			if( vertexOldDecl[iChannelIndex].Usage == D3DDECLUSAGE_BINORMAL )
			{
				bHadBinormal = true;
			}
		}  
	} 

	if ( pTempMesh == NULL && ( bHadNormal == false || bHadTangent == false || bHadBinormal == false ))
	{
		// We failed to clone the mesh and we need the tangent space for our effect:
		return E_FAIL;
	}

	//==============================================================//
	// Generate normals / tangents / binormals if they were missing //
	//==============================================================//
	SAFE_RELEASE( pMesh );
	pMesh = pTempMesh;

	if( ! bHadNormal )
	{
		// Compute normals in case the meshes have them
		D3DXComputeNormals( pMesh, NULL );
	}  

	DWORD *rgdwAdjacency = NULL;
	rgdwAdjacency = new DWORD[ pMesh->GetNumFaces() * 3 ];

	if( rgdwAdjacency == NULL )
	{
		return E_OUTOFMEMORY;
	}
	V( pMesh->GenerateAdjacency( 1e-6f, rgdwAdjacency ) );

	// Optimize the mesh for this graphics card's vertex cache 
	// so when rendering the mesh's triangle list the vertices will 
	// cache hit more often so it won't have to re-execute the vertex shader 
	// on those vertices so it will improve perf.     
	V( pMesh->OptimizeInplace( D3DXMESHOPT_VERTEXCACHE, rgdwAdjacency, NULL, NULL, NULL) );

	if ( ! bHadTangent || ! bHadBinormal )
	{
		ID3DXMesh* pNewMesh;

		// Compute tangents, which are required for normal mapping
		if ( FAILED( D3DXComputeTangentFrameEx( pMesh, D3DDECLUSAGE_TEXCOORD, 0, D3DDECLUSAGE_TANGENT, 0, D3DDECLUSAGE_BINORMAL, 0, 
			D3DDECLUSAGE_NORMAL, 0, 0, rgdwAdjacency, -1.01f,
			-0.01f, -1.01f, &pNewMesh, NULL ) ) )
		{
			return E_FAIL;
		}

		SAFE_RELEASE( pMesh );
		pMesh = pNewMesh;
	}  

	SAFE_DELETE_ARRAY( rgdwAdjacency );

	*ppMesh = pMesh;

	return S_OK;

}