      //====================================================================================================================   
      #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      processShadow_44bit_Stride_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_processShadow_44bit_Stride =                                                                                                        

      "    #define highp                                                                                                     \n"                           

      "    uniform         mat4  mvpMatrix;                                                                                  \n"                           
      "    uniform         mat4  mvMatrix;                                                                                   \n"        
           //-----
      "    uniform         mat4  projectionShadow;                                                                           \n"        
      "    uniform         mat4  modelViewShadow;                                                                            \n"        
           //-----      
      "    uniform         mat4  textureMatrix;                                                                              \n"         
      "    attribute       vec4  position;                                                                                   \n"                           
      //--------------------------------------------
      "    varying   highp vec4  shadowTexcoord;                                                                             \n"       
      "              highp vec4  TEMP_shadowTexcoord;                                                                        \n" 

      //--------------------------------------------    
      "    const mat4  ScaleMatrix = mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);   \n"  
  
//========================================================================================================================== 
      "    void main()                                                                                                       \n"                           
      "    {                                                                                                                 \n"                           
                   //---------------------------------------------------------------------------------------------------------     
      "            TEMP_shadowTexcoord   =   ScaleMatrix * projectionShadow * modelViewShadow * textureMatrix * position;    \n" 
      "            TEMP_shadowTexcoord   =   TEMP_shadowTexcoord / TEMP_shadowTexcoord.w;                                    \n"      
      "            shadowTexcoord        =   TEMP_shadowTexcoord;                                                            \n"    
                   //---------------------------------------------------------------------------------------------------------
      "            gl_Position           =   mvpMatrix * position;                                                           \n"                           

      "    }\n";                                                                                                                             
      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################        
   
   
      //---------------------------------------------------------------------                                                                   
      processShadow_44bit_Stride_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(processShadow_44bit_Stride_SHADER_VERTEX, 1, &vertexSource_processShadow, NULL);                                                                        
      glCompileShader(processShadow_44bit_Stride_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_processShadow_44bit_Stride =                                                                                                            

      " #ifdef GL_ES                                                                                                              \n"                       
      " #else                                                                                                                     \n"                       
      " #define highp                                                                                                             \n"                       
      " #endif                                                                                                                    \n"                       

      "    uniform sampler2D   ShadowTexture;                                                                                     \n"     
      //--------------------------------------------
      "    varying highp vec4  shadowTexcoord;                                                                                    \n"         
      "    varying highp vec2  varTexcoord;                                                                                       \n"                       
      //--------------------------------------------
      "            highp vec4    shadow;                                                                                          \n"     
      //=============================================================================================================================     
      "     void main()                                                                                                           \n"                       
      "     {                                                                                                                     \n"                       
   
      "     highp float comp          = (shadowTexcoord.z / shadowTexcoord.w) - 8.4e-005;                                         \n" 
      "     highp float depth_PowerVR = texture2DProj(ShadowTexture, shadowTexcoord).r;                                           \n" 
      "     highp float shadowVal     = comp <= depth_PowerVR ? 1.0 : 0.4;                                                        \n" 
     
      "      gl_FragColor             = vec4(shadowVal, shadowVal, shadowVal, shadowVal);                                         \n"
      
 
       "    }\n";                                                                                                                                   

//=====================================================================================================================================






      //---------------------------------------------------------------------                                                                         
      processShadow_44bit_Stride_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(processShadow_44bit_Stride_SHADER_FRAGMENT, 1, &fragmentSource_processShadow, NULL);                                                                          
      glCompileShader(processShadow_44bit_Stride_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(processShadow_44bit_Stride_SHADER, processShadow_44bit_Stride_SHADER_VERTEX);                                                                                              
      glAttachShader(processShadow_44bit_Stride_SHADER, processShadow_44bit_Stride_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(processShadow_44bit_Stride_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(processShadow_44bit_Stride_SHADER, 1, "normal");       
      glBindAttribLocation(processShadow_44bit_Stride_SHADER, 2, "tangent");  
      glBindAttribLocation(processShadow_44bit_Stride_SHADER, 3, "texture");                                                                                             
      //------------------------------------------------                                                                                              
      glLinkProgram(processShadow_44bit_Stride_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(processShadow_44bit_Stride_SHADER, processShadow_44bit_Stride_SHADER_VERTEX);                                                                                              
      glDetachShader(processShadow_44bit_Stride_SHADER, processShadow_44bit_Stride_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(processShadow_44bit_Stride_SHADER_VERTEX);                                                                                                            
      glDeleteShader(processShadow_44bit_Stride_SHADER_FRAGMENT);                                                                                                          
      //-----------------------------------------------------------------------------------------------------------------------------------                
      UNIFORM_MODELVIEWPROJ_processShadow_44bit_Stride                   = glGetUniformLocation(processShadow_44bit_Stride_SHADER,   "mvpMatrix"); 
      UNIFORM_MODELVIEW_processShadow_44bit_Stride                       = glGetUniformLocation(processShadow_44bit_Stride_SHADER,   "mvMatrix");        
      //-------------------------------
      UNIFORM_SHADOW_PROJ_processShadow_44bit_Stride                     = glGetUniformLocation(processShadow_44bit_Stride_SHADER,   "projectionShadow");                                                  
      UNIFORM_modelViewShadow_processShadow_44bit_Stride                 = glGetUniformLocation(processShadow_44bit_Stride_SHADER,   "modelViewShadow");            
      //-------------------------------------
      UNIFORM_TEXTURE_SHADOW_processShadow_44bit_Stride                  = glGetUniformLocation(processShadow_44bit_Stride_SHADER,   "ShadowTexture");        
      //-----------------------------------------------------------------------------------------------------------------------------------                
