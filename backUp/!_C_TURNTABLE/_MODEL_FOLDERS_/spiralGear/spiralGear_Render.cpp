                                 
                                                                                                                                      
    glBindBuffer(GL_ARRAY_BUFFER, spiralGear_VBO);   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spiralGear_INDEX_VBO);                                                                                                                                      
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                                                                   
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable); 
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]); 
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);        
        //--------------------------------------------------------------------------------------
        Translate(modelView, spiralGear_POSITION[0], spiralGear_POSITION[1], spiralGear_POSITION[2]);                                                                                         
        Rotate(modelView, spiralGear_ROTATE[0], spiralGear_ROTATE[1], spiralGear_ROTATE[2], spiralGear_ROTATE[3]);        
                                                                                                                                                    
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
                                                                                                                    
    //======================================================================================================                                                                  
   //======================================================================================================                              
SelectShader(shaderNumber);//plastic/rubber/
    //======================================================================================================    
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);                                                                                                                 
    //---  
   glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, spiralGear_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, spiralGear_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 1092, GL_UNSIGNED_INT, 0);                                                                                                

