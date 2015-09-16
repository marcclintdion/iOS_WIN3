GLuint      geometryLightPass_fboId; 
GLuint      geometryLightPass_depth_fboId; 


GLuint      lightSpheres_SHADER_VERTEX;                                                                                                      
GLuint      lightSpheres_SHADER_FRAGMENT;                                                                                                    
GLuint      lightSpheres_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_lightSpheres;   
GLuint      UNIFORM_MODELVIEW_lightSpheres;                                                                                             
GLuint      UNIFORM_LIGHT_MATRIX_lightSpheres;  
GLuint      UNIFORM_textureMatrix_lightSpheres;
GLuint      UNIFORM_INVERSEMATRIX_lightSpheres;
//------------------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_lightSpheres;                                                                                          
//------------------------------------------------  
GLuint      UNIFORM_QUADRATIC_ATTENUATION_lightSpheres; 
GLuint      UNIFORM_LINEAR_ATTENUATION_lightSpheres; 
GLuint      UNIFORM_CONSTANT_ATTENUATION_lightSpheres; 
//------------------------------------------------  
GLuint      UNIFORM_SHININESS_lightSpheres; 
GLuint      UNIFORM_offset_lightSpheres; 
GLuint      UNIFORM_TEXTURE_SHADOW_lightSpheres;
GLuint      UNIFORM_TEXTURE_DOT3_lightSpheres;
GLuint      UNIFORM_TEXTURE_lightSpheres;                                                                                                    

//============================================================================== 
//==============================================================================                                                                      


  //GLfloat     lightSpheres_LIGHT_POSITION_01[] = {2, 15, 30, 1};

  //GLfloat     lightSpheres_SHININESS           =  0.000400022;
//==============================================================================                                               
//==============================================================================       


//-----------------------------------------------------------------                                                                       
GLuint      lightSpheres_VBO;
GLuint      lightSpheres_INDEX_VBO;                                                                                                                 
//-----------------------------------------------------------------                                                                       
GLuint      lightSpheres_HEIGHT; 
GLuint      lightSpheres_NORMALMAP;                                                                                                          
GLuint      lightSpheres_TEXTUREMAP;                                                                                                         