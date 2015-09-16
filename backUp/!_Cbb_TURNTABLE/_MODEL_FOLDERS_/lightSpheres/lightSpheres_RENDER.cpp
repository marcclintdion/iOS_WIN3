        //=========================================================================================================================================================    
        
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      
        //----------------------------------------------------------------------------------
         glViewport(0, 0, (GLsizei)viewWidth / resize_SHADOW_FBO, (GLsizei)viewHeight / resize_SHADOW_FBO);
        PerspectiveMatrix(projection, fieldOfView, viewWidth / viewHeight, adjustNearFar[0],  adjustNearFar[1]);
        //=========================================================================================================================================================
        #ifdef __APPLE__
        Rotate(projection, 0.0, 0.0, 1.0, -90.0);//_____FOR_iOS_LANDSCAPE_VIEW 
        #endif        
        //=========================================================================================================================================================        
        
     
     
       //====================================================================================   
        LoadIdentity(modelView);                                                                                                                                                  
        gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
        Rotate(modelView, 0.0, 1.0, 0.0, turnTable);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);        
        //-----------------
        Translate(modelView, matchColorModelToShadowPosition[0], matchColorModelToShadowPosition[1], matchColorModelToShadowPosition[2]);    
        Translate(modelView, lightSpheres_POSITION[0], lightSpheres_POSITION[1], lightSpheres_POSITION[2]);            
      
        Rotate(modelView, lightSpheres_ROTATE[0], lightSpheres_ROTATE[1], lightSpheres_ROTATE[2], lightSpheres_ROTATE[3]);              
    
    //==========================================================================================
    glUseProgram(lightSpheres_SHADER);                                                                                                                                              
    glBindBuffer(GL_ARRAY_BUFFER, lightSpheres_VBO); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightSpheres_INDEX_VBO);                                                                                                                                   
    
    //==========================================================================================
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(BiasMatrix);
    Translate(BiasMatrix, shadowsPositionOffset[0], shadowsPositionOffset[1], shadowsPositionOffset[2]);
    Scale(BiasMatrix, scaleShadows, scaleShadows, scaleShadows);   
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);  
    glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));                                                                                                 
    glEnableVertexAttribArray(2);     
    glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));                                                                                                 
    glEnableVertexAttribArray(3);                                                                                                                                                
    //======================================================================================================                
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_lightSpheres,   1,0,  mvpMatrix); 
    glUniformMatrix4fv(UNIFORM_MODELVIEW_lightSpheres,       1,0,  modelView);                                                                                                          
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_lightSpheres,    1,0,  lightMatrix);
    glUniformMatrix4fv(UNIFORM_textureMatrix_lightSpheres,   1,0,  BiasMatrix);  
    glUniformMatrix4fv(UNIFORM_INVERSEMATRIX_lightSpheres,      1,0,  modelView);                                                                                                           
    //---------------------------------------------------------------------------------
    glUniform4f(UNIFORM_offset_lightSpheres,                        offsetFinalShadow[0], 
                                                                 offsetFinalShadow[1], 
                                                                 offsetFinalShadow[2], 
                                                                 offsetFinalShadow[3]);      
    //---------------------------------------------------------------------------------    
    glUniform4f(UNIFORM_LIGHT_POSITION_01_lightSpheres, lightSpheres_LIGHT_POSITION_01[0], 
                                                     lightSpheres_LIGHT_POSITION_01[1], 
                                                     lightSpheres_LIGHT_POSITION_01[2], 
                                                     lightSpheres_LIGHT_POSITION_01[3]);        
    //---------------------------------------------------------------------------------    
    glUniform1f(UNIFORM_QUADRATIC_ATTENUATION_lightSpheres, lightSpheres_quadraticAttenuation);    
    glUniform1f(UNIFORM_LINEAR_ATTENUATION_lightSpheres,    lightSpheres_linearAttenuation); 
    glUniform1f(UNIFORM_CONSTANT_ATTENUATION_lightSpheres,  lightSpheres_constantAttenuation); 
    //---------------------------------------------------------------------------------     
    glUniform1f(UNIFORM_SHININESS_lightSpheres, lightSpheres_SHININESS);     
    glUniform1f(UNIFORM_zDirBias_lightSpheres, zDirectionBias);              
    //---------------------------------------------------------------------------------    
    glUniform1i (UNIFORM_TEXTURE_SHADOW_lightSpheres, 3);      
    glUniform1i (UNIFORM_TEXTURE_HEIGHT_lightSpheres, 2);     
    glUniform1i (UNIFORM_TEXTURE_DOT3_lightSpheres, 1);                                                                                                                             
    glUniform1i (UNIFORM_TEXTURE_lightSpheres, 0 );                                                                                                                                 
    //======================================================================================================                                                                  
    glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, shadowMap_2D);                                                                                                                          
    //---     
    glActiveTexture ( GL_TEXTURE2 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, lightSpheres_HEIGHT);                                                                                                                          
    //---     
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, lightSpheres_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, lightSpheres_TEXTUREMAP );                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 2640, GL_UNSIGNED_INT, 0);
        
        //====================================================================================  
