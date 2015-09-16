          
          
          
          glBindBuffer(GL_ARRAY_BUFFER, pyramidTile_VBO);                                                                          
          //-----------------------------------------------------------------------------|__TRANSFORMATIONS                           
    LoadIdentity(modelView);                                                                                                              
    gluLookAt(modelView, eyeposition[0], eyeposition[1], eyeposition[2], lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);                                                                                                
          Translate(modelView,   pyramidTile_POSITION[0] + moveSet[0], pyramidTile_POSITION[1]+ moveSet[1], pyramidTile_POSITION[2]+moveSet[2]);                          
          Rotate(modelView, pyramidTile_ROTATE[0], pyramidTile_ROTATE[1]+1.0, pyramidTile_ROTATE[2], pyramidTile_ROTATE[3]);                                                                    
          //Scale(modelView,pyramidTile_SCALE,pyramidTile_SCALE, pyramidTile_SCALE);                                                  
          //-----------------------------------------------------------------------------|__MATRIX_MATH                               
          MultiplyMatrix(mvpMatrix, projection, modelView);                                                                 
          //InvertMatrix(mvpMatrix, ModelViewProjection);                                                              
          //AssignMatrix(TextureMatrix, bias);                                                                                        
          //------------------------------------------------------------------------------|__LIGHT                                    
          LoadIdentity(lightMatrix);                                                                                                  
          InvertMatrix(lightMatrix, modelView);                                                                                       
          //Translate(LightMatrix, pyramidTile_LIGHT_POSITION[0] , pyramidTile_LIGHT_POSITION[1] ,pyramidTile_LIGHT_POSITION[2]);                                                                                    
         Rotate(lightMatrix,1.0, 0.0, 0.0,  -look_UP_DOWN+45);
         Rotate(lightMatrix,0.0, 1.0, 0.0,  look_LEFT_RIGHT);          
          //------------------------------------------------------------------------------|__ATTRIBUTES                               
          
          
          //===============================================================================================================================          
#include  "../../_SHADERS/BACKGROUND/goldenSunset_RENDER.cpp"          
          //===============================================================================================================================
          
          
          glActiveTexture(GL_TEXTURE1);                                                                                        
          glBindTexture(GL_TEXTURE_2D,  pyramidTile_NORMAL_TEX);          
          glActiveTexture(GL_TEXTURE0);                                                                                        
          glBindTexture(GL_TEXTURE_2D,   pyramidTile_TEXTURE1);                                                                         
          //-------------------------------------------------------------------------------|__DRAW                                    
          glDrawArrays(GL_TRIANGLES, 0, 30);                                                           

