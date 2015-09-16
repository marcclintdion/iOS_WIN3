
      
                                                                                                                                             
    glBindBuffer(GL_ARRAY_BUFFER, sculptris_VBO);   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sculptris_INDEX_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
                                                                                                                                                
                                                                     
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix, 1.0, -10.0, 2.0);                                                                                                                                
                                                                                                                        
    //======================================================================================================                                                                  
   //======================================================================================================                              
   #include "../../_SHADERS/plastic/rubber/rubber_RENDER.cpp"                                                                       
    //======================================================================================================        
    //======================================================================================================                                                                  
        
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, sculptris_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, sculptris_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 1584, GL_UNSIGNED_INT, 0);                                                                                                    

