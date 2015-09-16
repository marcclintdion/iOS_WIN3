    goldenSunset_SHADER = glCreateProgram();                                                                                     
        //----------------------------------------------------                                                                  
    const GLchar *vertexSource_goldenSunset =                                                                                    

    " #define highp                                                                                                        \n" 
    "     attribute vec4 vertex_01;                                                                                        \n" 
    "     attribute vec2 texture;                                                                                          \n" 
    " //-------------------------------------------------                                                                  \n"     
    "     uniform   highp vec4 light_POSITION_01;                                                                          \n" 
    "     uniform        mat4 ModelView;                                                                                   \n" 
    "     uniform        mat4 ModelViewProjection;                                                                         \n" 
    "     uniform        mat4 LightMatrix;                                                                         \n"     
    " //-------------------------------------------------                                                                  \n" 
    "     varying highp   vec4 lightPosition_PASS;                                                                         \n" 
    "     varying highp   vec2 varTexcoord;                                                                                \n" 
    " //-------------------------------------------------                                                                  \n" 
    " 	  varying highp  float dist;                                                                                       \n" 
    "             highp   vec4 ecPos;                                                                                      \n" 
    "             highp   vec3 aux;                                                                                        \n" 
    
    " void main()                                                                                                          \n" 
    " {                                                                                                                    \n" 
    
    "		     ecPos = ModelView * vertex_01;                                                                            \n" //this portion comes from --> Lighthouse3d.com
    "		     aux   = vec3(light_POSITION_01 - ecPos);                                                                  \n" //this portion comes from --> Lighthouse3d.com 
    "		     dist = length(aux);                                                                                       \n" //this portion comes from --> Lighthouse3d.com 
    
    "     varTexcoord             = texture;                                                                               \n" 
    "     lightPosition_PASS      = normalize(LightMatrix * light_POSITION_01-vertex_01);                                  \n" 
    "     gl_Position             = ModelViewProjection * vertex_01;                                                       \n" 
    " } \n";   
    //--------------------------------------------------------------------------------------------------------                  

    const GLchar *fragmentSource_goldenSunset =                                                                                  

    "#ifdef GL_ES                                                                                                          \n" 
    "#else                                                                                                                 \n" 
    "#define highp                                                                                                         \n" 
    "#endif                                                                                                                \n" 

    "//---------------------------------------------------------------------------------------GLOBALS                      \n" 

    "     uniform sampler2D    Texture1;                                                                                   \n" 
    "     uniform sampler2D    NormalMap;                                                                                  \n" 
    "     uniform sampler2D    ShadowTexture;                                                                              \n" 
    "     uniform highp float  ambient;                                                                                    \n" 
    "     uniform highp float  counter;                                                                                    \n"        
    "//--------------------------------------------                                                                        \n" 
    "     varying highp  vec4  lightPosition_PASS;                                                                         \n" 
    "     varying highp  vec2  varTexcoord;                                                                                \n" 
    "//--------------------------------------------                                                                        \n" 
    "             highp  vec4  tempColor;                                                                                  \n" 
    "             highp  vec3  NormalTex;                                                                                  \n" 
    "             highp  vec4  shadow;                                                                                     \n" 
    "             highp vec4   specular;                                                                                   \n"     
    "             //------------------------                                                                               \n" 
    "             highp float  NdotL1;                                                                                     \n" 
    "//-------------------------------------------------                                                                   \n" 
    " 	  varying highp float  dist;                                                                                       \n"     
    "             highp float  attenuation;                                                                                \n" 

    "//---------------------------------------------------------------------------------------MAIN                         \n" 
    "void main()                                                                                                           \n" 
    "{                                                                                                                     \n" 
	"		     attenuation     =  1.0 / (ambient * dist);                                                                \n"     //this portion comes from --> Lighthouse3d.com 
	"		     attenuation    +=  counter;                                                                               \n"     
    "            //----------------------------------------------------------------------------                            \n"     
    "            NormalTex       =  texture2D(NormalMap,  varTexcoord.xy).xyz;                                             \n" 
    "            NormalTex       =  normalize((NormalTex  - 0.5));                                                         \n" 
    "            NdotL1          =  dot(NormalTex, lightPosition_PASS.xyz);                                                \n"   
    "            //----------------------------------------------------------------------------                            \n"        
    "            tempColor       =  texture2D(Texture1, varTexcoord.xy);                                                   \n" 
    "	         specular        =  (vec4(5.2, 3.1, 1.0, 1.0) * pow(NdotL1,  35.0) * tempColor + tempColor);               \n" 
    "            gl_FragColor    =  specular * attenuation * NdotL1* NdotL1 + shadow;                                      \n" 
    "}\n";

    
      //--------------------------------------------------------------------------------------------------                    

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
        glBindAttribLocation(goldenSunset_SHADER,   0, "vertex_01");                                                              
        //glBindAttribLocation(goldenSunset_SHADER,   1, "normal");                                                            
        glBindAttribLocation(goldenSunset_SHADER,   1, "texture");                                                             
        //--------------------------------------------------------------------------------------------------                    
        glDeleteShader( goldenSunset_SHADER_VERTEX);                                                                             
        glDeleteShader( goldenSunset_SHADER_FRAGMENT);                                                                           
        glLinkProgram(goldenSunset_SHADER);                                                                                      
        //--------------------------------------------------------------------------------------------------                    
        UNIFORM_MODELVIEW_goldenSunset               = glGetUniformLocation(goldenSunset_SHADER, "ModelView");                  
        UNIFORM_MODELVIEWPROJ_goldenSunset           = glGetUniformLocation(goldenSunset_SHADER, "ModelViewProjection");        
        //UNIFORM_MODELVIEWPROJ_INVERSE_goldenSunset = glGetUniformLocation(goldenSunset_SHADER, "ModelViewProjectionInverse"); 
        UNIFORM_LIGHT_MATRIX_goldenSunset            = glGetUniformLocation(goldenSunset_SHADER, "LightMatrix");                
        UNIFORM_TEXTURE_MATRIX_goldenSunset          = glGetUniformLocation(goldenSunset_SHADER, "TextureMatrix");         
        //-----------------------------                                                                                         
        UNIFORM_LIGHT_POSITION_01_goldenSunset       = glGetUniformLocation(goldenSunset_SHADER, "light_POSITION_01");          
        UNIFORM_offset_goldenSunset                  = glGetUniformLocation(goldenSunset_SHADER, "offset");                     
        UNIFORM_tileJump_goldenSunset                = glGetUniformLocation(goldenSunset_SHADER, "tileJump");                   
        UNIFORM_ambient_goldenSunset                 = glGetUniformLocation(goldenSunset_SHADER, "ambient");  
        UNIFORM_counter_goldenSunset                 = glGetUniformLocation(goldenSunset_SHADER, "counter");                 
        //-----------------------------                                                                                         
        UNIFORM_TEXTURE_SHADOW_goldenSunset          = glGetUniformLocation(goldenSunset_SHADER, "ShadowTexture");              
        UNIFORM_TEXTURE_DOT3_goldenSunset            = glGetUniformLocation(goldenSunset_SHADER, "NormalMap");                  
        UNIFORM_TEXTURE_goldenSunset                 = glGetUniformLocation(goldenSunset_SHADER, "Texture1");  