     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      lightSpheres_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_lightSpheres =                                                                                                        

      "    #define highp                                                                                                   \n"                           

      "    uniform highp vec4  light_POSITION_01;                                                                          \n"                           
      "    uniform       mat4  mvpMatrix;                                                                                  \n"                           
      "    uniform       mat4  mvMatrix;                                                                                   \n"        
      "    uniform       mat4  lightMatrix;                                                                                \n"                                                             
            
      "    attribute     vec4  position;                                                                                   \n"                           
      "    attribute     vec2  texture;                                                                                    \n"                           

      "    varying highp vec4  lightPosition_PASS;                                                                         \n"                           
      //-------------------------------------------
      "    uniform       mat4  textureMatrix;                                                                              \n"         
      "    varying highp vec4  shadowTexcoord;                                                                             \n"       
      "            highp vec4  TEMP_shadowTexcoord;                                                                        \n" 
      "    uniform highp vec4  offset;                                                                                     \n" 
       
      //------------------------------------------- 
      "    varying highp vec2  varTexcoord;                                                                                \n"                           
        
//-----------------------------------------------------------------------------------------------------------------
      "    varying highp vec3  vertex_pos;                                                                                  \n" 
//-----------------------------------------------------------------------------------------------------------------      
      "    void main()                                                                                                      \n"                           
      "    {                                                                                                                \n"                           
    
                   //---------------------------------------------------------------------------------------------------------     
      "            TEMP_shadowTexcoord   =   textureMatrix * mvpMatrix * position + mvMatrix[3][3] * 1.0;                   \n" 
      "            shadowTexcoord        =   TEMP_shadowTexcoord + offset;                                                  \n"    
                   //---------------------------------------------------------------------------------------------------------
      "            lightPosition_PASS    =   normalize(lightMatrix * light_POSITION_01);                                    \n"                           
  
      "            varTexcoord           =   texture;                                                                        \n"                           
      "            gl_Position           =   mvpMatrix * position;                                                           \n"                           



      "    }\n";                                                                                                                             
      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################        
   
   
      //---------------------------------------------------------------------                                                                   
      lightSpheres_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(lightSpheres_SHADER_VERTEX, 1, &vertexSource_lightSpheres, NULL);                                                                        
      glCompileShader(lightSpheres_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_lightSpheres =                                                                                                            

      " #ifdef GL_ES                                                                                                              \n"                       
      " #else                                                                                                                     \n"                       
      " #define highp                                                                                                             \n"                       
      " #endif                                                                                                                    \n"                       

      
      "    uniform sampler2D   Texture1;                                                                                          \n"                       
      "    uniform sampler2D   NormalMap;                                                                                         \n"                       
      //--------------------------------------------
      "    uniform sampler2DShadow   ShadowTexture;                                                                               \n"     
      "    varying highp vec4        shadowTexcoord;                                                                              \n"         
      "            highp vec4        shadow;                                                                                      \n"     
      //--------------------------------------------  
      "    varying highp vec4  lightPosition_PASS;                                                                                \n"                       
      "    varying highp vec2  varTexcoord;                                                                                       \n"                       
      //--------------------------------------------

      "            highp float   NdotL2;                                                                                          \n"                       
      
     
      "            highp vec3    normal_2;                                                                                        \n"                       
      "            highp vec3    NormalTex;                                                                                       \n"                       
      //-----------------------------------

      "     void main()                                                                                                           \n"                       
      "     {                                                                                                                     \n"                       

                         //--------------------------------------------------------------------------------------------------     
      " 		         vec4  shadowCoordinateWdivide    =  shadowTexcoord / shadowTexcoord.w;                                   \n" 
      " 		               shadowCoordinateWdivide.z +=  -0.2855;                                                             \n" 
      " 		         float distanceFromLight          =  shadow2DProj(ShadowTexture, shadowTexcoord).r;                       \n" 
     
      " 		         float shadow                     =  1.0;                                                                 \n" 
      " 		         if (shadowTexcoord.w             >  0.0)                                                                 \n" 
      " 		      		  shadow = distanceFromLight  <  shadowCoordinateWdivide.z ? 0.5 : 1.0 ;                              \n"   
                //--------------------------------------------------------------------------------------------------
      "         NormalTex              =  texture2D(NormalMap,  varTexcoord.xy).xyz;                                              \n"                       
      "         NormalTex              = (NormalTex - 0.5);                                                                       \n"        
      "         normal_2               =  normalize(NormalTex);                                                                   \n"      
      "         NdotL2                 =  max(dot(normal_2, lightPosition_PASS.xyz), 0.0);                                        \n"      
      
      //-----------------------------------------------------------------------------------------------------------------------------
      "         gl_FragColor           = vec4(1.0, 1.0, 1.0, 1.0) * shadow;                                    \n"
      
      
      
      
      
      "    }\n"                                                                                                                                   


;



      //---------------------------------------------------------------------                                                                         
      lightSpheres_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(lightSpheres_SHADER_FRAGMENT, 1, &fragmentSource_lightSpheres, NULL);                                                                          
      glCompileShader(lightSpheres_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(lightSpheres_SHADER, lightSpheres_SHADER_VERTEX);                                                                                              
      glAttachShader(lightSpheres_SHADER, lightSpheres_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(lightSpheres_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(lightSpheres_SHADER, 1, "normal");       
      glBindAttribLocation(lightSpheres_SHADER, 2, "tangent");  
      glBindAttribLocation(lightSpheres_SHADER, 3, "texture");                                                                                             
      //------------------------------------------------                                                                                              
      glLinkProgram(lightSpheres_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(lightSpheres_SHADER, lightSpheres_SHADER_VERTEX);                                                                                              
      glDetachShader(lightSpheres_SHADER, lightSpheres_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(lightSpheres_SHADER_VERTEX);                                                                                                            
      glDeleteShader(lightSpheres_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_lightSpheres                   = glGetUniformLocation(lightSpheres_SHADER,   "mvpMatrix");                                              
      UNIFORM_MODELVIEW_lightSpheres                       = glGetUniformLocation(lightSpheres_SHADER,   "mvMatrix");        
      UNIFORM_LIGHT_MATRIX_lightSpheres                    = glGetUniformLocation(lightSpheres_SHADER,   "lightMatrix");                                            
      UNIFORM_textureMatrix_lightSpheres                   = glGetUniformLocation(lightSpheres_SHADER,   "textureMatrix");       
      UNIFORM_INVERSEMATRIX_lightSpheres                      = glGetUniformLocation(lightSpheres_SHADER,   "inverseMatrix");   
      UNIFORM_offset_lightSpheres                          = glGetUniformLocation(lightSpheres_SHADER,   "offset");      
      //-------------------------------------
      UNIFORM_LIGHT_POSITION_01_lightSpheres               = glGetUniformLocation(lightSpheres_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_lightSpheres                       = glGetUniformLocation(lightSpheres_SHADER,   "shininess");                                              
      //-------------------------------------
      UNIFORM_QUADRATIC_ATTENUATION_lightSpheres           = glGetUniformLocation(lightSpheres_SHADER,   "quadraticAttenuation");
      UNIFORM_LINEAR_ATTENUATION_lightSpheres              = glGetUniformLocation(lightSpheres_SHADER,   "linearAttenuation");      
      UNIFORM_CONSTANT_ATTENUATION_lightSpheres            = glGetUniformLocation(lightSpheres_SHADER,   "constantAttenuation");        
      //-------------------------------------
      UNIFORM_TEXTURE_SHADOW_lightSpheres                  = glGetUniformLocation(lightSpheres_SHADER,   "ShadowTexture");       
      UNIFORM_TEXTURE_DOT3_lightSpheres                    = glGetUniformLocation(lightSpheres_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_lightSpheres                         = glGetUniformLocation(lightSpheres_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"lightSpheres_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &lightSpheres_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, lightSpheres_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"lightSpheres" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &lightSpheres_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, lightSpheres_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/lightSpheres/lightSpheres_DOT3.bmp",          lightSpheres_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/lightSpheres/lightSpheres.png",               lightSpheres_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "lightSpheres.cpp"                                                                                                                
      glGenBuffers(1,              &lightSpheres_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, lightSpheres_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(lightSpheres), lightSpheres, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //--------------------------------------------------------------------------------------------------------------------     
      #include    "lightSpheres_INDICES.cpp" 
      glGenBuffers(1, &lightSpheres_INDEX_VBO);                       
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightSpheres_INDEX_VBO);                   
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lightSpheres_INDICES), lightSpheres_INDICES, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);      
      //=================================================================================================================================       




