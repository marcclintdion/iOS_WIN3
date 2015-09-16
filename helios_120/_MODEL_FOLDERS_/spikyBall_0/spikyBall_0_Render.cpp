                                                                                            
    //-----------------------------                                                                                                       
    glBindBuffer(GL_ARRAY_BUFFER, spikyBall_0_VBO);                                                                                       
    //-----------------------------------------------------------------------------|__TRANSFORMATIONS                                     
    LoadIdentity(modelView);                                                                                                              
    gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                               
    Translate(modelView,   spikyBall_0_POSITION[0] + moveSet[0], spikyBall_0_POSITION[1] + moveSet[1], spikyBall_0_POSITION[2] + moveSet[2]);      
    Rotate(modelView,      spikyBall_0_ROTATE[0], spikyBall_0_ROTATE[1], spikyBall_0_ROTATE[2], spikyBall_0_ROTATE[3]);                               
    //Scale(ModelView,     spikyBall_0_SCALE,       spikyBall_0_SCALE, spikyBall_0_SCALE);                                                         
    //-----------------------------------------------------------------------------|__MATRIX_MATH                                         
    
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                           
    //InvertMatrix(ModelViewProjectionInverse, ModelViewProjection);                                                                      
    //------------------------------------------------------------------------------|__LIGHT                                              
    LoadIdentity(lightMatrix);                                                                                                            
    InvertMatrix(lightMatrix, modelView);                                                                                                 
         Translate(lightMatrix,   spikyBall_0_LIGHT_POSITION[0], spikyBall_0_LIGHT_POSITION[1], spikyBall_0_LIGHT_POSITION[2]);        
        // Translate(LightMatrix,   goldenSunset_LIGHT_POSITION_01[0], goldenSunset_LIGHT_POSITION_01[1], goldenSunset_LIGHT_POSITION_01[2]); 
         Rotate(lightMatrix,1.0, 0.0, 0.0,  -look_UP_DOWN);
         Rotate(lightMatrix,0.0, 1.0, 0.0,  look_LEFT_RIGHT);                                                                           
    //======================================================================================================                              
    #include  "../../_SHADERS/BACKGROUND/goldenSunset_RENDER.cpp"                                                                        
    //======================================================================================================                              
    glActiveTexture(GL_TEXTURE2);                                                                                                      
    glBindTexture(GL_TEXTURE_2D,  shadowMap_2D);                                                                                          
    //----------------------------------------------------                                                                                
    glActiveTexture(GL_TEXTURE1);                                                                                                      
    glBindTexture(GL_TEXTURE_2D,  spikyBall_0_NORMAL_TEX);                                                                                   
    //----------------------------------------------------                                                                                
    glActiveTexture(GL_TEXTURE0);                                                                                                      
    glBindTexture(GL_TEXTURE_2D, spikyBall_0_TEXTURE1);                                                                                      
    //-------------------------------------------------------------------------------|__DRAW                                              
    glDrawArrays(GL_TRIANGLES, 0, 540);                                                                     