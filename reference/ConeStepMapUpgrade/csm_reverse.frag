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

float intersect_cone_exact(in vec2 dp,in vec3 ds);
float intersect_cone_fixed(in vec2 dp, in vec3 ds);
float in_shadow(in vec2 dp,in vec3 ds);

void main(void)
{
   vec4 t,c;
   vec3 p,v,l,s;
   vec2 uv;
   float d=0.0, ds=100.0,a;

   // ray intersect in view direction
   p  = eyeSpaceVert;
   v  = normalize(p);
   s = normalize(vec3(
           dot(v,eyeSpaceTangent),
           dot(v,eyeSpaceBinormal),
           dot(v,eyeSpaceNormal)/depth));
   a  = s.z;
   
   //	pick _one_ of the following variations
   //d = intersect_cone_fixed(texCoord,s);
   d = intersect_cone_exact(texCoord,s);
      
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
   //p -= v*d*a;
   
   // compute light direction
   l=eyeSpaceLight.xyz-p;
   
   // compute attenuation
   float att = gl_LightSource[0].linearAttenuation;
   att = min (1.0, inversesqrt(dot(l,l)*att*att));
   
   //	now the self-shadowing
   // If I'm facing away from the light, 
   // I want the quickest solution possible!
   // So make sure the z component is ~ -1
   // (otherwise i need an "if (s.z<0.0)",
   // which is _SLOW_)
   float shade = 1.0;
   //*
   shade = dot(l,eyeSpaceNormal);
   s = normalize(vec3(
   			dot(l,eyeSpaceTangent),
   			dot(l,eyeSpaceBinormal),
   			dot(l,eyeSpaceNormal)/depth + 1000.0*step (0.0, shade)));
   //*/
   /*
   s = normalize(vec3(
   			dot(l,eyeSpaceTangent),
   			dot(l,eyeSpaceBinormal),
   			dot(l,eyeSpaceNormal)/depth));
   //*/  
   shade = step (0.0, s.z);
   shade = min (shade, in_shadow (uv, s));
   
   // add back in attenuation
   // rescale the light vector
   l = normalize(l) * att * shade;

   // compute the final color
   gl_FragColor = vec4(
   			ambient.xyz*c.xyz+
   			c.xyz*diffuse.xyz*max(0.0,dot(l,t.xyz)), 
   			1.0);
}

// slowest, but best quality
float intersect_cone_exact(in vec2 dp, in vec3 ds)
{
   // the "not Z" component of the direction vector
   // (requires that the vector ds was normalized!)
   float iz = sqrt(1.0-ds.z*ds.z);
   // minimum feature size parameter (along ds)
   float w = 1.0 / texsize;
   //float w = 1.0 / (iz*texsize - ds.z);
   // my starting location (is at z=1, 
   // and moving down so I don't have 
   // to invert height maps)
   // texture lookup
   vec4 t;
   // scaling distance along vector ds
   float sc=0.0, dsc = 1.0;
   // and how high above the surface am I?
   float ht, old_ht = 2.0;
   
   //	find the starting location and height
   t=texture2D(stepmap,dp);
   ht = t.r;
   while (ht > 0.0)
   {
     float CR = t.g * t.g;
	   // right, I need to take one step.
	   // I use the current height above the texture,
	   // and the information about the cone-ratio
	   // to size a single step.  So it is fast and 
	   // precise!  (like a coneified version of
	   // "space leaping", but adapted from voxels)
     
     // faster version, and pretty precise!
     dsc = (ht*CR + w*1.4142) / (iz - ds.z*CR);
     //dsc = (ht*CR + w*(1.0 + CR*0.4142)) / (iz - ds.z*CR);
     
     // slower, but more exact
     //dsc = w + (ht*CR) / (iz - ds.z*CR);
	   
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
   
   //*
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
      dsc *= 0.5 + 0.5*step(float(i), 1.5);
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
}

//	the super fast version 
// (change number of iterations at compile time)
float intersect_cone_fixed(in vec2 dp, in vec3 ds)
{
   // the "not Z" component of the direction vector
   // (requires that the vector ds was normalized!)
   float iz = sqrt(1.0-ds.z*ds.z);
   // my starting location (is at z=1, 
   // and moving down, so I inverted 
   // theheight maps)
   // texture lookup (and initialized to starting location)
   vec4 t;
   // scaling distance along vector ds
   float sc=0.0;

   //	find the initial location and height
   t=texture2D(stepmap,dp);
   // right, I need to take one step.
   // I use the current height above the texture,
   // and the information about the cone-ratio
   // to size a single step.  So it is fast and 
   // precise!  (like a coneified version of
   // "space leaping", but adapted from voxels)
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   
   // and repeat a few (4x) times 
   //*
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   
   //*
   // and another five!
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);  
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   //*/
   
   /*
   // and another five!
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);  
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   t=texture2D(stepmap,dp+ds.xy*sc);
   sc += (t.r + ds.z*sc) / (iz/(t.g*t.g) - ds.z);
   //*/
   
   // return the vector length needed to hit the height-map
   return (sc);
}

float in_shadow(in vec2 dp,in vec3 ds)
{
   float iz = sqrt(1.0-ds.z*ds.z);
   vec4 t;
   //	start one step removed
   float w=1.0/(iz*texsize+ds.z);
   float sc = w;
   float ht=1.0, deep;
   
   //	1st sample
   t = texture2D(stepmap,dp);
   deep = t.r;
   
   //for (int i = 10; i > 0; --i) 
   while ((deep > sc*ds.z) && (ht > 0.0))
   {
	   t=texture2D(stepmap,dp+ds.xy*sc);
	   ht = t.r - deep + ds.z*sc;
       sc += w + ht / max (0.001, (iz/(t.g*t.g) - ds.z));
       sc = min (sc, 1.1/ds.z);
   }
   
   // am I in the light?
   /*
   deep -= sc*ds.z;
   return (step (deep,0.0));
   //*/
   deep = clamp (sc*ds.z/(deep), 0.0, 1.0);
   return deep*deep;
}