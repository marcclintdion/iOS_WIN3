    glUseProgram(frameBufferPlane_SHADER);                                                                                                                                              
    glBindBuffer(GL_ARRAY_BUFFER, frameBufferPlane_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
 
    LoadIdentity(modelView);                                                                                                                                                  
    //gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
    Translate(modelView, frameBufferPlane_POSITION[0], frameBufferPlane_POSITION[1], frameBufferPlane_POSITION[2]);                                                                                         
    Rotate(modelView, frameBufferPlane_ROTATE[0], frameBufferPlane_ROTATE[1], frameBufferPlane_ROTATE[2], frameBufferPlane_ROTATE[3]);//--MODEL                                                                       
    Scale(modelView, frameBufferPlane_SCALE[0], frameBufferPlane_SCALE[1], frameBufferPlane_SCALE[2]);     
         
    //------------------------------------------------------------------------------------------------------------------------------------    
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
  
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);                                                                                                                                             
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_frameBufferPlane, frameBufferPlane_LIGHT_POSITION_01[0], frameBufferPlane_LIGHT_POSITION_01[1], frameBufferPlane_LIGHT_POSITION_01[2], frameBufferPlane_LIGHT_POSITION_01[3]);        
                                                                                                               
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_frameBufferPlane,   1,0,  mvpMatrix);                                                                                                      
                                                                                                                          
    glUniform1i (UNIFORM_TEXTURE_frameBufferPlane, 0 );                                                                                                                                 
    //======================================================================================================                                                                  
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);   //  textureMap[2]      
                   
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawArrays(GL_TRIANGLES, 0, 6);                                                                                                     

