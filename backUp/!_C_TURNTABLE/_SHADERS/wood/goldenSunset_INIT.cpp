    goldenSunset_SHADER = glCreateProgram();                                                                                     
        //----------------------------------------------------                                                                  
    const GLchar *vertexSource_goldenSunset =                                                                                    
    
    " #define highp                                                                                                                       \n" 

//========================================================================================================================================
   
    "     attribute vec4 position;                                                                                                        \n" 
    "     attribute vec2 textureCoords;                                                                                                   \n" 
    " //-------------------------------------------------                                                                                 \n"     
    "     uniform   highp vec4 light_POSITION_01;                                                                                         \n" 
    "     uniform        mat4 ModelView;                                                                                                  \n" 
    "     uniform        mat4 ModelViewProjection;                                                                                        \n" 
    "     uniform        mat4 LightMatrix;                                                                                                \n" 
    "     uniform        mat4 TextureMatrix;                                                                                              \n" 
    " //-------------------------------------------------                                                                                 \n" 
    "     varying highp   vec4 lightPosition_PASS;                                                                                        \n" 
    "     varying highp   vec2 varTexcoord;                                                                                               \n" 
    " //-------------------------------------------------                                                                                 \n" 
    //========================================================================================================================================  
    " void main()                                                                                                                         \n" 
    " {                                                                                                                                   \n" 
 
    "     varTexcoord             = textureCoords;                                                                                        \n" 
    "     lightPosition_PASS      = normalize(LightMatrix * light_POSITION_01);                                                           \n" 
    
    "     gl_Position             = ModelViewProjection * position;                                                                       \n" 
    
    " } \n";   

//========================================================================================================================================
    const GLchar *fragmentSource_goldenSunset =                                                                                  

    "#ifdef GL_ES                                                                                                                         \n" 
    "#else                                                                                                                                \n" 
    "#define highp                                                                                                                        \n" 
    "#endif                                                                                                                               \n" 

//========================================================================================================================================
 
    "     uniform sampler2D    NormalMap;                                                                                                 \n" 
    "             highp  vec3  NormalTex;                                                                                                 \n" 
    "             highp float  NdotL1;                                                                                                    \n" 
    //-------------------------------------------------   
    "     uniform sampler2D    Texture1;                                                                                                  \n"     
   
    "     uniform highp float  shininess;                                                                                                 \n"    
    "     uniform highp float  ambient;                                                                                                   \n" 
    //--------------------------------------------                                                                      
    "     varying highp  vec4  lightPosition_PASS;                                                                                        \n" 
    "     varying highp  vec2  varTexcoord;                                                                                               \n" 
    //--------------------------------------------                                                                       
    "             highp  vec4  tempColor;                                                                                                 \n" 
    "             highp  vec4  specular;                                                                                                  \n"     
    //-------------------------------------------- 

    //====================================================================================================================================
   
   "void main()                                                                                                                                                                                                \n" 
    "{                                                                                                                                    \n" 

    "            //----------------------------------------------------------------------------                                           \n"     
    "            NormalTex       =  texture2D(NormalMap,  varTexcoord.xy).xyz;                                                            \n" 
    "            NormalTex       =  normalize((NormalTex  - 0.5));                                                                        \n" 
    "            NdotL1          =  dot(NormalTex, lightPosition_PASS.xyz);                                                               \n"   
    "            //----------------------------------------------------------------------------                                           \n" 
    "            tempColor       =  texture2D(Texture1, varTexcoord.xy);                                                                  \n" 
    "	         specular        =  (vec4(1.0, .5, .2, 1.0) * 1.2 * pow(NdotL1,  shininess) * tempColor);                                 \n" 
    "            gl_FragColor    =   tempColor *tempColor * ambient * NdotL1 + specular;                                                  \n" 
    "}\n";


//====================================================================================================================================    
    
    
        goldenSunset_SHADER_VERTEX = glCreateShader( GL_VERTEX_SHADER);                                                          
        glShaderSource( goldenSunset_SHADER_VERTEX, 1, &vertexSource_goldenSunset, NULL );                                        
        glCompileShader( goldenSunset_SHADER_VERTEX);                                              //glShaderBinary                              
        //----------------------------------------------------                                                                  
        goldenSunset_SHADER_FRAGMENT = glCreateShader( GL_FRAGMENT_SHADER);                                                      
        glShaderSource( goldenSunset_SHADER_FRAGMENT, 1, &fragmentSource_goldenSunset, NULL );                                    
        glCompileShader(goldenSunset_SHADER_FRAGMENT);                                              //glShaderBinary                                                                             
        //--------------------------------------------------------------------------------------------------                    
        glAttachShader( goldenSunset_SHADER, goldenSunset_SHADER_VERTEX );                                                        
        glAttachShader( goldenSunset_SHADER, goldenSunset_SHADER_FRAGMENT );                                                      
        //--------------------------------------------------------------------------------------------------                    
        glBindAttribLocation(goldenSunset_SHADER,   0, "position");                                                              
        glBindAttribLocation(goldenSunset_SHADER,   1, "normal");                                                            
        glBindAttribLocation(goldenSunset_SHADER,   2, "textureCoords");                                                             
        //--------------------------------------------------------------------------------------------------                    
        glDeleteShader( goldenSunset_SHADER_VERTEX);                                                                             
        glDeleteShader( goldenSunset_SHADER_FRAGMENT);                                                                           
        glLinkProgram(goldenSunset_SHADER);                                                                                      
        //--------------------------------------------------------------------------------------------------                    
        UNIFORM_MODELVIEW_goldenSunset               = glGetUniformLocation(goldenSunset_SHADER, "ModelView");                  
        UNIFORM_MODELVIEWPROJ_goldenSunset           = glGetUniformLocation(goldenSunset_SHADER, "ModelViewProjection");        
        UNIFORM_LIGHT_MATRIX_goldenSunset            = glGetUniformLocation(goldenSunset_SHADER, "LightMatrix");                
        UNIFORM_TEXTURE_MATRIX_goldenSunset          = glGetUniformLocation(goldenSunset_SHADER, "TextureMatrix");         
        //-----------------------------                                                                                         
        UNIFORM_LIGHT_POSITION_01_goldenSunset       = glGetUniformLocation(goldenSunset_SHADER, "light_POSITION_01");          
        UNIFORM_shininess_goldenSunset                 = glGetUniformLocation(goldenSunset_SHADER, "shininess");  
       
        UNIFORM_ambient_goldenSunset                 = glGetUniformLocation(goldenSunset_SHADER, "ambient");  
          
        UNIFORM_TEXTURE_DOT3_goldenSunset            = glGetUniformLocation(goldenSunset_SHADER, "NormalMap");                  
        UNIFORM_TEXTURE_goldenSunset                 = glGetUniformLocation(goldenSunset_SHADER, "Texture1");  
