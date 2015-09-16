glUseProgram(SHADER_shadow_44bit_Stride);
      LoadIdentity(modelView);                                                                                                                                                  
       gluLookAt(modelView, eyeposition[0]+eyeposition_SHADOW[0] * scaleMoveShadows[0], 
                            eyeposition[1]+eyeposition_SHADOW[1] * scaleMoveShadows[1], 
                            eyeposition[2]+eyeposition_SHADOW[2] * scaleMoveShadows[2], 
                            lookAt[0]+lookAt_SHADOW[0]      * scaleMoveShadows[0], 
                            lookAt[1]+lookAt_SHADOW[1]      * scaleMoveShadows[1], 
                            lookAt[2]+lookAt_SHADOW[2]      * scaleMoveShadows[2], 
                            upVector[0], 
                            upVector[1], 
                            upVector[2]);                                                                                                                                                    
       Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
       //--------------------------------------------------------------------------------------  
       Translate(modelView, moveSet[0] + moveShadow[0] , moveSet[1] + moveShadow[1] , moveSet[2] + moveShadow[2]); 
       Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
       Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
       //----------------------------------------------------------------------------------------
       //------------------------------------------------------------
       Translate(modelView, facing_VIEW_blocks_01_POSITION[0] * scaleMoveShadows[0], facing_VIEW_blocks_01_POSITION[1] * scaleMoveShadows[1], facing_VIEW_blocks_01_POSITION[2] * scaleMoveShadows[2]);                                                                                         
       Rotate(modelView, facing_VIEW_blocks_01_ROTATE[0], facing_VIEW_blocks_01_ROTATE[1], facing_VIEW_blocks_01_ROTATE[2], facing_VIEW_blocks_01_ROTATE[3]);          
      
       //-------------------------------------------------------------
            glBindBuffer(GL_ARRAY_BUFFER, facing_Sideways_blocks_01_VBO);   
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facing_Sideways_blocks_01_INDICES_VBO);                                                                                                                                     
            //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
                MultiplyMatrix(mvpMatrix, ProjectionShadow, modelView);                                                                                                                         
                //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
                LoadIdentity(lightMatrix);                                                                                                                                                
                InvertMatrix(lightMatrix, modelView);                                                                                                                                     
                                                                
                glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
                glBindTexture(GL_TEXTURE_2D, facing_VIEW_blocks_01_NORMALMAP);                                                                                                                          
                //---                                                                                                                                                                     
                glActiveTexture (GL_TEXTURE0);                                                                                                                                            
                glBindTexture(GL_TEXTURE_2D, facing_VIEW_blocks_01_TEXTUREMAP);                                                                                                                            
                //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
               
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));
                           glEnableVertexAttribArray(3);                              
                           glUniform4f(UNIFORM_offset_shadow_32bit_Stride, offset_ShadowShader[0],  
                                                                offset_ShadowShader[1], 
                                                                offset_ShadowShader[2], 
                                                                offset_ShadowShader[3]);
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow_32bit_Stride,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow_32bit_Stride, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow_32bit_Stride,  1, 0,  lightMatrix);  
                      //--------------------------------------------------------------------------------------------------------------------------------------
                      
    glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_INT, 0);
