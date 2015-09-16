    glUseProgram(shinyPlastic_04_SHADER);      
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   2, GL_FLOAT, GL_FALSE, 20, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);                                                                                                                                             
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_shinyPlastic_04, shinyPlastic_04_LIGHT_POSITION_01[0], shinyPlastic_04_LIGHT_POSITION_01[1], shinyPlastic_04_LIGHT_POSITION_01[2], shinyPlastic_04_LIGHT_POSITION_01[3]);        
    glUniform1f(UNIFORM_SHININESS_shinyPlastic_04, shinyPlastic_04_SHININESS);                                                                                                                  
    glUniform1f(UNIFORM_ATTENUATION_shinyPlastic_04, shinyPlastic_04_ATTENUATION);                                                                                                                  
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shinyPlastic_04,   1,0,  mvpMatrix);                                                                                                      
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shinyPlastic_04,    1,0,  lightMatrix);                                                                                                    
    glUniform1i (UNIFORM_TEXTURE_DOT3_shinyPlastic_04, 1);      
    glUniform1i (UNIFORM_TEXTURE_shinyPlastic_04, 0 );   
