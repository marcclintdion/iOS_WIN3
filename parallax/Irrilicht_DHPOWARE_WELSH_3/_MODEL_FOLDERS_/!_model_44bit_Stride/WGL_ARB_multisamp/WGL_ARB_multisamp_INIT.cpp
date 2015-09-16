      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"WGL_ARB_multisamp_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &WGL_ARB_multisamp_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, WGL_ARB_multisamp_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"WGL_ARB_multisamp" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &WGL_ARB_multisamp_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, WGL_ARB_multisamp_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/WGL_ARB_multisamp/WGL_ARB_multisamp_DOT3.bmp",          WGL_ARB_multisamp_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/WGL_ARB_multisamp/WGL_ARB_multisamp.png",               WGL_ARB_multisamp_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "WGL_ARB_multisamp.cpp"                                                                                                                
      glGenBuffers(1,              &WGL_ARB_multisamp_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, WGL_ARB_multisamp_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(WGL_ARB_multisamp), WGL_ARB_multisamp, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //------------------------------------------------------------------------------------------------------------       
      #include    "WGL_ARB_multisamp_INDICES.cpp"                                                                                                                
      glGenBuffers(1,              &WGL_ARB_multisamp_INDICES_VBO);                                                                                                
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, WGL_ARB_multisamp_INDICES_VBO);                                                                                                
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(WGL_ARB_multisamp_INDICES), WGL_ARB_multisamp_INDICES, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                                                                                                         
      //------------------------------------------------------------------------------------------------------------       
