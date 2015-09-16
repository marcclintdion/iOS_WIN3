    #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      wood_B_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_wood_B =                                                                                                        

      "    #define highp                                                                                       \n"                           

      "    uniform highp vec4   light_POSITION_01;                                                             \n"                           
      "    uniform       mat4   mvpMatrix;                                                                     \n"                           
      "    uniform       mat4   lightMatrix;                                                                   \n"                           

      "    attribute     vec4   position;                                                                      \n"                           
      "    attribute     vec4   normal;                                                                        \n"      
      "    attribute     vec2   texture;                                                                       \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                            \n"                           
      "    varying highp vec3   vPosition;                                                                     \n"        
      "    varying highp vec3   vNormal;                                                                       \n"       
      "    varying highp vec2   varTexcoord;                                                                   \n"                           

      "    void main()                                                                                         \n"                           
      "    {                                                                                                   \n"                           
     
      "    vPosition =  normalize(position.xyz);                                                                          \n"
      "    vNormal   = -mvpMatrix * normal;                                                                    \n"
                                                                                                            
      
      "     lightPosition_PASS      = normalize(lightMatrix * light_POSITION_01);                              \n"                           
      "     varTexcoord             = texture;                                                                 \n"                           
      "     gl_Position             = mvpMatrix * position;                                                    \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      wood_B_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(wood_B_SHADER_VERTEX, 1, &vertexSource_wood_B, NULL);                                                                        
      glCompileShader(wood_B_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_wood_B =                                                                                                            

     
     
      " #ifdef GL_ES                                                                                                     \n"                       
      " #else                                                                                                            \n"                       
      " #define highp                                                                                                    \n"                       
      " #endif                                                                                                           \n"                       

      "    uniform sampler2D    Texture1;                                                                                \n"                       
      "    uniform sampler2D    NormalMap;                                                                               \n"                       
      "    uniform highp float  shininess;                                                                               \n"                       
      "    uniform highp float  attenuation;                                                                             \n"                       

      "    varying highp vec4   lightPosition_PASS;                                                                      \n"                       
      "    varying highp vec3   vPosition;                                                                               \n"        
      "    varying highp vec3   vNormal;                                                                                 \n"             
      "    varying highp vec2   varTexcoord;                                                                             \n"                       

      "            highp float  NdotL1;                                                                                  \n"                       
      "            highp vec3   normal;                                                                                  \n"                       
      "            highp vec3   NormalTex;                                                                               \n"                       
  

      "  float getDisplacement( float dx, float dy )                                                                     \n"   
      "  {                                                                                                               \n"   
      "  	vec2 uv = varTexcoord;                                                                                       \n"   
      "  	return texture2D( NormalMap, uv + vec2( dFdx(uv.s) * dx, dFdy(uv.t) * dy ) ).r;                              \n"   
      "  }                                                                                                               \n"   

  
      
      "     void main()                                                                                                  \n"                       
      "     {                                                                                                            \n"                       
      

//===================================================================================================================================      
//      "         NormalTex             =  texture2D(NormalMap,  varTexcoord).xyz;                                       \n"                       
//      "         NormalTex             = (NormalTex - 0.5);                                                             \n"                       
//     "          normal                =  normalize(NormalTex);                                                         \n"                       
      
     
      " 	      normal.x = -0.5 * (getDisplacement(1.0,0.0) - getDisplacement(-1.0,0.0));                              \n" 
      " 	      normal.z = -0.5 * (getDisplacement(0.0,1.0) - getDisplacement(0.0,-1.0));                              \n" 
      "       	  normal.y = 1.0 / attenuation;                                                                            \n" 
      "       	  normal = normalize(normal);                                                                            \n" 
      
      
      "         NdotL1                =  dot(normal, lightPosition_PASS.xyz);                                            \n"                       

      
      "         gl_FragColor          =  texture2D(Texture1, varTexcoord.st) * NdotL1;        \n"                       

      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      wood_B_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(wood_B_SHADER_FRAGMENT, 1, &fragmentSource_wood_B, NULL);                                                                          
      glCompileShader(wood_B_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(wood_B_SHADER, wood_B_SHADER_VERTEX);                                                                                              
      glAttachShader(wood_B_SHADER, wood_B_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(wood_B_SHADER,    0, "position");                                                                                            
      glBindAttribLocation(wood_B_SHADER,    1, "normal");       
      glBindAttribLocation(wood_B_SHADER,    2, "texture");                                                                                            
      //------------------------------------------------                                                                                              
      glLinkProgram(wood_B_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(wood_B_SHADER, wood_B_SHADER_VERTEX);                                                                                              
      glDetachShader(wood_B_SHADER, wood_B_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(wood_B_SHADER_VERTEX);                                                                                                            
      glDeleteShader(wood_B_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_wood_B                   = glGetUniformLocation(wood_B_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_wood_B                    = glGetUniformLocation(wood_B_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_wood_B               = glGetUniformLocation(wood_B_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_wood_B                       = glGetUniformLocation(wood_B_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_wood_B                     = glGetUniformLocation(wood_B_SHADER,   "attenuation");                                              
      UNIFORM_TEXTURE_DOT3_wood_B                    = glGetUniformLocation(wood_B_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_wood_B                         = glGetUniformLocation(wood_B_SHADER,   "Texture1");                                   
