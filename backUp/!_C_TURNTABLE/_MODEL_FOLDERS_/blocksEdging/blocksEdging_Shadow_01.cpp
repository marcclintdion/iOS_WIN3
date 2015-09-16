glBindBuffer(GL_ARRAY_BUFFER, blocksEdging_VBO);                                                                                                                                
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, blocksEdging_INDICES_VBO);       
//---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
       LoadIdentity(modelViewShadow);                                                                                                                                                  
       gluLookAt(modelViewShadow, eyeposition[0]+eyeposition_SHADOW[0] * scaleMoveShadows[0], 
                            eyeposition[1]+eyeposition_SHADOW[1] * scaleMoveShadows[1], 
                            eyeposition[2]+eyeposition_SHADOW[2] * scaleMoveShadows[2], 
                            lookAt[0]+lookAt_SHADOW[0]      * scaleMoveShadows[0], 
                            lookAt[1]+lookAt_SHADOW[1]      * scaleMoveShadows[1], 
                            lookAt[2]+lookAt_SHADOW[2]      * scaleMoveShadows[2], 
                            upVector[0], 
                            upVector[1], 
                            upVector[2]);                                                                                                                                                    
   
       Rotate(modelViewShadow, 0.0, 1.0, 0.0, turnTable); 
       //--------------------------------------------------------------------------------------  
       Translate(modelViewShadow, moveSet[0] + moveShadow[0] , moveSet[1] + moveShadow[1] , moveSet[2] + moveShadow[2]); 
       Rotate(modelViewShadow, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
       Rotate(modelViewShadow, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
       //----------------------------------------------------------------------------------------
       Translate(modelViewShadow, blocksEdging_POSITION[0] * scaleMoveShadows[0], 
                                  blocksEdging_POSITION[1] * scaleMoveShadows[1], 
                                  blocksEdging_POSITION[2] * scaleMoveShadows[2]);                                                                                         
                                  //------------------------------------------------------
       Rotate(modelViewShadow,    blocksEdging_ROTATE[0], 
                                  blocksEdging_ROTATE[1], 
                                  blocksEdging_ROTATE[2], 
                                  blocksEdging_ROTATE[3]);         
                                  //------------------------------------------------------ 
       Scale(modelViewShadow,     scaleShadowSize, 
                                  scaleShadowSize, 
                                  scaleShadowSize);         
       //------------------------------------------------------------------------------------------------                                                                                                                                            
                MultiplyMatrix(mvpMatrix, ProjectionShadow, modelViewShadow);                                                                                                                         
                //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           //------------------------------------------------------------------------------------
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow_32bit_Stride, 1, 0,  mvpMatrix);
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 2286, GL_UNSIGNED_INT, 0);