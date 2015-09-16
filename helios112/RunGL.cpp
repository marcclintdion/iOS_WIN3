
//####################################################################################################################


#ifdef WIN32
#define glGenerateMipmap       glGenerateMipmapEXT        
#define glGenFramebuffers      glGenFramebuffersEXT    
#define glBindFramebuffer      glBindFramebufferEXT          
#define glFramebufferTexture2D glFramebufferTexture2DEXT            

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream.h>
#include <fstream.h>
//using namespace std; //___used for string object

#include <GL/gl.h>

HDC	   hDC        = NULL;
HGLRC      hRC        = NULL;
HWND       hWnd       = NULL;
HINSTANCE  hInstance  = NULL;
//-------------------------------
int        WINAPI       WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT    CALLBACK     WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//-------------------------------
void       ProcessKeyboard();
int        LoadTexture(char *texture_name, GLuint *texture);
//-------------------------------
bool keys[256], keypressed[256];



#include "headerFiles/glext.h" 
#include "headerFiles/glext_Init_A.cpp" 

#include "headerFiles/VSync.h"   

#include <windows.h>

void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
#include "headerFiles/FreeImage.h"
#include "cpp/freeImage.cpp"


#endif



//####################################################################################################################


#include <math.h>


//###############################################################################################################################################

#include "MATRIX_MATH.cpp"

//###############################################################################################################################################
//-------------------------------------------------------------------------------------------------------------- 

const       int TEXTURE_WIDTH  = 2048;
const       int TEXTURE_HEIGHT = 2048;
//------------------------------------
GLuint      depth;

GLuint      fboId_2D; 

//-----------------------
GLuint      shadowMap_2D;


GLfloat moveShadow_01[] = {0.0, 0.0, 0.0};

//--------------------------------------------------------------------------------------------------------------
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//----------------------------------------------------------------------------------------

extern GLuint msaaFramebuffer;

void RenderGL(void);
void InitGL  (void);
void shutDownGL(void);

#ifdef WIN32
GLfloat viewWidth    = 1920;
GLfloat viewHeight   = 1080;
#endif
#ifdef __APPLE__
GLfloat viewWidth;
GLfloat viewHeight;
GLuint  viewFramebuffer;        
#endif        
//-------------------------------------------------------------------------------

GLfloat eyePosition[3];
GLfloat look_LEFT_RIGHT;
GLfloat look_UP_DOWN;   


//#########################################################################################################|_FREE_IMAGE

void ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight )
{
        #ifdef __APPLE__
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        #endif
        
        #ifdef WIN32
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);	        
        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
        #endif  
}

//===============================================================================================================================                                                   

GLfloat     modelView[16];
GLfloat     projection[16];
GLfloat     mvpMatrix[16];
GLfloat     mvpMatrixInverse[16];
GLfloat     lightMatrix[16];  
GLfloat     moveSetMatrix[16]; 
GLfloat     textureMatrix[16];
GLfloat     ProjectionShadow[16];
GLfloat     LightModelViewMatrix[16];


GLuint      UNIFORM_MODELVIEWPROJ;
GLuint      UNIFORM_MODELVIEWPROJ_INVERSE;
GLuint      UNIFORM_LIGHT_MATRIX;

//===============================================================================================================================

GLfloat frameRateAdjustment  =     1.0; 

//######################################################################################################################
GLfloat       globalLinearAttenuation                                   =     0.09;
GLfloat       offset[]                                                  =  {20.04, 4.58902, 4.18, 1};
GLfloat       moveSet[]                                                 = {0.0, 0.0, 0.0}; 
//---------------------------------------------------- 
#include    "_SHADERS/SHADOWS/shadows_24B_GLOBALS.cpp"                              
//---------------------------------------------------- 
GLfloat       adjustShadowMove[]                                        =  {  0.11, 0.0, 0.0, 1.0}; 
//================================================================================================= 
GLfloat       shadows_POSITION[]                                        =  {  0.0, 0.0, 0.0, 1.0}; 
GLfloat       shadows_ROTATE[]                                          =  {  1.0, 0.0, 0.0, 0.0};
//-------------------------
GLfloat       moveShadow_A[]                                            =  { -6.02503, -7.28592, -12.7902, 1};
GLfloat       rotateShadow_A[]                                          =  {  0, 1, 0.66, 30};
GLfloat       adjustModelShadow_A_ROTATION                              =    33;
//-------------------------
GLfloat       moveShadow_B[]                                            =  {  0.71,   -0.27,    0.0,      1.0};
GLfloat       rotateShadow_02[]                                         =  {  0.12,   -4.7,     2.42,   -32.456};
GLfloat       adjustModelShadow_02_ROTATION                             =    25.0;
//-------------------------
GLfloat       moveShadow_03[]                                           =  { -0.515, -12.6952, -0.440011,   1.0};
GLfloat       rotateShadow_03[]                                         =  {  0.0,     1.0,       1.0,    29.28};                           
GLfloat       darkness_shadow[]                                         =  {  0.0,     0.0,       0.0,     1.0};                                                     
//######################################################################################################################

//----------------------------------------------------
GLfloat       lightPositionMultiplier[]                                 =  {   1.0, 1.0, 1.0, 1};
GLfloat       goldenSunset_LIGHT_POSITION_01[]                          =  {  -0.068917, 3.9, -0.715183, 1};
GLfloat       ambient_goldenSunset                                      =      0.451993;   
#include    "_SHADERS/BACKGROUND/goldenSunset_GLOBALS.cpp"
//--------------------------------------------------------
GLfloat       wood_LIGHT_POSITION_01[]                                  =  {  -0.168917, 4.73002, -0.115183, 1};
GLfloat       shininess_wood                                            =     34.3499;
GLfloat       ambient_wood                                              =      0.106997;                            
GLfloat       attenuation_SHINY_wood                                    =      1/0.014997;                              
#include    "_SHADERS/BACKGROUND/wood_GLOBALS.cpp"  
//------------------------------------------------------ 
//#include    "_SHADERS/BACKGROUND/wood_32B_GLOBALS.cpp"                                                         
//------------------------------------------------------
GLfloat       backDrop_LIGHT_POSITION_01[]                              =  {  -0.168917, 4.73002, -0.115183, 1};
GLfloat       shininess_backDrop                                        =     34.3499;
GLfloat       ambient_backDrop                                          =      0.0619971;                             
#include    "_SHADERS/BACKGROUND/backDrop_GLOBALS.cpp"                                  
//----------------------------------------------------                              
GLfloat       plant_LIGHT_POSITION_01[]                                 =  {  -0.168917, 4.73002, -0.115183, 1};
GLfloat       ambient_plant                                             =      0.0539995;                                 
#include    "_SHADERS/BACKGROUND/plant_GLOBALS.cpp"
//-------------------------------------------------           
//######################################################################################################################                          
 
                                GLfloat       movePiece[]                                               =  {  0.0,     0.0,       0.0,     0.0};
                                //--------------------------------------------------------------                                                    
                                GLfloat       backDrop_POSITION[]                                       =  {  0.0,  1000.0,       0.0,     1.0};     
                                #include    "_MODEL_FOLDERS_/backDrop/backDrop_Globals.cpp"                                                          
                                //===================================================================================================================
                                #include    "_MODEL_FOLDERS_/marcParts/marc_GLOBALS.cpp"
                                //===================================================================================================================    
                                #include    "_MODEL_FOLDERS_/marcParts/head/head_Globals.cpp"                                                                
                                //=================================================================================================================== 
                                //GLfloat     tile_2m_LIGHT_POSITION_01[]                               = { 1.0, 5.0, 2.0, 1.0};
                                GLuint        tile_2m_NORMALMAP;
                                GLuint        tile_2m_TEXTUREMAP;
                                #include    "_MODEL_FOLDERS_/tile_2m/tile_2m_Globals.cpp" 
                                //---------------------
                                //GLfloat     pyramidTile_LIGHT_POSITION[]                              = { 1.0, 5.0, 2.0, 1.0};
                                #include    "_MODEL_FOLDERS_/pyramidTile/pyramidTile_Globals.cpp"     
                                //--------------------------------------------------------------
                                //GLfloat     smallPillar_LIGHT_POSITION[]                              = { 1.0, 5.0, 2.0, 1.0};
                                #include    "_MODEL_FOLDERS_/smallPillar/smallPillar_Globals.cpp"     
                                //--------------------------------------------------------------
                                GLfloat       moveShadow_PlantPot_01[]                                  =  {-4.0, -6.28005, 0, 1};
                                GLfloat       plantPot_01_LIGHT_POSITION[]                              =  { 0.38, -2.04, 9.82004, 1};
                                #include    "_MODEL_FOLDERS_/plantPot_01/plantPot_01_Globals.cpp"   
                                //--------------------------------------------------------------  
                                GLfloat       plant_01_POSITION[]                                       =  { 0.0, 0.0, 0.0, 1.0};                                                                 
                                GLfloat       plant_01_ROTATE[]                                         =  { 0.0, 1.0,  0.0, 0.0};                                                                
                                GLfloat       plant_01_SCALE                                            =    0.21;   
                                //------------
                                GLfloat       moveShadow_plant_01[]                                     =  { 0.216, 0.0, -0.61, 1};
                                GLfloat       adjustMoveShadow_plant_01[]                               =  { 0.0, 0.0, 0.0, 1};
                                //------------
                                GLfloat       scaleMoveShadow_plant_01                                  =    0.058;
                                //------------
                                GLfloat       scaleShadow_plant_01                                      =    0.605005;
                                GLfloat       scaleShadow_plant_02                                      =    0.605005;
                                //------------
                                GLfloat       plant_01_Shadow_ROTATE[]                                  =  { 5.07, 5.39, 4.84, 43.1701};
                                GLfloat       plant_01_LIGHT_POSITION[]                                 =  { 0.0, 0.0, 0.0, 1.0}; 
                                GLfloat       plant_01_AMBIENT                                          =    0.198903;
                                #include    "_MODEL_FOLDERS_/plant_01/plant_01_Globals.cpp"                                                          
                                //-------------------------------------------------------------------
                                #include    "_MODEL_FOLDERS_/rightWall_2x1/rightWall_2x1_Globals.cpp"                                                          
                                //-------------------------------------------------------------------                                                    
                                GLfloat       backWall_2x2_LIGHT_POSITION[]                             = { -0.2, -1.4, 3, 1};
                                #include    "_MODEL_FOLDERS_/backWall_2x2/backWall_2x2_Globals.cpp"                                                          
                                //====================================================================================                                                   
                                GLfloat       spikyBall_00_time                                         =    0.0;
                                //---------------------------------------------                              
                                GLfloat       initialVelocitySpikyBall_1                                =    0.0;
                                GLuint        UNIFORM_initialVelocitySpikyBall_1;
                                //---------------------------------------------
                                GLfloat       velocityIncreaseRotation_1                                =    1.0;
                                GLfloat       velocitySwap_1[]                                          = {  0.0, 0.0, 0.0, 0.0};
                                #include     "ADD_COLLISION_BALL/GLOBALS_1.cpp"
                                //---------------------------------------------
                                #include    "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Globals.cpp"                                                          
                                //==============================================================================================================================


                                #include "_MODEL_FOLDERS_/springBoard/baseMain/baseMain_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/springBoard/springCore/springCore_Globals.cpp"                                                                
                                //====================================================================================                                          
                                #include "_MODEL_FOLDERS_/springBoard/spring/spring_Globals.cpp"                                                                
                                //====================================================================================   






//======================================================================================================================================================================================



#ifdef WIN32
#include "cpp/winInit.cpp"
#endif  


//------------------------------------------------------------------------------------------------------------------------                 
//------------------------------------------------------------------------------------------------------------------------                 
                                                            
GLfloat    moveModel[]                           = {0.0, 0.0, 0.0, 0.0};

GLfloat    positionY                             =  0.0;
GLfloat    positionX                             =  0.0;                                  

GLfloat    boundingBox_MAIN_CHARACTER_left_edge  = -0.179;      
GLfloat    boundingBox_MAIN_CHARACTER_right_edge =  0.179; 
GLfloat    boundingBox_MAIN_CHARACTER_lower_edge =  0.01;
GLfloat    boundingBox_MAIN_CHARACTER_upper_edge =  1.253;
GLfloat    boundingBox_MAIN_CHARACTER_near_edge  =  0.179;     
GLfloat    boundingBox_MAIN_CHARACTER_far_edge   = -0.179;

int        numberOfCollisionObjects              =  5;

GLfloat    left_edge_SecondaryObjects[500];
GLfloat    right_edge_SecondaryObjects[500];
GLfloat    lower_edge_SecondaryObjects[500];
GLfloat    upper_edge_SecondaryObjects[500];
GLfloat    near_edge_SecondaryObjects[500];
GLfloat    far_edge_SecondaryObjects[500];

bool       RIGHT = true;
bool       LEFT  = true;                                      
bool       UP    = true;
bool       DOWN  = true;

GLuint     objectNumber;

#include "cpp/collisionCheck.cpp" 
//------------------------------------------------------------------------------------------------------------------------------------

//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################

#ifdef __APPLE__
#import <AVFoundation/AVFoundation.h>
AVAudioPlayer *funkLoop;
//------------------------------------
AVAudioPlayer *laser;
//------------------------------------
#endif


//#include <AudioToolbox/AudioToolbox.h>
//SystemSoundID _pewPewSound;
//------------------------------------


void InitGL( void )//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___END_INIT__
{

#ifdef __APPLE__        
        //NSString *pewPewPath = [[NSBundle mainBundle]  pathForResource:@"funkLoop" ofType:@"mp3"];
        //NSURL *pewPewURL = [NSURL fileURLWithPath:[[NSBundle mainBundle]  pathForResource:@"funkLoop" ofType:@"mp3"]];
        //AudioServicesCreateSystemSoundID((CFURLRef)pewPewURL, &_pewPewSound);
        //AudioServicesPlaySystemSound(_pewPewSound);
        
        //====================================================================================================================            
        NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle]  pathForResource:@"funkLoop" ofType:@"mp3"]];
        funkLoop = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
	    funkLoop.numberOfLoops = -1;
	    funkLoop.volume = 1.0;
        [funkLoop play];  
        //====================================================================================================================           
        NSURL *url2 = [NSURL fileURLWithPath:[[NSBundle mainBundle]  pathForResource:@"laser" ofType:@"wav"]];
        laser = [[AVAudioPlayer alloc] initWithContentsOfURL:url2 error:nil];
	    laser.numberOfLoops = -1;
	    laser.volume = 1.0;
        [laser play];  
        //====================================================================================================================         
#endif       
       
        eyePosition[0]                     =  -0.0; 
        eyePosition[1]                     =  -4.49996; 
        eyePosition[2]                     =   7.45011;
        
        look_LEFT_RIGHT                   =    0.0;
        look_UP_DOWN                      =    8.6;   
        
        
        //==========================================================================
#ifdef WIN32    
#include "cpp/setPixelFormat.cpp"
#include "headerFiles/glext_Init_B.cpp" 
        //-------------------------------------
        SetVSyncState(true);        
#endif
        
        //=========================================================================================================================================        
        //====================================================================================================================    
        glGenTextures(1, &shadowMap_2D);
        glBindTexture(GL_TEXTURE_2D, shadowMap_2D);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glBindTexture(GL_TEXTURE_2D, 0);   
        //-----------------------------------------
        glGenFramebuffers(1, &fboId_2D);
        glBindFramebuffer(GL_FRAMEBUFFER, fboId_2D);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowMap_2D, 0);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //====================================================================================================================                                         

        
        
        
        //-------------------------------------------------------------------------------------------------------------------     
        #include "_SHADERS/BACKGROUND/goldenSunset_INIT.cpp"  
        //-------------------------------------------------------------------------------------------------------------------     
         #include "_SHADERS/BACKGROUND/plant_INIT.cpp"      
        //-------------------------------------------------------------------------------------------------------------------     
        #include "_SHADERS/BACKGROUND/wood_INIT.cpp"  
        //-------------------------------------------------------------------------------------------------------------------     
        //#include "_SHADERS/BACKGROUND/wood_32B_INIT.cpp"       
        //-------------------------------------------------------------------------------------------------------------------     
        #include "_SHADERS/BACKGROUND/backDrop_INIT.cpp"      //__SHADER_AND_MODEL_WERE_GIVEN_SAME_NAME
        #include "_MODEL_FOLDERS_/backDrop/backDrop_Init.cpp" //__SHADER_AND_MODEL_WERE_GIVEN_SAME_NAME
        //===================================================================================================================    
        #include "_SHADERS/SHADOWS/shadows_24B_INIT.cpp"                            
        //-------------------------------------------------------------------------------------------------------------------   
        #include "_MODEL_FOLDERS_/marcParts/marc_INIT.cpp"
        //------------------------------------------------------------------------------------------------------------------- 
        #include "_MODEL_FOLDERS_/marcParts/head/head_Init.cpp"                                                                   
        //-------------------------------------------------------------------------------------------------------------------
        #include "_MODEL_FOLDERS_/tile_2m/tile_2m_Init.cpp"     
        //-------------------------------------------------------------------------------------------------------------------
        #include "_MODEL_FOLDERS_/pyramidTile/pyramidTile_Init.cpp"        
        //-------------------------------------------------------------------------------------------------------------------
        #include "_MODEL_FOLDERS_/smallPillar/smallPillar_Init.cpp"        
        //-------------------------------------------------------------------------------------------------------------------
        #include "_MODEL_FOLDERS_/plantPot_01/plantPot_01_Init.cpp"        
        //-------------------------------------------------------------------------------------------------------------------
        #include "_MODEL_FOLDERS_/plant_01/plant_01_Init.cpp"                                                             
        //--------------------------------------------------------------                                                    
        #include "_MODEL_FOLDERS_/rightWall_2x1/rightWall_2x1_Init.cpp"                                                             
        //--------------------------------------------------------------                                                    
        #include "_MODEL_FOLDERS_/backWall_2x2/backWall_2x2_Init.cpp"                                                             
        //--------------------------------------------------------------                                                    
        #include "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Init.cpp"                                                             
        //===================================================================================================================         
        #include "_MODEL_FOLDERS_/springBoard/baseMain/baseMain_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/springBoard/springCore/springCore_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/springBoard/spring/spring_Init.cpp"                                                                   
        //====================================================================================           
       
        
        
        
        
        //=================================================================================================================== 
        
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);	
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glAlphaFunc(GL_GREATER, 0.1);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);  
        
        
        //=====================================================================================================================
        
        
        
        
        
}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___END_INIT__



//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################


void RenderGL(void)
{
        

                 if(marcWalking)
                 {
                           if(resetAnimation)
                           {
                                    mainBodyPosition_setSelection         = 1;
                                    setSelection_LEFT_ARM                 = 1;
                                    setSelection_RIGHT_ARM                = 1;
                                    setSelection_LEFT_LEG                 = 1;
                                    setSelection_RIGHT_LEG                = 1;                                    
                                    setSelection_HEAD                     = 1;
                                    setSelection_TORSO                    = 1;
                                    setSelection_HIPS                     = 1;
                                    
                                    resetAnimation = false;
                           }
                           
                           #include "_MODEL_FOLDERS_/marcParts/ME_AnimationSet_WALK.cpp"
                           #include "_MODEL_FOLDERS_/marcParts/ME_animationSequencing.cpp" 
                 }      

        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        //======================================================_SHADOWS_BEGIN_===========================================================================	                       
        
        
        
        //=============================================================================================================================  
        
        glBindFramebuffer(GL_FRAMEBUFFER, fboId_2D);//-----------------------F.B.O.     
        //----------------------------------------------------------------
        //glColor4f(color is changed using fragment program)
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear (GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);
        //----------------------------------------------------------------
        
        
        //-----------------------------------------------------------------------------------------------------------------------------                                
        
        
        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        
        
        PerspectiveMatrix(ProjectionShadow, 45, 1.0, 0.01, 1000.0);
        
        
        Rotate(ProjectionShadow, 0.0, 1.0, 0.0, 20.0);
        Rotate(ProjectionShadow, 1.0, 0.0, 0.0, 45.0);
        
        
        
        glUseProgram(SHADER_shadow);//---------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  
        
        //############################################################################################################################################################|__SHADOW_01
        //============================================================================================================================================================|__LAYER__01
        glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE); 
        //===================================================== 
        darkness_shadow[0] = 0.5;
        darkness_shadow[1] = 0.5;
        darkness_shadow[2] = 0.5;
        
        
        
        //-----------------------------------------------------                        
        #include "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Shadow_01.cpp"  
        //------------------------------------------------------------------  
        
        //-----------------------------------------------------------                      
        #include "_MODEL_FOLDERS_/marcParts/RenderMarc_SHADOW_01.cpp"
        //================================================================================================================   
        

        //============================================================================================================================================================|__LAYER__02       
        glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE); 
        //===========================================================                     
        
        
        
        
        //---------------------------------------------------------
        movePiece[0]   =  -1.5;                                                                                                 
        movePiece[1]   =  -1.5;                                                                                                 
        movePiece[2]   =   0.0; 
        //------------------------------
        adjustMoveShadow_plant_01[0] = 0.0;
        adjustMoveShadow_plant_01[1] = 0.0;
        adjustMoveShadow_plant_01[2] = 0.0;                      
        #include "_MODEL_FOLDERS_/plant_01/plant_01_SHADOW_01.cpp"
        //---------------------------------------------------------
        movePiece[0]   =   1.7;                                                                                                 
        movePiece[1]   =  -2.0;                                                                                                 
        movePiece[2]   =   0.0; 
        //------------------------------
        adjustMoveShadow_plant_01[0] = adjustShadowMove[0];// 0.11
        adjustMoveShadow_plant_01[1] = adjustShadowMove[1];// 0.00
        adjustMoveShadow_plant_01[2] = adjustShadowMove[2];// 0.00                                              
        #include "_MODEL_FOLDERS_/plant_01/plant_01_SHADOW_01.cpp"
        //---------------------------------------------------------                                  
        
        
        
        //############################################################################################################################################################|__SHADOW_02
        
        
        
        //============================================================================================================================================================|__LAYER__01
        glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE); 
        //===========================================================                       
        darkness_shadow[0] = 0.3;
        darkness_shadow[1] = 0.3;
        darkness_shadow[2] = 0.3;
        
        
        
        //============================================================================================================================================================|__LAYER__02     
        glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_TRUE); 
        //===========================================================
        
        
        
        //------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
        LoadIdentity(textureMatrix);
        AssignMatrix(textureMatrix, ProjectionShadow); 
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        glEnable(GL_DEPTH_TEST);                                 
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 	                       
	glBindFramebuffer(GL_FRAMEBUFFER, 0);	                       
       
        //======================================================_SHADOWS_END_=============================================================================	                       
        //======================================================_SHADOWS_END_=============================================================================	                       
        //======================================================_SHADOWS_END_=============================================================================	                       
        //======================================================_SHADOWS_END_=============================================================================	 
        
        //##################################################################################################################################################################################################        
        //##################################################################################################################################################################################################         
        //##################################################################################################################################################################################################         
        //##################################################################################################################################################################################################          
        

        
        

        //#################################################################################################################################################################        

        
#include "DrawScene_01.cpp"        
           
           
        //============================================================================================                                                 
        #include  "ADD_COLLISION_BALL/RENDER_1.cpp"
        #include "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Render.cpp"              
        //============================================================================================ 
        
        
#ifdef WIN32
        SwapBuffers( hDC );
#endif
}

//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################


#ifdef WIN32 
void ProcessKeyboard()					
{
//#########################################################################################################################################################       
        
        
#include "_MODEL_FOLDERS_/marcParts/head/head_Keyboard.cpp"                                                               
        if (keys[VK_F8]) 			                                                                                                                   
	{                                                                                                                                              
                ofstream outKeys("CALIBRATION.cpp");                                                                                     
                
                outKeys << "  GLfloat     moveShadow_A[] = {"           << moveShadow_A[0] << ", "                               
                                                                        << moveShadow_A[1] << ", "                               
                                                                        << moveShadow_A[2] << ", " << 1.0 << "};\n";          
                
                outKeys << "  GLfloat     head_ATTENUATION         =  " << head_ATTENUATION   << ";\n";                                    
                outKeys << "  GLfloat     head_SHININESS           =  " << head_SHININESS  << ";\n";                                       
        }             
        
        //====================================================================================                                          





#include "_MODEL_FOLDERS_/marcParts/marc_KEYBOARD_CONTROLS.cpp"

//--------------------------------------------------------------------    
    if (keys['A'])
	{
          eyePosition[0]    += .05;
    }	
    if (keys['D'])
	{
          eyePosition[0]    -= .05;
    }
//-----------------------------------
    if (keys['S'])
	{
          eyePosition[2] += .05;
    }
          if (keys['S'] && keys[VK_SHIFT])
	      {
                eyePosition[2] += 0.5;
          
          }    
//-----------------------------------	
    if (keys['W'])
	{
          eyePosition[2] -= .05;       
    }    
	      if (keys['W'] && keys[VK_SHIFT])
	      {
                eyePosition[2] -= 0.5;      
          }	
//-----------------------------------    
    if (keys['E'])
	{
          eyePosition[1] -= 0.05;
    }
	      if (keys['E'] && keys[VK_SHIFT])
	      {
                eyePosition[1] -= 0.5;      
          }		
    
    if (keys['Q'])
	{
          eyePosition[1] += 0.05;      
    }
	      if (keys['Q'] && keys[VK_SHIFT])
	      {
                eyePosition[1] += 0.5;      
          }            

//#########################################################################################################################################################       
}
#endif


//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################



void shutDownGL( void )
{
#ifdef WIN32
#include "cpp/shutDownWin.cpp"
#endif 	 
        
        //====================================================================================
        #include "_MODEL_FOLDERS_/marcParts/DeleteMarc.cpp"  
        //====================================================================================
        #include "_MODEL_FOLDERS_/marcParts/head/head_Shutdown.cpp"                                                               
        //====================================================================================   
        #include "_MODEL_FOLDERS_/springBoard/baseMain/baseMain_Shutdown.cpp"                                                               
        //====================================================================================         
        #include "_MODEL_FOLDERS_/springBoard/springCore/springCore_Shutdown.cpp"                                                               
        //====================================================================================                                                              
        #include "_MODEL_FOLDERS_/springBoard/spring/spring_Shutdown.cpp"                                                               
        //====================================================================================        
        
}


//===================================================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//===================================================================================================================================================================




