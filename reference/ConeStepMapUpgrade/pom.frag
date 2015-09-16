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

float intersect_POM(in vec2 dp,in vec3 ds, in float lerping);

void main(void)
{
   vec4 t,c;
   vec3 p,v,l,s;
   vec2 uv;
   float d,a;

   // ray intersect in view direction
   p  = eyeSpaceVert;
   v  = normalize(p);
   a  = dot(eyeSpaceNormal,v)/depth;
   s = normalize(vec3(dot(v,eyeSpaceTangent),dot(v,eyeSpaceBinormal),a));
   
   //	pick _one_ of the following variations
   d = intersect_POM(texCoord,s, -a*depth);
      
   /*
   // uncomment me to just show the depth after the search
   gl_FragColor = vec4(max(1.0-d,0.0), 0.0, 0.0, 1.0);
   return;
   //*/   
  
   // get rm and color texture points
   uv=texCoord+s.xy*d;
   c=texture2D(texmap,uv);

   // expand normal from normal map in local polygon space
   // blue = df/dx
   // alpha = df/dy (image coords are no longer backward!)
   // note: I _need_ the texture size to scale the normal properly!
   //*
   t=texture2D(stepmap,uv);
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

float intersect_POM(in vec2 dp,in vec3 ds, in float lerping)
{
   // number of steps (between 25% and 100% of conesteps)
   // note that (lerping squared looks a bit better...slower)
   //int nSteps = 1 + int(mix (1.0, 0.25, lerping) * float(conesteps));
  int nSteps = 1 + int(mix (2.0, 0.5, lerping) * float(conesteps));
   // minimum feature size parameter (along ds)
   float dsc = 1.0 / (-ds.z * float(nSteps));
   // my starting location (is at z=1, 
   // and moving down so I don't have 
   // to invert height maps)
   // texture lookup
   vec4 t;
   // scaling distance along vector ds
   float sc=0.0;
   // and how high above the surface am I?
   float ht, old_ht = 2.0;
   
   //	find the starting location and height
   t=texture2D(stepmap,dp);
   ht = t.r;
   for (int i = nSteps; (i > 0) && (ht > 0.0); --i)
   {
     // and take the step
     sc += dsc;

     // remember the old location
     old_ht = ht;
     
	   //	find the new location and height
	   t=texture2D(stepmap,dp+ds.xy*sc);
     ht = t.r + ds.z*sc;
   }
   
   // set up for the linear step
   float old_sc = sc - dsc;
   
   /*
   // binary search refinement
   // comment this part out if 
   // you don't need the extra 
   // precision!
   for (int i = 3; i > 0; --i)
   {
      // get the old values
      old_sc = sc;
      old_ht = ht;
      // take 1/2 step, except on last, take full
      dsc *= 0.5 + 0.5*step(i, 1.5);
      // take the new step
      sc += sign (ht) * dsc;
      // get the new height
      t=texture2D(stepmap,dp+ds.xy*sc);
      ht = t.r + ds.z*sc;
   }
   //*/
   
   // _Now_ take one linear step
   dsc = clamp (ht / (ht - old_ht), 0.0, 1.0);
   sc = sc*(1.0-dsc) + old_sc*(dsc);
   
   // return the vector length needed to hit the height-map
   return (sc);
   
   //return (float(nSteps) / float(conesteps));
}