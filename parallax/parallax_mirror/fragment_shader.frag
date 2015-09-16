uniform sampler2D testTexture;
uniform sampler2D HeightTexture;
uniform sampler2D NormalTexture;
uniform sampler2D TangentTexture;
uniform sampler2D BiNormalTexture;

uniform     vec4  Eye;

varying     vec2 v_texCoord;
varying     vec3 m_Vector;
varying     vec3 m_Tangent;
varying     vec3 m_Normal;
varying     vec3 m_BiNormal;
    
            vec3 dirEye;  
            vec3 EyeDir;
            
            vec3 normal;
            vec3 tangent;
            vec3 biNormal;       
                 
void main( void )
{
    
    normal          =  texture2D( NormalTexture,  v_texCoord ).xyz;     
    normal          = (normal - 0.5) * 2.0;
	normal          =  normalize(normal);
    
    tangent         =  texture2D( TangentTexture, v_texCoord ).xyz;     
    tangent         = (tangent - 0.5) * 2.0;
	tangent         =  normalize(tangent);   
   
    biNormal        =  texture2D( BiNormalTexture, v_texCoord ).xyz;     
    biNormal        = (biNormal - 0.5) * 2.0;
	biNormal        =  normalize(biNormal);    
   
    dirEye          =  Eye.xyz - m_Vector;
        
    EyeDir.x        =  dot(tangent.xyz,  dirEye);
    EyeDir.y        =  dot(biNormal.xyz, dirEye);
    EyeDir.z        =  dot(normal.xyz,   dirEye);     
     
    vec3 EyeT       =  normalize(EyeDir);
    vec4 Offset     =  texture2D(HeightTexture,v_texCoord);
    
    Offset          = (Offset * 0.04) - 0.02;
    
    vec2 TexCoords  =  Offset.xy * EyeT.xy + v_texCoord;

    gl_FragColor    =  texture2D( testTexture, TexCoords ); 

}
