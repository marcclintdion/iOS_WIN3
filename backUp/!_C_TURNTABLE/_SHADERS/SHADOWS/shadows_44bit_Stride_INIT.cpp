    
    SHADER_shadow_44bit_Stride = glCreateProgram();
    //---------------------------------------------------- 
const GLchar *vertexSource_shadow_44bit_Stride =

"    #define highp                                                                                                         \n"

"    uniform           mat4  ModelViewProjection;                                                                          \n"

"    attribute  highp  vec4  position;                                                                                     \n"
"    varying    highp  vec4  position_PASS;                                                                                \n"

"    void main()                                                                                                           \n"
"    {                                                                                                                     \n"                                                                            

"         position_PASS              =  ModelViewProjection * position;                                                    \n"
"         gl_Position                =  position_PASS;                                                                     \n"


"    }\n";
    
//============================================================================================================================

const GLchar *fragmentSource_shadow_44bit_Stride =     

" #ifdef GL_ES                                                                                                             \n"
" #else                                                                                                                    \n"
" #define lowp                                                                                                             \n"
" #endif                                                                                                                   \n"

"    uniform   highp  vec4  darkness;                                                                                      \n"
"    varying   highp  vec4  position_PASS;                                                                                 \n"

"     void main()                                                                                                          \n"
"     {                                                                                                                    \n"

"         gl_FragColor = vec4(position_PASS.x, position_PASS.y, position_PASS.z, position_PASS.w);                                                                         \n"         


"    }\n";



    //--------------------------------------------------------------------------------------------------------------------------------------   
    SHADER_VERTEX_shadow_44bit_Stride = glCreateShader( GL_VERTEX_SHADER);
    glShaderSource( SHADER_VERTEX_shadow_44bit_Stride, 1, &vertexSource_shadow_44bit_Stride, NULL );
    glCompileShader( SHADER_VERTEX_shadow_44bit_Stride);

    //----------------------------------------------------        
    SHADER_FRAGMENT_shadow_44bit_Stride = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource( SHADER_FRAGMENT_shadow_44bit_Stride, 1, &fragmentSource_shadow_44bit_Stride, NULL );
    glCompileShader(SHADER_FRAGMENT_shadow_44bit_Stride);
       
    //--------------------------------------------------------------------------------------------------------------------------------------    
    glAttachShader( SHADER_shadow_44bit_Stride, SHADER_VERTEX_shadow_44bit_Stride );
    glAttachShader( SHADER_shadow_44bit_Stride, SHADER_FRAGMENT_shadow_44bit_Stride );
    //--------------------------------------------------------------------------------------------------------------------------------------    
      glBindAttribLocation(SHADER_shadow_44bit_Stride, 0, "position");                                                                                            
      glBindAttribLocation(SHADER_shadow_44bit_Stride, 1, "normal");       
      glBindAttribLocation(SHADER_shadow_44bit_Stride, 2, "tangent");  
      glBindAttribLocation(SHADER_shadow_44bit_Stride, 3, "texture");     
    //--------------------------------------------------------------------------------------------------------------------------------------    
    glDeleteShader(SHADER_VERTEX_shadow_44bit_Stride);
    glDeleteShader(SHADER_FRAGMENT_shadow_44bit_Stride);   
    glLinkProgram( SHADER_shadow_44bit_Stride);  
    //--------------------------------------------------------------------------------------------------------------------------------------  
    UNIFORM_MODELVIEWPROJ_shadow_44bit_Stride           = glGetUniformLocation(SHADER_shadow_44bit_Stride, "ModelViewProjection");
    
    
    
