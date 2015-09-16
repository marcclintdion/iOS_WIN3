      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
                                          
      frameBufferPlane_GaussianVertical_SHADER = glCreateProgram();                                                                                                         
                                                                   
      const GLchar *vertexSource_frameBufferPlane_GaussianVertical =                                                                                                        
      //===============================================================================================================================  
      "    #define highp                                                                                                      \n"                           

      "    attribute vec4 position;                                                                                        \n" 
      "    attribute vec2 texture;                                                                                        \n" 
      "    uniform   float blurRadius;                                                                                     \n" 
                                    
      "    varying vec2 v_texCoord;                                                                                        \n" 
      "    varying vec2 v_blurTexCoords[14];                                                                                        \n" 
 
      "    void main()                                                                                        \n" 
      "    {                                                                                        \n" 
      
      "         vec2 Pos;                                                                                                     \n"  
      "         Pos = sign(position.xy);                                                                                      \n"  
 
      "         gl_Position = vec4(Pos, 0.0, 1.0);                                                                            \n"  
                //Image-space
      "         v_texCoord = Pos * 0.5 + 0.5;                                                                                  \n"  
           
      
      
      "       v_texCoord = texture;                                                                                        \n" 
      "           v_blurTexCoords[ 0] = v_texCoord + vec2(0.0, -0.028 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 1] = v_texCoord + vec2(0.0, -0.024 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 2] = v_texCoord + vec2(0.0, -0.020 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 3] = v_texCoord + vec2(0.0, -0.016 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 4] = v_texCoord + vec2(0.0, -0.012 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 5] = v_texCoord + vec2(0.0, -0.008 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 6] = v_texCoord + vec2(0.0, -0.004 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 7] = v_texCoord + vec2(0.0,  0.004 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 8] = v_texCoord + vec2(0.0,  0.008 * blurRadius);                                                    \n"
      "           v_blurTexCoords[ 9] = v_texCoord + vec2(0.0,  0.012 * blurRadius);                                                    \n"
      "           v_blurTexCoords[10] = v_texCoord + vec2(0.0,  0.016 * blurRadius);                                                    \n"
      "           v_blurTexCoords[11] = v_texCoord + vec2(0.0,  0.020 * blurRadius);                                                    \n"
      "           v_blurTexCoords[12] = v_texCoord + vec2(0.0,  0.024 * blurRadius);                                                    \n"
      "           v_blurTexCoords[13] = v_texCoord + vec2(0.0,  0.028 * blurRadius);                                                    \n"
 
//------------------------------------------------------------------------------------------------------------------------------------  
      "    }\n";                                                                                                                             
      //===============================================================================================================================                                                                    
      frameBufferPlane_GaussianVertical_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(frameBufferPlane_GaussianVertical_SHADER_VERTEX, 1, &vertexSource_frameBufferPlane_GaussianVertical, NULL);                                                                        
      glCompileShader(frameBufferPlane_GaussianVertical_SHADER_VERTEX);                                                                                                     
      //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      const GLchar *fragmentSource_frameBufferPlane_GaussianVertical =                                                                                                            
      //=============================================================================================================================== 
      " #ifdef GL_ES                                                                                                          \n"                       
      " #else                                                                                                                 \n"                       
      " #define highp                                                                                                         \n"                       
      " #endif                                                                                                                \n"                       

      "       uniform sampler2D s_texture;                                                                                     \n" 
 
      "       varying vec2 v_texCoord;                                                                                     \n" 
      "       varying vec2 v_blurTexCoords[14];                                                                                     \n" 
 
      "       void main()                                                                                                           \n" 
      "       {                                                                                                                     \n" 
      "           gl_FragColor = vec4(0.0);                                                                                     \n" 
      "           gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 0])*0.0044299121055113265;                              \n" 
      "           gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 1])*0.00895781211794;                              \n" 
      "           gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 2])*0.0215963866053;                              \n" 
      "           gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 3])*0.0443683338718;                              \n" 
      "           gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 4])*0.0776744219933;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 5])*0.115876621105;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 6])*0.147308056121;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_texCoord         )*0.159576912161;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 7])*0.147308056121;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 8])*0.115876621105;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[ 9])*0.0776744219933;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[10])*0.0443683338718;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[11])*0.0215963866053;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[12])*0.00895781211794;                              \n" 
      "               gl_FragColor += texture2D(s_texture, v_blurTexCoords[13])*0.0044299121055113265;                              \n" 

//------------------------------------------------------------------------------------------------------------------------------------  
      "    }\n";                                                                                                                                   

//====================================================================================================================================      

      //---------------------------------------------------------------------                                                                         
      frameBufferPlane_GaussianVertical_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(frameBufferPlane_GaussianVertical_SHADER_FRAGMENT, 1, &fragmentSource_frameBufferPlane_GaussianVertical, NULL);                                                                          
      glCompileShader(frameBufferPlane_GaussianVertical_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(frameBufferPlane_GaussianVertical_SHADER, frameBufferPlane_GaussianVertical_SHADER_VERTEX);                                                                                              
      glAttachShader(frameBufferPlane_GaussianVertical_SHADER, frameBufferPlane_GaussianVertical_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(frameBufferPlane_GaussianVertical_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(frameBufferPlane_GaussianVertical_SHADER, 1, "texture");                                                                                             
      //glBindAttribLocation(frameBufferPlane_GaussianVertical _SHADER, 2, "normal");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(frameBufferPlane_GaussianVertical_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(frameBufferPlane_GaussianVertical_SHADER, frameBufferPlane_GaussianVertical_SHADER_VERTEX);                                                                                              
      glDetachShader(frameBufferPlane_GaussianVertical_SHADER, frameBufferPlane_GaussianVertical_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(frameBufferPlane_GaussianVertical_SHADER_VERTEX);                                                                                                            
      glDeleteShader(frameBufferPlane_GaussianVertical_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      
      UNIFORM_MODELVIEWPROJ_frameBufferPlane_GaussianVertical      = glGetUniformLocation(frameBufferPlane_GaussianVertical_SHADER,   "mvpMatrix");                                              
      UNIFORM_TEXTURE_frameBufferPlane_GaussianVertical            = glGetUniformLocation(frameBufferPlane_GaussianVertical_SHADER,   "s_texture");                                               
      UNIFORM_blurRadius_frameBufferPlane_GaussianVertical            = glGetUniformLocation(frameBufferPlane_GaussianVertical_SHADER,   "blurRadius");       
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
                                                                                                                                 
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "frameBufferPlane_GaussianVertical.cpp"                                                                                                                
      glGenBuffers(1,              &frameBufferPlane_GaussianVertical_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, frameBufferPlane_GaussianVertical_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(frameBufferPlane_GaussianVertical), frameBufferPlane_GaussianVertical, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //=================================================================================================================================       
