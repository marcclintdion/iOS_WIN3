
                               var           facing_UP_LIGHT_POSITION_01[]                             =  {2.5, 24.401, 17.701, 0.0};
                               
                               var           facing_UP_SHININESS                                       =   1.581;

                              // var           facing_UP_constantAttenuation                             =   0.001;
                              // var           facing_UP_linearAttenuation                               =   0.385;
                              // var           facing_UP_quadraticAttenuation                            =   0.063;
                               
                               var           adjustModelViewFor_CSM_UP                                 =  30.2501; 
                               
                               var           zDirectionBias                                            = 274.219;


GLuint      facing_UP_SHADER_VERTEX;                                                                                                      
GLuint      facing_UP_SHADER_FRAGMENT;                                                                                                    
GLuint      facing_UP_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_facing_UP;  
GLuint      UNIFORM_MODELVIEW_facing_UP;                                                                                             
//----
GLuint      UNIFORM_SHADOW_PROJ_facing_UP;   
GLuint      UNIFORM_modelViewShadow_facing_UP; 
//----
GLuint      UNIFORM_viewMatrix_facing_UP; 
//----
GLuint      UNIFORM_LIGHT_MATRIX_facing_UP;  
GLuint      UNIFORM_textureMatrix_facing_UP;
GLuint      UNIFORM_INVERSEMATRIX_facing_UP;
//------------------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_facing_UP;                                                                                          
//------------------------------------------------  
GLuint      UNIFORM_QUADRATIC_ATTENUATION_facing_UP; 
GLuint      UNIFORM_LINEAR_ATTENUATION_facing_UP; 
GLuint      UNIFORM_CONSTANT_ATTENUATION_facing_UP; 
//------------------------------------------------  

GLuint      UNIFORM_SHININESS_facing_UP; 
GLuint      UNIFORM_offset_facing_UP; 
GLuint      UNIFORM_zDirBias_facing_UP;  
GLuint      UNIFORM_TEXTURE_LightMap_facing_UP;
GLuint      UNIFORM_TEXTURE_SHADOW_facing_UP;                                                                                              
GLuint      UNIFORM_TEXTURE_HEIGHT_facing_UP;
GLuint      UNIFORM_TEXTURE_DOT3_facing_UP;
GLuint      UNIFORM_TEXTURE_facing_UP;                                                                                                    
//--------------------------------------                                                                                                  
GLfloat     facing_UP_POSITION[]            =  {  0.0, 0.0,  0.0, 1.0};                                                                    
GLfloat     facing_UP_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};                                                                   
GLfloat     facing_UP_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                   

//============================================================================== 
//==============================================================================                                                                      


//------------------------------------------------------------------------ 
//__TRISTEN_DEAN_codeSampler_below                 
  //GLfloat     facing_UP_LIGHT_POSITION_01[] = {2, 15, 30, 1};
  //GLfloat     facing_UP_ATTENUATION         =  0.001;
  //GLfloat     facing_UP_SHININESS           =  0.000400022;
//==============================================================================                                               
//==============================================================================       


//-----------------------------------------------------------------                                                                       
GLuint      facing_UP_VBO;
GLuint      facing_UP_INDEX_VBO;                                                                                                                 
//-----------------------------------------------------------------                                                                       
GLuint      facing_UP_HEIGHT; 
GLuint      facing_UP_NORMALMAP;                                                                                                          
GLuint      facing_UP_TEXTUREMAP;                                                                                                         
