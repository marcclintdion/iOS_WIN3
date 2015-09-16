uniform vec4 ambient;
uniform vec4 diffuse;
uniform float depth;
uniform float texsize;
uniform int conesteps;
   
varying vec2 texCoord;
varying vec3 eyeSpaceVert;
varying vec3 eyeSpaceTangent;
varying vec3 eyeSpaceBinormal;
varying vec3 eyeSpaceNormal;
varying vec3 eyeSpaceLight;

uniform sampler2D stepmap;
uniform sampler2D texmap;

#if 0
#define float4 half4
#define float3 half3
#define float2 half2
#define float half
#endif 

void intersect_cone_3step(inout vec3 dp, in vec3 ds);

void main(void)
{
   vec4 t,c;
   vec3 p,v,l,s, pt;
   float a;

   // ray intersect in view direction
   p  = eyeSpaceVert;
   v  = normalize(p);
   a  = -depth / dot(eyeSpaceNormal,v);
   s = vec3(dot(v,eyeSpaceTangent)*a, dot(v,eyeSpaceBinormal)*a, 1.0);
   
   //	pick _one_ of the following variations
   pt = vec3 (texCoord,0.0);
   intersect_cone_3step(pt,s);
      
   /*
   // uncomment me to just show the depth after the search
   gl_FragColor = vec4(max(1.0-d,0.0), 0.0, 0.0, 1.0);
   return;
   //*/   
  
   // get rm and color texture points
   c=texture2D(texmap,pt.xy);

   // expand normal from normal map in local polygon space
   // blue = df/dx
   // alpha = df/dy (image coords are no longer backward!)
   // note: I _need_ the texture size to scale the normal properly!
   //*
   t=texture2D(stepmap,pt.xy );
   t = vec4 ((t.ba-0.5) * (-depth * texsize), 1.0, 0.0);
   t.xyz=normalize(t.x*eyeSpaceTangent+t.y*eyeSpaceBinormal+t.z*eyeSpaceNormal);

   // adjust the hit-position
   // (only useful if the light is near relative
   // to the depth)
   //p -= v*d*a;
   
   // compute light direction
   l=eyeSpaceLight.xyz-p;
   
   // compute attenuation
   float att = gl_LightSource[0].linearAttenuation;
   att = min (1.0, inversesqrt(dot(l,l)*att*att));
   
   // rescale the light vector
   l = att * normalize(l);

   // compute the final color
   gl_FragColor = vec4(
   			ambient.xyz*c.xyz+
   			c.xyz*diffuse.xyz*max(0.0,dot(l,t.xyz)), 
   			1.0);
}

//	the super fast version 
// (change number of iterations at compile time)
void intersect_cone_3step(inout vec3 dp, in vec3 ds)
{
   const float w = 1.2;
   // the "not Z" component of the direction vector
   // (requires that the vector ds was normalized!)
   float iz = length(ds.xy);
   // my starting location (is at z=1, 
   // and moving down, so I inverted 
   // theheight maps)
   // texture lookup (and initialized to starting location)
   vec4 t;
  
   //  initial step is farther out (a *HACK*)
   dp += 0.3 * ds;

   //	find the initial location and height
   t=texture2D(stepmap,dp.xy);
   // right, I need to take one step.
   // I use the current height above the texture,
   // and the information about the cone-ratio
   // to size a single step.  So it is fast and 
   // precise!  (like a coneified version of
   // "space leaping", but adapted from voxels)
   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);
   
   // and repeat a few (4x) times 
   //*
   t=texture2D(stepmap,dp.xy);
   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);
   t=texture2D(stepmap,dp.xy);
   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);
      
   // all done
   return;
}
