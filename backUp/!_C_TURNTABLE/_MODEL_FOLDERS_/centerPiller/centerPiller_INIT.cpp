      
    #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      centerPiller_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_centerPiller =                                                                                                        

      "    #define highp                                                                                       \n"                           

      "    uniform       mat4   mvpMatrix;                                                                     \n"  
      "    attribute     vec4   position;                                                                      \n" 

      "    void main()                                                                                          \n"                           
      "    {                                                                                                    \n"                           
      

      "        gl_Position           = mvpMatrix * position;                                                   \n" 
      
      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      centerPiller_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(centerPiller_SHADER_VERTEX, 1, &vertexSource_centerPiller, NULL);                                                                        
      glCompileShader(centerPiller_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      
 
 
      
      const GLchar *fragmentSource_centerPiller =                                                                                                            

     
     
      " #ifdef GL_ES                                                                                                     \n"                       
      " #else                                                                                                            \n"                       
      " #define highp                                                                                                    \n"                       
      " #endif                                                                                                           \n"   
   

      "     void main()                                                                                                  \n"                       
      "     {                                                                                                            \n"                       
   

     
      "         gl_FragColor          =    vec4(.1, .1, .1, .1) ;           \n" 
     "    }\n";                                                                                                                                   


      //---------------------------------------------------------------------                                                                         
      centerPiller_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(centerPiller_SHADER_FRAGMENT, 1, &fragmentSource_centerPiller, NULL);                                                                          
      glCompileShader(centerPiller_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(centerPiller_SHADER, centerPiller_SHADER_VERTEX);                                                                                              
      glAttachShader(centerPiller_SHADER, centerPiller_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(centerPiller_SHADER,    0, "position");                                                                                            
      glBindAttribLocation(centerPiller_SHADER,    1, "normal");
      glBindAttribLocation(centerPiller_SHADER,    2, "tangent");             
      glBindAttribLocation(centerPiller_SHADER,    3, "texture");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(centerPiller_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(centerPiller_SHADER, centerPiller_SHADER_VERTEX);                                                                                              
      glDetachShader(centerPiller_SHADER, centerPiller_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(centerPiller_SHADER_VERTEX);                                                                                                            
      glDeleteShader(centerPiller_SHADER_FRAGMENT); 
      
                                                                                                        
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_centerPiller                   = glGetUniformLocation(centerPiller_SHADER,      "mvpMatrix");                                              
     
      UNIFORM_LIGHT_MATRIX_centerPiller                    = glGetUniformLocation(centerPiller_SHADER,      "lightMatrix");                                            
      UNIFORM_textureMatrix_centerPiller                      = glGetUniformLocation(centerPiller_SHADER,   "textureMatrix");        
      UNIFORM_LIGHT_POSITION_01_centerPiller               = glGetUniformLocation(centerPiller_SHADER,      "light_POSITION_01");                                      
      UNIFORM_SHININESS_centerPiller                       = glGetUniformLocation(centerPiller_SHADER,      "shininess");                                              
      UNIFORM_ATTENUATION_centerPiller                     = glGetUniformLocation(centerPiller_SHADER,      "attenuation");                                              
      UNIFORM_TEXTURE_SHADOW_centerPiller                  = glGetUniformLocation(centerPiller_SHADER,      "ShadowMap");       
      UNIFORM_TEXTURE_DOT3_centerPiller                    = glGetUniformLocation(centerPiller_SHADER,      "NormalMap");                                              
      UNIFORM_TEXTURE_centerPiller                         = glGetUniformLocation(centerPiller_SHADER,      "Texture1");                                   
      
      
     
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"centerPiller_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &centerPiller_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, centerPiller_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"centerPiller" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &centerPiller_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, centerPiller_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/centerPiller/centerPiller_DOT3.bmp",          centerPiller_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/centerPiller/centerPiller.png",               centerPiller_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "centerPiller.cpp"                                                                                                                
      glGenBuffers(1,              &centerPiller_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, centerPiller_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(centerPiller), centerPiller, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //------------------------------------------------------------------------------------------------------------       
      #include    "centerPiller_INDICES.cpp"                                                                                                                
      glGenBuffers(1,              &centerPiller_INDICES_VBO);                                                                                                
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, centerPiller_INDICES_VBO);                                                                                                
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(centerPiller_INDICES), centerPiller_INDICES, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                                                                                                         
      //------------------------------------------------------------------------------------------------------------       

