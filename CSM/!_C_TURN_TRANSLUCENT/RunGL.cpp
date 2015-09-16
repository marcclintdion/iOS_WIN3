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





//------------------------------------
GLuint fbo, color, depth, mainLightPass_fboId, mainLightPass_depth, textureID, shadow_2D_ID, fboId;
GLuint componentShaderPass_fbo, componentShaderPass_color, componentShaderPass_depth;
//------------------------------------
//===============================================================================================================================                                          
GLfloat     frameBufferPlane_SCALE[]                                                    =  { 1.84778, 1.0,  1.0, 1.0};   
#include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Globals.cpp"        
//===============================================================================================================================  
GLuint      UNIFORM_screenRatio_frameBufferPlane_GaussianVertical;  
GLfloat     screenRatio;
//------------------------------------------  
GLuint      gaussianBlurHorizontal_TEXTURE, gaussianBlurVertical_TEXTURE, mainLightPass_TEXTURE, geometryLightPass_TEXTURE;
GLfloat     frameBufferPlane_GaussianHorizontal_blurRadius                              =   0.00060001; 
GLfloat     frameBufferPlane_GaussianVertical_blurRadius                                =   0.00060001 ; 
#include "_MODEL_FOLDERS_/frameBufferPlane/gaussianBlur_GLOBALS.cpp"        
//================================================================================================================================ 
 
//####################################################################################################################
var           fieldOfView                                        =     35.0;

//------------------
//@70.0 = 0.241004;
//@70.0 =  1.73;
//------------------
//@70.0 = 0.221004;
//@70.0 = 1.52;
//------------------------------------------------------------------------------
GLsizei       resize_SHADOW_FBO = 2;
GLsizei       resize_LIGHTS_FBO = 2;

var           adjustNearFar[]                                  =  {  0.1, 300.0 };
//------------------------------------------------------------------------------
var           moveShadow[]                                     =  { -0.01, 0.2, -0.839999, 0.0};
var           matchColorModelToShadowPosition[]                =  { -0.79, -0.31, 0.02, 0.0};
//------------------------
var           moveSet[]                                        =  {  0.0, 0, 25.0, 1.0};
//---------------------------------------------------------------------------------------
var           eyeposition[]      =  {0, 3.4, 37.95, 0.0};
var           lookAt[]           =  {0, -2.8, 0, 0.0};
var           rotateModelWithLeftMouse[]           =  {4.90001, 0.0};


//------------------------
var           turnTable                                        =   -00.0;
//------------------------------------------------------------------------------
var           radius_Of_eyePosition_LookAt                     =    40.0;
var           Scale_X_ofLookAtForShadow                        =     1.0;

//------------------------------------------------------------------------------
var           upVector[]             	                       =  {  0.0, 1.0, 0.0};
//------------------------------------------------------------------------------

var           eyeposition_SHADOW[]      =  {0.3, 0.0800003, 0.25, 1.0};
var           lookAt_SHADOW[]           =  {-0.15, -0.599999, -14.2498, 1.0};

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
var     ProjectionShadow[16];
var     LightModelViewMatrix[16];


float   modelWorld[16];
float   LightView[16];
float   LightProjection[16];
float   modelViewInverse[16];

float   tempMatrix[16];

var     textureMatrix[16] = {0.5f, 0.0f, 0.0f, 0.0f,
						  0.0f, 0.5f, 0.0f, 0.0f,
						  0.0f, 0.0f, 0.5f, 0.0f,
						  0.5f, 0.5f, 0.5f, 1.0f};

var     inverseMatrix[16];


//===============================================================================================================================
                               

//######################################################################################################################
                                   
                               var groupSelection       =    1.0;                           
                               var select_POSITION[]    = {  0.0, 0.0, 0.0, 0.0};
                               var spinModel            =    0.0;
                               //---------------------------------------------------- 
                               var lightPosition[]      = {  0, 10, 10};
                               var lightLookAt[]        = { 0, 0, -10};                               
                               
                               //====================================================================================                                          
                               #include "_SHADERS/plastic/rubber/rubber_GLOBALS.cpp"    
                               //====================================================================================                               
                               
                               GLfloat       globalLinearAttenuation                                   =     0.09;
                                                    
                               GLfloat       lightPositionMultiplier[]                                 =  {  1.0, 1.0, 1.0, 1};
                               GLfloat       goldenSunset_LIGHT_POSITION_01[]                         =  {-0.999999, 24.401, 14.801, 0.0};
                               GLfloat       ambient_goldenSunset                                      =     0.451993;   
                               #include     "_SHADERS/BACKGROUND/goldenSunset_GLOBALS.cpp"
                               //--------------------------------------------------------                               
                               var           facing_UP_LIGHT_POSITION_01[]                             =  {2.5, 24.401, 17.701, 0.0};
                               
                               var         facing_UP_SHININESS                  =  0.261004;

                               var         facing_UP_constantAttenuation        =  .8;
                               var         facing_UP_linearAttenuation          =  0.385;
                               var         facing_UP_quadraticAttenuation       =  0.063;
                               
                               var           adjustModelViewFor_CSM_UP                                 =    30.2501; 
                               
                               var           zDirectionBias                                            =   274.219;
                               //----------
                               #include     "_MODEL_FOLDERS_/facing_UP/facing_UP_Globals.cpp"                                                                
                               //====================================================================================  
                               var           facing_VIEW_LIGHT_POSITION_01[]                             =  {-10.8, 47.1001, 37.601, 0.0};
                               
                               var         facing_VIEW_SHININESS                  =  0.261004;

                               var         facing_VIEW_constantAttenuation        =  1.57;
                               var         facing_VIEW_linearAttenuation          =  0.385;
                               var         facing_VIEW_quadraticAttenuation       =  0.063;
                               
                               var           adjustModelViewFor_CSM_VIEW                                 =    30.2501; 
                               
                               //====================================================================================                                          
                               #include     "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_Globals.cpp"                                                                
                               //====================================================================================                                          
                               GLfloat       velocityIncreaseRotation_1                                =    1.0;
                               GLfloat       velocitySwap_1[]                                          = {  0.0, 0.0, 0.0, 0.0};
                               #include     "ADD_COLLISION_BALL/GLOBALS_1.cpp"
                               //---------------------------------------------
                               #include     "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Globals.cpp"                                                          
                               //====================================================================================
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
                               GLfloat     centerPiller_POSITION[]            =  {0, 2.0, -38, 0.0};     
                               GLfloat     centerPiller_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};    
                               GLfloat     centerPiller_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                
                               #include "_MODEL_FOLDERS_/centerPiller/centerPiller_Globals.cpp"                                                                
                               //====================================================================================                                          
                               var         lightSpheres_LIGHT_POSITION_01[]       =  {4.04, 0.01, 10.701, 0.0};
                               var         lightSpheres_SHININESS                  =  0.261004;
                               var         lightSpheres_constantAttenuation        =  .8;
                               var         lightSpheres_linearAttenuation          =  0.385;
                               var         lightSpheres_quadraticAttenuation       =  0.063;
                               //--------------------------------------                                                                                                  
                               GLfloat     lightSpheres_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};                                                                   
                               GLfloat     lightSpheres_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                   
                               //--------------------------------------
                               #define     numberOfGeometryLights 1000
                               GLfloat     lightSpheres_POSITION_ARRAY[numberOfGeometryLights][3]; 
                               GLfloat     lightSpheres_VELOCITY_ARRAY[numberOfGeometryLights][3];                              
                               GLfloat     lightSpheres_ROTATION_ARRAY[numberOfGeometryLights][4];                               
                               
                               #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Globals.cpp"                                                                
                               //====================================================================================                             



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
    glReadBuffer(GL_NONE);//_THIS_MAY_BE_OPTIONAL
	#endif
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, shadowMap_2D, 0);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    //------------------------
	glEnable( GL_DEPTH_TEST );
    glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);       
    //#####################################################################################################################     
    //#####################################################################################################################        
                                                       
    //====================================================================================================================
    //#####################################################################################################################     
    //#####################################################################################################################      
    glGenFramebuffersEXT(1, &geometryLightPass_fboId);    
    glGenTextures(1, &geometryLightPass_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, geometryLightPass_TEXTURE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth / resize_LIGHTS_FBO, (GLsizei)viewHeight / resize_LIGHTS_FBO, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);  
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, geometryLightPass_fboId);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, geometryLightPass_TEXTURE, 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    //====================================================================================================================   
             srand(time(0));
  
             float randomVelocity[]    = {0.0, 0.0, 0.0};  
             float randomGravity       =  0.0;  

             for(int i = 0; i < numberOfGeometryLights; i++)    
             {    
                 lightSpheres_POSITION_ARRAY[i][0]     =  float((rand()% 10) - 5) *1.1; 
                 lightSpheres_POSITION_ARRAY[i][1]     =  float((rand()% 10) - 5) *1.1;              
                 lightSpheres_POSITION_ARRAY[i][2]     =  float((rand()% 10) - 5) *1.1;                 
                 //--------------------------------------------------------------------
                 lightSpheres_VELOCITY_ARRAY[i][0]     =  float((rand()% 10) - 5) *.002; 
                 lightSpheres_VELOCITY_ARRAY[i][1]     =  float((rand()% 10) - 5) *.002;              
                 lightSpheres_VELOCITY_ARRAY[i][2]     =  float((rand()% 10) - 5) *.002;              
                 //--------------------------------------------------------------------
                 lightSpheres_ROTATION_ARRAY[i][0]     =  float((rand()% 10) - 5) *.002; 
                 lightSpheres_ROTATION_ARRAY[i][1]     =  float((rand()% 10) - 5) *.002;              
                 lightSpheres_ROTATION_ARRAY[i][2]     =  float((rand()% 10) - 5) *.002;              
                 lightSpheres_ROTATION_ARRAY[i][3]     =  float((rand()% 10) - 5) *.002;
                 //--------------------------------------------------------------------
            
             }
    //-----------------------------------------------------------------    
    #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Init.cpp"                                                                   
    glGenFramebuffersEXT(1, &mainLightPass_fboId);    
    glGenTextures(1, &mainLightPass_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, mainLightPass_TEXTURE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth, (GLsizei)viewHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);  
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mainLightPass_fboId);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mainLightPass_TEXTURE, 0);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glGenRenderbuffersEXT(1, &mainLightPass_depth);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mainLightPass_depth); 
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, (GLsizei)viewWidth, (GLsizei)viewHeight);        
    //====================================================================================================================                 
    //#####################################################################################################################            
    //#####################################################################################################################      
    #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Init.cpp"                                                                   
    //====================================================================================     
    #include "_MODEL_FOLDERS_/frameBufferPlane/gaussianBlur_INIT.cpp"
    //#####################################################################################################################            
    //#####################################################################################################################         
        
   
        //====================================================================================================================                                         
        #include "_SHADERS/plastic/rubber/rubber_INIT.cpp"                                   
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
        #include "_MODEL_FOLDERS_/centerPiller/centerPiller_Init.cpp"                                                                   
        //====================================================================================                                          
                                                 
               
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
                   
                   
//turnTable += 0.00;

                  
                   
    
  

 
//====================================================================================================================================================         
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
//====================================================================================================================================================   
         



        #include "runDepth_FBO.cpp"   
                    
//====================================================================================================================================================         
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
///////////////________FRAMEBUFFER_SHADOWS_BEGINS_HERE_______@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE________@_______FRAMEBUFFER_SHADOWS_BEGINS_HERE__
//====================================================================================================================================================    


//####################################################################################################################################################
//####################################################################################################################################################
//####################################################################################################################################################
//====================================================================================================================================================                               
///////////////=============DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO________
glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mainLightPass_fboId);
glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mainLightPass_depth);
glCullFace(GL_BACK);

#include "drawMainColor_FBO.cpp" //_DEPTH_BUFFER_CLEAR_AND_WRITES_SHOULD_BE_DISABLED,_BUT_DEPTH_MUST_STILL_BE_READABLE
//--------------------------------------------------------------------------------------------------------------------------
glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);



//####################################################################################################################################################
//####################################################################################################################################################
//####################################################################################################################################################
//====================================================================================================================================================                               

        glBindFramebuffer(GL_FRAMEBUFFER, geometryLightPass_fboId);//-----------------------F.B.O.   
        //---------------------------------
        glClearColor( 0.3, 0.3, 0.3, 1.0 );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //============================================================================================================================================
        glViewport(0, 0, (GLsizei)viewWidth / resize_LIGHTS_FBO, (GLsizei)viewHeight / resize_LIGHTS_FBO);
        PerspectiveMatrix(projection, fieldOfView, viewWidth / viewHeight, adjustNearFar[0],  adjustNearFar[1]);
        //============================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        #endif        
        //============================================================================================================================================   
        LoadIdentity(modelView);                                                                                                              
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);     
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);         
         //----------------------------------------------------------- 
        Translate(modelView,   spikyBall_0_POSITION[0], spikyBall_0_POSITION[1], spikyBall_0_POSITION[2]);      
        Rotate(modelView,      spikyBall_0_ROTATE[0], spikyBall_0_ROTATE[1], spikyBall_0_ROTATE[2], spikyBall_0_ROTATE[3]); 

        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Render.cpp" 
        //====================================================================================                                          
        //#############################################################################################################################################
        //============================================================================================================================================   
        //============================================================================================================================================     
             for(int i = 0; i < numberOfGeometryLights; i++)    
             {    
                 
                 lightSpheres_POSITION_ARRAY[i][0] += lightSpheres_VELOCITY_ARRAY[i][0];
                 lightSpheres_POSITION_ARRAY[i][1] += lightSpheres_VELOCITY_ARRAY[i][1];
                 lightSpheres_POSITION_ARRAY[i][2] += lightSpheres_VELOCITY_ARRAY[i][2]; 
                 //---------------------------------------------------------------------
                 //lightSpheres_ROTATION_ARRAY[i][0] += ;
                 //lightSpheres_ROTATION_ARRAY[i][1] += ;
                 //lightSpheres_ROTATION_ARRAY[i][2] += ; 
                 //lightSpheres_ROTATION_ARRAY[i][3] += ;                                   
                 //---------------------------------------------------------------               
                 if(lightSpheres_POSITION_ARRAY[i][0] <= -6)///wall_Collision
                 {
                       lightSpheres_VELOCITY_ARRAY[i][0] *= -1;

                 }
                 if(lightSpheres_POSITION_ARRAY[i][0] >= 6)////wall_Collision
                 {
                       lightSpheres_VELOCITY_ARRAY[i][0] *= -1;

                 }                                                        
                 //------------------------------------------------------
                 if(lightSpheres_POSITION_ARRAY[i][1] < -0.0)///wall_Collision
                 {
                       lightSpheres_VELOCITY_ARRAY[i][1] *= -1.0;

                 }
                 if(lightSpheres_POSITION_ARRAY[i][1] > 4.0)///wall_Collision
                 {
                       lightSpheres_VELOCITY_ARRAY[i][1] *= -1.0;

                 }
                 //------------------------------------------------------
                 if(lightSpheres_POSITION_ARRAY[i][2] <= -5.0)///wall_Collision
                 {
                       lightSpheres_VELOCITY_ARRAY[i][2] *= -1;

                 }
                 if(lightSpheres_POSITION_ARRAY[i][2] >= 5)////wall_Collision
                 {
                       lightSpheres_VELOCITY_ARRAY[i][2] *= -1;
                 
                 }

             }                                                   
        //=================================================================================================================================
        
        for(int i = 0; i < numberOfGeometryLights; i++)    
        {        
                LoadIdentity(modelView);                                                                                                              
                gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
                Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
                //--------------------------------------------------------------
                Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
                Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
                Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);     
                //--------------------------------------------------------------
                Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);         
                //-------------------------------------------------------------- 
                Translate(modelView,   lightSpheres_POSITION_ARRAY[i][0], lightSpheres_POSITION_ARRAY[i][1], lightSpheres_POSITION_ARRAY[i][2]);      
                Rotate(modelView,      lightSpheres_ROTATION_ARRAY[i][0], lightSpheres_ROTATION_ARRAY[i][1], lightSpheres_ROTATION_ARRAY[i][2], lightSpheres_ROTATION_ARRAY[i][3]++); 
                //====================================================================================                                          
                #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Render.cpp" 
                //====================================================================================                                          
        
        }

                                               
//====================================================================================                                          
glBindFramebuffer(GL_FRAMEBUFFER, 0);
//==================================================================================== 

//*******************************************************************************************************************************************       
//*******************************************************************************************************************************************        
//*******************************************************************************************************************************************         
        
        glActiveTexture (GL_TEXTURE0);                                                                                                                                            
        glBindTexture(GL_TEXTURE_2D, geometryLightPass_TEXTURE);         
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianHorizontal_Render.cpp"                                                                 
        //-------------------------------------------------------------------------------------                                
        glActiveTexture (GL_TEXTURE0);                                                                                                                                            
        glBindTexture(GL_TEXTURE_2D, gaussianBlurHorizontal_TEXTURE);         
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_GaussianVertical_Render.cpp"  

                                                                  
//*******************************************************************************************************************************************       
//*******************************************************************************************************************************************        
//*******************************************************************************************************************************************         



///////////////=============DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO=============##===========DRAW_MAIN_COLOR_FBO________                            
//====================================================================================================================================================
//####################################################################################################################################################
//####################################################################################################################################################
//####################################################################################################################################################


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                                           
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++           
//====================================================================================                                          
      
        glActiveTexture (GL_TEXTURE1);                                                                                                                                            
        glBindTexture(GL_TEXTURE_2D, gaussianBlurVertical_TEXTURE);         
        glActiveTexture (GL_TEXTURE0);                                                                                                                                            
        glBindTexture(GL_TEXTURE_2D, mainLightPass_TEXTURE);   
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Render.cpp"                                                                 

//====================================================================================   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++                                           
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++           


        #ifdef __APPLE__    
            glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
        #endif 
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
             knight_POSITION[0]         +=  0.05;                                                                            
    }                                                                                                                                   
    if (keys[VK_NUMPAD4])                                                                                                                   
    {                                                                                                                                   
             knight_POSITION[0]         -=  0.05;                                                                         
    }    
    if (keys[VK_NUMPAD8])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[1]         +=  0.05;                                                                            
    }	                                                                                                                                  
    if (keys[VK_NUMPAD2])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[1]         -=  0.05;                                                                            
    }                                                                                                                                   
    if (keys[VK_NUMPAD7])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[2]         +=  0.05;                                                                            
    }	                                                                                                                                  
    if (keys[VK_NUMPAD9])                                                                                                                      
    {	                                                                                                                                  
             knight_POSITION[2]         -=  0.05;      
    }	                                                                                                                                  
   //=======================================================================================  
    if (keys['L'] && !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             lightSpheres_LIGHT_POSITION_01[0]         +=  1.01;                                                                            
    }                                                                                                                                   
    if (keys['J'] && !keys[VK_SHIFT])                                                                                                                   
    {                                                                                                                                   
             lightSpheres_LIGHT_POSITION_01[0]         -=  1.01;                                                                         
    }    
    if (keys['I'] && !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             lightSpheres_LIGHT_POSITION_01[1]         +=  1.01;                                                                            
    }	                                                                                                                                  
    if (keys['K'] && !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             lightSpheres_LIGHT_POSITION_01[1]         -=  1.01;                                                                            
    }                                                                                                                                   
    if (keys['O'] && !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             lightSpheres_LIGHT_POSITION_01[2]         +=  1.01;                                                                          
    }	                                                                                                                                  
    if (keys['U'] && !keys[VK_SHIFT])                                                                                                                      
    {	                                                                                                                                  
             lightSpheres_LIGHT_POSITION_01[2]         -=  1.01;      
    }
    //======================================================================================
    
    if (keys['M'] && keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             frameBufferPlane_GaussianHorizontal_blurRadius                   +=  0.0001;                                                                            
             frameBufferPlane_GaussianVertical_blurRadius                       +=  0.0001;  
    }	                                                                                                                                  
    if (keys['N'] && keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             frameBufferPlane_GaussianHorizontal_blurRadius                   -=  0.0001;                                                                            
             frameBufferPlane_GaussianVertical_blurRadius                      -=  0.0001;  
    }  
    //=======================================================================================        
    if (keys['M'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             lightSpheres_constantAttenuation                   +=  0.01;                                                                            
    }	                                                                                                                                  
    if (keys['N'] && !keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
            lightSpheres_constantAttenuation                   -=  0.01;                                                                            
    }     
    //----------------------------------------------------------------
    if (keys['M'] && keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
          //   facing_UP_linearAttenuation                     +=  0.005;                                                                            
    }	                                                                                                                                  
    if (keys['N'] && keys[VK_SHIFT] && !keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
           //  facing_UP_linearAttenuation                     -=  0.005;                                                                            
    }  
    //----------------------------------------------------------------    
    if (keys['M'] && !keys[VK_SHIFT] && keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
              facing_UP_quadraticAttenuation                 +=  0.001;                                                                            
    }	                                                                                                                                  
    if (keys['N'] && !keys[VK_SHIFT] && keys[VK_CONTROL])                                                                                                                      
    {	                                                                                                                                  
             facing_UP_quadraticAttenuation                  -=  0.001;                                                                            
    }  
    //----------------------------------------------------------------

    if (keys['X'])                                                                                                                      
    {	                                                                                                                                  
            facing_UP_SHININESS                    +=  0.005;                                                                            
    }	                                                                                                                                  
    if (keys['Z'])                                                                                                                      
    {	                                                                                                                                 
            facing_UP_SHININESS                    -=  0.005;                                                                            
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
         outSettings << "var         frameBufferPlane_SCALE[]             =  {"   << frameBufferPlane_SCALE[0] << ", "
                                                                                       << frameBufferPlane_SCALE[1] << ", "
                                                                                       << frameBufferPlane_SCALE[2] << ", 1.0};\n\n";            
         outSettings << "            //-------------------------------------------------------------------------------------------" << ";\n";              
        
         outSettings << "                               var         facing_UP_SHININESS                  =  "    << facing_UP_SHININESS    << ";\n\n";   
         
         outSettings << "                               var         frameBufferPlane_GaussianHorizontal_blurRadius        =  "    << frameBufferPlane_GaussianHorizontal_blurRadius << ";\n";                        
         outSettings << "                               var         lightSpheres_constantAttenuation        =  "    << lightSpheres_constantAttenuation << ";\n";
         
         outSettings << "                               var         facing_UP_linearAttenuation          =  "    << facing_UP_linearAttenuation << ";\n";            
         outSettings << "                               var         facing_UP_quadraticAttenuation       =  "    << facing_UP_quadraticAttenuation << ";\n\n";
         
         
         outSettings << "                               var         knight_POSITION[]                    =  {"   << knight_POSITION[0]    << ", "
                                                                                                                      << knight_POSITION[1]    << ", "
                                                                                                                      << knight_POSITION[2]    << ", "         
                                                                                                                      << "0.0};\n\n";      
      
         outSettings << "                               var         lightSpheres_LIGHT_POSITION_01[]                            =  {"   << lightSpheres_LIGHT_POSITION_01[0]    << ", "
                                                                                                                      << lightSpheres_LIGHT_POSITION_01[1]    << ", "
                                                                                                                      << lightSpheres_LIGHT_POSITION_01[2]    << ", "         
                                                                                                                      << "0.0};\n\n";      
            
         outSettings << "                               var         matchColorModelToShadowPosition[]    =  {"   << matchColorModelToShadowPosition[0]    << ", "
                                                                                                                      << matchColorModelToShadowPosition[1]    << ", "
                                                                                                                      << matchColorModelToShadowPosition[2]    << ", "         
                                                                                                                      << "0.0};\n\n";      
         
        
        outSettings << "                                var         adjustNearFar[]                      =  {"    << adjustNearFar[0]    << ", "
                                                                                                                      << adjustNearFar[1]    << ", "
                                                                                                                      << "};\n\n\n";            
        
       
        
        
         outSettings << "                               var         adjustModelViewFor_CSM_UP            =   "    << adjustModelViewFor_CSM_UP << ";\n\n\n";           
         outSettings << "            //-------------------------------------------------------------------------------------------" << ";\n";
         outSettings << "            //-------------------------------------------------------------------------------------------" << "\n";    
         //---------------------------------------------------------------------------------------------------------------------------------  

             outSettings << "var           eyeposition[]      =  {"   << eyeposition[0] << ", "
                                                                      << eyeposition[1] << ", "
                                                                      << eyeposition[2] << ", 0.0};\n";                
             
             outSettings << "var           lookAt[]           =  {"   << lookAt[0] << ", "
                                                                      << lookAt[1] << ", "
                                                                      << lookAt[2] << ", 0.0};\n";             
             outSettings << "var           rotateModelWithLeftMouse[]           =  {"    << rotateModelWithLeftMouse[0]    << ", "
                                                                                       << rotateModelWithLeftMouse[1]    << ", "
                                                                                                                         << "};\n\n\n";                  
             //------------------------------------------------------------------------------------------------------------------------------      
             outSettings << "var           lightSpheres_LIGHT_POSITION_01[]      =  {"   << lightSpheres_LIGHT_POSITION_01[0] << ", "
                                                                             << lightSpheres_LIGHT_POSITION_01[1] << ", "
                                                                             << lightSpheres_LIGHT_POSITION_01[2] << ", 1.0};\n";                
             //------------------------------------------------------------------------------------------------------------------------------       
             outSettings << "var           lookAt_SHADOW[]           =  {"   << lookAt_SHADOW[0] << ", "
                                                                             << lookAt_SHADOW[1] << ", "
                                                                             << lookAt_SHADOW[2] << ", 1.0};\n\n";                
             
             
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
          turnTable += 0.1;
          //lookAt[0]      -= 0.15;
    }	
//-----------------------------------     
    if (keys['D'] && !keys[VK_SHIFT])
	{
          turnTable -= 0.1;
          //lookAt[0]      += 0.15;    
    }
//=================================== 
    if (keys['S'] && !keys[VK_SHIFT])
	{
          eyeposition[1] += 0.15;
          //lookAt[1]      -= 0.15;   
    }
//-----------------------------------	
    if (keys['W'] && !keys[VK_SHIFT])
	{
          eyeposition[1] -= 0.15;       
          //lookAt[1]      += 0.15;    
//-----------------------------------  
    }    
    if (keys['Q'] && !keys[VK_SHIFT])
	{
          eyeposition[2] += 0.15;      
          //lookAt[2]       -= 0.15;     
    }
//===================================   
    if (keys['E'] && !keys[VK_SHIFT])
	{
          eyeposition[2] -= 0.15;
          //lookAt[2]      += 0.15;     
    }
//===================================  	

//=======================================================================================
//=======================================================================================
    if (keys['A'] && keys[VK_SHIFT])
	{
          lookAt_SHADOW[0]    += 0.15;
    }	
//-----------------------------------     
    if (keys['D'] && keys[VK_SHIFT])
	{
          lookAt_SHADOW[0]    -= 0.15;
    }
//=================================== 
    if (keys['S'] && keys[VK_SHIFT])
	{
          lookAt_SHADOW[1] += 0.15;
    }
//-----------------------------------	
    if (keys['W'] && keys[VK_SHIFT])
	{
          lookAt_SHADOW[1] -= 0.15;       
    }    
//===================================   
    if (keys['Q'] && keys[VK_SHIFT])
	{
          lookAt_SHADOW[2] += 0.15;      
    }
//-----------------------------------  	
    if (keys['E'] && keys[VK_SHIFT])
	{
          lookAt_SHADOW[2] -= 0.15;
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
        #include "_MODEL_FOLDERS_/centerPiller/centerPiller_Shutdown.cpp"                                                               
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Shutdown.cpp"                                                               
        //====================================================================================                             
   
}


//===================================================================================================================================================================
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//===================================================================================================================================================================




