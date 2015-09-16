        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gaussianBlurVerticalPass_fboId);//----
        //-------------------------------------------------------------------------------------                                         

        //=========================================================================================================================================================    
        glClearColor( 1.0f, 0.0f, 0.0f, 0.5f );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
        //----------------------------------------------------------------------------------
        glViewport(0, 0, (GLsizei)viewWidth / resize_SHADOW_FBO, (GLsizei)viewHeight / resize_SHADOW_FBO );
        
        PerspectiveMatrix2(projection, viewWidth / viewHeight);
        
        //=========================================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        #endif        
        //=========================================================================================================================================================        
        #ifdef WIN32        
        #endif           
        //=========================================================================================================================================================               
       
glUseProgram(frameBufferPlane_GaussianVertical_SHADER);                                                                                                                                              
glBindBuffer(GL_ARRAY_BUFFER, frameBufferPlane_VBO);                                                                                                                                
    //------------------------------------------------------------------------------------------------------------------------------------           
 
    LoadIdentity(modelView);                                                                                                                                                  
    //gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
    Rotate(modelView, frameBufferPlane_ROTATE[0], frameBufferPlane_ROTATE[1], frameBufferPlane_ROTATE[2], frameBufferPlane_ROTATE[3]);//--MODEL                                                                       
    Scale(modelView, frameBufferPlane_SCALE[0], frameBufferPlane_SCALE[1], frameBufferPlane_SCALE[2]);     
          
    //------------------------------------------------------------------------------------------------------------------------------------    
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //------------------------------------------------------------------------------------------------------------------------------------
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
  
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);                                                                                                                                             
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_frameBufferPlane_GaussianVertical, frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[0], frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[1], frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[2], frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[3]);        
                                                                                                               
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_frameBufferPlane_GaussianVertical,   1,0,  mvpMatrix);                                                                                                      
    
    glUniform1f (UNIFORM_blurRadius_frameBufferPlane_GaussianVertical, frameBufferPlane_GaussianVertical_blurRadius);                                                                                                                           
                                                                                                                           
    glUniform1i (UNIFORM_TEXTURE_frameBufferPlane_GaussianVertical, 0 );                                                                                                                                 
    //======================================================================================================                                                                  

    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
   glDrawArrays(GL_TRIANGLES, 0, 6);                                                                                                     
        
        //---------------------------------------------------------------------------------------------------------------------
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);    //--------------------------------
        
        
        
                 
  
