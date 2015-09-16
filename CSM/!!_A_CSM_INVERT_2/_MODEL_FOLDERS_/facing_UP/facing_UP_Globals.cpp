GLuint      facing_UP_SHADER_VERTEX;                                                                                                      
GLuint      facing_UP_SHADER_FRAGMENT;                                                                                                    
GLuint      facing_UP_SHADER;                                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_MODELVIEWPROJ_facing_UP;   
GLuint      UNIFORM_MODELVIEW_facing_UP;                                                                                             
GLuint      UNIFORM_LIGHT_MATRIX_facing_UP;  
                                                                                             
//--------------------------------------                                                                                                  
GLuint      UNIFORM_LIGHT_POSITION_01_facing_UP;                                                                                          
GLuint      UNIFORM_SHININESS_facing_UP;                                                                                                  
GLuint      UNIFORM_ATTENUATION_facing_UP;  
GLuint      UNIFORM_zDirBias_facing_UP;                                                                                                
GLuint      UNIFORM_TEXTURE_HEIGHT_facing_UP;
GLuint      UNIFORM_TEXTURE_DOT3_facing_UP;
GLuint      UNIFORM_TEXTURE_facing_UP;                                                                                                    
//--------------------------------------                                                                                                  
GLfloat     facing_UP_POSITION[]            =  {  0.0, 0.0,  0.0, 1.0};                                                                    
GLfloat     facing_UP_ROTATE[]              =  {  0.0, 1.0,  0.0, 0.0};                                                                   
GLfloat     facing_UP_SCALE[]               =  {  1.0, 1.0,  1.0, 1.0};                                                                   

//============================================================================== 
//==============================================================================                                                                      
  //__DPHOWARE_below
var         facing_UP_LIGHT_POSITION_01[]            =  {40.31, 55.1199, 40, 1.0};

var         facing_UP_ATTENUATION            =  1.03;
var         zDirectionBias              =  274.219;
var         facing_UP_SHININESS              =  0.24;



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
