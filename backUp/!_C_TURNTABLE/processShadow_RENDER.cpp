glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, processShadow_fboId);
glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, processShadow_depthFboId);
//-------------------------------------------------------        


        //================================================================================================================================================
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0 );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      
        //----------------------------------------------------------------------------------
        glViewport(0, 0, (GLsizei)viewWidth, (GLsizei)viewHeight);
        PerspectiveMatrix(projection, fieldOfView, viewWidth / viewHeight, adjustNearFar[0],  adjustNearFar[1]);
        //=====================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW
        #endif
        //#################################################################################################################################
        //---------------------------------------------------------------------------------------------------------------------------------
        //###############____________32_bit_Stride____________#############################################################################
       
 
        //====================================================================================---------------
        shaderNumber = 47;//plastic/rubber/ 
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Render.cpp"
        //====================================================================================
        shaderNumber = 47;//plastic/rubber/ 
        #include "_MODEL_FOLDERS_/sculptris/sculptris_Render.cpp"
        //====================================================================================
        shaderNumber = 47;//plastic/rubber/ 
        #include "_MODEL_FOLDERS_/sphere/sphere_Render.cpp"
        //====================================================================================
        shaderNumber = 47;//plastic/rubber/ 
        #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Render.cpp"
        //====================================================================================
        shaderNumber = 47;//plastic/rubber/ 
        #include "_MODEL_FOLDERS_/knight/knight_Render.cpp"
        //====================================================================================---------------
        shaderNumber = 47;//wood/goldenSunset 
        #include "_MODEL_FOLDERS_/floorStraps/floorStraps_Render.cpp"
        //====================================================================================
        shaderNumber = 47;//wood/goldenSunset 
        #include "_MODEL_FOLDERS_/wallStraps/wallStraps_Render.cpp"
        //====================================================================================
        shaderNumber = 47;//wood/goldenSunset 
        #include "_MODEL_FOLDERS_/blocksEdging/blocksEdging_Render.cpp"
        //====================================================================================

        //#################################################################################################################################          
        //---------------------------------------------------------------------------------------------------------------------------------
        //###############____________44_bit_Stride____________#############################################################################
 
/*
        //====================================================================================---------------
        shaderNumber = 48;//ConeStep_01/shallowRound
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_Render.cpp"
        //====================================================================================
        shaderNumber = 48;//ConeStep_01/shallowRound
        #include "_MODEL_FOLDERS_/facing_Sideways_blocks_01/facing_Sideways_blocks_01_RENDER.cpp"                   
        //====================================================================================
        shaderNumber = 48;//ConeStep_01/shallowRound
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_blocks_01/facing_UP_blocks_01_RENDER.cpp"
        //====================================================================================---------------
        shaderNumber = 48;//ConeStep_01/steepPointy
        #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_Render.cpp"
        //====================================================================================
        shaderNumber = 48;//ConeStep_01/steepPointy
        #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_blocks_01_Render.cpp"
        //====================================================================================
*/
        
        
                                                                      
//==============================================================================================================================


//------------------------------------------------------------------------------------------------------------------------------
glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

