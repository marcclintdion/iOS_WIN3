 
    #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      renderMonkeyish_H_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_renderMonkeyish_H =                                                                                                        

      "    #define highp                                                                                                 \n"                           

      "    uniform highp vec4   light_POSITION_01;                                                                       \n"                           
      "    uniform       mat4   mvpMatrix;                                                                               \n"                           
      "    uniform       mat4   lightMatrix;                                                                             \n"                           

      "    attribute     vec4   position;                                                                                \n"                           
      "    attribute     vec3   normal;                                                                                  \n"       
      "    attribute     vec2   texture;                                                                                 \n"                           

      "    varying highp vec4   lightPosition_PASS;                                                                      \n"                           
      "    varying highp vec4   normal_PASS;                                                                             \n"        
     
      "    varying highp vec3   column0;                                                                                 \n"   
      "    varying highp vec3   column1;                                                                                 \n"   
      "    varying highp vec3   column2;                                                                                 \n"        
      
      "    varying highp vec3   vViewVec;                                                                                \n"   
      "    varying highp vec2   varTexcoord;                                                                             \n"                           


      "    void main()                                                                                                   \n"                           
      "    {                                                                                                             \n"                           
      
      "        column0               =  vec3(mvpMatrix[0].xyz);                                                          \n"   
      "        column1               =  vec3(mvpMatrix[1].xyz);                                                          \n"   
      "        column2               =  vec3(mvpMatrix[2].xyz);                                                          \n"         
       
      "        normal_PASS             = -normalize(mvpMatrix * vec4(normal, 0.0));                                      \n"  
 
      "        vViewVec.xyz            = vec3(  mvpMatrix * position );                                                  \n"  
      "        vViewVec.z              = -vViewVec.z;                                                                    \n"  
     
      "        lightPosition_PASS      = normalize(lightMatrix * light_POSITION_01);                                     \n"        
     
      "        varTexcoord             = texture;                                                                        \n"                           
      "        gl_Position             = mvpMatrix * position;                                                           \n"                           

      "    }\n";                                                                                                                             
      //---------------------------------------------------------------------                                                                   
      renderMonkeyish_H_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(renderMonkeyish_H_SHADER_VERTEX, 1, &vertexSource_renderMonkeyish_H, NULL);                                                                        
      glCompileShader(renderMonkeyish_H_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_renderMonkeyish_H =                                                                                                            

     
      " #ifdef GL_ES                                                                                                                  \n"                       
      " #else                                                                                                                         \n"                       
      " #define highp                                                                                                                 \n"                       
      " #endif                                                                                                                        \n"                        

      "    uniform sampler2D     Texture1;                                                                                            \n"                       
      "    uniform sampler2D     NormalMap;                                                                                           \n"                       
      "    uniform highp vec4    light_POSITION_01;                                                                                   \n" 
      "    varying highp vec4    lightPosition_PASS;                                                                                  \n"                       
      "    varying highp vec4    normal_PASS;                                                                                         \n"        
      "    varying highp vec3    vViewVec;                                                                                            \n"      
     
      "    varying highp vec3   column0;                                                                                              \n"   
      "    varying highp vec3   column1;                                                                                              \n"   
      "    varying highp vec3   column2;                                                                                              \n"        
      
      "    varying highp vec2    varTexcoord;                                                                                         \n"                       
      "    uniform highp float   shininess;                                                                                           \n"                       
      "    uniform highp float   attenuation;                                                                                         \n"        
      "    uniform highp float   noiseScale;                                                                                          \n"       
      "    highp float cosA, sinA, tanA;                                                                                              \n" 
      
      "            highp vec4    color      = vec4(1.0, 0.5, 0.01, 1.0);                                                              \n"          
      "            highp vec4    gloss      = vec4(0.6, 0.4, 0.2, 1.0);                                                               \n"    
      "            highp vec3    normal;                                                                                              \n"                       
      "            highp vec3    normalFrag;                                                                                          \n"         
      "            highp vec3    NormalTex;                                                                                           \n"                       
      "            highp vec3    ColorTex;                                                                                            \n"         
      "            highp float   NdotL1;                                                                                              \n"  
    
      "     void main()                                                                                                               \n"                       
      "     {                                                                                                                         \n"                       
      "         mat3 n = mat3(column0, column1, column2);                                                                             \n"       
      
      "         NormalTex                  =  texture2D(NormalMap,  varTexcoord).xyz;                                                 \n"                       
      "         NormalTex                  = (NormalTex - 0.5);                                                                       \n"                       
      "         normal                     =  normalize(n * NormalTex);                                                               \n"                       
      "         NdotL1                     =  dot(normal, normalize(light_POSITION_01.xyz));                                          \n"                       
    
//=======================================================================================================
      "         highp vec3 viewVec         = normalize(vViewVec);                                                                     \n"  
      "         highp vec3 oglLightDir     = vec3(light_POSITION_01.x, light_POSITION_01.y, -light_POSITION_01.z);                    \n"  
    
      "         ColorTex                   =  texture2D(Texture1,  varTexcoord).xyz;                                                  \n"        
      
      "         highp float angle          = noiseScale * ColorTex.x * NdotL1* NdotL1* NdotL1;                                        \n"  
  
      "         sinA = sin(angle);                                                                                                    \n" 
      "         cosA = cos(angle);                                                                                                    \n" 
      "         tanA = tan(angle);                                                                                                    \n" 

//========================================================================================================
      "         vec3 tang                  =  tanA * vec3(normal.z, normal.y, normal.x) + sinA * vec3(normal.x, normal.y, normal.z);  \n"  //!var         renderMonkeyish_H_ATTENUATION    =  1.057;var         renderMonkeyish_H_SHININESS    =  205.001;var         renderMonkeyish_H_NOISE_SCALE      =  -0.0034;


//========================================================================================================
      "         float cs                   = -dot(viewVec, tang);                                                                     \n" 
      "         float sn                   =  sqrt(1.0 - cs * cs) ;                                                                   \n" 
      "         float cl                   =  dot(oglLightDir.xyz, tang)* ColorTex.x ;                                                \n" 
      "         float sl                   =  sqrt(1.0 - cl * cl);                                                                    \n" 
      "         float specular             =  pow( (cs * cl + sn * sl), shininess)* NdotL1;                                           \n" 


//=======================================================================================================      
     
     
      "         gl_FragColor          =   texture2D(Texture1, varTexcoord.xy) * color  * NdotL1 *NdotL1 * attenuation                 \n"  
      "                               +   gloss * specular;                                                                           \n"                    

      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------                                                                         
      renderMonkeyish_H_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(renderMonkeyish_H_SHADER_FRAGMENT, 1, &fragmentSource_renderMonkeyish_H, NULL);                                                                          
      glCompileShader(renderMonkeyish_H_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(renderMonkeyish_H_SHADER, renderMonkeyish_H_SHADER_VERTEX);                                                                                              
      glAttachShader(renderMonkeyish_H_SHADER, renderMonkeyish_H_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(renderMonkeyish_H_SHADER,    0, "position");                                                                                            
      glBindAttribLocation(renderMonkeyish_H_SHADER,    1, "normal");       
      glBindAttribLocation(renderMonkeyish_H_SHADER,    2, "texture");                                                                                            
      //------------------------------------------------                                                                                              
      glLinkProgram(renderMonkeyish_H_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(renderMonkeyish_H_SHADER, renderMonkeyish_H_SHADER_VERTEX);                                                                                              
      glDetachShader(renderMonkeyish_H_SHADER, renderMonkeyish_H_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(renderMonkeyish_H_SHADER_VERTEX);                                                                                                            
      glDeleteShader(renderMonkeyish_H_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_renderMonkeyish_H                   = glGetUniformLocation(renderMonkeyish_H_SHADER,   "mvpMatrix");                                              
      UNIFORM_LIGHT_MATRIX_renderMonkeyish_H                    = glGetUniformLocation(renderMonkeyish_H_SHADER,   "lightMatrix");                                            
      UNIFORM_LIGHT_POSITION_01_renderMonkeyish_H               = glGetUniformLocation(renderMonkeyish_H_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_renderMonkeyish_H                       = glGetUniformLocation(renderMonkeyish_H_SHADER,   "shininess");                                              
      UNIFORM_ATTENUATION_renderMonkeyish_H                     = glGetUniformLocation(renderMonkeyish_H_SHADER,   "attenuation");
      UNIFORM_NOISE_SCALE_renderMonkeyish_H                     = glGetUniformLocation(renderMonkeyish_H_SHADER,   "noiseScale");                                                    
      UNIFORM_TEXTURE_DOT3_renderMonkeyish_H                    = glGetUniformLocation(renderMonkeyish_H_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_renderMonkeyish_H                         = glGetUniformLocation(renderMonkeyish_H_SHADER,   "Texture1");                                   
      UNIFORM_ANISO_renderMonkeyish_H                           = glGetUniformLocation(renderMonkeyish_H_SHADER,   "TextureAniso"); 

      #ifdef WIN32  
      loadTexture("_SHADERS/aniso/renderMonkeyish_H/ogl_aniso.tga",                renderMonkeyish_H_ANISOMAP);       
      #endif 



