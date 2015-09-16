glUseProgram(SHADER_shadow_32bit_Stride);    
       LoadIdentity(LightModelViewMatrix);                                                                                                                                                  
      gluLookAt(LightModelViewMatrix, eyeposition[0] + eyeposition_SHADOW[0] - eyeposition[0] * adjustLookAtMove[0], 
                                      eyeposition[1] + eyeposition_SHADOW[1] - eyeposition[1] * adjustLookAtMove[1], 
                                      eyeposition[2] + eyeposition_SHADOW[2] - eyeposition[2] * adjustLookAtMove[2],
                                      lookAt[0]      + lookAt_SHADOW[0]      * scaleMoveShadows[0], 
                                      lookAt[1]      + lookAt_SHADOW[1]      * scaleMoveShadows[1], 
                                      lookAt[2]      + lookAt_SHADOW[2]      * scaleMoveShadows[2], 
                                      upVector[0], 
                                      upVector[1], 
                                      upVector[2]);                                                                                                                                                   
       //--------------------------------------------------------------------------------------  
       Rotate(LightModelViewMatrix, 0.0, 1.0, 0.0, turnTable * scaleTurnTable); 
       //--------------------------------------------------------------------------------------         
       AssignMatrix(modelViewShadow, LightModelViewMatrix);
       //-------------------------------------------------------------------------------------- 
       Translate(LightModelViewMatrix, moveSet[0] + moveShadow[0] , moveSet[1] + moveShadow[1] , moveSet[2] + moveShadow[2]); 
       //----------------------------------------------------------------------------------------------------------  
       Rotate(   LightModelViewMatrix, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
       Rotate(   LightModelViewMatrix, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
       //---------------------------------------------------------------------
       Translate(LightModelViewMatrix, sculptris_POSITION[0] * scaleMoveShadows[0], 
                                  sculptris_POSITION[1] * scaleMoveShadows[1], 
                                  sculptris_POSITION[2] * scaleMoveShadows[2]);        
                                  //------------------------------------------
       Rotate(LightModelViewMatrix,    sculptris_ROTATE[0], 
                                  sculptris_ROTATE[1], 
                                  sculptris_ROTATE[2], 
                                  sculptris_ROTATE[3]);        
                                  //---------------------------------------------------------------------
       Scale(LightModelViewMatrix,     scaleShadowSize, 
                                  scaleShadowSize, 
                                  scaleShadowSize);       
       //------------------------------------------------------------------------------------------------
          glBindBuffer(GL_ARRAY_BUFFER, sculptris_VBO);    
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sculptris_INDEX_VBO);                                                                                                                                 
          //---------------------------------------------------------------------------       
          MultiplyMatrix(mvpMatrix, ProjectionShadow, LightModelViewMatrix);                                                                                                                         
          //---------------------------------------------------------------------------            
          LoadIdentity(lightMatrix);                                                                                                                                                
          InvertMatrix(lightMatrix, LightModelViewMatrix);                                                                                                                                     
          //---------------------------------------------------------------------------                
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           //--------------------------------------------------------------------------- 
                           glUniform4f(UNIFORM_offset_shadow_32bit_Stride, offset_ShadowShader[0],  
                                                                           offset_ShadowShader[1], 
                                                                           offset_ShadowShader[2], 
                                                                           offset_ShadowShader[3]);
                          //-----------------
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow_32bit_Stride,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow_32bit_Stride, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow_32bit_Stride,  1, 0,  lightMatrix);  
                           //--------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                                      
glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, sculptris_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, sculptris_TEXTUREMAP);                                                                                                                                             
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 1584, GL_UNSIGNED_INT, 0);  
