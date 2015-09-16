varying vec2 v_texCoord;

uniform vec4 Tangent;
uniform vec4 Normal;
uniform vec4 BiNormal;

uniform vec4 Eye;



varying  vec3 m_Vector;

varying  vec3 m_Tangent;
varying  vec3 m_Normal;
varying  vec3 m_BiNormal;
    
varying  vec3 dirEye;    

void main( void )
{
    v_texCoord      = (gl_ModelViewMatrix * gl_MultiTexCoord0).xy;
    
    m_Vector        = vec3(gl_ModelViewMatrix * gl_Vertex);    
    gl_Position     = gl_ModelViewProjectionMatrix * gl_Vertex;    
    
    m_Tangent       = vec3(gl_ModelViewMatrix * Tangent);
    m_Normal        = vec3(gl_ModelViewMatrix * Normal);
    m_BiNormal      = vec3(gl_ModelViewMatrix * BiNormal);

}






/*
varying vec2 v_texCoord;

uniform vec4 Tangent;
uniform vec4 Normal;
uniform vec4 BiNormal;

uniform vec4 Eye;
varying vec3 EyeDir;

void main( void )
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    v_texCoord = gl_MultiTexCoord0.xy;

   
    vec3 m_Tangent = vec3(gl_ModelViewMatrix * Tangent);
    vec3 m_Normal = vec3(gl_ModelViewMatrix * Normal);
    vec3 m_BiNormal = vec3(gl_ModelViewMatrix * BiNormal);

    vec3 m_Vector = vec3(gl_ModelViewMatrix * gl_Vertex);

    vec3  dirEye   = Eye.xyz  - m_Vector;
        
    EyeDir.x = dot(m_Tangent.xyz , dirEye);
    EyeDir.y = dot(m_BiNormal.xyz , dirEye);
    EyeDir.z = dot(m_Normal.xyz , dirEye);

}
*/
