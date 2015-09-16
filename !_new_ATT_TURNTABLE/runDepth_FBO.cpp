	glBindFramebuffer(GL_FRAMEBUFFER, fboId_3D);//-----------------------F.B.O.     
        //----------------------------------------------------------------
        //glColor4f(color is changed using fragment program)
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glClear (GL_DEPTH_BUFFER_BIT);
        glViewport(1, 1, (GLsizei)viewWidth / resize_SHADOW_FBO - 2, (GLsizei)viewHeight / resize_SHADOW_FBO - 2);
        //----------------------------------------------------------------
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
    

        PerspectiveMatrix(ProjectionShadow, fieldOfView, viewWidth / viewHeight,  adjustNearFar[0],  adjustNearFar[1]);
        //Rotate(ProjectionShadow, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        //Rotate(ProjectionShadow, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
       
        //glPolygonOffset(2.5, 10.0);
        //glEnable(GL_POLYGON_OFFSET_FILL);
        
        //glDisable(GL_CULL_FACE);
        
        

        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();       
        #include "_MODEL_FOLDERS_/sculptris/sculptris_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();       
        #include "_MODEL_FOLDERS_/sphere/sphere_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();      
        #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();       
        #include "_MODEL_FOLDERS_/knight/knight_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();      
        #include "_MODEL_FOLDERS_/blocksEdging/blocksEdging_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 48;//shadow_44bit_Stride
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_blocks_01_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 48;//shadow_44bit_Stride        
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/facing_Sideways_blocks_01/facing_Sideways_blocks_01_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 48;//shadow_44bit_Stride          
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_blocks_01/facing_UP_blocks_01_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride          
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/pillerPlantPot/pillerPlantPot_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride          
        setupTransforms_Shadows();    
        #include "_MODEL_FOLDERS_/plant_v005/plant_v005_Shadow_01.cpp"                                                              
        //====================================================================================                                                                
  
        
        
        //glEnable(GL_CULL_FACE);


//========================================================================================================================================



//############################################################################################################################################### 
//###############################################################################################################################################   
//###############################################################################################################################################   
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 	                       
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	
	
	
	
	
	
