
                              var           facing_VIEW_LIGHT_POSITION_01[]                           =  {2.5, 4.90094, 17.701, 0.0};
                               
                               var           facing_VIEW_SHININESS                                     =   0.261004;


                               
                               //var           adjustModelViewFor_CSM_VIEW                               =  30.2501;  

//==============================================================================                                                                      

GLuint      facing_VIEW_SHADER_VERTEX;                                                                                                      
GLuint      facing_VIEW_SHADER_FRAGMENT;                                                                                                    
GLuint      facing_VIEW_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_facing_VIEW;
GLuint      UNIFORM_SHADOW_PROJ_facing_VIEW;   
GLuint      UNIFORM_MODELVIEW_facing_VIEW;                                                                                             
GLuint      UNIFORM_LIGHT_MATRIX_facing_VIEW;  
GLuint      UNIFORM_textureMatrix_facing_VIEW;
GLuint      UNIFORM_INVERSEMATRIX_facing_VIEW;
//------------------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_facing_VIEW;                                                                                          
//------------------------------------------------  
GLuint      UNIFORM_QUADRATIC_ATTENUATION_facing_VIEW; 
GLuint      UNIFORM_LINEAR_ATTENUATION_facing_VIEW; 
GLuint      UNIFORM_CONSTANT_ATTENUATION_facing_VIEW; 
//------------------------------------------------  

GLuint      UNIFORM_SHININESS_facing_VIEW; 
GLuint      UNIFORM_offset_facing_VIEW; 
GLuint      UNIFORM_zDirBias_facing_VIEW;  
GLuint      UNIFORM_TEXTURE_SHADOW_facing_VIEW;                                                                                              
GLuint      UNIFORM_TEXTURE_HEIGHT_facing_VIEW;
GLuint      UNIFORM_TEXTURE_DOT3_facing_VIEW;
GLuint      UNIFORM_TEXTURE_facing_VIEW;
                                                                                                    
//--------------------------------------                                                                                                  
GLfloat     facing_VIEW_POSITION[]            =  {  0.0, 0.0,  0.0, 1.0};                                                                    
GLfloat     facing_VIEW_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};                                                                   
GLfloat     facing_VIEW_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                   

//============================================================================== 


//------------------------------------------------------------------------ 
//__TRISTEN_DEAN_codeSampler_below                 
  //GLfloat     facing_VIEW_LIGHT_POSITION_01[] = {2, 15, 30, 1};
  //GLfloat     facing_VIEW_ATTENUATION         =  0.001;
  //GLfloat     facing_VIEW_SHININESS           =  0.000400022;
//==============================================================================                                               
//==============================================================================       


//-----------------------------------------------------------------                                                                       
GLuint      facing_VIEW_backWall_VBO;
GLuint      facing_VIEW_backWall_INDEX_VBO;
//---------
//-----------------------------------------------------------------                                                                       

                                                                                                                 
//-----------------------------------------------------------------                                                                       
GLuint      facing_VIEW_HEIGHT; 
GLuint      facing_VIEW_NORMALMAP;                                                                                                          
GLuint      facing_VIEW_TEXTUREMAP;                                                                                                         
