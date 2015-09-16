
    glBindBuffer(GL_ARRAY_BUFFER, plant_v005_VBO);                                                                                                                                
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plant_v005_INDICES_VBO);                                                                                                                                
    //----------------------------------------------------------------------------------------------------------------------------------------------          
                                                                                                                                 
    Translate(modelView, plant_v005_POSITION[0], plant_v005_POSITION[1], plant_v005_POSITION[2]);                          
    Rotate(modelView, plant_v005_ROTATE[0], plant_v005_ROTATE[1], plant_v005_ROTATE[2], plant_v005_ROTATE[3]); 

//=================================================================================================================         
SelectShader(shaderNumber);
//=================================================================================================================

                                     
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                           
    glBindTexture(GL_TEXTURE_2D, plant_v005_NORMALMAP);                                                                                            
    //---                                                                                                                                                      
    glActiveTexture (GL_TEXTURE0);                                                                                                                             
    glBindTexture(GL_TEXTURE_2D, plant_v005_TEXTUREMAP);                                                                                           
    //---------------------------------------------------------------------------------------------------------------------------------------------------      
    glDrawElements(GL_TRIANGLES, 4620, GL_UNSIGNED_INT, 0);                                                                                                     
