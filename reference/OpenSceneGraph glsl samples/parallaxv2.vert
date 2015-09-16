/*******************************************************************************/
/*
 * Author: Ing. Jose Larios Delgado.
 * Project:  glsl shaders implementation with OpenSceneGraph.
 * Institutions: DGSCA, UNAM, Virtual Reality Department.
 * Description: Parallax Map shader for a directional light in OSG.   
 */
/*******************************************************************************/
varying vec3 lightVec;/*!< Light vector passed to the fragment program.*/  
varying vec3 viewVec;/*!< View vector passed to the fragment program.*/
varying vec2 texCoord;/*!< Texture coordinates passed to the fragment program.*/
attribute vec3 Tangent;/*!< Tangent space vector.*/  
	                     
//!Main function.
/*!
   Calculates the necessary data to use in the fragment shader, light position, eye vector
   and texture coordinates.
*/	
void main(void)
{
	gl_Position = ftransform();
	texCoord = gl_MultiTexCoord0.xy*vec2(1.0, 1.0);
	
	
		
	vec3 n = normalize(gl_NormalMatrix * gl_Normal);
	vec3 t = normalize(gl_NormalMatrix * Tangent);
	vec3 b = cross(n, t);
		
	vec3 v;
	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 lVec = gl_LightSource[0].position.xyz - vVertex;
	
	v.x = dot(lVec, t);
	v.y = dot(lVec, b);
	v.z = dot(lVec, n);
	lightVec = v;
	
	vec3 vVec = -vVertex;
	v.x = dot(vVec, t);
	v.y = dot(vVec, b);
	v.z = dot(vVec, n);
	viewVec = v;
	
	
}
