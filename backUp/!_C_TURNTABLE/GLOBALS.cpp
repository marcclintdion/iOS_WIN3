GLuint      fbo, 
            color, 
            depth, 
            mainLightPass_fboId, 
            mainLightPass_depth, 
            textureID, 
            fboId_3D, 
            fboId,
            componentShaderPass_fbo, 
            componentShaderPass_color, 
            componentShaderPass_depth, 
            flatten_3D_SHADOW_fboId, 
            flatten_3D_SHADOW_TEXTURE,
            processShadow_fboId,
            processShadow_TEXTURE,
            processShadow_depthFboId;


var           fieldOfView                                        =     35.0;

//---------------------------------------------------------------------------------------
GLsizei       resize_SHADOW_FBO = 1;
GLsizei       resize_LIGHTS_FBO = 4;

var           adjustNearFar[]                                  =  {  0.1, 200.0 };

//---------------------------------------------------------------------------------------
var           moveSet[]                                        =  {  0.0, 0, 25.0, 1.0};
//---------------------------------------------------------------------------------------

var           eyeposition[]      =  {0, 4.75, 39.45, 0.0};
var           lookAt[]           =  {0, -2.8, 0, 0.0};
var           rotateModelWithLeftMouse[]           =  {1.30001, 0.0, };

//---------------------------------------------------------------------------------------
var           turnTable                                        =   - 0.0;
//---------------------------------------------------------------------------------------
var           upVector[]             	                       =  {  0.0, 1.0, 0.0};
//---------------------------------------------------------------------------------------
var           moveShadow[]                                     =  {-00, -0.00, -0.00, 0.0};
var           matchColorModelToShadowPosition[]                =  { -0.0, -0.0, 0.0, 0.0};

var           eyeposition_SHADOW[]      =  {5.81004, -1.42, 4.52001, 1.0};
var           lookAt_SHADOW[]           =  {-0.43, 0, 0.19}; 

var           shadowsPositionOffset[]	                       =  {  0.5, 0.5, 0.5 };//BIAS_MATRIX
var           scaleShadows                                     =     0.5;//__________//BIAS_MATRIX

var           offset[]                                         =  { -0.0, 0.0, -0, 0.0};
var           offset_ShadowShader[]                            =  { -0.0, 0.0, -0, 0.0};

var           scaleShadowSize                                =      1.00;

var           offsetFinalShadow[]                              =  {  0, 0, 0, 0.0}; //_ADJUSTMENT_IN_THE_FINAL_COLOR_SHADER

var           scaleMoveShadows[]	                           =  {  1.0, 1.0, 1.0, 0.0};//=  {0.971, 0.937001, 1.043, 0.0};
//============================================================================================================================


GLuint        fboId_2D;
GLuint        shadowMap_2D;
#include    "_SHADERS/SHADOWS/shadows_32bit_Stride_GLOBALS.cpp" 
#include    "_SHADERS/SHADOWS/shadows_44bit_Stride_GLOBALS.cpp" 
//=========================================================================================== 

#include    "_SHADERS/SHADOWS/flatten_3D_shadow_GLOBALS.cpp" 
//===========================================================================================                                     
GLfloat      frameBufferPlane_SCALE[]                                                    =  { 1.84778, 1.0,  1.0, 1.0};   
#include    "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Globals.cpp"        
//===============================================================================================================================  
GLuint       UNIFORM_screenRatio_frameBufferPlane_GaussianVertical;  
GLfloat      screenRatio;
//------------------------------------------  
GLuint       gaussianBlurHorizontal_TEXTURE, gaussianBlurVertical_TEXTURE, mainLightPass_TEXTURE, geometryLightPass_TEXTURE;
GLfloat      frameBufferPlane_GaussianHorizontal_blurRadius                              =   0.00530001; 
GLfloat      frameBufferPlane_GaussianVertical_blurRadius                                =   0.00530001; 
#include    "_MODEL_FOLDERS_/frameBufferPlane/gaussianBlur_GLOBALS.cpp"        
//================================================================================================================================ 
                          
                              
                               //====================================================================================                                          
                               #include "_SHADERS/plastic/rubber/rubber_GLOBALS.cpp"    
                               //====================================================================================                               
                               #include "_SHADERS/wood/goldenSunset_GLOBALS.cpp"
                               //====================================================================================  
                               
                               #include "_MODEL_FOLDERS_/facing_UP/facing_UP_Globals.cpp"                                                                
                               //-----------------------------------------------------------------------------------------------------------
                               GLfloat    facing_Sideways_blocks_01_LIGHT_POSITION_01[]       =  {-9.1288, 5.2889, 1.721}; 
                                                      
                               #include "_MODEL_FOLDERS_/facing_Sideways_blocks_01/facing_Sideways_blocks_01_GLOBALS.cpp"
                               //-----------------------------------------------------------------------------------------------------------
                               #include "_MODEL_FOLDERS_/facing_UP/facing_UP_blocks_01/facing_UP_blocks_01_GLOBALS.cpp"
                               //-----------------------------------------------------------------------------------------------------------                               
                               //====================================================================================  
                               var         facing_VIEW_constantAttenuation         =  1.57198;
                               var         facing_VIEW_linearAttenuation           =  -0.2645;
                               var         facing_VIEW_quadraticAttenuation        =  0.0472;
              
                               #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_Globals.cpp"                                                                
                               //-------------------------------------------------------------
                               #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_blocks_01_Globals.cpp"                                
                               //====================================================================================
                               #include "ADD_COLLISION_BALL/GLOBALS_1.cpp"
                               //====================================================================================
                               #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/sculptris/sculptris_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/sphere/sphere_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Globals.cpp"                                                                
                               //====================================================================================                                          
                               GLfloat    knightShadowPosition[]                                =  {0, 0.18, 0, 1.0};
                               #include "_MODEL_FOLDERS_/knight/knight_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Globals.cpp"                                                                
                               //====================================================================================                             
                               #include "_MODEL_FOLDERS_/floorStraps/floorStraps_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/wallStraps/wallStraps_Globals.cpp"                                                                
                               //====================================================================================                                          
                               #include "_MODEL_FOLDERS_/blocksEdging/blocksEdging_Globals.cpp"                                                                
                               //====================================================================================   
