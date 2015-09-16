GLuint      capsule_SHADER_VERTEX;                                                                                                      
GLuint      capsule_SHADER_FRAGMENT;                                                                                                    
GLuint      capsule_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_capsule;                                                                                              
GLuint      UNIFORM_LIGHT_MATRIX_capsule;                                                                                               
//--------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_capsule;                                                                                          
GLuint      UNIFORM_SHININESS_capsule;                                                                                                  
GLuint      UNIFORM_ATTENUATION_capsule;                                                                                                  
GLuint      UNIFORM_TEXTURE_DOT3_capsule;                                                                                               
GLuint      UNIFORM_TEXTURE_capsule;                                                                                                    
//--------------------------------------                                                                                                  
GLfloat     capsule_POSITION[]            =  {0.74, 1.07, 0, 1.0};                                                                  
GLfloat     capsule_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};                                                                   
GLfloat     capsule_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                   
//-----------------------------------------------------------------                                                                       
GLfloat     capsule_LIGHT_POSITION_01[]   =  {  2.0, 15.0, 30.0, 1.0};                                                                  
GLfloat     capsule_SHININESS             =    80.0;                                                                                    
GLfloat     capsule_ATTENUATION           =     1.0;                                                                                    
//-----------------------------------------------------------------                                                                       
GLuint      capsule_VBO;                                                                                                                
//-----------------------------------------------------------------                                                                       
GLuint      capsule_NORMALMAP;                                                                                                          
GLuint      capsule_TEXTUREMAP;                                                                                                         
