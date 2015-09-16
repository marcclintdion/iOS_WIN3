
                                                                                                                                               
    glBindBuffer(GL_ARRAY_BUFFER, flowerShield_VBO);                                                                                                                                
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flowerShield_INDEX_VBO);       
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
        Translate(modelView, flowerShield_POSITION[0], flowerShield_POSITION[1], flowerShield_POSITION[2]);                                                                                         
        Rotate(modelView, flowerShield_ROTATE[0], flowerShield_ROTATE[1], flowerShield_ROTATE[2], flowerShield_ROTATE[3]);         
    //---------------------------------------------------------------------------------------------------------            
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Translate(lightMatrix1, 1.0, -10.0, 2.0);                                                                                                                                
//======================================================================================================                                                                  
   //======================================================================================================                              
SelectShader(shaderNumber);//plastic/rubber/
    //======================================================================================================        
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);                                                                                                                 
    //---               
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, flowerShield_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, flowerShield_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
