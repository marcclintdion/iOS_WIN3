       
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //========================================================================================================================================================        
        #ifdef __APPLE__    
            glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
        #endif    
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!          
        //========================================================================================================================================================

        //=========================================================================================================================================================    
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0 );
         glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //----------------------------------------------------------------------------------
        glViewport(0, 0, (GLsizei)viewWidth, (GLsizei)viewHeight);
        PerspectiveMatrix(projection, 35,viewWidth / viewHeight, adjustNearFar[0],  adjustNearFar[1]);
        //=========================================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        #endif        
        //=========================================================================================================================================================        
        //=====================================================================================================================
        
       
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                                                                    
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);         
        //--------------------------------------------------------------------------------------
        Translate(modelView, flowerShield_POSITION[0], flowerShield_POSITION[1], flowerShield_POSITION[2]);                                                                                         
        Rotate(modelView, flowerShield_ROTATE[0], flowerShield_ROTATE[1], flowerShield_ROTATE[2], flowerShield_ROTATE[3]+spinModel);         
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Render.cpp"                                                                 
        //------------------------------------------------------------------------------------                                           
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                                                                    
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);         
        //-------------------------------------------------------------------------------------- 
        Translate(modelView, sculptris_POSITION[0], sculptris_POSITION[1], sculptris_POSITION[2]);                                                                                         
        Rotate(modelView, sculptris_ROTATE[0], sculptris_ROTATE[1], sculptris_ROTATE[2], sculptris_ROTATE[3]+spinModel);         
        #include "_MODEL_FOLDERS_/sculptris/sculptris_Render.cpp"                                                                 
        //------------------------------------------------------------------------------------                                           
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                                                                   
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);         
        //--------------------------------------------------------------------------------------
        Translate(modelView, sphere_POSITION[0], sphere_POSITION[1], sphere_POSITION[2]);                                                                                         
        Rotate(modelView, sphere_ROTATE[0], sphere_ROTATE[1], sphere_ROTATE[2], sphere_ROTATE[3] + spinModel);          
        #include "_MODEL_FOLDERS_/sphere/sphere_Render.cpp"  
        //------------------------------------------------------------------------------------                                           
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                                                                   
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);        
        //--------------------------------------------------------------------------------------
        Translate(modelView, spiralGear_POSITION[0], spiralGear_POSITION[1], spiralGear_POSITION[2]);                                                                                         
        Rotate(modelView, spiralGear_ROTATE[0], spiralGear_ROTATE[1], spiralGear_ROTATE[2], spiralGear_ROTATE[3]);        
        #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Render.cpp"          
        //------------------------------------------------------------------------------------                                          
        LoadIdentity(modelView); 
        moveKnight += 0.005;                                                                                                                                                 
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                                                                    
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);       
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);         
        Translate(modelView, knight_POSITION[0], knight_POSITION[1], knight_POSITION[2]);                                                                                         
        Rotate(modelView, knight_ROTATE[0], knight_ROTATE[1], knight_ROTATE[2], knight_ROTATE[3]);        
        #include "_MODEL_FOLDERS_/knight/knight_Render.cpp"                                                                 
       //------------------------------------------------------------------------------------
                                                         
        //===================================================================================================================== 
/**/        

        //====================================================================================   
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);        
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);    
        Translate(modelView, facing_UP_POSITION[0], facing_UP_POSITION[1], facing_UP_POSITION[2]);            
        Rotate(modelView, facing_UP_ROTATE[0], facing_UP_ROTATE[1], facing_UP_ROTATE[2], facing_UP_ROTATE[3]);              
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_Render.cpp"                                                                 
        //====================================================================================   
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
         Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);    
      //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]); 
        Translate(modelView, facing_VIEW_POSITION[0], facing_VIEW_POSITION[1], facing_VIEW_POSITION[2]);                                                                                         
        Rotate(modelView, facing_VIEW_ROTATE[0], facing_VIEW_ROTATE[1], facing_VIEW_ROTATE[2], facing_VIEW_ROTATE[3]);//--MODEL         
        #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_Render.cpp"                                                                 
        //====================================================================================                                          
        #include  "ADD_COLLISION_BALL/RENDER_1.cpp"
        LoadIdentity(modelView);                                                                                                              
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);     
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);         
         //----------------------------------------------------------- 
        Translate(modelView,   spikyBall_0_POSITION[0], spikyBall_0_POSITION[1], spikyBall_0_POSITION[2]);      
        Rotate(modelView,      spikyBall_0_ROTATE[0], spikyBall_0_ROTATE[1], spikyBall_0_ROTATE[2], spikyBall_0_ROTATE[3]);         
        #include "_MODEL_FOLDERS_/spikyBall_0/spikyBall_0_Render.cpp"   
        //====================================================================================                                          
        glEnable(GL_BLEND);
        #include "_MODEL_FOLDERS_/frameBufferPlane/frameBufferPlane_Render.cpp"                                                                 
        glDisable(GL_BLEND);        
        //====================================================================================      
