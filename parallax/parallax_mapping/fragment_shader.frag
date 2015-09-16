uniform sampler2D testTexture;
uniform sampler2D HeightTexture;
uniform sampler2D NormalTexture;
uniform sampler2D TangentTexture;
uniform sampler2D BiNormalTexture;

uniform     vec4  Eye;

varying     vec2 v_texCoord;
varying     vec3 m_Vector;

varying     vec3 m_Tangent;
varying     vec3 m_BiNormal;
varying     vec3 m_Normal;
            vec3 EyeDir;
            
        
varying     vec4 position;                

void main( void )
{
   
    EyeDir.x        =  dot(m_Tangent.xyz,  -m_Vector);
    EyeDir.y        =  dot(m_BiNormal.xyz, -m_Vector);
    EyeDir.z        =  dot(m_Normal.xyz,   -m_Vector);     
     
    vec3 EyeT       =  normalize(EyeDir);
    vec4 Offset     =  texture2D(HeightTexture,v_texCoord);
    
    Offset          = (Offset * 0.04) - 0.02;
    
    vec2 TexCoords  =  Offset.xy * EyeT.xy + v_texCoord;
    
    gl_FragColor    =  texture2D( testTexture, TexCoords ); 
}
