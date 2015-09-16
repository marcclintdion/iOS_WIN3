    backDrop_SHADER = glCreateProgram();                                                                                     
        //----------------------------------------------------                                                                  
    const GLchar *vertexSource_backDrop =                                                                                    

    " #define highp                                                                                                        \n" 
    "     attribute vec4 vertex_01;                                                                                       \n" 
    "     attribute vec2 texture;                                                                                         \n" 
    " //-------------------------------------------------                                                                 \n"     
    "     uniform   highp vec4 light_POSITION_01;                                                                          \n" 
    "     uniform        mat4 ModelView;                                                                                  \n" 
    "     uniform        mat4 ModelViewProjection;                                                                        \n" 
    "   //uniform        mat4 ModelViewProjectionInverse;                                                                 \n" 
    "     uniform        mat4 LightMatrix;                                                                                \n" 
    "     uniform        mat4 TextureMatrix;                                                                              \n" 
    "     uniform highp   vec4 offset;                                                                                     \n" 
    "     uniform highp   vec4 tileJump;                                                                                   \n" 
    "   //uniform highp  float counter;                                                                                    \n" 
    " //-------------------------------------------------                                                                 \n" 
    "     varying highp   vec4 TEMP_shadowTexcoord;                                                                        \n" 
    "     varying highp   vec4 shadowTexcoord;                                                                             \n" 
    "     varying highp   vec4 lightPosition_PASS;                                                                         \n" 
    "     varying highp   vec2 varTexcoord;                                                                                \n" 
    " //-------------------------------------------------                                                                 \n" 
    " 	  varying highp  float dist;                                                                                       \n" 
    "             highp   vec4 ecPos;                                                                                      \n" 
    "             highp   vec3 aux;                                                                                        \n" 
    
    " void main()                                                                                                         \n" 
    " {                                                                                                                   \n" 
    
    "     varTexcoord             = texture;                                                                              \n" 
    "     gl_Position             = ModelViewProjection * vertex_01;                                                      \n" 
    " } \n";   
    //--------------------------------------------------------------------------------------------------------                  

    const GLchar *fragmentSource_backDrop =                                                                                  

    "#ifdef GL_ES                                                                                                         \n" 
    "#else                                                                                                                \n" 
    "#define highp                                                                                                         \n" 
    "#endif                                                                                                               \n" 

    "//---------------------------------------------------------------------------------------GLOBALS                     \n" 

    "     uniform sampler2D   Texture1;                                                                                   \n" 
    "     uniform sampler2D   NormalMap;                                                                                  \n" 
    "     uniform sampler2D   ShadowTexture;                                                                              \n" 
     
    "     uniform highp float  ambient;                                                                                    \n" 
    "     uniform highp float  shininess;                                                                                    \n"      
    "//--------------------------------------------                                                                       \n" 
    "     varying highp  vec4  lightPosition_PASS;                                                                         \n" 
    "     varying highp  vec2  varTexcoord;                                                                                \n" 
    "     varying highp  vec4  shadowTexcoord;                                                                             \n" 
    "//--------------------------------------------                                                                       \n" 
    "             highp  vec4  tempColor;                                                                                  \n" 
    "             highp  vec3  NormalTex;                                                                                  \n" 
    "             highp  vec4  shadow;                                                                                     \n" 
    "             highp  vec4  specular;                                                                                   \n"     
    "             highp float  shadowLayer_01;                                                                             \n"     
    "             highp float  shadowLayer_02;                                                                             \n"  
    "             highp float  shadowLayer_03;                                                                             \n"     
    "             highp float  shadowLayer_04;                                                                             \n"   
   "             //------------------------                                                                              \n" 
    "             highp float  NdotL1;                                                                                     \n" 
    "//-------------------------------------------------                                                                  \n" 
    " 	  varying highp float  dist;                                                                                       \n"     
    "             highp float  attenuation;                                                                                \n" 

    
    
    "//---------------------------------------------------------------------------------------MAIN                        \n" 
    "void main()                                                                                                          \n" 
    "{                                                                                                                    \n" 
    "            gl_FragColor    =   texture2D(Texture1, varTexcoord.xy);                                  \n" 

    "}\n";

    
      //--------------------------------------------------------------------------------------------------                    

        backDrop_SHADER_VERTEX = glCreateShader( GL_VERTEX_SHADER);                                                          
        glShaderSource( backDrop_SHADER_VERTEX, 1, &vertexSource_backDrop, NULL );                                        
        glCompileShader( backDrop_SHADER_VERTEX);                                                                            
        //----------------------------------------------------                                                                  
        backDrop_SHADER_FRAGMENT = glCreateShader( GL_FRAGMENT_SHADER);                                                      
        glShaderSource( backDrop_SHADER_FRAGMENT, 1, &fragmentSource_backDrop, NULL );                                    
        glCompileShader(backDrop_SHADER_FRAGMENT);                                                                           
        //--------------------------------------------------------------------------------------------------                    
        glAttachShader( backDrop_SHADER, backDrop_SHADER_VERTEX );                                                        
        glAttachShader( backDrop_SHADER, backDrop_SHADER_FRAGMENT );                                                      
        //--------------------------------------------------------------------------------------------------                    
        glBindAttribLocation(backDrop_SHADER,   0, "vertex_01");                                                              
        //glBindAttribLocation(backDrop_SHADER,   1, "normal");                                                            
        glBindAttribLocation(backDrop_SHADER,   1, "texture");                                                             
        //--------------------------------------------------------------------------------------------------                    
        glDeleteShader( backDrop_SHADER_VERTEX);                                                                             
        glDeleteShader( backDrop_SHADER_FRAGMENT);                                                                           
        glLinkProgram(backDrop_SHADER);                                                                                      
        //--------------------------------------------------------------------------------------------------                    
        UNIFORM_MODELVIEW_backDrop               = glGetUniformLocation(backDrop_SHADER, "ModelView");                  
        UNIFORM_MODELVIEWPROJ_backDrop           = glGetUniformLocation(backDrop_SHADER, "ModelViewProjection");        
        //UNIFORM_MODELVIEWPROJ_INVERSE_backDrop = glGetUniformLocation(backDrop_SHADER, "ModelViewProjectionInverse"); 
        UNIFORM_LIGHT_MATRIX_backDrop            = glGetUniformLocation(backDrop_SHADER, "LightMatrix");                
        UNIFORM_TEXTURE_MATRIX_backDrop          = glGetUniformLocation(backDrop_SHADER, "TextureMatrix");         
        //-----------------------------                                                                                         
        UNIFORM_LIGHT_POSITION_01_backDrop       = glGetUniformLocation(backDrop_SHADER, "light_POSITION_01");          
        UNIFORM_offset_backDrop                  = glGetUniformLocation(backDrop_SHADER, "offset");                     
        UNIFORM_tileJump_backDrop                = glGetUniformLocation(backDrop_SHADER, "tileJump");                   
        UNIFORM_ambient_backDrop                 = glGetUniformLocation(backDrop_SHADER, "ambient");         
        UNIFORM_shininess_backDrop               = glGetUniformLocation(backDrop_SHADER, "shininess");     
        //-----------------------------                                                                                         
        UNIFORM_TEXTURE_SHADOW_backDrop          = glGetUniformLocation(backDrop_SHADER, "ShadowTexture");              
        UNIFORM_TEXTURE_DOT3_backDrop            = glGetUniformLocation(backDrop_SHADER, "NormalMap");                  
        UNIFORM_TEXTURE_backDrop                 = glGetUniformLocation(backDrop_SHADER, "Texture1");  
