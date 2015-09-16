    
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                                                                    
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);                                                                                                                                                  
    
    Translate(modelView, centerPiller_POSITION[0], centerPiller_POSITION[1], centerPiller_POSITION[2]);                                                                                         
    
    Rotate(modelView, centerPiller_ROTATE[0], centerPiller_ROTATE[1], centerPiller_ROTATE[2], centerPiller_ROTATE[3]);                                                                      
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------    
    
    glBindBuffer(GL_ARRAY_BUFFER, centerPiller_VBO);                                                                                                                                
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, centerPiller_INDICES_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
            
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix, 1.0, -10.0, 2.0);                                                                                                                                
    //======================================================================================================                                                                  
    //------------------------------------------------------------------------------------------------------          
    
    glUseProgram(centerPiller_SHADER);      
   
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));                                                                                                  
    glEnableVertexAttribArray(1);    
    glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));                                                                                                  
    glEnableVertexAttribArray(2);      
    glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));                                                                                                 
    glEnableVertexAttribArray(3);                                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_centerPiller, centerPiller_LIGHT_POSITION_01[0], centerPiller_LIGHT_POSITION_01[1], centerPiller_LIGHT_POSITION_01[2], centerPiller_LIGHT_POSITION_01[3]);        
    glUniform1f(UNIFORM_SHININESS_centerPiller, centerPiller_SHININESS);                                                                                                                  
    glUniform1f(UNIFORM_ATTENUATION_centerPiller, centerPiller_ATTENUATION);                                                                                                                  
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_centerPiller,   1,0,  mvpMatrix);                                                                                                      
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_centerPiller,    1,0,  lightMatrix);    
    glUniformMatrix4fv(UNIFORM_textureMatrix_centerPiller,   1,0,  BiasMatrix);                                                                                                     
    //------------------------------------------------    
    glUniform1i (UNIFORM_TEXTURE_SHADOW_centerPiller, 3);      
    
    glUniform1i (UNIFORM_TEXTURE_DOT3_centerPiller, 1);      
    glUniform1i (UNIFORM_TEXTURE_centerPiller, 0 );   
                                                                                                                        
    //------------------------------------------------                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 192, GL_UNSIGNED_INT, 0);                                                                                                     

