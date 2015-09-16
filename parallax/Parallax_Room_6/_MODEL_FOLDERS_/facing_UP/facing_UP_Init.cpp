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
      "    uniform         mat4   invertMatrix;                                                                  \n"                                 
      "    uniform         float  zDirBias;                                                                     \n"
      "    attribute       vec4   position;                                                                     \n"                           
      "    attribute       vec3   normal;                                                                       \n"         
      "    attribute       vec3   tangent;                                                                      \n"             
     
      "    attribute       vec2   texture;                                                                      \n"                           

      "    varying highp   vec3   column0;                                                                      \n"   
      "    varying highp   vec3   column1;                                                                      \n"   
      "    varying highp   vec3   column2;                                                                      \n"        
  

      "    varying highp vec4   lightPosition_PASS;                                                             \n"                           
      "    varying highp vec3   EyeDir;                                                                         \n"           
      "    varying highp vec2   varTexcoord;                                                                    \n"                           
      
      "    varying highp  vec3	lightDir;                                                                       \n"   
      "    varying highp  vec3	viewDir;                                                                        \n"   
      "    highp float fParallaxScale = 0.065;                                                                  \n"  

      "    vec3 view;                                                                                           \n"    
//---------------------------------------------------------------------------------------------------------------------------
      "    void main()                                                                                          \n"                           
      "    {                                                                                                    \n"                           
	//_____________________________________________________________________Create a Matrix to transform from eye space to tangent space
	//_____________________________________________________________________Start by calculating the normal, tangent and binormal.
      "  	highp vec3 n = normalize(mvMatrix * vec4(normal, 0.0));                                             \n" 
      "  	highp vec3 t = normalize(mvMatrix * vec4(tangent, 0.0));                                            \n" 
      "  	highp vec3 b = cross(n,t);                                                                          \n" 
//__POWER_VR_SDK
	//_____________________________________________________________________Create the matrix from the above
     "  	highp mat3 mEyeToTangent = mat3( t.x, b.x, n.x,                                                     \n" 
     "  							         t.y, b.y, n.y,                                                     \n" 
     "  							         t.z, b.z, n.z);                                                    \n" 
//__POWER_VR_SDK	
	//_____________________________________________________________________Write gl_pos
      "  	highp vec4 tempPos = mvMatrix * position;                                                                      \n" 				   
//__POWER_VR_SDK	
	//_____________________________________________________________________Translate the view direction into Tangent Space
	//_____________________________________________________________________Translate the position into eye space
    "  	viewDir = tempPos.xyz;                                                                              \n" 
	//_____________________________________________________________________Then translate that into Tangent Space (multiplied by parallax scale as only has to
	//_____________________________________________________________________be done once per surface, not per fragment)
      "  	viewDir = normalize(mEyeToTangent * viewDir) * fParallaxScale;                                      \n" 


     //-----------------------------------------------------------------------------------------------------------------
      "        column0               =   vec3(mvpMatrix[0].xyz);                                              \n"   
      "        column1               =   vec3(mvpMatrix[1].xyz);                                              \n"   
      "        column2               =   vec3(mvpMatrix[2].xyz);                                              \n"        
             
      
      "      lightPosition_PASS = normalize(lightMatrix * light_POSITION_01);                                   \n"                           

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

      "    varying highp   vec3   column0;                                                                                        \n"   
      "    varying highp   vec3   column1;                                                                                        \n"   
      "    varying highp   vec3   column2;                                                                                        \n"        
        
      "            highp float   NdotL1;                                                                                          \n"                       
      "            highp vec3    normal;                                                                                          \n"                       
      "            highp vec3    NormalTex;                                                                                       \n"                       

      "            highp float   scale;                                                                                           \n"  
      "            highp float   bias;                                                                                            \n"  

      "    varying highp  vec3	 lightDir;                                                                                        \n"   
      "    varying highp  vec3	 viewDir;                                                                                         \n"   

//------------------------------------------------------------------------------------------------------------------------------
      "     void main()                                                                                                           \n"                       
      "     {                                                                                                                     \n"                       
                      

	//_____________________________________________________________________Calculate how far we're shifting by (using parallax scale).
      
      " 	    highp float fDepth = texture2D(Texture1, varTexcoord.xy).x;                                       \n"  
	
	//_____________________________________________________________________Set the UV Coord appropriately
      
      " 	    highp vec2 vTexCoord = varTexcoord - (fDepth * viewDir.xy);                                        \n"  
     
      //------------------------------------------------------------------------------------------------------------------------
      "         mat3 n = mat3(column0, column1, column2);                                                                                          \n"       
     
      "         NormalTex   =  texture2D(NormalMap,  vTexCoord).xyz;                                                                  \n"                       
      "         NormalTex             = (NormalTex - 0.5);                                                                              \n"                       
      "         normal                =  normalize(n * NormalTex);                                                                          \n"      
      "         NdotL1                =  dot(normal, normalize(light_POSITION_01.xyz));                                                 \n"                       

      //------------------------------------------------------------------------------------------------------------------------      
      
      "         gl_FragColor          =  (vec4(1.0, 1.0, 1.0, 1.0) * .1                                                                 \n"                       

      "                               +  texture2D(Texture1, vTexCoord.xy) * NdotL1 * 0.5                                    \n"                       

      "                               +  texture2D(Texture1, vTexCoord.xy) * pow(NdotL1, 20.0) * vec4(2.0, 1.0, .1, 1.0) * 0.2)  \n"                       
      
      "                               ;                                                                                   \n"
      
      "    }\n";                                                                                                                                   



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
      UNIFORM_invertMatrix_facing_UP                    = glGetUniformLocation(facing_UP_SHADER,   "invertMatrix");                                                  
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




