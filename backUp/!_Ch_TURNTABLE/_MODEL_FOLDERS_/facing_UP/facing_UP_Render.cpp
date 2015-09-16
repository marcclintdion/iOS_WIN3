glUseProgram(facing_UP_SHADER);                                                                                                                                              
    glBindBuffer(GL_ARRAY_BUFFER, facing_UP_VBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facing_UP_INDEX_VBO);                                                                                                                                   
    
    //==========================================================================================
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(textureMatrix);
    //Translate(textureMatrix, shadowsPositionOffset[0], shadowsPositionOffset[1], shadowsPositionOffset[2]);
    //Scale(textureMatrix, scaleShadows, scaleShadows, scaleShadows);   
    
    //gluLookAt(textureMatrix, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
    //Rotate(textureMatrix, 0.0, 1.0, 0.0, -turnTable);
    
    
    
    //Rotate(textureMatrix, 1.0, 0.0, 0.0,  rotateModelWithLeftMouse[0]);  
    //mtxTranspose(textureMatrix, textureMatrix);
    
    
    //Rotate(textureMatrix, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);    
     
    //InvertMatrix(textureMatrix, textureMatrix);     
     
    
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);  
    glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));                                                                                                 
    glEnableVertexAttribArray(2);     
    glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));                                                                                                 
    glEnableVertexAttribArray(3);                                                                                                                                                
    //======================================================================================================                
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_facing_UP,     1,0,  mvpMatrix); 
    glUniformMatrix4fv(UNIFORM_MODELVIEW_facing_UP,         1,0,  modelView);     
    //---------------     
    glUniformMatrix4fv(UNIFORM_viewMatrix_facing_UP,        1,0,  viewMatrix);     
    //---------------  
    glUniformMatrix4fv(UNIFORM_SHADOW_PROJ_facing_UP,       1,0,  ProjectionShadow);   
    glUniformMatrix4fv(UNIFORM_modelViewShadow_facing_UP,   1,0,  modelViewShadow);     
    //----------------                                                                                                         
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_facing_UP,      1,0,  lightMatrix);
    glUniformMatrix4fv(UNIFORM_textureMatrix_facing_UP,     1,0,  textureMatrix);  
    //---------------------------------------------------------------------------------
    glUniform4f(UNIFORM_offset_facing_UP,                        offsetFinalShadow[0], 
                                                                 offsetFinalShadow[1], 
                                                                 offsetFinalShadow[2], 
                                                                 offsetFinalShadow[3]);      
    //---------------------------------------------------------------------------------    
    glUniform4f(UNIFORM_LIGHT_POSITION_01_facing_UP, facing_UP_LIGHT_POSITION_01[0], 
                                                     facing_UP_LIGHT_POSITION_01[1], 
                                                     facing_UP_LIGHT_POSITION_01[2], 
                                                     facing_UP_LIGHT_POSITION_01[3]);        
    //---------------------------------------------------------------------------------     
    glUniform1f(UNIFORM_SHININESS_facing_UP, facing_UP_SHININESS);  
    //---------------------------------------------------------------------------------    
    glUniform1f(UNIFORM_CONSTANT_ATTENUATION_facing_UP,  facing_VIEW_constantAttenuation);     
    glUniform1f(UNIFORM_LINEAR_ATTENUATION_facing_UP,    facing_VIEW_linearAttenuation); 
    glUniform1f(UNIFORM_QUADRATIC_ATTENUATION_facing_UP, facing_VIEW_quadraticAttenuation);    
    //---------------------------------------------------------------------------------    
    glUniform1i (UNIFORM_TEXTURE_LightMap_facing_UP, 4);     
    glUniform1i (UNIFORM_TEXTURE_SHADOW_facing_UP, 3);      
    glUniform1i (UNIFORM_TEXTURE_HEIGHT_facing_UP, 2);     
    glUniform1i (UNIFORM_TEXTURE_DOT3_facing_UP, 1);                                                                                                                             
    glUniform1i (UNIFORM_TEXTURE_facing_UP, 0 );                                                                                                                                 
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE4 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, geometryLightPass_TEXTURE);                                                                                                                          
    //---      
    glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, shadowMap_TEXTURE);                                                                                                                          
    //---     
    glActiveTexture ( GL_TEXTURE2 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, facing_UP_HEIGHT);                                                                                                                          
    //---     
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, facing_UP_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, facing_UP_TEXTUREMAP );                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 294, GL_UNSIGNED_INT, 0);