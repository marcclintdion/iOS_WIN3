 glUseProgram(processShadow_44bit_Stride_SHADER);          
          //------------------------------------------------------------------------------------        
          glVertexAttribPointer(0,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));                                                  
          glEnableVertexAttribArray(0);	                                                                                              
          glVertexAttribPointer(1,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));                                                 
          glEnableVertexAttribArray(1);	                                                                                          
          glVertexAttribPointer(2,     2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));                                                 
          glEnableVertexAttribArray(2);                                                                                               
          //------------------------------------------------------------------------------------                               
          glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_goldenSunset,   1, 0,         mvpMatrix);                                   
          glUniformMatrix4fv(UNIFORM_TEXTURE_MATRIX_goldenSunset,  1, 0,         textureMatrix);                                       
          //------------------------------------------------------------------------------------                               
          glUniform1i(UNIFORM_TEXTURE_SHADOW_goldenSunset, 0);                                                                      
