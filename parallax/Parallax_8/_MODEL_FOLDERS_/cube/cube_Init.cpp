     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      cube_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_cube =                                                                                                        

      "    #define highp                                                                                        \n"                           

      "    uniform highp vec4   light_POSITION_01;                                                              \n"                           
      "    uniform       mat4   mvpMatrix;                                                                      \n"                           
      "    uniform       mat4   mvMatrix;                                                                       \n"        
      "    uniform       mat4   lightMatrix;                                                                    \n"                           

      "    attribute     vec4   position;                                                                       \n"                           
      "    attribute     vec3   normal;                                                                         \n"         
      "    attribute     vec3   tangent;                                                                        \n"             
      "    attribute     vec3   bitangent;                                                                      \n"       
      
      "    attribute     vec2   texture;                                                                        \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                             \n"                           
      "    varying highp vec3   dirEye;                                                                         \n"           
      "    varying highp vec3   n;                                                                              \n"         
      "    varying highp vec3   t;                                                                              \n"         
      "    varying highp vec3   b;                                                                              \n"         
      "    varying highp vec3   m_Vector;                                                                       \n"       
 
  
      "    varying highp vec2   varTexcoord;                                                                    \n"                           

      "    vec3 view;                                                                                           \n"    

      "    void main()                                                                                          \n"                           
      "    {                                                                                                    \n"                           
      
      "       n =  (mvMatrix * vec4(normal, 0.0));                                                              \n"  
      "       t =  (mvMatrix * vec4(tangent, 0.0));                                                             \n"  
      "       b =   cross(n, t);                                                                                \n"  
  
 
      "        vec3 vertexPosition   =  position;                                                               \n"        
      "        dirEye                =  vec3(0.0,0.0, -1.0);                                                    \n"  
      
      "     m_Vector        = vec3(mvMatrix * position);                                                        \n"  
 
     //-----------------------------------------------------------------------------------------------------------------
      "      lightPosition_PASS = normalize(lightMatrix * light_POSITION_01);                                   \n"                           

      "      varTexcoord        = texture;                                                                      \n"                           

      "      gl_Position        = mvpMatrix * position;                                                         \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      cube_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(cube_SHADER_VERTEX, 1, &vertexSource_cube, NULL);                                                                        
      glCompileShader(cube_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_cube =                                                                                                            

      " #ifdef GL_ES                                                                                           \n"                       
      " #else                                                                                                     \n"                       
      " #define highp                                                                                             \n"                       
      " #endif                                                                                                    \n"                       

      "    uniform sampler2D     Texture1;                                                                        \n"                       
      "    uniform sampler2D     NormalMap;                                                                       \n"                       
      "    uniform sampler2D     HeightMap;                                                                       \n"        
      "    uniform highp float   shininess;                                                                       \n"                       
      "    uniform highp float   angle;                                                                            \n"   
      "    uniform highp float   scaleRadian;                                                                       \n"       
      
      "    uniform highp float   attenuation;                                                                     \n"                       
      "    uniform highp vec4    light_POSITION_01;                                                               \n"    
      "    varying highp vec4    lightPosition_PASS;                                                              \n"                       
      "    varying highp vec3    dirEye;                                                                         \n"     
      
      "    varying highp vec2    varTexcoord;                                                                     \n"                       

      "            highp float   NdotL1;                                                                          \n"                       
      "            highp vec3    normal;                                                                          \n"                       
      "            highp vec3    NormalTex;                                                                      \n"                       
      "            highp vec3    EyeDir;                                                                         \n" 
      "    varying highp vec3    n;                                                                              \n"         
      "    varying highp vec3    t;                                                                              \n"         
      "    varying highp vec3    b;                                                                              \n"         
      "    varying highp vec3    m_Vector;                                                                       \n"       
       
      "            highp float   scale;                                                                          \n"  
      "            highp float   bias;                                                                           \n"  


      "     void main()                                                                                          \n"                       
      "     {                                                                                                    \n"                       
      "        float angle_rad       =  scaleRadian * 0.1 * 3.14159 / 180.0;                                                  \n" 
                       
      "        EyeDir.x              =  dot(t.xyz , -m_Vector);                                                    \n"  
      "        EyeDir.y              =  dot(b.xyz , -m_Vector);                                                    \n"  
      "        EyeDir.z              =  dot(n.xyz , -m_Vector);                                                    \n"        
     
      "        vec3 EyeT       =  normalize(EyeDir);                                                               \n"   
      "        vec4 Offset     =  texture2D(HeightMap,varTexcoord);                                            \n"   
      "        Offset          = (Offset * (1.0 - EyeDir.z * -1.0) * angle_rad ) - attenuation;                                                          \n"   
      "        vec2 TexCoords  =  Offset.xy * EyeT.xy  + varTexcoord;                                               \n"   
 
     
      //------------------------------------------------------------------------------------------------------------------------
      
      "         NormalTex   =  texture2D(NormalMap,  TexCoords).xyz;                                                                             \n"                       
      "         NormalTex             = (NormalTex - 0.5);                                                                                         \n"                       
      "         normal                =  normalize(NormalTex);                                                                                     \n"      
      "         NdotL1                =  dot(normal, lightPosition_PASS.xyz);                                                            \n"                       

      //------------------------------------------------------------------------------------------------------------------------      
      
      "         gl_FragColor          =  vec4(1.0, 1.0, 1.0, 1.0) * .1                                                                        \n"                       

      "                               +  texture2D(Texture1, TexCoords.xy) * NdotL1 * NdotL1 * 0.5                                                        \n"                       

      "                               +  texture2D(Texture1, TexCoords.xy) * pow(NdotL1, 50.0) * vec4(2.0, 1.0, .1, 1.0)*1.0;                  \n"                       

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




