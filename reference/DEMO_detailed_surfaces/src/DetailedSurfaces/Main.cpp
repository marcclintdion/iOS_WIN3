//--------------------------------------------------------------------------------------
// Detailed Surface Rendering Demo
// Autor: Bruno Evangelista (www.brunoevangelista.com)
//
// The technique currently implemented are:
//		- Mip-Mapping
//		- Texture Mapping
// 		- Normal Mapping
//		- Parallax Offset Mapping
//		- Relief Mapping
//		- Parallax Occlusion Mapping
//		- Cone Step Mapping
//		- Multi-Layer Cone Step Mapping
//		- Sphere Mapping
//
//--------------------------------------------------------------------------------------

#include "Common/dxstdafx.h"

#include "Mesh.h"
#include "Shader.h"

// Disable deprecated warning
#pragma warning( disable : 4995 4996)

#define SAFE_FILE_CLOSE(a) if(a) { fclose(a); a = NULL; }

TCHAR fileStr[MAX_PATH];

// User Interface
CDXUTDialogResourceManager dialogResourceManager;
CDXUTDialog hud;
boolean showUI = true;

enum UI_COMPONENTS
{
	BUTTON_FULLSCREEN,
	BUTTON_RELOAD_MEDIA,
	TECHNIQUE_COMBO_BOX,
	TEXTURE_COMBO_BOX,
	DEPTH_SLIDER,
	DEPTH_SCALE_STATIC,

	TILE_SLIDER,
	TILE_SCALE_STATIC,

	DEPTHBIAS_CHECK_BOX,
	BORDERCLAMP_CHECK_BOX,
		
	INC_ITERATIONS_BUTTON,
	DEC_ITERATIONS_BUTTON,
	ITERATIONS_STATIC
};

enum TECHNIQUE_IDS
{
	MIPMAP,
	TEXTURE,

	DISPLACEMENT,

	BUMP,
	PARALLAX,
	RELIEF,
	POM,
	CONE,
	CONE3D_EMULATED,
	CONE3D_FIXED,
	CONE3D_VARIABLE,
	SPHERE
};

WCHAR* TECHNIQUE_NAMES[] = {
	{L"MIP-MAPPING"}, L"TEXTURE MAPPING", L"DISPLACEMENT MAPPING",
	L"NORMAL MAPPING", L"OFFSET PARALLAX MAPPING", L"RELIEF MAPPING",
	L"PARALLAX OCCLUSION MAPPING", L"CONE STEP MAPPING",
	L"MULTI-LAYER CSM - EMULATED", L"MULTI-LAYER CSM - FIXED",
	L"MULTI-LAYER CSM - VARIABLE", L"SPHERE TRACING"
};

// Textures
int NUM_TEXTURES = 7;
enum TEXTURE_IDS
{
	FOUR_OBJECTS,
	ROCK_WALL,
	ROCK_BUMP,
	SAINTS,
	SCULPTURE,
	SIMPLE_WALL,
	TEXT
};
int selectTexture = ROCK_BUMP;

TCHAR* colorFileName[] = {L"wood.jpg", L"rockwall.jpg", L"rockbump.jpg",
	L"saints.jpg", L"sculpture.jpg", L"stone.jpg", L"rockbump.jpg"};

TCHAR* dispFileName[] = {L"four_objects_disp.dds", L"rockwall_disp.dds",
L"rockbump_disp.dds", L"saints_disp.dds", L"sculpture_disp.dds", L"stone_disp.dds",
L"text_disp.dds"};

TCHAR* coneFileName[] = {L"four_objects.tga", L"rockwall.tga", L"rockbump.tga",
	L"saints.tga", L"sculpture.tga", L"stone.tga", L"text.tga"};

TCHAR* cone3DFixedFileName[] = {L"four_objects3D.dds", L"rockwall3D.dds",
	L"rockbump3D.dds", L"saints3D.dds", L"sculpture3D.dds", L"stone3D.dds",
	L"text3D.dds"};

/*
TCHAR* cone3DVariableFileName[] = {L"four_objects3Dv.dds", L"rockwall3Dv.dds",
	L"rockbump3Dv.dds", L"saints3Dv.dds", L"sculpture3Dv.dds", L"stone3Dv.dds",
	L"text3Dv.dds"};
*/

TCHAR* sphereFileName[] = {L"four_objectsSphere.dds", L"rockwallSphere.dds",
	L"rockbumpSphere.dds", L"saintsSphere.dds", L"sculptureSphere.dds", 
	L"stoneSphere.dds", L"textSphere.dds"};

LPDIRECT3DTEXTURE9* colorTexture = NULL;
LPDIRECT3DTEXTURE9* dispTexture = NULL;
LPDIRECT3DTEXTURE9* coneTexture = NULL;
LPDIRECT3DVOLUMETEXTURE9* cone3DFixedTexture = NULL;
LPDIRECT3DVOLUMETEXTURE9* cone3DVariableTexture = NULL;
LPDIRECT3DVOLUMETEXTURE9* sphereTexture = NULL;

// Effect
TCHAR* shaderFileName = L"BumpTechniques.fx";
LPD3DXEFFECT effect = NULL;
//int currentTechniqueID = CONE3D_FIXED;
int currentTechniqueID = 7;
float bumpDepth = 0.1f;
int numIterations = 16;

float textureTileFactor = 1.0f;
bool depthBias = false;
bool borderClamp = false;

bool updateShaderParametersMatrix = true;
bool updateShaderParameters = true;

// Mesh
LPD3DXMESH mesh = NULL;
float meshRadius = 0.0f;
D3DXVECTOR3 meshCenter;

// Camera and Light
CModelViewerCamera camera;
LPD3DXMESH lightMesh = NULL;
float lightPos[] = {0.0f, 80.0f, -80.0f};

// Transformations
D3DXMATRIX matWorld;

// Used to render the device stats
ID3DXFont* font = NULL;
ID3DXFont* font2 = NULL;
ID3DXSprite* sprite = NULL;

// Screenshot
int numScreenshot = 0;
LPDIRECT3DTEXTURE9 renderTarget = NULL;
int screenWidth = 0;
int screenHeight = 0;
bool showTechniqueName = true;

// Direct3D device
LPDIRECT3DDEVICE9 m_pd3dDevice = NULL;

// Functions headers
void CALLBACK GUIEventProc( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );

void CreateUIComponents()
{
	WCHAR uiText[256];
	int startX = 2;
	int startY = 40;

	// Buttons
	CDXUTButton *pFullScreenButton = NULL;
	hud.AddButton(BUTTON_FULLSCREEN, L"Full Screen", startX, startY, 100, 20, 0,
		false, &pFullScreenButton);

	CDXUTButton *pReloadShaderButton = NULL;
	hud.AddButton(BUTTON_RELOAD_MEDIA, L"Reload Media", startX + 100, startY,
		100, 20, 0, false, &pReloadShaderButton);
	startY += 25;

	// Technique selection combo box
	CDXUTComboBox *pTechniqueComboBox = NULL;
	hud.AddComboBox( TECHNIQUE_COMBO_BOX, startX, startY, 200, 24, L'C', false, &pTechniqueComboBox );
	if ( pTechniqueComboBox )
	{
		pTechniqueComboBox->SetDropHeight( 120 );
		pTechniqueComboBox->AddItem( L"Mip-Mapping", (LPVOID)MIPMAP);
		pTechniqueComboBox->AddItem( L"Texture Mapping", (LPVOID)TEXTURE);
		
		pTechniqueComboBox->AddItem( L"Displacement Mapping", (LPVOID)DISPLACEMENT);
		
		pTechniqueComboBox->AddItem( L"Normal Mapping", (LPVOID)BUMP);
		pTechniqueComboBox->AddItem( L"Offset Parallax Mapping", (LPVOID)PARALLAX);
		pTechniqueComboBox->AddItem( L"Relief Mapping", (LPVOID)RELIEF);
		pTechniqueComboBox->AddItem( L"Parallax Occlusion Mapping", (LPVOID)POM);
		pTechniqueComboBox->AddItem( L"Cone Step Mapping", (LPVOID)CONE);
		//pTechniqueComboBox->AddItem( L"Multi-Layer CSM Emulated", (LPVOID)CONE3D_EMULATED);
		pTechniqueComboBox->AddItem( L"Multi-Layer CSM Fixed", (LPVOID)CONE3D_FIXED);
		//pTechniqueComboBox->AddItem( L"Multi-Layer CSM Variable", (LPVOID)CONE3D_VARIABLE);
		pTechniqueComboBox->AddItem( L"Sphere Tracing", (LPVOID)SPHERE);
	}
	pTechniqueComboBox->SetSelectedByIndex(currentTechniqueID);
	startY += 26;

	// Technique selection combo box
	CDXUTComboBox *pTextureComboBox = NULL;
	hud.AddComboBox( TEXTURE_COMBO_BOX, startX, startY, 200, 24, L'T', false, &pTextureComboBox );
	if ( pTextureComboBox )
	{
		pTextureComboBox->SetDropHeight( 100 );
		pTextureComboBox->AddItem( L"Four Objects", (LPVOID)FOUR_OBJECTS);
		pTextureComboBox->AddItem( L"Rockwall", (LPVOID)ROCK_WALL);
		pTextureComboBox->AddItem( L"Rockbump", (LPVOID)ROCK_BUMP);
		pTextureComboBox->AddItem( L"Saints", (LPVOID)SAINTS);
		pTextureComboBox->AddItem( L"Sculpture", (LPVOID)SCULPTURE);
		pTextureComboBox->AddItem( L"Stone", (LPVOID)SIMPLE_WALL);
		pTextureComboBox->AddItem( L"Text", (LPVOID)TEXT);
	}
	pTextureComboBox->SetSelectedByIndex(selectTexture);
	startY += 30;

	// Depth Slider
	hud.AddSlider(DEPTH_SLIDER, startX, startY, 200, 20, 1, 20, 
		(int)(bumpDepth * 100));
	startY += 20;

	// Depth text
	StringCchPrintf(uiText, 256, L"Height scale: %0.2f", bumpDepth); 
	hud.AddStatic( DEPTH_SCALE_STATIC, uiText, startX, startY, 100, 20);
	startY += 30;

	// Tile slider
	hud.AddSlider(TILE_SLIDER, startX, startY, 200, 20, 1, 50, (int)(textureTileFactor * 10));
	startY += 20;

	// Tile text
	StringCchPrintf(uiText, 256, L"Tile scale: %0.2f", textureTileFactor); 
	hud.AddStatic( TILE_SCALE_STATIC, uiText, startX, startY, 100, 20);
	startY += 30;

	hud.AddCheckBox(DEPTHBIAS_CHECK_BOX, L"Depth Bias", startX, startY, 100, 20, false);
	hud.AddCheckBox(BORDERCLAMP_CHECK_BOX, L"Border Clamp", startX+100, startY, 100, 20, false);
	startY += 30;

	// Iteration Buttons
	hud.AddButton(DEC_ITERATIONS_BUTTON, L"-", startX, startY, 30, 20, 0);
	hud.AddButton(INC_ITERATIONS_BUTTON, L"+", startX + 35, startY,
		30, 20, 0);

	// Iteration text
	StringCchPrintf(uiText, 256, L"Iterations: %d", numIterations); 
	hud.AddStatic( ITERATIONS_STATIC, uiText, startX + 70, startY, 80, 20);
	startY += 30;

	// Controls text
	hud.AddStatic( -1, L"F1 - Show/Hide UI", startX, startY, 100, 20);
	startY += 20;
	hud.AddStatic( -1, L"F10 - Screenshot", startX, startY, 100, 20);
	startY += 30;
	hud.AddStatic( -1, L"Mouse Buttons:", startX, startY, 90, 20);
	startY += 15;
	hud.AddStatic( -1, L"Left - Rotate", startX, startY, 90, 20);
	startY += 15;
	hud.AddStatic( -1, L"Middle - Rotate w/ Light", startX, startY, 145, 20);
	startY += 15;
	hud.AddStatic( -1, L"Middle - Zoom", startX, startY, 95, 20);
}

void GenerateAndLoadShader()
{
	HRESULT hr;

	// Shader code
	char* shaderCode = NULL;
	int shaderCodeSize = 30 * 1024;
	shaderCode = new char[shaderCodeSize];
	int shaderCodePos = 0;

	// Generate iterations defines
	char defineStr[64];
	int strLenght;

	// Global num iterations
	sprintf(defineStr, "#define NUM_ITERATIONS %d\n", numIterations);
	strLenght = (int)strlen(defineStr);
	memcpy(&shaderCode[shaderCodePos], defineStr, strLenght);
	shaderCodePos += strLenght;

	// Relief num iterations
	sprintf(defineStr, "#define NUM_ITERATIONS_RELIEF1 %d\n", 
		(int)(numIterations * 0.67f + 0.999f));
	strLenght = (int)strlen(defineStr);
	memcpy(&shaderCode[shaderCodePos], defineStr, strLenght);
	shaderCodePos += strLenght;
	sprintf(defineStr, "#define NUM_ITERATIONS_RELIEF2 %d\n\n", 
		(int)(numIterations * 0.33f));
	strLenght = (int)strlen(defineStr);
	memcpy(&shaderCode[shaderCodePos], defineStr, strLenght);
	shaderCodePos += strLenght;

	// Open original shader file
	V(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, shaderFileName) );
	char fileStrChar[512];
	wcstombs(fileStrChar, fileStr, wcslen(fileStr) + 1);
	FILE *file = NULL;
	file = fopen(fileStrChar, "rt");

	// Copy the shader code to the code buffer
	int maxShaderCode = shaderCodeSize - shaderCodePos;
	int numReaded = (int)fread(&shaderCode[shaderCodePos], sizeof(char),
		maxShaderCode, file);
	SAFE_FILE_CLOSE(file);

	shaderCodePos += numReaded;
	shaderCode[shaderCodePos++] = '\0';

	// Save data in a temp file
	char* newShaderFileNameChar = "temp_shader.fx";
	TCHAR* newShaderFileNameTCHAR = L"temp_shader.fx";

	file = fopen("temp_shader.fx", "wt");
	fwrite(shaderCode, sizeof(char), shaderCodePos + 1, file);
	SAFE_FILE_CLOSE(file);

	delete [] shaderCode;
	shaderCode = NULL;

	V(LoadShader( m_pd3dDevice, &effect, newShaderFileNameTCHAR ));
}

HRESULT LoadTextures(LPDIRECT3DDEVICE9 pd3dDevice)
{
	HRESULT hr;

	colorTexture = new LPDIRECT3DTEXTURE9[NUM_TEXTURES];
	dispTexture = new LPDIRECT3DTEXTURE9[NUM_TEXTURES];
	coneTexture = new LPDIRECT3DTEXTURE9[NUM_TEXTURES];
	cone3DFixedTexture = new LPDIRECT3DVOLUMETEXTURE9[NUM_TEXTURES];
	cone3DVariableTexture = new LPDIRECT3DVOLUMETEXTURE9[NUM_TEXTURES];
	sphereTexture = new LPDIRECT3DVOLUMETEXTURE9[NUM_TEXTURES];
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		// Load color texture
		V_RETURN(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, colorFileName[i]) );
		V_RETURN(D3DXCreateTextureFromFileEx( pd3dDevice, fileStr, D3DX_DEFAULT,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &colorTexture[i])); 

		// Displacement textures
		V_RETURN(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, dispFileName[i]) );
		V_RETURN(D3DXCreateTextureFromFileEx( pd3dDevice, fileStr, D3DX_DEFAULT,
			//D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_R32F,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL,
			&dispTexture[i])); 

		// Load cone texture
		V_RETURN(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, coneFileName[i]) );
		V_RETURN(D3DXCreateTextureFromFileEx( pd3dDevice, fileStr, D3DX_DEFAULT,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &coneTexture[i])); 

		// Load cone 3D fixed texture
		V_RETURN(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, cone3DFixedFileName[i]) );
		V_RETURN(D3DXCreateVolumeTextureFromFileEx(pd3dDevice, fileStr, D3DX_DEFAULT,
			//D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_L8, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &cone3DFixedTexture[i])); 

		/*
		// Load cone 3D variable texture
		V_RETURN(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, cone3DVariableFileName[i]) );
		V_RETURN(D3DXCreateVolumeTextureFromFileEx(pd3dDevice, fileStr, D3DX_DEFAULT,
			D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
			D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &cone3DVariableTexture[i])); 
		*/

		// Load sphere 3D texture
		V_RETURN(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, sphereFileName[i]) );
		V_RETURN(D3DXCreateVolumeTextureFromFileEx(pd3dDevice, fileStr, D3DX_DEFAULT,
			//D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_L8, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
			D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &sphereTexture[i])); 
	}

	return hr;
}

void SetEffectTextures()
{
	// Set textures
	effect->SetTexture("color_map_tex", colorTexture[selectTexture]);
	
	effect->SetTexture("displacement_map_tex", dispTexture[selectTexture]);
	
	effect->SetTexture("cone_map_tex", coneTexture[selectTexture]);
	effect->SetTexture("cone_map3D_tex", cone3DFixedTexture[selectTexture]);
	//effect->SetTexture("cone_map3Dv_tex", cone3DVariableTexture[selectTexture]);
	effect->SetTexture("sphere_map_tex", sphereTexture[selectTexture]);
}

void ConfigureCameraView()
{
	// Set camera
	D3DXMATRIX rotation;
	D3DXMatrixTranslation( &matWorld, -meshCenter.x, -meshCenter.y, -meshCenter.z );
	D3DXMatrixRotationY( &rotation, -D3DX_PI / 2.0f );
	matWorld *= rotation;
	D3DXMatrixRotationX( &rotation, -D3DX_PI / 1.34f);
	matWorld *= rotation;

	//D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 1.5f * meshRadius, -1.5f * meshRadius);
	D3DXVECTOR3 eye = D3DXVECTOR3(0.0f, 1.1f * meshRadius, -1.1f * meshRadius);
	D3DXVECTOR3 lookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	camera.SetViewParams(&eye, &lookAt);

	camera.SetButtonMasks( MOUSE_LEFT_BUTTON, MOUSE_WHEEL, MOUSE_MIDDLE_BUTTON );
}

/**
 * Called when the device is created
 * Create all resources that don't need to be re-created after a reset call
 */
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9*       pd3dDevice,
								const D3DSURFACE_DESC*  pBackBufferSurfaceDesc, 
								void*                   pUserContext )
{
	HRESULT hr;
	
	m_pd3dDevice = pd3dDevice;

	// UI
	V_RETURN(dialogResourceManager.OnCreateDevice(pd3dDevice));
	hud.Init(&dialogResourceManager);
	hud.SetCallback( GUIEventProc );
	CreateUIComponents();

	// Create font
	V_RETURN(D3DXCreateFont(pd3dDevice, 15, 0, FW_DEMIBOLD, 1, FALSE, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
		L"Arial", &font));

	// Create font2
	V_RETURN(D3DXCreateFont(pd3dDevice, 26, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, 
		L"Arial", &font2));

	// Load textures
	V_RETURN(LoadTextures(pd3dDevice));

	// Load shader
	GenerateAndLoadShader();
	SetEffectTextures();
	//V_RETURN(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, shaderFileName) );
	//V_RETURN(LoadShader( pd3dDevice, &effect, fileStr ));
	
	// Load object mesh
	V_RETURN(LoadMesh(pd3dDevice, L"Disc.x", &mesh));

	// Compute mesh bounding sphere (Used to correctly set camera)
	D3DXVECTOR3* pData; 
	V_RETURN( mesh->LockVertexBuffer( 0, (LPVOID*) &pData ) );
	V_RETURN(D3DXComputeBoundingSphere( pData, mesh->GetNumVertices(),
		s_iDECL_SIZE, &meshCenter, &meshRadius ));
	V_RETURN(mesh->UnlockVertexBuffer() );
	pData = NULL;

	//
	ConfigureCameraView();

	// Camera mesh
	D3DXCreateSphere(pd3dDevice, meshRadius * 0.1f, 18, 18, &lightMesh, NULL);

	return S_OK;
}

/**
 * Called when the device is restarted (resized, minimized, chaged, ...)
 * Create all resources that need to be re-created after a reset call
 */
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9*        pd3dDevice, 
							   const D3DSURFACE_DESC*   pBackBufferSurfaceDesc, 
							   void*                    pUserContext )
{
	HRESULT hr;

	// UI
	V_RETURN(dialogResourceManager.OnResetDevice());
	hud.SetLocation( 0, 0 );
	hud.SetSize( 640, 480 );

	// Create render target
	V_RETURN(D3DXCreateTexture(pd3dDevice, pBackBufferSurfaceDesc->Width,
		pBackBufferSurfaceDesc->Height, 1, D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &renderTarget));

	// Get screen size
	screenWidth = pBackBufferSurfaceDesc->Width;
	screenHeight = pBackBufferSurfaceDesc->Height;

	// Configure camera projection and viewport
	camera.SetProjParams(D3DX_PI * 0.4f,
		(float)pBackBufferSurfaceDesc->Width/pBackBufferSurfaceDesc->Height,
		1.0f, 1000.0f);
	camera.SetWindow( pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

	// Reset resources
	if (effect)
		V_RETURN(effect->OnResetDevice());
	if (font)
		V_RETURN(font->OnResetDevice());
	if (font2)
		V_RETURN(font2->OnResetDevice());

	return S_OK;
}

/**
 * Called when the window is Lost (resized, minimized, chaged, ...)
 * Release all resources created in the ResetDevice call
 */
void CALLBACK OnLostDevice( void* pUserContext )
{
	// UI
	dialogResourceManager.OnLostDevice();

	if (effect)
		effect->OnLostDevice();
	if (font)
		font->OnLostDevice();
	if (font2)
		font2->OnLostDevice();

	SAFE_RELEASE(sprite);
	SAFE_RELEASE(renderTarget);
}

void ReleaseMedia()
{
	SAFE_RELEASE(effect);
	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		SAFE_RELEASE(colorTexture[i]);
		SAFE_RELEASE(dispTexture[i]);
		SAFE_RELEASE(coneTexture[i]);
		SAFE_RELEASE(cone3DFixedTexture[i]);
		//SAFE_RELEASE(cone3DVariableTexture[i]);
		SAFE_RELEASE(sphereTexture[i]);
	}
	SAFE_DELETE_ARRAY(colorTexture);
	SAFE_DELETE_ARRAY(dispTexture);
	SAFE_DELETE_ARRAY(coneTexture);
	SAFE_DELETE_ARRAY(cone3DFixedTexture);
	//SAFE_DELETE_ARRAY(cone3DVariableTexture);
	SAFE_DELETE_ARRAY(sphereTexture);
}

/**
 * Called when the device is destroyed (Close application)
 * Release all resources created in the CreateDevice call
 */
void CALLBACK OnDestroyDevice( void* pUserContext )
{
	dialogResourceManager.OnDestroyDevice();

	SAFE_RELEASE(lightMesh);
	SAFE_RELEASE(mesh);
	SAFE_RELEASE(font);
	SAFE_RELEASE(font2);
	
	ReleaseMedia();
}

/**
 * Called to render the device stats and fps
 */
void RenderDeviceStats()
{
	CDXUTTextHelper textHelper( font, sprite, 15 );

	// Output statistics
	textHelper.Begin();
	textHelper.SetInsertionPos( 2, 2 );
	textHelper.SetForegroundColor( D3DXCOLOR( 0.0f, 0.0f, 0.8f, 1.0f ) );
	textHelper.DrawTextLine( DXUTGetFrameStats( true ) );
	textHelper.DrawTextLine( DXUTGetDeviceStats() );
	textHelper.End();

	if (showTechniqueName)
	{
		CDXUTTextHelper textHelper2( font2, sprite, 26 );

		// Output technique
		//int rightAlign = (int)wcslen(TECHNIQUE_NAMES[currentTechniqueID]);
		//textHelper2.SetInsertionPos( screenWidth - rightAlign * 15, 2 );

		textHelper2.Begin();
		textHelper2.SetInsertionPos( 2, screenHeight - 26 * 2 );
		textHelper2.SetForegroundColor( D3DXCOLOR( 0.7f, 0.7f, 0.0f, 1.0f ) );
		textHelper2.DrawTextLine( TECHNIQUE_NAMES[currentTechniqueID] );

		WCHAR temp[256];
		if (currentTechniqueID == POM)
			swprintf(temp, L"%d - %d iterations", (int)(numIterations*0.5), numIterations*2);
		else if (currentTechniqueID == RELIEF)
			swprintf(temp, L"%d Linear and %d Binary iterations", 
			(int)(numIterations * 0.67f + 0.999f), 
			(int)(numIterations*0.333f));
		else if (currentTechniqueID > RELIEF)
			swprintf(temp, L"%d iterations", numIterations);
		else
			swprintf(temp, L"");

		textHelper2.DrawTextLine( temp );
		textHelper2.End();
	}
}

/**
 * Called to render each frame
 *
 */
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, 
							double            fTime, 
							float             fElapsedTime, 
							void*             pUserContext )
{
	HRESULT hr;
	V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f), 1.0f, 0 ) );

	// Render the scene
	if ( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{
		if (updateShaderParametersMatrix)
		{
			// Set transformation
			D3DXMATRIX matW, matWV, matWVP;
			matW = matWorld * *camera.GetWorldMatrix();
			D3DXMatrixMultiply(&matWV, &matW, camera.GetViewMatrix());
			D3DXMatrixMultiply(&matWVP, &matWV, camera.GetProjMatrix());

			D3DXMATRIX matVI;
			//D3DXMatrixTranspose(&matVI, camera.GetViewMatrix());
			D3DXMatrixInverse(&matVI, NULL, camera.GetViewMatrix());

			effect->SetMatrix("matWVP", &matWVP);
			effect->SetMatrix("matW", &matW);
			effect->SetMatrix("matVI", &matVI);

			updateShaderParametersMatrix = false;
		}

		if (updateShaderParameters)
		{
			// Set parameters
			effect->SetFloat("depth", bumpDepth);
			effect->SetFloat("tile", textureTileFactor);
			effect->SetBool("DEPTH_BIAS", depthBias);
			effect->SetBool("BORDER_CLAMP", borderClamp);
			effect->SetFloatArray("lightPos", lightPos, 3);

			// Set dimensions for the Bump/Parallax/Relief/POM/Cone texture
			D3DSURFACE_DESC desc;
			coneTexture[selectTexture]->GetLevelDesc(0, &desc);
			effect->SetInt("TEXTURE_WIDTH", desc.Width);
			effect->SetInt("TEXTURE_HEIGHT", desc.Height);
			effect->SetInt("TEXTURE_DEPTH", 1);

			// Set technique
			if (currentTechniqueID == TEXTURE)
				effect->SetTechnique("texture_mapping");
			if (currentTechniqueID == MIPMAP)
				effect->SetTechnique("mip_mapping");
			if (currentTechniqueID == DISPLACEMENT)
				effect->SetTechnique("displacement_mapping");
			if (currentTechniqueID == BUMP)
				effect->SetTechnique("normal_mapping");
			else if (currentTechniqueID == PARALLAX)
				effect->SetTechnique("parallax_mapping");
			else if (currentTechniqueID == RELIEF)
				effect->SetTechnique("relief_mapping");
			else if (currentTechniqueID == POM)
				effect->SetTechnique("parallax_occlusion_mapping");
			else if (currentTechniqueID == CONE)
				effect->SetTechnique("cone_mapping");
			else if (currentTechniqueID == CONE3D_EMULATED)
				effect->SetTechnique("cone3D_emulated");
			else if (currentTechniqueID == CONE3D_FIXED)
			{
				effect->SetTechnique("cone3D_fixed");

				// Set dimensions for the Bump/Parallax/Relief/Cone texture
				D3DVOLUME_DESC desc;
				cone3DFixedTexture[selectTexture]->GetLevelDesc(0, &desc);
				effect->SetInt("TEXTURE_WIDTH", desc.Width);
				effect->SetInt("TEXTURE_HEIGHT", desc.Height);
				effect->SetInt("TEXTURE_DEPTH", desc.Depth);
			}
			/*
			else if (currentTechniqueID == CONE3D_VARIABLE)
			{
				effect->SetTechnique("cone3D_variable");

				// Set dimensions for the Bump/Parallax/Relief/Cone texture
				D3DVOLUME_DESC desc;
				cone3DVariableTexture[selectTexture]->GetLevelDesc(0, &desc);
				effect->SetInt("TEXTURE_WIDTH", desc.Width);
				effect->SetInt("TEXTURE_HEIGHT", desc.Height);
				effect->SetInt("TEXTURE_DEPTH", desc.Depth);
			}
			*/
			else if (currentTechniqueID == SPHERE)
			{
				effect->SetTechnique("sphere_mapping");

				// Set dimensions for the Bump/Parallax/Relief/Cone texture
				D3DVOLUME_DESC desc;
				sphereTexture[selectTexture]->GetLevelDesc(0, &desc);
				effect->SetInt("TEXTURE_WIDTH", desc.Width);
				effect->SetInt("TEXTURE_HEIGHT", desc.Height);
				effect->SetInt("TEXTURE_DEPTH", desc.Depth);
			}

			updateShaderParameters = false;
		}

		UINT numPasses;
		V( effect->Begin(&numPasses, 0) );
		V( effect->BeginPass(0) );

		// Render
		mesh->DrawSubset(0);

		V( effect->EndPass() );
		V( effect->End() );

		// Draw light sphere
		/*
		D3DXMATRIX matCameraW;
		D3DXMatrixTranslation(&matCameraW, lightPos[0], lightPos[1], lightPos[2]);
		pd3dDevice->SetTransform(D3DTS_WORLD, &(matWorld * matCameraW));
		pd3dDevice->SetTransform(D3DTS_VIEW, camera.GetViewMatrix());
		pd3dDevice->SetTransform(D3DTS_PROJECTION, camera.GetProjMatrix());
		lightMesh->DrawSubset(0);
		*/

		if (showUI)
		{
			// Render UI
			hud.OnRender( fElapsedTime ); 

			// Render device stats
			RenderDeviceStats();
		}

		V( pd3dDevice->EndScene() );
	}
}

/**
 * Called to update each frame
 *
 */
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, 
						  double            fTime, 
						  float             fElapsedTime, 
						  void*             pUserContext )
{
	camera.FrameMove( fElapsedTime );
}

/**
 * Check if the device is acceptable
 *
 */
bool CALLBACK IsDeviceAcceptable( D3DCAPS9*  pCaps, 
								 D3DFORMAT  AdapterFormat, 
								 D3DFORMAT  BackBufferFormat, 
								 bool       bWindowed, 
								 void*      pUserContext )
{
	if(pCaps->PixelShaderVersion < D3DPS_VERSION(3, 0))
		return false;
	//if (pCaps->)

	return true;
}

/**
 * Called before create device
 * Allow application to change the device settings
 */
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, 
								   const D3DCAPS9*     pCaps, 
								   void*               pUserContext )
{
	pDeviceSettings->BehaviorFlags &= ~D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	pDeviceSettings->BehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;

	#ifdef DEBUG_VS
	if ( pDeviceSettings->DeviceType != D3DDEVTYPE_REF )
	{
		pDeviceSettings->BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
		pDeviceSettings->BehaviorFlags &= ~D3DCREATE_PUREDEVICE;                            
		pDeviceSettings->BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	#endif

	#ifdef DEBUG_PS
		pDeviceSettings->DeviceType = D3DDEVTYPE_REF;
	#endif

	// Turn off VSynch
	pDeviceSettings->pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	return true;
}

/**
 * Called to process window messages
 *
 */
LRESULT CALLBACK MsgProc( HWND   hWnd, 
						 UINT   uMsg, 
						 WPARAM wParam, 
						 LPARAM lParam, 
						 bool*  pbNoFurtherProcessing, 
						 void*  pUserContext )
{
	// Give the dialogs a chance to handle the message first
	*pbNoFurtherProcessing = hud.MsgProc( hWnd, uMsg, wParam, lParam );
	if ( *pbNoFurtherProcessing )
		return 0;

	camera.HandleMessages( hWnd, uMsg, wParam, lParam );
	updateShaderParametersMatrix = true;

	return 0;
}  

HRESULT saveScreenshot()
{
	HRESULT hr;

	// Render to texture
	// ----------------------------------------------------------------
	LPDIRECT3DSURFACE9 pRenderSurface, pDefaultSurface;
	V(m_pd3dDevice->GetRenderTarget(0, &pDefaultSurface));

	// Render targets
	V(renderTarget->GetSurfaceLevel(0, &pRenderSurface));
	V(m_pd3dDevice->SetRenderTarget(0, pRenderSurface));

	showUI = false;
	OnFrameRender(m_pd3dDevice, 0.0, 0.0, NULL);
	showUI = true;

	V(m_pd3dDevice->SetRenderTarget(0, pDefaultSurface));
	SAFE_RELEASE(pRenderSurface);
	SAFE_RELEASE(pDefaultSurface);

	// Save screenshot
	WCHAR mapName[256];
	CHAR mapNameChar[256];

	FILE *imageFile = NULL;

	do
	{
		if (imageFile != NULL)
		{
			fclose(imageFile);
			imageFile = NULL;
		}

		swprintf(mapName, L"screenshot%d.jpg", numScreenshot);
		sprintf(mapNameChar, "screenshot%d.jpg", numScreenshot);
		numScreenshot++;

		imageFile = fopen(mapNameChar, "r");
	} while (imageFile != NULL);

	D3DXSaveTextureToFile(mapName, D3DXIFF_JPG, renderTarget, NULL);
	wprintf(L"Saving texture: %s\n", mapName);

	return hr;
}

/**
 * Called when the keyboard is pressed
 */
static float modelHeight = 0.0f;

void CALLBACK KeyboardProc( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
	if ( bKeyDown )
	{
		D3DXMATRIX mat;

		switch( nChar )
		{
			case VK_F1: 
				showUI = !showUI;
			break;

			case VK_F10: 
				saveScreenshot();
			break;

			case VK_F5:
				D3DXMatrixTranslation(&mat, 0.0f, -1.0f, 0.0f);
				matWorld *= mat;
			break;

			case VK_F6:
				D3DXMatrixTranslation(&mat, 0.0f, 1.0f, 0.0f);
				matWorld *= mat;
			break;

			case VK_F7:
				D3DXMatrixTranslation(&mat, -1.0f, 0.0f, 0.0f);
				matWorld *= mat;
			break;

			case VK_F8:
				D3DXMatrixTranslation(&mat, 1.0f, 0.0f, 0.0f);
				matWorld *= mat;
			break;
		}
	}  
} 

void SetIterationsText()
{
	// Set text
	CDXUTStatic* iterationsStatic = hud.GetStatic( ITERATIONS_STATIC );
	WCHAR uiText[256];
	StringCchPrintf(uiText, 256, L"Iterations: %d", numIterations); 
	iterationsStatic->SetText(uiText);
}

/**
 * Called to handle UI events
 */
void CALLBACK GUIEventProc( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	switch(nControlID)
	{
		case BUTTON_FULLSCREEN:
			DXUTToggleFullScreen();
			break;

		case BUTTON_RELOAD_MEDIA:

			ReleaseMedia();

			// Reload shader
			HRESULT hr;
			V(DXUTFindDXSDKMediaFileCch(fileStr, MAX_PATH, shaderFileName) );
			GenerateAndLoadShader();
			V(LoadTextures(m_pd3dDevice));
			SetEffectTextures();
			updateShaderParametersMatrix = true;
			updateShaderParameters = true;

			break;

		case DEPTH_SLIDER:
		{
			float depthValue = (float) (hud.GetSlider(DEPTH_SLIDER)->GetValue());
			bumpDepth = depthValue/100.0f;

			CDXUTStatic* heightRangeStatic = hud.GetStatic( DEPTH_SCALE_STATIC );
			WCHAR uiText[256];
			StringCchPrintf(uiText, 256, L"Height scale: %0.2f", bumpDepth); 
			heightRangeStatic->SetText(uiText);

			updateShaderParameters = true;
		}
			break;

		case TILE_SLIDER:
		{
			int tileValue = hud.GetSlider(TILE_SLIDER)->GetValue();
			textureTileFactor = tileValue/10.0f;

			CDXUTStatic* tileStatic = hud.GetStatic( TILE_SCALE_STATIC );
			WCHAR uiText[256];
			StringCchPrintf(uiText, 256, L"Tile scale: %0.2f", textureTileFactor); 
			tileStatic->SetText(uiText);

			updateShaderParameters = true;
		}
		break;

		case DEPTHBIAS_CHECK_BOX:
		{
			depthBias = hud.GetCheckBox(DEPTHBIAS_CHECK_BOX)->GetChecked();
			
			updateShaderParameters = true;
		}
		break;

		case BORDERCLAMP_CHECK_BOX:
		{
			borderClamp = hud.GetCheckBox(BORDERCLAMP_CHECK_BOX)->GetChecked();

			updateShaderParameters = true;
		}
		break;

		case DEC_ITERATIONS_BUTTON:
		{
			if (numIterations == 8)
				return;

			numIterations -= 8;
			SAFE_RELEASE(effect);
			GenerateAndLoadShader();
			SetEffectTextures();
			updateShaderParametersMatrix = true;
			updateShaderParameters = true;

			// Set text
			SetIterationsText();
		}
			break;

		case INC_ITERATIONS_BUTTON:
		{
			if (numIterations == 40)
				return;

			numIterations += 8;
			SAFE_RELEASE(effect);
			GenerateAndLoadShader();
			SetEffectTextures();
			updateShaderParametersMatrix = true;
			updateShaderParameters = true;

			// Set text
			SetIterationsText();
		}
		break;

		case TECHNIQUE_COMBO_BOX:
		{
			DXUTComboBoxItem* pSelectedItem = ((CDXUTComboBox*)pControl)->GetSelectedItem();
			if ( pSelectedItem )
				currentTechniqueID = (int)(INT_PTR) pSelectedItem->pData;

			updateShaderParameters = true;
		}
			break;
		
		case TEXTURE_COMBO_BOX:
			DXUTComboBoxItem* pSelectedItem = ((CDXUTComboBox*)pControl)->GetSelectedItem();
			if ( pSelectedItem )
				selectTexture = (int)(INT_PTR) pSelectedItem->pData;

			SetEffectTextures();
			updateShaderParameters = true;
			break;
	}
}

/**
 * Main
 */
int main(int argc, char *argv[])
{
	// Set the callback functions
	DXUTSetCallbackDeviceCreated  ( OnCreateDevice );
	DXUTSetCallbackDeviceReset    ( OnResetDevice );
	DXUTSetCallbackDeviceLost     ( OnLostDevice );
	DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );

	DXUTSetCallbackMsgProc        ( MsgProc );
	DXUTSetCallbackKeyboard       ( KeyboardProc );
	DXUTSetCallbackFrameRender    ( OnFrameRender );
	DXUTSetCallbackFrameMove      ( OnFrameMove );

	// 
	printf("Loading all media files... Wait...\n");

	//DXUTSetCursorSettings( true, true );
	DXUTInit( true, true, true );
	DXUTSetCursorSettings(true, true);
	DXUTCreateWindow( L"Detailed Surface Rendering - by Bruno Evangelista (www.brunoevangelista.com)" );
	DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 800, 600, IsDeviceAcceptable, ModifyDeviceSettings );
	
	printf("Done\n");
	DXUTMainLoop();

	return DXUTGetExitCode();
}  