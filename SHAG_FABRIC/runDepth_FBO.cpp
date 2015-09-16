    

        
        PerspectiveMatrix(ProjectionShadow, 35, viewWidth / viewHeight,  adjustNearFar[0],  adjustNearFar[1]);
        //Translate(ProjectionShadow, eyeposition_SHADOW[0], eyeposition_SHADOW[1], eyeposition_SHADOW[2]);
         
        glUseProgram(SHADER_shadow);
        
//================================================================================================================================                         
                      //-----------------------------                      
                      glBindBuffer(GL_ARRAY_BUFFER, spikyBall_0_VBO);   
                      //-------------------------------------------------------------------------------------------------------------------------------------------|__TRANSFORMATIONS         
    LoadIdentity(modelView);                                                                                                              
       gluLookAt(modelView, eyeposition[0] * scaleMoveShadows[0], 
                            eyeposition[1] * scaleMoveShadows[1], 
                            eyeposition[2] * scaleMoveShadows[2], 
                            lookAt[0]      * scaleMoveShadows[0], 
                            lookAt[1]      * scaleMoveShadows[1], 
                            lookAt[2]      * scaleMoveShadows[2], 
                            upVector[0], 
                            upVector[1], 
                            upVector[2]);                                                                                                                                                    
       Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
       //--------------------------------------------------------------------------------------  
       Translate(modelView, moveSet[0] + moveShadow[0] , moveSet[1] + moveShadow[1] , moveSet[2] + moveShadow[2]); 
       Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
       Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
       //-------------------------------------------------------------------------------------------------------------------
       Translate(modelView,   spikyBall_0_POSITION[0] * scaleMoveShadows[0], spikyBall_0_POSITION[1] * scaleMoveShadows[1], spikyBall_0_POSITION[2] * scaleMoveShadows[2]);      
       Rotate(modelView,      spikyBall_0_ROTATE[0], spikyBall_0_ROTATE[1], spikyBall_0_ROTATE[2], spikyBall_0_ROTATE[3]);  
       Scale(modelView, scaleShadowSize[0], scaleShadowSize[1], scaleShadowSize[2]);                     
                      //-------------------------------------------------------------------------------------------- 
                      MultiplyMatrix(mvpMatrix, ProjectionShadow, modelView); 
                      //--------------------------------------------------------------------------------------------------------------------------------------
                                      
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);               
                           //--------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS
                           glUniform4f(UNIFORM_LIGHT_POSITION_01_shadow, shadowLightPosition[0],  
                                                                shadowLightPosition[1], 
                                                                shadowLightPosition[2], 
                                                                shadowLightPosition[3]);    
                           glUniform4f(UNIFORM_offset_shadow, offset_ShadowShader[0],  
                                                                offset_ShadowShader[1], 
                                                                offset_ShadowShader[2], 
                                                                offset_ShadowShader[3]);                                                                
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow,  1, 0,  lightMatrix);  
                      //--------------------------------------------------------------------------------------------------------------------------------------
                      
                      glDrawArrays(GL_TRIANGLES, 0, 540);  	 

//================================================================================================================================
    LoadIdentity(modelView);                                                                                                                                                  
       gluLookAt(modelView, eyeposition[0] * scaleMoveShadows[0], 
                            eyeposition[1] * scaleMoveShadows[1], 
                            eyeposition[2] * scaleMoveShadows[2], 
                            lookAt[0]      * scaleMoveShadows[0], 
                            lookAt[1]      * scaleMoveShadows[1], 
                            lookAt[2]      * scaleMoveShadows[2], 
                            upVector[0], 
                            upVector[1], 
                            upVector[2]);                                                                                                                                                    
       Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
       //--------------------------------------------------------------------------------------  
       Translate(modelView, moveSet[0] + moveShadow[0] , moveSet[1] + moveShadow[1] , moveSet[2] + moveShadow[2]); 
       Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
       Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
       //----------------------------------------------------------------------------------------
       Translate(modelView, flowerShield_POSITION[0] * scaleMoveShadows[0], flowerShield_POSITION[1] * scaleMoveShadows[1], flowerShield_POSITION[2] * scaleMoveShadows[2]);                                                                                         
       Rotate(modelView, flowerShield_ROTATE[0], flowerShield_ROTATE[1], flowerShield_ROTATE[2], flowerShield_ROTATE[3]);         
       Scale(modelView, scaleShadowSize[0], scaleShadowSize[1], scaleShadowSize[2]);
                                                                                                                                               
    glBindBuffer(GL_ARRAY_BUFFER, flowerShield_VBO);                                                                                                                                
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flowerShield_INDEX_VBO);       
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
                                                                     
    MultiplyMatrix(mvpMatrix, ProjectionShadow, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
   
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix, 1.0, -10.0, 2.0);                                                                                                                                
                           
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           glUniform4f(UNIFORM_LIGHT_POSITION_01_shadow, shadowLightPosition[0],  
                                                                shadowLightPosition[1], 
                                                                shadowLightPosition[2], 
                                                                shadowLightPosition[3]);         
                           glUniform4f(UNIFORM_offset_shadow, offset_ShadowShader[0],  
                                                                offset_ShadowShader[1], 
                                                                offset_ShadowShader[2], 
                                                                offset_ShadowShader[3]);                           
                           //--------------
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow,  1, 0,  lightMatrix);  
                           //--------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                                           
    //---               
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, flowerShield_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, flowerShield_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
//================================================================================================================================       //------------------------------------------------------------------------------------                                           
    LoadIdentity(modelView);                                                                                                                                                  
       gluLookAt(modelView, eyeposition[0] * scaleMoveShadows[0], 
                            eyeposition[1] * scaleMoveShadows[1], 
                            eyeposition[2] * scaleMoveShadows[2], 
                            lookAt[0]      * scaleMoveShadows[0], 
                            lookAt[1]      * scaleMoveShadows[1], 
                            lookAt[2]      * scaleMoveShadows[2], 
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
       Translate(modelView, sculptris_POSITION[0] * scaleMoveShadows[0], sculptris_POSITION[1] * scaleMoveShadows[1], sculptris_POSITION[2] * scaleMoveShadows[2]);                                                                                         
       Rotate(modelView, sculptris_ROTATE[0], sculptris_ROTATE[1], sculptris_ROTATE[2], sculptris_ROTATE[3]+spinModel);         
       Scale(modelView, scaleShadowSize[0], scaleShadowSize[1], scaleShadowSize[2]);
      
                                                                                                                                             
    glBindBuffer(GL_ARRAY_BUFFER, sculptris_VBO);   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sculptris_INDEX_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
                                                                                                                                                
                                                                     
    MultiplyMatrix(mvpMatrix, ProjectionShadow, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix, 1.0, -10.0, 2.0);                                                                                                                                
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           glUniform4f(UNIFORM_LIGHT_POSITION_01_shadow, shadowLightPosition[0],  
                                                                shadowLightPosition[1], 
                                                                shadowLightPosition[2], 
                                                                shadowLightPosition[3]);         
                           glUniform4f(UNIFORM_offset_shadow, offset_ShadowShader[0],  
                                                                offset_ShadowShader[1], 
                                                                offset_ShadowShader[2], 
                                                                offset_ShadowShader[3]);
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow,  1, 0,  lightMatrix);  
                      //--------------------------------------------------------------------------------------------------------------------------------------
                      
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, sculptris_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, sculptris_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 1584, GL_UNSIGNED_INT, 0);                                                                                                    
//================================================================================================================================                                                               
       //------------------------------------------------------------------------------------                                           
       LoadIdentity(modelView);                                                                                                                                                  
       gluLookAt(modelView, eyeposition[0] * scaleMoveShadows[0], 
                            eyeposition[1] * scaleMoveShadows[1], 
                            eyeposition[2] * scaleMoveShadows[2], 
                            lookAt[0]      * scaleMoveShadows[0], 
                            lookAt[1]      * scaleMoveShadows[1], 
                            lookAt[2]      * scaleMoveShadows[2], 
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
       Translate(modelView, sphere_POSITION[0] * scaleMoveShadows[0], sphere_POSITION[1] * scaleMoveShadows[1], sphere_POSITION[2] * scaleMoveShadows[2]);                                                                                         
       Rotate(modelView, sphere_ROTATE[0], sphere_ROTATE[1], sphere_ROTATE[2], sphere_ROTATE[3] + spinModel);          
       Scale(modelView, scaleShadowSize[0], scaleShadowSize[1], scaleShadowSize[2]);   
       //-------------------------------------------------------------
            glBindBuffer(GL_ARRAY_BUFFER, sphere_VBO);   
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_INDEX_VBO);                                                                                                                                     
            //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
                MultiplyMatrix(mvpMatrix, ProjectionShadow, modelView);                                                                                                                         
                //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
                LoadIdentity(lightMatrix);                                                                                                                                                
                InvertMatrix(lightMatrix, modelView);                                                                                                                                     
                                                                
                glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
                glBindTexture(GL_TEXTURE_2D, sphere_NORMALMAP);                                                                                                                          
                //---                                                                                                                                                                     
                glActiveTexture (GL_TEXTURE0);                                                                                                                                            
                glBindTexture(GL_TEXTURE_2D, sphere_TEXTUREMAP);                                                                                                                            
                //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
               
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           glUniform4f(UNIFORM_LIGHT_POSITION_01_shadow, shadowLightPosition[0],  
                                                                shadowLightPosition[1], 
                                                                shadowLightPosition[2], 
                                                                shadowLightPosition[3]);            
                           glUniform4f(UNIFORM_offset_shadow, offset_ShadowShader[0],  
                                                                offset_ShadowShader[1], 
                                                                offset_ShadowShader[2], 
                                                                offset_ShadowShader[3]);
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow,  1, 0,  lightMatrix);  
                      //--------------------------------------------------------------------------------------------------------------------------------------
                      
    glDrawElements(GL_TRIANGLES, 6624, GL_UNSIGNED_INT, 0);
//================================================================================================================================    LoadIdentity(modelView);                                                                                                                                                  

       gluLookAt(modelView, eyeposition[0] * scaleMoveShadows[0], 
                            eyeposition[1] * scaleMoveShadows[1], 
                            eyeposition[2] * scaleMoveShadows[2], 
                            lookAt[0]      * scaleMoveShadows[0], 
                            lookAt[1]      * scaleMoveShadows[1], 
                            lookAt[2]      * scaleMoveShadows[2], 
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
       Translate(modelView, spiralGear_POSITION[0] * scaleMoveShadows[0], spiralGear_POSITION[1] * scaleMoveShadows[1], spiralGear_POSITION[2] * scaleMoveShadows[2]);                                                                                         
       Rotate(modelView, spiralGear_ROTATE[0], spiralGear_ROTATE[1], spiralGear_ROTATE[2], spiralGear_ROTATE[3]);        
       Scale(modelView, scaleShadowSize[0], scaleShadowSize[1], scaleShadowSize[2]);      
            //---------------------------------------------------------------
            glBindBuffer(GL_ARRAY_BUFFER, spiralGear_VBO);   
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spiralGear_INDEX_VBO);                                                                                                                                      
            //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
            MultiplyMatrix(mvpMatrix, ProjectionShadow, modelView);                                                                                                                         
            //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
            LoadIdentity(lightMatrix);                                                                                                                                                
            InvertMatrix(lightMatrix, modelView);   
    
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           glUniform4f(UNIFORM_LIGHT_POSITION_01_shadow, shadowLightPosition[0],  
                                                                shadowLightPosition[1], 
                                                                shadowLightPosition[2], 
                                                                shadowLightPosition[3]);            
                           glUniform4f(UNIFORM_offset_shadow, offset_ShadowShader[0],  
                                                                offset_ShadowShader[1], 
                                                                offset_ShadowShader[2], 
                                                                offset_ShadowShader[3]);
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow,  1, 0,  lightMatrix);  
                          
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, spiralGear_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, spiralGear_TEXTUREMAP);                                                                                                                            
    //-----------------------------------------------------
    glDrawElements(GL_TRIANGLES, 1092, GL_UNSIGNED_INT, 0);                                                                                                
//================================================================================================================================         
       //------------------------------------------------------------------------------------                                          
       LoadIdentity(modelView);                                                                                                                                                  
       gluLookAt(modelView, eyeposition[0] * scaleMoveShadows[0], 
                            eyeposition[1] * scaleMoveShadows[1], 
                            eyeposition[2] * scaleMoveShadows[2], 
                            lookAt[0]      * scaleMoveShadows[0], 
                            lookAt[1]      * scaleMoveShadows[1], 
                            lookAt[2]      * scaleMoveShadows[2], 
                            upVector[0], 
                            upVector[1], 
                            upVector[2]);                                                                                                                                                    
       Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
       //--------------------------------------------------------------------------------------  
       Translate(modelView, moveSet[0] + moveShadow[0] , moveSet[1] + moveShadow[1] , moveSet[2] + moveShadow[2]); 
       Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
       Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
       //----------------------------------------------------------------------------------------
       //-----------------------------------------------------------------------------------------             
       Translate(modelView, knight_POSITION[0] * scaleMoveShadows[0], knight_POSITION[1] * scaleMoveShadows[1], knight_POSITION[2] * scaleMoveShadows[2]);        
       Rotate(modelView, knight_ROTATE[0], knight_ROTATE[1], knight_ROTATE[2], knight_ROTATE[3]);        
       Scale(modelView, scaleShadowSize[0], scaleShadowSize[1], scaleShadowSize[2]);    
          //--------------------------------------------------------------------------
          glBindBuffer(GL_ARRAY_BUFFER, knight_VBO);    
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, knight_INDEX_VBO);                                                                                                                                 
          //---------------------------------------------------------------------------       
          MultiplyMatrix(mvpMatrix, ProjectionShadow, modelView);                                                                                                                         
          //---------------------------------------------------------------------------            
          LoadIdentity(lightMatrix);                                                                                                                                                
          InvertMatrix(lightMatrix, modelView);                                                                                                                                     
          //---------------------------------------------------------------------------                
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           glUniform4f(UNIFORM_LIGHT_POSITION_01_shadow, shadowLightPosition[0],  
                                                                shadowLightPosition[1], 
                                                                shadowLightPosition[2], 
                                                                shadowLightPosition[3]);            
                           glUniform4f(UNIFORM_offset_shadow, offset_ShadowShader[0],  
                                                                offset_ShadowShader[1], 
                                                                offset_ShadowShader[2], 
                                                                offset_ShadowShader[3]);
                           glUniformMatrix4fv(UNIFORM_MODELVIEW_shadow,     1, 0,  LightModelViewMatrix);
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow, 1, 0,  mvpMatrix);
                           glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shadow,  1, 0,  lightMatrix);  
                          
                           //--------------------------------------------------------------------------------------------------------------------------------------
                                                                                                                                      
glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, knight_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, knight_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 1386, GL_UNSIGNED_INT, 0);                                                                                                
//================================================================================================================================ 
   
   
                                                              
//===============================================================================================================           
        
        //=================================================================================
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 	                       
	glBindFramebuffer(GL_FRAMEBUFFER, 0);	                       
 
