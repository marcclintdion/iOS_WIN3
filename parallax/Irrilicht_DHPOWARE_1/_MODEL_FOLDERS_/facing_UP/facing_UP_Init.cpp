     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      facing_UP_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_facing_UP =                                                                                                        

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
      facing_UP_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(facing_UP_SHADER_VERTEX, 1, &vertexSource_facing_UP, NULL);                                                                        
      glCompileShader(facing_UP_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_facing_UP =                                                                                                            

      " #ifdef GL_ES                                                                                                                            \n"                       
      " #else                                                                                                                                   \n"                       
      " #define highp                                                                                                                           \n"                       
      " #endif                                                                                                                                  \n"                       

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
                      
      //"          vec3 tEyeDir = normalize(EyeDir);                                                                       \n" 
      //"          float tHeight = texture2D(HeightMap, varTexcoord).r * shininess + attenuation;                          \n" 
      //"          vec2 tTexCoord = varTexcoord + (tHeight * tEyeDir.xy);                                                  \n" 
      
      "            vec3 tEyeDir = normalize(EyeDir);                                                                       \n"       
      "            float height = texture2D(HeightMap, varTexcoord).r;                                                     \n" 
      "            height = height * shininess + attenuation;                                                              \n" 
      "            vec2 tTexCoord = varTexcoord + (height * tEyeDir.xy);                                                      \n" 
     
     //------------------------------------------------------------------------------------------------------------------------
      "          mat3 n = mat3(column0, column1, column2);                                                                 \n"       
                 
      "          NormalTex   =  texture2D(NormalMap,  tTexCoord).xyz;                                                      \n"                       
      "          NormalTex             = (NormalTex - 0.5);                                                                \n"                       
      "          normal                =  normalize(NormalTex);                                                            \n"      
      "          NdotL1                =  dot(normal, lightPosition_PASS.xyz);                                             \n"                       

      //------------------------------------------------------------------------------------------------------------------------      
      
      "          gl_FragColor          =  (vec4(1.0, 1.0, 1.0, 1.0) * 0.1                                                         \n"                       

      "                                +  texture2D(Texture1, tTexCoord.xy) * NdotL1 * 0.5                                        \n"                       

      "                                +  texture2D(Texture1, tTexCoord.xy) * pow(NdotL1, 20.0) * vec4(1.0, .5, .1, 1.0) * 0.2)  \n"                       
      
      "                                ;                                                                                          \n"
      
      "    }\n";                                                                                                                                   

    
/*   
      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      facing_UP_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_facing_UP =                                                                                                        

      "    #define highp                                                                                       \n"                           

      "    uniform highp   vec4   light_POSITION_01;                                                           \n"                           
      "    uniform         mat4   mvpMatrix;                                                                   \n"                           
      "    uniform         mat4   lightMatrix;                                                                 \n"                           

      "    attribute       vec4   position;                                                                    \n"                           
      "    attribute       vec3   normal;                                                                      \n"         
      "    attribute       vec3   tangent;                                                                     \n"             
      "    attribute       vec2   texture;                                                                     \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                            \n"                           

      "    varying highp vec3   EyeDir;                                                                        \n"   
      "    varying highp vec2   varTexcoord;                                                                   \n"                           

      "    vec3 view;                                                                                          \n"    

      "    void main()                                                                                         \n"                           
      "    {                                                                                                   \n"                           
      
      "        vec3 m_Tangent = -vec3(mvpMatrix * vec4(tangent, 0.0));                                          \n" 
      "        vec3 m_Normal  = -vec3(mvpMatrix * vec4(normal, 0.0));                                            \n" 
      
      "        vec3 m_BiNormal = cross(m_Normal, m_Tangent);                                                    \n"  
  
      "        vec3 m_Vector = (lightMatrix * position).xyz;                                                     \n" 

      "        vec3  dirEye   = vec3(0.0, 0.0, 0.0) - m_Vector;                                                \n" 
                                              
      "        EyeDir.x = dot(m_Tangent, dirEye);                                                              \n" 
      "        EyeDir.y = dot(m_BiNormal , dirEye);                                                           \n" 
      "        EyeDir.z = dot(m_Normal , dirEye);                                                              \n"   
      
//------------------------------------------------------------------------------------------------------------------------      
      "        lightPosition_PASS = normalize(lightMatrix * light_POSITION_01);                                \n"                           

      "        varTexcoord        = texture;                                                                   \n"                           

      "        gl_Position        = mvpMatrix * position;                                                      \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      facing_UP_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(facing_UP_SHADER_VERTEX, 1, &vertexSource_facing_UP, NULL);                                                                        
      glCompileShader(facing_UP_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_facing_UP =                                                                                                            

      " #ifdef GL_ES                                                                                                                               \n"                       
      " #else                                                                                                                                      \n"                       
      " #define highp                                                                                                                              \n"                       
      " #endif                                                                                                                                     \n"                       

      "    uniform sampler2D     Texture1;                                                                                                         \n"                       
      "    uniform sampler2D     NormalMap;                                                                                                        \n"                       
      "    uniform sampler2D     HeightMap;                                                                                                        \n"       
      "    uniform highp float   shininess;                                                                                                        \n"                       
      "    uniform highp float   attenuation;                                                                                                      \n"                       

      "    varying highp vec4    lightPosition_PASS;                                                                                               \n"                       

      "    varying highp vec3    EyeDir;                                                                                                           \n"         
      
      "    varying highp vec2    varTexcoord;                                                                                                      \n"                       

      "            highp float   NdotL1;                                                                                                           \n"                       
      "            highp vec3    normal;                                                                                                           \n"                       
      "            highp vec3    NormalTex;                                                                                                        \n"                       


      "     void main()                                                                                                                            \n"                       
      "     {                                                                                                                                      \n"                       
                      
      "         vec3 EyeT       = normalize(EyeDir);                                                                                               \n"  
      "         vec4 Offset     = texture2D(HeightMap, varTexcoord. xy);                                                                               \n"  
      "         Offset          = Offset * shininess - attenuation;                                                                                            \n" 
      "         vec2 TexCoords  = Offset.xy * EyeT.xy + varTexcoord;                                                                               \n" 
  
      //------------------------------------------------------------------------------------------------------------------------
      
      "         NormalTex   =  texture2D(NormalMap,  TexCoords.xy).xyz;                                                                             \n"                       
      "         NormalTex             = (NormalTex - 0.5);                                                                                         \n"                       
      "         normal                =  normalize(NormalTex);                                                                                     \n"      
      "         NdotL1                =  dot(normal, lightPosition_PASS.xyz);                                                                      \n"                       

      //------------------------------------------------------------------------------------------------------------------------      
      
      "         gl_FragColor          =  texture2D(Texture1, TexCoords.xy) *  0.0                                                                \n"                       

      "                               +  texture2D(Texture1, TexCoords.xy) * NdotL1* 1.0                                       \n"                       

      "                               +  texture2D(Texture1, TexCoords.xy) * pow(NdotL1, 50.0) * vec4(2.0, 1.0, .1, 1.0)*0.0;                       \n"                       

      "    }\n";    
*/



      //---------------------------------------------------------------------                                                                         
      facing_UP_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(facing_UP_SHADER_FRAGMENT, 1, &fragmentSource_facing_UP, NULL);                                                                          
      glCompileShader(facing_UP_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(facing_UP_SHADER, facing_UP_SHADER_VERTEX);                                                                                              
      glAttachShader(facing_UP_SHADER, facing_UP_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(facing_UP_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(facing_UP_SHADER, 1, "normal");       
      glBindAttribLocation(facing_UP_SHADER, 2, "tangent");  
      glBindAttribLocation(facing_UP_SHADER, 3, "texture");                                                                                             
      //------------------------------------------------                                                                                              
      glLinkProgram(facing_UP_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(facing_UP_SHADER, facing_UP_SHADER_VERTEX);                                                                                              
      glDetachShader(facing_UP_SHADER, facing_UP_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(facing_UP_SHADER_VERTEX);                                                                                                            
      glDeleteShader(facing_UP_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_facing_UP                   = glGetUniformLocation(facing_UP_SHADER,   "mvpMatrix");                                              
      UNIFORM_MODELVIEW_facing_UP                       = glGetUniformLocation(facing_UP_SHADER,   "mvMatrix");        
      UNIFORM_LIGHT_MATRIX_facing_UP                    = glGetUniformLocation(facing_UP_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_facing_UP               = glGetUniformLocation(facing_UP_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_facing_UP                       = glGetUniformLocation(facing_UP_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_facing_UP                     = glGetUniformLocation(facing_UP_SHADER,   "attenuation");
      UNIFORM_zDirBias_facing_UP                        = glGetUniformLocation(facing_UP_SHADER,   "zDirBias");      
      UNIFORM_TEXTURE_HEIGHT_facing_UP                  = glGetUniformLocation(facing_UP_SHADER,   "HeightMap");                                                      
      UNIFORM_TEXTURE_DOT3_facing_UP                    = glGetUniformLocation(facing_UP_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_facing_UP                         = glGetUniformLocation(facing_UP_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"facing_UP_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &facing_UP_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, facing_UP_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"facing_UP" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &facing_UP_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, facing_UP_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/facing_UP/facing_UP_height.png",             facing_UP_HEIGHT);         
      loadTexture("_MODEL_FOLDERS_/facing_UP/facing_UP_DOT3.bmp",          facing_UP_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/facing_UP/facing_UP.png",               facing_UP_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "facing_UP.cpp"                                                                                                                
      glGenBuffers(1,              &facing_UP_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, facing_UP_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(facing_UP), facing_UP, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //--------------------------------------------------------------------------------------------------------------------     
      #include    "facing_UP_INDEX.cpp" 
      glGenBuffers(1, &facing_UP_INDEX_VBO);                       
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facing_UP_INDEX_VBO);                   
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(facing_UP_INDEX), facing_UP_INDEX, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);      
      //=================================================================================================================================       




