        glGenFramebuffersEXT(1, &mainLightPass_fboId);    
        glGenTextures(1, &mainLightPass_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, mainLightPass_TEXTURE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth, (GLsizei)viewHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);  
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mainLightPass_fboId);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mainLightPass_TEXTURE, 0);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glGenRenderbuffersEXT(1, &mainLightPass_depth);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mainLightPass_depth); 
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, (GLsizei)viewWidth, (GLsizei)viewHeight);        
        //====================================================================================================================              
        #include "_MODEL_FOLDERS_/lightSpheres/lightSpheres_Init.cpp"                                                                   
        //#####################################################################################################################            
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Init.cpp"                                                                   
        //#####################################################################################################################         
        #include "_MODEL_FOLDERS_/frameBufferPlane/gaussianBlur_INIT.cpp"//__GAUSSIAN_BLUR_IS_USING->> [frameBufferPlane] MODEL
        //#####################################################################################################################            
        glGenTextures(1, &shadowMap_2D);
	    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, (GLsizei)viewWidth / resize_SHADOW_FBO, (GLsizei)viewHeight / resize_SHADOW_FBO, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //----------------------------------------------------------------   
        glGenFramebuffers(1, &fboId_3D);
	    glBindFramebuffer(GL_FRAMEBUFFER, fboId_3D);
        #ifdef WIN32
        glDrawBuffer(GL_NONE);//_ON_SOME_MACHINES_THIS_IS_REQUIRED / ON_SOME_IT_FAILS
        glReadBuffer(GL_NONE);//_THIS_MAY_BE_OPTIONAL
	    #endif 
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); 
        //-------------------------------------------------------
        #include "_SHADERS/SHADOWS/shadows_32bit_Stride_INIT.cpp"                            
        #include "_SHADERS/SHADOWS/shadows_44bit_Stride_INIT.cpp" 
        //#####################################################################################################################                    
        //==================================================================================== 
        glGenFramebuffersEXT(1, &processShadow_fboId);    
        glGenTextures(1, &processShadow_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, processShadow_TEXTURE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)viewWidth, (GLsizei)viewHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);  
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, processShadow_fboId);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, processShadow_TEXTURE, 0);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glGenRenderbuffersEXT(1, &processShadow_depthFboId);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, processShadow_depthFboId); 
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, (GLsizei)viewWidth, (GLsizei)viewHeight);        
        //-------------------------------------------------------
        #include "_SHADERS/SHADOWS/processShadow_32bit_Stride_INIT.cpp"
        #include "_SHADERS/SHADOWS/processShadow_44bit_Stride_INIT.cpp"
        //====================================================================================     
        #include "_SHADERS/SHADOWS/flatten_3D_shadow_INIT.cpp"        
        //##################################################################################################################### 
        
        //====================================================================================================================                                         
        #include "_SHADERS/plastic/rubber/rubber_INIT.cpp"                                   
        //====================================================================================  
        #include "_SHADERS/wood/goldenSunset_INIT.cpp"  
        //====================================================================================       
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_Init.cpp"  
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_Init.cpp"                                                                   
        //==================================================================================== 
        #include "_MODEL_FOLDERS_/facing_Sideways_blocks_01/facing_Sideways_blocks_01_INIT.cpp"                                                                           
        //====================================================================================   
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/sculptris/sculptris_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/sphere/sphere_Init.cpp"                                                                   
        //====================================================================================    
        #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Init.cpp"                                                                   
        //====================================================================================   
        #include "_MODEL_FOLDERS_/knight/knight_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/floorStraps/floorStraps_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/wallStraps/wallStraps_Init.cpp"                                                                   
        //====================================================================================                                          
        #include "_MODEL_FOLDERS_/blocksEdging/blocksEdging_Init.cpp"                                                                   
        //====================================================================================                                          









