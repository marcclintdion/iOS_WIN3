    glBindBuffer(GL_ARRAY_BUFFER, wallStraps_VBO);                                                                                                                                
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wallStraps_INDICES_VBO);                                                                                                                                
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__MODEL             
    //goldenSunset_LIGHT_POSITION_01[0] =  1.53;
    //goldenSunset_LIGHT_POSITION_01[1] =  4.39098;
    //goldenSunset_LIGHT_POSITION_01[2] =  5.34102;
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);    
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]); 
        Translate(modelView, wallStraps_POSITION[0], wallStraps_POSITION[1], wallStraps_POSITION[2]);                                                                                         
        Rotate(modelView, wallStraps_ROTATE[0], wallStraps_ROTATE[1], wallStraps_ROTATE[2], wallStraps_ROTATE[3]);

    //----------------------------------------------------------------------------------------------------------------------------------
     MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                   
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //Rotate(lightMatrix, 1.0, 0.0, 0.0,  90.0);                                                                                                                              
    //======================================================================================================                                                                  
SelectShader(shaderNumber);//wood/goldenSunset                                                                                                                                             
    //======================================================================================================                                                                 
    glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);                                                                                                                 
    //---  
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, wallStraps_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, wallStraps_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 936, GL_UNSIGNED_INT, 0);                                                                                                     

