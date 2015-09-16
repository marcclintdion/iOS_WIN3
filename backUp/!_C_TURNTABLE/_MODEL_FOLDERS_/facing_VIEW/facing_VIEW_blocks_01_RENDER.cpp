            
   
    glBindBuffer(GL_ARRAY_BUFFER, facing_VIEW_blocks_01_VBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facing_VIEW_blocks_01_INDICES_VBO);                                                                                                                                   
    //==========================================================================================================================    
        LoadIdentity(modelView);                                                                                                                                                  
        //--------------------------------------------------------------------------------------
        gluLookAt(modelView, eyeposition[0], 
                             eyeposition[1], 
                             eyeposition[2], 
                             lookAt[0], 
                             lookAt[1], 
                             lookAt[2], 
                             upVector[0], 
                             upVector[1], 
                             upVector[2]);
        //--------------------------------------------------------------------------------------                                                                                                                                   
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);    
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], 
                             matchColorModelToShadowPosition[1], 
                             matchColorModelToShadowPosition[2]); 
        //--------------------------------------------------------------------------------------                     
        Translate(modelView, facing_VIEW_POSITION[0], 
                             facing_VIEW_POSITION[1], 
                             facing_VIEW_POSITION[2]);                                                                                         
        //-------------------------------------------------------------------------------------- 
        Rotate(modelView,    facing_VIEW_ROTATE[0], 
                             facing_VIEW_ROTATE[1], 
                             facing_VIEW_ROTATE[2], 
                             facing_VIEW_ROTATE[3]);        
    //===========================================================================================================================
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Rotate(lightMatrix,1.0, 0.0, 0.0, 45.0);
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(textureMatrix);
    //Translate(textureMatrix, shadowsPositionOffset[0], shadowsPositionOffset[1], shadowsPositionOffset[2]);
    //Scale(textureMatrix, scaleShadows, scaleShadows, scaleShadows);   
//======================================================================================================                                                                  
glUseProgram(facing_VIEW_SHADER);                                                                                                                                              
   
  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);  
    glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));                                                                                                 
    glEnableVertexAttribArray(2);     
    glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));                                                                                                 
    glEnableVertexAttribArray(3);                                                                                                                                                
   
//======================================================================================================   
//======================================================================================================                
SelectShader(shaderNumber);//ConeStep_01/steepPointy
//======================================================================================================                                                                  
//======================================================================================================                                                                  
    
    glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);                                                                                                                          
    //---     
    glActiveTexture ( GL_TEXTURE2 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, facing_VIEW_HEIGHT);                                                                                                                          
    //---     
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, facing_VIEW_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, facing_VIEW_TEXTUREMAP );                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_INT, 0);
