    
    SHADER_shadow = glCreateProgram();
    //---------------------------------------------------- 
const GLchar *vertexSource_shadow =

"    #define lowp                                                                                                                            \n"

"    uniform      mat4  ModelView;                                                                                                           \n"
"    uniform      mat4  ModelViewProjection;                                                                                                 \n"
"    uniform      vec4  offset;                                                                                                              \n"
"    uniform      vec4  light_POSITION_01;                                                                                                   \n"

"    attribute    vec4  position;                                                                                                            \n"
"    attribute    vec3  normal;                                                                                                              \n"
"                 vec4  tempPosition;                                                                                                        \n"

"                 float shadowDirection;                                                                                                     \n"  


"    void main()                                                                                                                             \n"
"    {                                                                                                                                       \n"                                                                            

//"         vec4 tempLight             = normalize( ModelViewProjection *light_POSITION_01);   \n"
//------------------------------------------------------------------------------
//"         shadowDirection            =  dot(normal, tempLight.xyz);                                                                  \n"
//------------------------------------------------------------------------------
"         tempPosition               =  position;                                                                                            \n"

//------------------------------------------------------------------------------
/*
"         if(shadowDirection <= 0.0)                                                                                                         \n"
"         {                                                                                                                                  \n"
"               tempPosition.xyz    +=   -normal * shadowDirection*.2;                                                                           \n"
"         }                                                                                                                                  \n"
*/
//------------------------------------------------------------------------------
"         tempPosition              +=  offset;                                                                                              \n"

"         gl_Position                =  ModelViewProjection * tempPosition;                                                                  \n"




"    }\n";

    //---------------------------------------------------------------------

const GLchar *fragmentSource_shadow =     

" #ifdef GL_ES                                                                                    \n"
" #else                                                                                           \n"
" #define lowp                                                                                    \n"
" #endif                                                                                          \n"

"    uniform lowp vec4 darkness;                                                                  \n"

"     void main()                                                                                 \n"
"     {                                                                                           \n"


"         gl_FragColor          =  darkness;                                                      \n"         


"    }\n";
    //--------------------------------------------------------------------------------------------------------------------------------------   
    SHADER_VERTEX_shadow = glCreateShader( GL_VERTEX_SHADER);
    glShaderSource( SHADER_VERTEX_shadow, 1, &vertexSource_shadow, NULL );
    glCompileShader( SHADER_VERTEX_shadow);

    //----------------------------------------------------        
    SHADER_FRAGMENT_shadow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource( SHADER_FRAGMENT_shadow, 1, &fragmentSource_shadow, NULL );
    glCompileShader(SHADER_FRAGMENT_shadow);
       
    //--------------------------------------------------------------------------------------------------------------------------------------    
    glAttachShader( SHADER_shadow, SHADER_VERTEX_shadow );
    glAttachShader( SHADER_shadow, SHADER_FRAGMENT_shadow );
    //--------------------------------------------------------------------------------------------------------------------------------------    
    glBindAttribLocation(SHADER_shadow,   0, "position");    
    glBindAttribLocation(SHADER_shadow,   1, "normal");    
    glBindAttribLocation(SHADER_shadow,   2, "texture");       
    //--------------------------------------------------------------------------------------------------------------------------------------    
    glDeleteShader(SHADER_VERTEX_shadow);
    glDeleteShader(SHADER_FRAGMENT_shadow);   
    glLinkProgram( SHADER_shadow);  
    //--------------------------------------------------------------------------------------------------------------------------------------  
  
    UNIFORM_MODELVIEW_shadow               = glGetUniformLocation(SHADER_shadow, "ModelView");  
    UNIFORM_LIGHT_POSITION_01_shadow       = glGetUniformLocation(SHADER_shadow, "light_POSITION_01");      
    UNIFORM_MODELVIEWPROJ_shadow           = glGetUniformLocation(SHADER_shadow, "ModelViewProjection");
    UNIFORM_MODELVIEWPROJ_INVERSE_shadow   = glGetUniformLocation(SHADER_shadow, "ModelViewProjectionInverse");    
    UNIFORM_LIGHT_MATRIX_shadow            = glGetUniformLocation(SHADER_shadow, "LightMatrix");        
    UNIFORM_offset_shadow                  = glGetUniformLocation(SHADER_shadow, "offset"); 
