   
//-----------------------------------------------------------------                     
GLfloat     centerPiller_LIGHT_POSITION_01[]   =  {  2.0, 15.0, 30.0, 1.0};   
GLfloat     centerPiller_SHININESS             =    80.0;                     
GLfloat     centerPiller_ATTENUATION           =     1.0;                     
//-----------------------------------------------------------------                     
GLuint      centerPiller_VBO;                                                 
GLuint      centerPiller_INDICES_VBO;                                         
//-----------------------------------------------------------------                     
GLuint      centerPiller_NORMALMAP;                                           
GLuint      centerPiller_TEXTUREMAP;                                          


//-------------------------------------- 
GLuint      centerPiller_SHADER_VERTEX;                                                                                                      
GLuint      centerPiller_SHADER_FRAGMENT;                                                                                                    
GLuint      centerPiller_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_centerPiller;                                                                                              
GLuint      UNIFORM_LIGHT_MATRIX_centerPiller;                                                                                               
GLuint      UNIFORM_textureMatrix_centerPiller;                                                                                                      
GLuint      UNIFORM_LIGHT_POSITION_01_centerPiller;                                                                                          
GLuint      UNIFORM_SHININESS_centerPiller;                                                                                                  
GLuint      UNIFORM_ATTENUATION_centerPiller;
//--------------------------------------
GLuint      UNIFORM_TEXTURE_SHADOW_centerPiller;                                                                                                    
GLuint      UNIFORM_TEXTURE_DOT3_centerPiller;                                                                                               
GLuint      UNIFORM_TEXTURE_centerPiller;
