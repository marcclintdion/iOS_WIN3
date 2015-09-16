                                 
                                                                                                                                      
    glBindBuffer(GL_ARRAY_BUFFER, spiralGear_VBO);   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spiralGear_INDEX_VBO);                                                                                                                                      
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
                                                                                                                                                 
                                                                     
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
                                                                                                                    
    //======================================================================================================                                                                  
   //======================================================================================================                              
   #include "../../_SHADERS/plastic/rubber/rubber_RENDER.cpp"                                                                         
    //======================================================================================================    
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, spiralGear_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, spiralGear_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 1092, GL_UNSIGNED_INT, 0);                                                                                                

