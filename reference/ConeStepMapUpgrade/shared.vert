//  starting texture coordinate
varying vec2 texCoord;
//  position and light in eye space
varying vec3 eyeSpaceVert;
varying vec3 eyeSpaceLight;
//  the matrix needed to convert to eye space
//varying mat3 eyeTransform;
//*
varying vec3 eyeSpaceTangent;
varying vec3 eyeSpaceBinormal;
varying vec3 eyeSpaceNormal;
//*/


void main(void)
{ 
   eyeSpaceVert = (gl_ModelViewMatrix * gl_Vertex).xyz;
   
   // convert to eyeSpace for programs other than Irrlicht
   //eyeSpaceLight = (gl_ModelViewMatrix * vec4(gl_LightSource[0].position.xyz,1.0)).xyz;
   
   // gl_LightSource[n].position is already in eyeSpace from Irrlicht!
   eyeSpaceLight = gl_LightSource[0].position.xyz;
   
  //*
   eyeSpaceTangent  = gl_NormalMatrix * gl_MultiTexCoord1.xyz;	//tangent;
   eyeSpaceBinormal = gl_NormalMatrix * (-gl_MultiTexCoord2.xyz);	//binormal;
   eyeSpaceNormal   = gl_NormalMatrix * gl_Normal;
  //*/
  
   /*
   eyeTransform = mat3 (
      gl_NormalMatrix * (gl_MultiTexCoord1.xyz),
      gl_NormalMatrix * (-gl_MultiTexCoord2.xyz),
      gl_NormalMatrix * (gl_Normal.xyz)
   );
   //*/
   
   texCoord   = gl_MultiTexCoord0.xy;
   
   gl_Position = ftransform();
}
