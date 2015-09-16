    //------------------------------------------------------------------------------------------------------          
    LoadIdentity(BiasMatrix);
    Translate(BiasMatrix, shadowsPositionOffset[0], shadowsPositionOffset[1], shadowsPositionOffset[2]);
    Scale(BiasMatrix, scaleShadows, scaleShadows, scaleShadows);
    //-------------------------------------------------------------------------------------------------------
  
    glUseProgram(rubber_SHADER);      
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));                                                                                                  
    glEnableVertexAttribArray(1);    
    glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));                                                                                                 
    glEnableVertexAttribArray(2);                                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__UNIFORMS          
    glUniform4f(UNIFORM_LIGHT_POSITION_01_rubber, rubber_LIGHT_POSITION_01[0], rubber_LIGHT_POSITION_01[1], rubber_LIGHT_POSITION_01[2], rubber_LIGHT_POSITION_01[3]);        
    glUniform1f(UNIFORM_SHININESS_rubber, rubber_SHININESS);                                                                                                                  
    glUniform1f(UNIFORM_ATTENUATION_rubber, rubber_ATTENUATION);                                                                                                                  
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_rubber,   1,0,  mvpMatrix);                                                                                                      
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_rubber,    1,0,  lightMatrix);    
    glUniformMatrix4fv(UNIFORM_textureMatrix_rubber,   1,0,  BiasMatrix);                                                                                                     
    //------------------------------------------------    
    glUniform1i (UNIFORM_TEXTURE_SHADOW_rubber, 3);      
    
    glUniform1i (UNIFORM_TEXTURE_DOT3_rubber, 1);      
    glUniform1i (UNIFORM_TEXTURE_rubber, 0 );   
    //------------------------------------------------      
    glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);                                                                                                                          
    //------------------------------------------------          
