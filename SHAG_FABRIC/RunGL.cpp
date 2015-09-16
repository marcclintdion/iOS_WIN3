#define var GLfloat
//####################################################################################################################
                                

#ifdef WIN32
        #define   glGenerateMipmap       glGenerateMipmapEXT        
        #define   glGenFramebuffers      glGenFramebuffersEXT    
        #define   glBindFramebuffer      glBindFramebufferEXT          
        #define   glFramebufferTexture2D glFramebufferTexture2DEXT            
         
        #define   STRICT
        #define   WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <iostream.h>
        #include <fstream.h>
        //using namespace std; //___used for string object

       //-----------------------------------------------------------------------------


        #include <GL/gl.h>
        #include <GL/glu.h>        
        #include "headerFiles/glext.h" 
        #include "headerFiles/glext_Init_A.cpp" 

      
        void InitGL(void);   
        void RenderGL(void); 
        
 
        void ProcessKeyboard(void);
                

        var  viewWidth;
        var  viewHeight;          
        
        //----------------------------------------------------------------------
        

        var   PassMouseMovementTo_GLSL_MATRIX[2];

        //----------------------------------------------------------------------

        //-------------------------------
        var keys[256], keypressed[256];        
        #include "cpp/WGL_ARB_multisample.h"
        //-------------------------------





        
        #include "headerFiles/VSync.h"   
        
        #include <windows.h>

        void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
        #include "headerFiles/glaux.h"        
        #include "headerFiles/FreeImage.h"
        #include "cpp/freeImage.cpp"
        //------------------------------------------
 
    
#endif

//####################################################################################################################


#include <math.h>
  

//####################################################################################################################

#include "MATRIX_MATH.cpp"

//####################################################################################################################
GLfloat screenBuffer_EyePosition[3];


GLuint textureID;
GLuint textureMap[10];
//------------------------------------
GLuint fbo, color, depth;
GLuint componentShaderPass_fbo, componentShaderPass_color, componentShaderPass_depth;
//------------------------------------
GLuint      shadow_2D_ID; 

//--------------------------------------
GLuint      fboId; 
//==================================================================================== 
GLuint      gaussianBlurHorizontalPass_fboId;
GLfloat     gaussianBlurHorizontalPass_POSITION[]                 = { 0.0,  0.0,  0.0,  1.0}; 
GLfloat     gaussianBlurHorizontalPass_ROTATE[]                 = { 0.0,  0.0,  0.0,  1.0}; 
GLfloat     gaussianBlurHorizontalPass_SCALE                     = 1.0; 
#include "_MODEL_FOLDERS_/gaussianBlur/gaussianBlurHorizontalPass/gaussianBlurHorizontalPass_vboGlobals.cpp"  //vboID = 300
//=================================================
GLuint      gaussianBlurVerticalPass_fboId;
GLfloat     gaussianBlurVerticalPass_POSITION[]                 = { 0.0,  0.0,  0.0,  1.0};
GLfloat     gaussianBlurVerticalPass_ROTATE[]                 = { 0.0,  0.0,  0.0,  1.0}; 
GLfloat     gaussianBlurVerticalPass_SCALE                     = 1.0;       
#include "_MODEL_FOLDERS_/gaussianBlur/gaussianBlurVerticalPass/gaussianBlurVerticalPass_vboGlobals.cpp"  //vboID = 301       
      

//====================================================================================                                          

GLfloat     frameBufferPlane_ratio_Global_2_Component                       =   1.0;  
//-----------
#include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Globals.cpp"        
                                                        

GLfloat     frameBufferPlane_GaussianHorizontal_SCALE[]                                        =  {1920.0/1080.0, 1.0,  1.0, 1.0};   
GLfloat     frameBufferPlane_GaussianHorizontal_ratio_Global_2_Component                       =   1.0;  
//-----------
#include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianHorizontal_Globals.cpp"        
  
GLfloat     frameBufferPlane_GaussianVertical_SCALE[]                                        =  {1920.0/1080.0, 1.0,  1.0, 1.0};   
GLfloat     frameBufferPlane_GaussianVertical_ratio_Global_2_Component                       =   1.0;  
//-----------
#include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianVertical_Globals.cpp"        
  
//==================================================================================== 
 
//####################################################################################################################

GLsizei       resize_SHADOW_FBO = 1;

var           adjustNearFar[]                                  =  {  0.270001, 31.101 };
//------------------------------------------------------------------------------
var           moveShadow[]                                     =  {-0.01, 0.2, -0.839999, 0.0};
var           matchColorModelToShadowPosition[]                =  {-0.79, -0.31, 0.02, 0.0};

var           rotateModelWithLeftMouse[] =  {21.4, -0.6, };

var           moveSet[]                                        =  {-1.35601e-007, 0, 17.0, 1.0};

var           eyeposition[]    =  {-0.8, 1.2, 26.5, 1.0};
var           turnTable                                        =   0.0;
var           lookAt[]              	                       =  {  0, 0, 0.0, 1.0 };
//------------------------------------------------------------------------------
var           radius_Of_eyePosition_LookAt                     =  40.0;
var           Scale_X_ofLookAtForShadow                        =  1.0;

//------------------------------------------------------------------------------
var           upVector[]             	                       =  {  0.0, 1.0, 0.0};
//------------------------------------------------------------------------------

var           eyeposition_SHADOW[]                             =  {  0, 3.6, 9.2, 1.0};
var           lookAt_SHADOW[]                                  =  {  0, -3.6, -28.1998, 1.0 };

var           shadowsPositionOffset[]	                       =  {  0.5, 0.5, 0.5 };//BIAS_MATRIX
var           scaleShadows                                     =     0.5;//__________//BIAS_MATRIX

var           offset[]                                         =  { -0.0, 0.0, -0, 0.0};
var           offset_ShadowShader[]                            =  { -0.0, 0.0, -0, 0.0};

var           shadowLightPosition[]    	                       =  { -6.15, 0.82, 12, 0.0};

var           scaleShadowSize[]                                =  {  1.2, 1.2, 1.2, 0.0};

var           offsetFinalShadow[]                              =  {  0, 0, 0, 0.0}; //_ADJUSTMENT_IN_THE_FINAL_COLOR_SHADER

var           scaleMoveShadows[]	                           =  {  1.0, 1.0, 1.0, 0.0};//=  {0.971, 0.937001, 1.043, 0.0};
//-------------------------------------------------------------------------------------------------------------------- 
GLuint        fboId_2D;
GLuint        shadowMap_2D;
#include    "_SHADERS/SHADOWS/shadows_24B_GLOBALS.cpp" 
//=========================================================================================== 
GLfloat       shadows_POSITION[]                               =  {  0.0, 0.0, 0.0, 1.0}; 
GLfloat       shadows_ROTATE[]                                 =  {  1.0, 0.0, 0.0, 0.0};
//-------------------------
GLfloat       moveShadow_A[]                                   =  { -6.02503, -7.28592, -12.7902, 1};
GLfloat       rotateShadow_A[]                                 =  {  0, 1, 0.66, 30};
GLfloat       adjustModelShadow_A_ROTATION                     =    33;
//-------------------------
GLfloat       moveShadow_B[]                                   =  {  0.71,   -0.27,    0.0,      1.0};
GLfloat       rotateShadow_02[]                                =  {  0.12,   -4.7,     2.42,   -32.456};
GLfloat       adjustModelShadow_02_ROTATION                    =    25.0;
//-------------------------
GLfloat       moveShadow_03[]                                  =  { -0.515, -12.6952, -0.440011,   1.0};
GLfloat       rotateShadow_03[]                                =  {  0.0,     1.0,       1.0,    29.28};                           
GLfloat       darkness_shadow[]                                =  {  0.0,     0.0,       0.0,     1.0};                                                     
//===========================================================================================  
 
//--------------------------------------------------------------------------------------------------------------
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//----------------------------------------------------------------------------------------

        extern GLuint msaaFramebuffer;

        void RenderGL(void);
        void InitGL  (void);
        void shutDownGL(void);
      
    
       
      

                
       
        #ifdef __APPLE__
               var viewWidth;
               var viewHeight;
               GLuint  viewFramebuffer;        
        #endif 
          
        //-------------------------------------------------------------------------------

 


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

var     modelView[16];
var     projection[16];
var     mvpMatrix[16];
var     mvpMatrixInverse[16];
var     lightMatrix[16];  
var     moveSetMatrix[16]; 
var     textureMatrix[16];
var     ProjectionShadow[16];
var     LightModelViewMatrix[16];
var     ScreenBufferMatrix[16];

float   modelWorld[16];
float   LightView[16];
float   TextureMatrix[16];
float   LightProjection[16];
float   modelViewInverse[16];

float   tempMatrix[16];

var     BiasMatrix[16] = {0.5f, 0.0f, 0.0f, 0.0f,
						  0.0f, 0.5f, 0.0f, 0.0f,
						  0.0f, 0.0f, 0.5f, 0.0f,
						  0.5f, 0.5f, 0.5f, 1.0f};
var     undoMatrix[16];




GLuint      UNIFORM_MODELVIEWPROJ;
GLuint      UNIFORM_MODELVIEWPROJ_INVERSE;
GLuint      UNIFORM_LIGHT_MATRIX;

//===============================================================================================================================
                               

//######################################################################################################################
                                   
                               var groupSelection       =    1.0;                           
                               var select_POSITION[]    = {  0.0, 0.0, 0.0, 0.0};
                               var spinModel            =    0.0;
                               //---------------------------------------------------- 
                               var lightPosition[]      = {  0, 10, 10};
                               var lightLookAt[]        = { 0, 0, -10};                               
                               
                               //====================================================================================                                          
                              
                               GLfloat       globalLinearAttenuation                                   =      0.09;
                                                    
                               GLfloat       lightPositionMultiplier[]                                 =  {   1.0, 1.0, 1.0, 1};
                               GLfloat       goldenSunset_LIGHT_POSITION_01[]                          =  {  -0.068917, 3.9, -0.715183, 1};
                               GLfloat       ambient_goldenSunset                                      =      0.451993;   
                               #include     "_SHADERS/BACKGROUND/goldenSunset_GLOBALS.cpp"
                               //--------------------------------------------------------                               
                               
                               var           facing_UP_LIGHT_POSITION_01[]                             =  {13.4, 95.5, 95.9009, 1.0};
                               var         facing_UP_constantAttenuation             =  0.160001;
                               var         facing_UP_linearAttenuation               =  0.2825;
                               var         facing_UP_quadraticAttenuation            =  3.94881e-009;
                              
                               var           adjustModelViewFor_CSM_UP                                 =  30.2501; 
                               //var           facing_UP_constantAttenuation                           =   -0.2855;   
                               
                               var           zDirectionBias                                            =  274.219;
                               var           facing_UP_SHININESS                                       =  0.03;  
                               
                               //----------
                               #include     "_MODEL_FOLDERS_/facing_UP/facing_UP_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include     "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_Globals.cpp"                                                                
                               //====================================================================================                                          
                               GLfloat       velocityIncreaseRotation_1                                =    1.0;
                               GLfloat       velocitySwap_1[]                                          = {  0.0, 0.0, 0.0, 0.0};
                               #include     "ADD_COLLISION_BALL/GLOBALS_1.cpp"
                               //---------------------------------------------
                               #include     "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Globals.cpp"                                                          
                               //==============================================================================================================================
                               GLfloat     frameBufferPlane_SCALE[]                                        =  { 1920.0/1080.0, 1.0,  1.0, 1.0};   
                               GLfloat     frameBufferPlane_POSITION[]                                     =  { 0, 0, -1.58798, 1.0};   
                               //-----------
                               //#include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Globals.cpp"  
                               //-------------------------------------------------------------------------------------------------
                               #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/sculptris/sculptris_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/sphere/sphere_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Globals.cpp"                                                                
                               //====================================================================================                                          
                               var moveKnight = 0;
                               #include "_MODEL_FOLDERS_/knight/knight_Globals.cpp"                                                                
                               //====================================================================================                                          
                               
                               //#############################################################################################
                               #include "_SHADERS/plastic/rubber/rubber_GLOBALS.cpp"    
                               //#############################################################################################
                                
//======================================================================================================================================================================================


          
          
//###################################################################################################################################################
//###################################################################################################################################################
//###################################################################################################################################################

var shaderNumber = 0;

void SelectShader(var shaderNumber)
{    
     //--------------------------------------------------------------------------------------
     if(shaderNumber == 1)
     {
            //#include "_SHADERS/fresnel/DelylaShield/DelylaShield_RENDER.cpp"        
     }
     //--------------------------------------------------------------------------------------
  
}

//###################################################################################################################################################
//###################################################################################################################################################
//###################################################################################################################################################

void InitGL( void )//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___BEGIN_INIT__
{
        //==========================================================================
        #ifdef WIN32 
            #include "cpp/setPixelFormat.cpp"
            #include "headerFiles/glext_Init_B.cpp" 
            //-------------------------------------
            SetVSyncState(true);        
        #endif
                   
                   PassMouseMovementTo_GLSL_MATRIX[0]        = rotateModelWithLeftMouse[0];
                   PassMouseMovementTo_GLSL_MATRIX[1]        = rotateModelWithLeftMouse[1];
        
//==========================================================================================================================================================================

/* 
        //====================================================================================================================    
        glGenTextures(1, &shadowMap_2D);
        glBindTexture(GL_TEXTURE_2D, shadowMap_2D);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth, (GLsizei)viewHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glBindTexture(GL_TEXTURE_2D, 0);   
        //-----------------------------------------
        glGenFramebuffers(1, &fboId_2D);
        glBindFramebuffer(GL_FRAMEBUFFER, fboId_2D);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowMap_2D, 0);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //====================================================================================================================                                         

  */ 
    //#####################################################################################################################       
    //##################################################################################################################### 
	glGenTextures(1, &shadowMap_2D);
	glBindTexture(GL_TEXTURE_2D, shadowMap_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, (GLsizei)viewWidth / resize_SHADOW_FBO, (GLsizei)viewHeight / resize_SHADOW_FBO, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
    //--------------------------------------------------
	glGenFramebuffersEXT(1, &fboId_2D);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId_2D);
    #ifdef WIN32
    glDrawBuffer(GL_NONE);//_ON_SOME_MACHINES_THIS_IS_REQUIRED / ON_SOME_IT_FAILS
    glReadBuffer(GL_NONE);//_ON_SOME_MACHINES_THIS_IS_REQUIRED / ON_SOME_IT_FAILS
	#endif
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, shadowMap_2D, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    //------------------------
	glEnable( GL_DEPTH_TEST );
    glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);       
    //#####################################################################################################################     
    //#####################################################################################################################        
    glGenFramebuffersEXT(1, &gaussianBlurHorizontalPass_fboId);    
    glGenTextures(1, &textureMap[1]);
    glBindTexture(GL_TEXTURE_2D, textureMap[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth / resize_SHADOW_FBO, (GLsizei)viewHeight / resize_SHADOW_FBO, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);  
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gaussianBlurHorizontalPass_fboId);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureMap[1], 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    ////////////////////////////////////////////////////////
    glGenFramebuffersEXT(1, &gaussianBlurVerticalPass_fboId);    
    glGenTextures(1, &textureMap[2]);
    glBindTexture(GL_TEXTURE_2D, textureMap[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth / resize_SHADOW_FBO, (GLsizei)viewHeight / resize_SHADOW_FBO, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);  
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gaussianBlurVerticalPass_fboId);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureMap[2], 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    //====================================================================================================================
    #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianHorizontal_Init.cpp"                                                                   
    #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianVertical_Init.cpp"                                                                   
    //#####################################################################################################################            
    //#####################################################################################################################         
        screenBuffer_EyePosition[0]                     =   0.0; 
        screenBuffer_EyePosition[1]                     =   0.0; 
        screenBuffer_EyePosition[2]                     =   0.0;  //57.4        
    //====================================================================================================================                                         

        
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Init.cpp"                                                                   
        //====================================================================================  
        #include "_SHADERS/SHADOWS/shadows_24B_INIT.cpp"                            
        //====================================================================================      
        #include "_SHADERS/BACKGROUND/goldenSunset_INIT.cpp"  
        //====================================================================================       
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Init.cpp"                                                             
        //====================================================================================   
                                
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/sculptris/sculptris_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/sphere/sphere_Init.cpp"                                                                   
        //====================================================================================    
        #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Init.cpp"                                                                   
        //====================================================================================   
        #include "_MODEL_FOLDERS_/knight/knight_Init.cpp"                                                                   
        //====================================================================================                                          
                                                         
        //====================================================================================                                          
        #include "_SHADERS/plastic/rubber/rubber_INIT.cpp"                                   
                      
//=================================================================================================================== 



    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);	
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_CULL_FACE);

//=====================================================================================================================

    



}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@___END_INIT__

var rotateEyePosition = 0.0;

//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################

GLfloat rotateModel;

void RenderGL(void)
{                
                   //***************************************************************
                   rotateModelWithLeftMouse[0] = PassMouseMovementTo_GLSL_MATRIX[0];
                   rotateModelWithLeftMouse[1] = PassMouseMovementTo_GLSL_MATRIX[1];
                   //***************************************************************

//####################################################################################################################################################
//####################################################################################################################################################
//####################################################################################################################################################
//====================================================================================================================================================         
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
//====================================================================================================================================================   
	glBindFramebuffer(GL_FRAMEBUFFER, fboId_2D);//-----------------------F.B.O.     
        //----------------------------------------------------------------
        //glColor4f(color is changed using fragment program)
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear (GL_DEPTH_BUFFER_BIT);
        glViewport(1, 1, (GLsizei)viewWidth / resize_SHADOW_FBO - 2, (GLsizei)viewHeight / resize_SHADOW_FBO - 2);
        //----------------------------------------------------------------
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 

#include "runDepth_FBO.cpp"//THE_DEPTH_BUFFER_FROM_THIS_PASS_CAN_BE_READ_FROM_OTHER_GEOMETRY_PASSES    

//====================================================================================================================================================         
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
//====================================================================================================================================================    
//####################################################################################################################################################
//####################################################################################################################################################
//####################################################################################################################################################
/*
     glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gaussianBlurHorizontalPass_fboId);//-----F.B.O.__HORIZONTAL_BLUR

        //=========================================================================================================================================================    
        glClearColor( 1.0f, 1.0f, 1.0f, 0.5f );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        //----------------------------------------------------------------------------------
        glViewport(1, 1, (GLsizei)viewWidth / resize_SHADOW_FBO - 2, (GLsizei)viewHeight / resize_SHADOW_FBO - 2);
        
        PerspectiveMatrix2(ScreenBufferMatrix,viewWidth / viewHeight);
        
        //=========================================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        #endif        
        //=========================================================================================================================================================        
        #ifdef WIN32        
        #endif           
        //=========================================================================================================================================================               
        Rotate(ScreenBufferMatrix, 1.0, 0.0, 0.0,  0);
        Rotate(ScreenBufferMatrix, 0.0, 1.0, 0.0, -0);        
    

        glActiveTexture (GL_TEXTURE0);                                                                                                                                            
        glBindTexture(GL_TEXTURE_2D, shadowMap_2D);                 
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianHorizontal_Render.cpp"                                                                 
        //====================================================================================                                       
                                                                
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);    //--------------------------------F.B.O.__HORIZONTAL_BLUR             

//==========================================================================================================================================================
//==========================================================================================================================================================
//==========================================================================================================================================================                               

   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gaussianBlurVerticalPass_fboId);//-----F.B.O.__HORIZONTAL_BLUR

        //=========================================================================================================================================================    
        glClearColor( 1.0f, 1.0f, 1.0f, 0.5f );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        //----------------------------------------------------------------------------------
        glViewport(1, 1, (GLsizei)viewWidth / resize_SHADOW_FBO - 2, (GLsizei)viewHeight / resize_SHADOW_FBO - 2);
        
        PerspectiveMatrix2(ScreenBufferMatrix, viewWidth / viewHeight);
        
        //=========================================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        ScreenBufferMatrix[12] = screenBuffer_EyePosition[0] + eyeposition[0];
        ScreenBufferMatrix[13] = screenBuffer_EyePosition[2] + eyeposition[2];
        ScreenBufferMatrix[15] = screenBuffer_EyePosition[1] + eyeposition[1];        
        #endif        
        //=========================================================================================================================================================        
        #ifdef WIN32        
        ScreenBufferMatrix[12] = screenBuffer_EyePosition[0] + eyeposition[0];
        ScreenBufferMatrix[13] = screenBuffer_EyePosition[1] + eyeposition[1];
        ScreenBufferMatrix[15] = screenBuffer_EyePosition[2] + eyeposition[2];  
        #endif           
        //=========================================================================================================================================================               
        Rotate(ScreenBufferMatrix, 1.0, 0.0, 0.0,  0);
        Rotate(ScreenBufferMatrix, 0.0, 1.0, 0.0, -0);        
    
        glActiveTexture (GL_TEXTURE0);                                                                                                                                            
        glBindTexture(GL_TEXTURE_2D,  textureMap[1]);                 
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianVertical_Render.cpp"                                                                 
        //====================================================================================                                       
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);    //--------------------------------F.B.O.__HORIZONTAL_BLUR             
*/       
    //*******************************************************************************************************************************************       
    //*******************************************************************************************************************************************        
    //*******************************************************************************************************************************************         
    //*******************************************************************************************************************************************       
    //*******************************************************************************************************************************************        
    //*******************************************************************************************************************************************         

//turnTable += 0.10;



//####################################################################################################################################################
//####################################################################################################################################################
//####################################################################################################################################################
//====================================================================================================================================================                               
///////////////=============DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO________

#include "drawMainColor_FBO.cpp" //_DEPTH_BUFFER_CLEAR_AND_WRITES_SHOULD_BE_DISABLED,_BUT_DEPTH_MUST_STILL_BE_READABLE

///////////////=============DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO________                            
//====================================================================================================================================================
//####################################################################################################################################################
//####################################################################################################################################################
//####################################################################################################################################################







}//_END_RenderGL()


//#######################################################################################################################################################
//#######################################################################################################################################################
//#######################################################################################################################################################
//#######################################################################################################################################################


void ProcessKeyboard(void)
{

     //====================================================================================                                          
 
    //=======================================================================================                                           
    if (keys[VK_NUMPAD6])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[0]         +=  .05;                                                                            
    }                                                                                                                                   
    if (keys[VK_NUMPAD4])                                                                                                                   
    {                                                                                                                                   
             knight_POSITION[0]         -=  .05;                                                                         
    }    
    if (keys[VK_NUMPAD8])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[1]         +=  .05;                                                                            
    }	                                                                                                                                  
    if (keys[VK_NUMPAD2])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[1]         -=  .05;                                                                            
    }                                                                                                                                   
    if (keys[VK_NUMPAD7])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[2]         +=  .05;                                                                            
    }	                                                                                                                                  
    if (keys[VK_NUMPAD9])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[2]         -=  .05;      
    }	                                                                                                                                  
   //=======================================================================================  
    if (keys['L'] || !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             gaussianBlurHorizontalPass_POSITION[0]         +=  .1;                                                                            
    }                                                                                                                                   
    if (keys['J'] || !keys[VK_SHIFT])                                                                                                                   
    {                                                                                                                                   
             gaussianBlurHorizontalPass_POSITION[0]         -=  .1;                                                                         
    }    
    if (keys['I'] || !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             gaussianBlurHorizontalPass_POSITION[1]         +=  .1;                                                                            
    }	                                                                                                                                  
    if (keys['K'] || !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             gaussianBlurHorizontalPass_POSITION[1]         -=  .1;                                                                            
    }                                                                                                                                   
    if (keys['O'] || !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             gaussianBlurHorizontalPass_POSITION[2]         +=  .1;                                                                          
    }	                                                                                                                                  
    if (keys['U'] || !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             gaussianBlurHorizontalPass_POSITION[2]         -=  .1;      
    }
    //======================================================================================

    //=======================================================================================        
    if (keys['M'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             facing_UP_constantAttenuation                  +=  0.005;                                                                            
    }	                                                                                                                                  
    if (keys['N'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             facing_UP_constantAttenuation                  -=  0.005;                                                                            
    }  
    //----------------------------------------------------------------
    if (keys['M'] && keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             facing_UP_linearAttenuation                     +=  0.0005;                                                                            
    }	                                                                                                                                  
    if (keys['N'] && keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             facing_UP_linearAttenuation                     -=  0.0005;                                                                            
    }  
    //----------------------------------------------------------------    
    if (keys['M'] && !keys[VK_SHIFT] && keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
              facing_UP_quadraticAttenuation                 +=  0.01;                                                                            
    }	                                                                                                                                  
    if (keys['N'] && !keys[VK_SHIFT] && keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             facing_UP_quadraticAttenuation                  -=  0.01;                                                                            
    }  
    //----------------------------------------------------------------


    
   
    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
            adjustNearFar[0]                    +=  0.01;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                  
            adjustNearFar[0]                    -=  0.01;                                                                            
    }  
    if (keys['V'])                                                                                                                      
    {	                                                                                                                                  
             adjustNearFar[1]                    +=  0.1;                                                                            
    }	                                                                                                                                  
    if (keys['C'])
    {	                                                                                                                                  
             adjustNearFar[1]                    -=  0.1;                                                                            
    }      
    //-----------------------------------------------------  
    if (keys['V'])                                                                                                                      
    {	                                                                                                                                  
             //facing_UP_SHININESS                 +=  0.1;                                                                            
    }	                                                                                                                                  
    if (keys['C'])
    {	                                                                                                                                  
             //facing_UP_SHININESS                 -=  0.1;                                                                            
    }      
       
                
   //==============================================================================
/*    if (keys['C'] && KEY_C_IS_RESET && !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
            stepVBOcount                    -=  10; 
            KEY_C_IS_RESET                    = false;                                                                           
    }	                                                                                                                                  
    if (!keys['C'])                                                                                                                      
    {	                                                                                                                                  
            KEY_C_IS_RESET                    = true;                                                                           
    } 
    //-----------------------------------------------------------------------------   
    if (keys['V'] && KEY_V_IS_RESET && !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
            stepVBOcount                    +=  10;
            KEY_V_IS_RESET                    = false;                                                                            
    }             
    if (!keys['V'])                                                                                                                      
    {	                                                                                                                                  
            KEY_V_IS_RESET                    = true;                                                                           
    } 
*/    //-----------------------------------------------------------------------------    
   //==============================================================================
       //----------------------------------------------
    if(keys[VK_F8])
    {
         ofstream outSettings("settings.cpp");
             
         //--------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var         flowerShield_POSITION[]             =  {"   << flowerShield_POSITION[0] << ", "
                                                                                       << flowerShield_POSITION[1] << ", "
                                                                                       << flowerShield_POSITION[2] << ", 1.0};\n\n";            
         outSettings << "            //-------------------------------------------------------------------------------------------" << ";\n";              
         
         outSettings << "                               var         facing_UP_constantAttenuation             =  "    << facing_UP_constantAttenuation << ";\n";                        
         outSettings << "                               var         facing_UP_linearAttenuation               =  "    << facing_UP_linearAttenuation << ";\n";            
         outSettings << "                               var         facing_UP_quadraticAttenuation            =  "    << facing_UP_quadraticAttenuation << ";\n\n";
         
         
         outSettings << "                               var         knight_POSITION[]                         =  {"   << knight_POSITION[0]    << ", "
                                                                                                                      << knight_POSITION[1]    << ", "
                                                                                                                      << knight_POSITION[2]    << ", "         
                                                                                                                      << "0.0};\n\n";      
      
         outSettings << "                               var         gaussianBlurHorizontalPass_POSITION[]                              =  {"   << gaussianBlurHorizontalPass_POSITION[0]    << ", "
                                                                                                                      << gaussianBlurHorizontalPass_POSITION[1]    << ", "
                                                                                                                      << gaussianBlurHorizontalPass_POSITION[2]    << ", "         
                                                                                                                      << "0.0};\n\n";      
            
         outSettings << "                               var         matchColorModelToShadowPosition[]         =  {"   << matchColorModelToShadowPosition[0]    << ", "
                                                                                                                      << matchColorModelToShadowPosition[1]    << ", "
                                                                                                                      << matchColorModelToShadowPosition[2]    << ", "         
                                                                                                                      << "0.0};\n\n";      
            
         
        outSettings << "                               var         adjustNearFar[]                           =  {"    << adjustNearFar[0]    << ", "
                                                                                                                      << adjustNearFar[1]    << ", "
                                                                                                                      << "};\n\n\n";            
        
        outSettings << "                               var         rotateModelWithLeftMouse[]                =  {"    << rotateModelWithLeftMouse[0]    << ", "
                                                                                                                      << rotateModelWithLeftMouse[1]    << ", "
                                                                                                                      << "};\n\n\n";            
        
        
         outSettings << "                               var         adjustModelViewFor_CSM_UP                 =  "    << adjustModelViewFor_CSM_UP << ";\n\n\n";           
         outSettings << "            //-------------------------------------------------------------------------------------------" << ";\n";
         outSettings << "            //-------------------------------------------------------------------------------------------" << "\n";    
         //---------------------------------------------------------------------------------------------------------------------------------  
 
         outSettings << "        var         rotateModelWithLeftMouse[]        =  {"   << rotateModelWithLeftMouse[0] << ", "
                                                                                       << rotateModelWithLeftMouse[1] << ", "
                                                                                       << "0.0, 0.0};\n\n";  
         //--------------------------------------------------------------------------------------------------------------------------------             //------------------------------------------------------------------------------------------------------------------------------
             outSettings << "var         eyeposition_SHADOW[]    =  {"   << eyeposition_SHADOW[0] << ", "
                                                                         << eyeposition_SHADOW[1] << ", "
                                                                         << eyeposition_SHADOW[2] << ", 1.0};\n";                
             //------------------------------------------------------------------------------------------------------------------------------ 
             outSettings << "var         eyeposition[]    =  {"   << eyeposition[0] << ", "
                                                                  << eyeposition[1] << ", "
                                                                  << eyeposition[2] << ", 1.0};\n";                
             //------------------------------------------------------------------------------------------------------------------------------      
      
             outSettings << "var         lookAt_SHADOW[]         =  {"   << lookAt_SHADOW[0] << ", "
                                                                    << lookAt_SHADOW[1] << ", "
                                                                    << lookAt_SHADOW[2] << ", 1.0};\n\n";                
             //------------------------------------------------------------------------------------------------------------------------------      
      
                //--------------------------------------------------------------------------------------------------------------------------              
        
       }
       //----------------------------------------------      
     
    //=======================================================================================                                           
    if (keys[VK_TAB] && TAB_KEY_RESET && !keys[VK_SHIFT])                                                                                                                   
    {                                                                                                                                   
             groupSelection          +=  1;                                                                         
             TAB_KEY_RESET           = false;
    }   
    if (!keys[VK_TAB])                                                                                                                   
    {                                                                                                                                   
             TAB_KEY_RESET           = true;
    }    
    
    if (keys[VK_TAB] && TAB_KEY_RESET && keys[VK_SHIFT])                                                                                                                   
    {                                                                                                                                   
             groupSelection         -=  1;                                                                         
             TAB_KEY_RESET           = false;
    }   
    if (!keys[VK_TAB])                                                                                                                   
    {                                                                                                                                   
             TAB_KEY_RESET           = true;
    }     
    
 
//=======================================================================================
    if (keys['A'] && !keys[VK_SHIFT])
	{
          eyeposition[0] += 0.05;
          //lookAt[0]      -= 0.05;
    }	
//-----------------------------------     
    if (keys['D'] && !keys[VK_SHIFT])
	{
          eyeposition[0] -= 0.05;
          //lookAt[0]      += 0.05;    
    }
//=================================== 
    if (keys['S'] && !keys[VK_SHIFT])
	{
          eyeposition[1] += 0.05;
          //lookAt[1]      -= 0.05;   
    }
//-----------------------------------	
    if (keys['W'] && !keys[VK_SHIFT])
	{
          eyeposition[1] -= 0.05;       
          //lookAt[1]      += 0.05;    
//-----------------------------------  
    }    
    if (keys['Q'] && !keys[VK_SHIFT])
	{
          eyeposition[2] += 0.05;      
          //lookAt[2]       -= 0.05;     
    }
//===================================   
    if (keys['E'] && !keys[VK_SHIFT])
	{
          eyeposition[2] -= 0.05;
          //lookAt[2]      += 0.05;     
    }
//===================================  	

//=======================================================================================
//=======================================================================================
    if (keys['A'] && keys[VK_SHIFT])
	{
          lookAt[0]    += 0.05;
    }	
//-----------------------------------     
    if (keys['D'] && keys[VK_SHIFT])
	{
          lookAt[0]    -= 0.05;
    }
//=================================== 
    if (keys['S'] && keys[VK_SHIFT])
	{
          lookAt[1] += 0.05;
    }
//-----------------------------------	
    if (keys['W'] && keys[VK_SHIFT])
	{
          lookAt[1] -= 0.05;       
    }    
//===================================   
    if (keys['Q'] && keys[VK_SHIFT])
	{
          lookAt[2] += 0.05;      
    }
//-----------------------------------  	
    if (keys['E'] && keys[VK_SHIFT])
	{
          lookAt[2] -= 0.05;
    }
//=======================================================================================
     
}//_END_ProcessKeyboard()



//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################
//#####################################################################################################################################



void shutDownGL( void )
{
        
        //====================================================================================  
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_Shutdown.cpp"                                                               
        //====================================================================================                                          
        

     
}


//===================================================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//===================================================================================================================================================================



