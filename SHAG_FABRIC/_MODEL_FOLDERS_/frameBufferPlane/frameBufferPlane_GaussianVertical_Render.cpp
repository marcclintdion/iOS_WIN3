    glUseProgram(frameBufferPlane_GaussianVertical_SHADER);                                                                                                                                              
    glBindBuffer(GL_ARRAY_BUFFER, frameBufferPlane_GaussianVertical_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
    LoadIdentity(modelView);                                                                                                                                                  
    Translate(modelView, frameBufferPlane_GaussianVertical_POSITION[0], frameBufferPlane_GaussianVertical_POSITION[1], frameBufferPlane_GaussianVertical_POSITION[2]);                                                                                         
    Rotate(modelView, frameBufferPlane_GaussianVertical_ROTATE[0], frameBufferPlane_GaussianVertical_ROTATE[1], frameBufferPlane_GaussianVertical_ROTATE[2], frameBufferPlane_GaussianVertical_ROTATE[3]);//--MODEL                                                                       
    Scale(modelView, frameBufferPlane_GaussianVertical_SCALE[0], frameBufferPlane_GaussianVertical_SCALE[1], frameBufferPlane_GaussianVertical_SCALE[2]);     
    MultiplyMatrix(mvpMatrix, ScreenBufferMatrix, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix, 1.0, -10.0, 2.0);                                                                                                                                
   //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);                                                                                                                                             
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_frameBufferPlane_GaussianVertical, frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[0], frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[1], frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[2], frameBufferPlane_GaussianVertical_LIGHT_POSITION_01[3]);        
    glUniform1f(UNIFORM_SHININESS_frameBufferPlane_GaussianVertical, frameBufferPlane_GaussianVertical_SHININESS);                                                                                                                  
    glUniform1f(UNIFORM_ATTENUATION_frameBufferPlane_GaussianVertical, frameBufferPlane_GaussianVertical_ATTENUATION); 
    glUniform1f(UNIFORM_ratio_Global_2_Component_frameBufferPlane_GaussianVertical, frameBufferPlane_GaussianVertical_ratio_Global_2_Component);     
                                                                                                                   
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_frameBufferPlane_GaussianVertical,   1,0,  mvpMatrix);                                                                                                      
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_frameBufferPlane_GaussianVertical,    1,0,  lightMatrix);                                                                                                    
    glUniform1i (UNIFORM_TEXTURE_2_frameBufferPlane_GaussianVertical, 1);                                                                                                                             
    glUniform1i (UNIFORM_TEXTURE_frameBufferPlane_GaussianVertical, 0 );                                                                                                                                 
    //======================================================================================================                                                                  
    
                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawArrays(GL_TRIANGLES, 0, 6);                                                                                                     

