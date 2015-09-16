                    if(WGL_ARB_multisamp_NORMALMAP != 0)                                                                                        
                    {                                                                                                              
                            glDeleteTextures(1, &WGL_ARB_multisamp_NORMALMAP);                                                                  
                            WGL_ARB_multisamp_NORMALMAP = 0;                                                                                    
                    }                                                                                                              
                    if(WGL_ARB_multisamp_TEXTUREMAP  != 0)                                                                                      
                    {                                                                                                              
                            glDeleteTextures(1, &WGL_ARB_multisamp_TEXTUREMAP);                                                                 
                            WGL_ARB_multisamp_TEXTUREMAP  = 0;                                                                                  
                    }                                                                                                              
                    if(WGL_ARB_multisamp_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &WGL_ARB_multisamp_VBO);                                                                         
                            WGL_ARB_multisamp_VBO  = 0;                                                                                         
                    }                                                                                                              
                    if(WGL_ARB_multisamp_INDICES_VBO  != 0)                                                                                             
                    {                                                                                                              
                            glDeleteBuffers(1, &WGL_ARB_multisamp_INDICES_VBO);                                                                         
                            WGL_ARB_multisamp_INDICES_VBO  = 0;                                                                                         
                    }                                                                                                              
