     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      cube_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_cube =                                                                                                        

      "    #define highp                                                                                                                        \n"                           

      "    uniform highp   vec4   light_POSITION_01;                                                                                            \n"                           
      "    uniform         mat4   mvpMatrix;                                                                                                    \n"                           
      "    uniform         mat4   mvMatrix;                                                                                                     \n"        
      "    uniform         mat4   lightMatrix;                                                                                                  \n"                           
      "    uniform         float  zDirBias;                                                                                                     \n"
      "    attribute       vec4   position;                                                                                                     \n"                           
      "    attribute       vec3   normal;                                                                                                       \n"         
      "    attribute       vec3   tangent;                                                                                                      \n"             
     
      "    attribute       vec2   texture;                                                                                                      \n"                           

      "    varying highp   vec3   column0;                                                                                                      \n"   
      "    varying highp   vec3   column1;                                                                                                      \n"   
      "    varying highp   vec3   column2;                                                                                                      \n"        
  

      "    varying highp vec4   lightPosition_PASS;                                                                                             \n"                           
      "    varying highp vec3   EyeDir;                                                                                                         \n"           
      "    varying highp vec2   varTexcoord;                                                                                                    \n"                           
                   
      "    vec3 view;                                                                                                                           \n"    

      "    void main()                                                                                                                          \n"                           
      "    {                                                                                                                                    \n"                           
      "           vec3 pos                =  normalize(vec3(mvMatrix * position));                                                              \n" 
      "           vec3 Eye                =  vec3(0.0, 0.0, 0.0) - pos;                                                                        \n" 
      "           vec3 Tangent            =  vec3(mvMatrix * vec4(tangent, 0.0));                                                               \n" 
      "           vec3 NormalTemp         =  vec3(mvMatrix * vec4(normal, 0.0));                                                                \n" 
      "           vec3 Binormal           =  cross(NormalTemp, Tangent);                                                                        \n" 
      "           EyeDir.x                =  dot(Eye, Tangent);                                                                                 \n" 
      "           EyeDir.y                =  dot(Eye, Binormal);                                                                                \n" 
      "           EyeDir.z                =  dot(Eye, NormalTemp);                                                                              \n"       
                      
     //-----------------------------------------------------------------------------------------------------------------
     
      "           column0                 =  vec3(mvpMatrix[0].xyz);                                                                            \n"   
      "           column1                 =  vec3(mvpMatrix[1].xyz);                                                                            \n"   
      "           column2                 =  vec3(mvpMatrix[2].xyz);                                                                            \n"       
      "           lightPosition_PASS      =  normalize(lightMatrix * light_POSITION_01);                                                        \n"                           

      "           varTexcoord             =  texture;                                                                                           \n"                           

      "           gl_Position             =  mvpMatrix * position;                                                                              \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      cube_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(cube_SHADER_VERTEX, 1, &vertexSource_cube, NULL);                                                                        
      glCompileShader(cube_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_cube =                                                                                                            

      " #ifdef GL_ES                                                                                               \n"                       
      " #else                                                                                                      \n"                       
      " #define highp                                                                                              \n"                       
      " #endif                                                                                                     \n"                       

      "    uniform sampler2D     Texture1;                                                                                                      \n"                       
      "    uniform sampler2D     NormalMap;                                                                                                     \n"                       
      "    uniform sampler2D     HeightMap;                                                                                                     \n"        
      "    uniform highp float   shininess;                                                                                                     \n"                       
      "    uniform highp float   attenuation;                                                                                                   \n"                       
      "    uniform highp vec4    light_POSITION_01;                                                                                             \n"    
      "    varying highp vec4    lightPosition_PASS;                                                                                            \n"                       
      "    varying highp vec3    EyeDir;                                                                                                        \n"     
      
      "    varying highp vec2    varTexcoord;                                                                                                   \n"                       

      "    varying highp   vec3   column0;                                                                                                      \n"   
      "    varying highp   vec3   column1;                                                                                                      \n"   
      "    varying highp   vec3   column2;                                                                                                      \n"        
        
      "            highp float   NdotL1;                                                                                                        \n"                       
      "            highp vec3    normal;                                                                                                        \n"                       
      "            highp vec3    NormalTex;                                                                                                     \n"                       

      "            highp float   scale;                                                                                                         \n"  
      "            highp float   bias;                                                                                                          \n"  


      "     void main()                                                                                                                         \n"                       
      "     {                                                                                                                                   \n"                       
                      
      "          vec3 tEyeDir = normalize(EyeDir);                                                                                              \n" 
      "          float tHeight = texture2D(HeightMap, varTexcoord).r * shininess + attenuation;                                                 \n" 
      "          vec2 tTexCoord = varTexcoord + (tHeight * tEyeDir.xy);                                                                         \n" 
     
     //------------------------------------------------------------------------------------------------------------------------
      "          mat3 n = mat3(column0, column1, column2);                                                                                      \n"       
                 
      "          NormalTex   =  texture2D(NormalMap,  tTexCoord).xyz;                                                                           \n"                       
      "          NormalTex             = (NormalTex - 0.5);                                                                                     \n"                       
      "          normal                =  normalize(NormalTex);                                                                             \n"      
      "          NdotL1                =  dot(normal, lightPosition_PASS.xyz);                                                        \n"                       

      //------------------------------------------------------------------------------------------------------------------------      
      
      "          gl_FragColor          =  (vec4(1.0, 1.0, 1.0, 1.0) * .1                                                                        \n"                       

      "                                +  texture2D(HeightMap, tTexCoord.xy) * NdotL1 * 0.5                                                      \n"                       

      "                                +  texture2D(HeightMap, tTexCoord.xy) * pow(NdotL1, 20.0) * vec4(2.0, 1.0, .1, 1.0) * 0.2)                \n"                       
      
      "                               ;                                                                                                         \n"
      
      "    }\n";                                                                                                                                   

 


      //---------------------------------------------------------------------                                                                         
      cube_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(cube_SHADER_FRAGMENT, 1, &fragmentSource_cube, NULL);                                                                          
      glCompileShader(cube_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(cube_SHADER, cube_SHADER_VERTEX);                                                                                              
      glAttachShader(cube_SHADER, cube_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(cube_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(cube_SHADER, 1, "normal");       
      glBindAttribLocation(cube_SHADER, 2, "tangent");  
      glBindAttribLocation(cube_SHADER, 3, "bitangent");               
      glBindAttribLocation(cube_SHADER, 4, "texture");                                                                                             
      //------------------------------------------------                                                                                              
      glLinkProgram(cube_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(cube_SHADER, cube_SHADER_VERTEX);                                                                                              
      glDetachShader(cube_SHADER, cube_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(cube_SHADER_VERTEX);                                                                                                            
      glDeleteShader(cube_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_cube                   = glGetUniformLocation(cube_SHADER,   "mvpMatrix");                                              
      UNIFORM_MODELVIEW_cube                       = glGetUniformLocation(cube_SHADER,   "mvMatrix");        
      UNIFORM_LIGHT_MATRIX_cube                    = glGetUniformLocation(cube_SHADER,   "lightMatrix");  
      UNIFORM_invertMatrix_cube                    = glGetUniformLocation(cube_SHADER,   "invertMatrix");                                                  
      UNIFORM_LIGHT_POSITION_01_cube               = glGetUniformLocation(cube_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_cube                       = glGetUniformLocation(cube_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_cube                     = glGetUniformLocation(cube_SHADER,   "attenuation");
      UNIFORM_angle_cube                           = glGetUniformLocation(cube_SHADER,   "angle");
      UNIFORM_scaleRadian_cube                     = glGetUniformLocation(cube_SHADER,   "scaleRadian");            
      UNIFORM_TEXTURE_HEIGHT_cube                  = glGetUniformLocation(cube_SHADER,   "HeightMap");                                                      
      UNIFORM_TEXTURE_DOT3_cube                    = glGetUniformLocation(cube_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_cube                         = glGetUniformLocation(cube_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"cube_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &cube_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, cube_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"cube" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &cube_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, cube_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/cube/height_map.png",             cube_HEIGHT);         
      loadTexture("_MODEL_FOLDERS_/cube/cube_DOT3.bmp",          cube_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/cube/cube.png",               cube_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "cube.cpp"                                                                                                                
      glGenBuffers(1,              &cube_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //--------------------------------------------------------------------------------------------------------------------     
      #include    "cube_INDICES.cpp" 
      glGenBuffers(1, &cube_INDEX_VBO);                       
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_INDEX_VBO);                   
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_INDICES), cube_INDICES, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);      
      //=================================================================================================================================       




