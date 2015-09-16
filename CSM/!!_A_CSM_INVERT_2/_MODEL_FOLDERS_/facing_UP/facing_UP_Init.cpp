     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      facing_UP_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_facing_UP =                                                                                                        

      "    #define highp                                                                                        \n"                           

      "    uniform highp   vec4   light_POSITION_01;                                                            \n"                           
      "    uniform         mat4   mvpMatrix;                                                                    \n"                           
      "    uniform         mat4   mvMatrix;                                                                     \n"        
      "    uniform         mat4   lightMatrix;                                                                  \n"                           
      "    uniform         float  zDirBias;                                                                     \n"
      "    attribute       vec4   position;                                                                     \n"                           
      "    attribute       vec3   normal;                                                                       \n"         
      "    attribute       vec3   tangent;                                                                      \n"             
      "    uniform highp float   shininess;                                                                     \n"                       
      "    uniform highp float   attenuation;                                                                   \n"                       
           
      "    attribute       vec2   texture;                                                                      \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                             \n"                           
      "    varying highp vec3   EyeDir;                                                                         \n"           
      "    varying highp vec2   varTexcoord;                                                                    \n"                           

      "    vec3 view;                                                                                           \n"    
//-----------------------------------------------------------------------------------------------------------------
      "    varying vec2 texCoord;                                                                               \n" 
      "    varying vec3 vertex_pos;                                                                             \n" 
      "    varying vec3 light_pos;                                                                              \n" 
      "    varying float vertex_dist;                                                                           \n" 
      "    varying float light_dist;                                                                            \n" 
//-----------------------------------------------------------------------------------------------------------------      
      "    void main()                                                                                          \n"                           
      "    {                                                                                                    \n"                           
      
      "   vec3 eyeSpaceVert = (mvMatrix * position).xyz;                                                        \n"
      "   vec3 eyeSpaceLight = (mvMatrix * light_POSITION_01).xyz;                                              \n"
      "                                                                                                         \n"
     
      
      "      vec3 eyeSpaceNormal =  (mvMatrix * vec4(normal, 0.0));                                             \n"  
      
      "      vec3 eyeSpaceTangent =  (mvMatrix * vec4(tangent, 0.0));                                           \n"  
      "      vec3 eyeSpaceBinormal =   cross(eyeSpaceNormal, eyeSpaceTangent);                                  \n"  
  

      "   vertex_pos = vec3 (                                                                                   \n" 
      "        dot (eyeSpaceTangent, eyeSpaceVert),                                                             \n" 
      "        dot (eyeSpaceBinormal, eyeSpaceVert),                                                            \n" 
      "        dot (eyeSpaceNormal, eyeSpaceVert));                                                             \n" 
      "   light_pos = vec3 (                                                                                    \n" 
      "        dot (eyeSpaceTangent, eyeSpaceLight),                                                            \n" 
      "        dot (eyeSpaceBinormal, eyeSpaceLight),                                                           \n" 
      "        dot (eyeSpaceNormal, eyeSpaceLight)) - vertex_pos;                                               \n" 
    
      "    vertex_dist = length (eyeSpaceVert);                                                                 \n"
      "    light_dist = length (light_pos);                                                                     \n"
                                                                                
      "    texCoord   = texture;                                                                                \n"
   
                                                                                 
    
//=============================================================================================================================    
      "      //lightPosition_PASS = normalize(lightMatrix * light_POSITION_01);                                 \n"                           

      "      varTexcoord        = texture;                                                                      \n"                           

      "      gl_Position        = mvpMatrix * position;                                                         \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      facing_UP_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(facing_UP_SHADER_VERTEX, 1, &vertexSource_facing_UP, NULL);                                                                        
      glCompileShader(facing_UP_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_facing_UP =                                                                                                            

      " #ifdef GL_ES                                                                                                              \n"                       
      " #else                                                                                                                     \n"                       
      " #define highp                                                                                                             \n"                       
      " #endif                                                                                                                    \n"                       

      "    uniform sampler2D     Texture1;                                                                                        \n"                       
      "    uniform sampler2D     NormalMap;                                                                                       \n"                       
      "    uniform sampler2D     HeightMap;                                                                                       \n"        
      "    uniform highp float   shininess;                                                                                       \n"                       
      "    uniform highp float   attenuation;                                                                                     \n"                       
      "    uniform highp vec4    light_POSITION_01;                                                                               \n"    
      "    varying highp vec4    lightPosition_PASS;                                                                              \n"                       
      "    varying highp vec3    EyeDir;                                                                                          \n"     
      
      "    varying highp vec2    varTexcoord;                                                                                     \n"                       
//-----------------------------------------------------------------------------------------------------------------
      "   float depth = 0.2;                                                                                                     \n" 

      "   float texsize = 512;                                                                                                    \n"   
      "    varying vec2 texCoord;                                                                                                 \n" 
      "    varying vec3 vertex_pos;                                                                                               \n" 
      "    varying vec3 light_pos;                                                                                                \n" 
      "    varying float vertex_dist;                                                                                             \n" 
      "    varying float light_dist;                                                                                              \n" 
//-----------------------------------------------------------------------------------------------------------------
    
      "            highp float   NdotL1;                                                                                          \n"                       
      "            highp vec3    normal;                                                                                          \n"                       
      "            highp vec3    NormalTex;                                                                                       \n"                       

      "            highp float   scale;                                                                                           \n"  
      "            highp float   bias;                                                                                            \n"  

      "            void intersect_square_cone_3step (inout vec3 dp, in vec3 ds);                                                  \n" 

      "     void main()                                                                                                           \n"                       
      "     {                                                                                                                     \n"                       
                
      "          vec4 t,c;                                                                                                              \n"
      "          vec3 l,s;                                                                                                              \n"
      "          vec3 pt_eye, pt_light;                                                                                                 \n"
      "          float a;                                                                                                               \n"

      "          a  = -depth / vertex_pos.z;                                                                                          \n"
      "          s = vertex_pos * a;                                                                                                    \n"
      "          s.z = 1.0;                                                                                                             \n"
  
      "          pt_eye = vec3 (texCoord, 0.0);                                                                                         \n"
      "          intersect_square_cone_3step (pt_eye, s);                                                                               \n"               
                        
      "          c=texture2D(Texture1,pt_eye.xy);                                                                                        \n" 

      "          t=texture2D(HeightMap, pt_eye.xy);                                                                                  \n" 
      "          t = vec4 ((t.ba-0.5) * (-depth * texsize), 1.0, 0.0);                                                                \n"
      "          t=normalize(t);                                                                                                      \n"

      "          float att = 1.0;                                                                                                     \n"
      "          att = min (1.0, 1.0 / (light_dist*att));                                                                             \n"
   
      "          l = att * normalize(light_pos);                                                                                      \n"

      "          gl_FragColor = vec4( vec3(1.0, 1.0, 1.0)*c.xyz +vec3(1.0, 1.0, 1.0)*c.xyz*max(0.0,dot(l,t.xyz)),1.0);                  \n"
     
      "    }\n"                                                                                                                                   

//===========================================================================================================================

"void intersect_square_cone_3step (inout vec3 dp, in vec3 ds)                                                                   \n"
"{                                                                                                                              \n"

"   float iz = max(abs(ds.x),abs(ds.y));                                                                                        \n"

"   float w = attenuation;                                                                                                        \n"

"   vec4 t;                                                                                                                     \n"

"   dp += shininess * ds;                                                                                                             \n"

//------------------------------------------------------
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);                                                                         \n"
//------------------------------------------------------   
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);                                                                         \n"
//------------------------------------------------------
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);                                                                         \n"
//------------------------------------------------------  

"   return;                                                                                                                     \n"
"}                                                                                                                              \n";



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
      loadTexture("_MODEL_FOLDERS_/facing_UP/facing_UP_step.png",             facing_UP_HEIGHT);         
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




