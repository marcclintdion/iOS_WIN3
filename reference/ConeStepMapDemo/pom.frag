uniform float depth;
uniform float texsize;
uniform int linear_search_steps;
uniform int binary_search_steps;

varying vec2 texCoord;
varying vec3 vertex_pos;
varying vec3 light_pos;
varying float vertex_dist;
varying float light_dist;
varying float dist_val;

uniform sampler2D stepmap;
uniform sampler2D texmap;

void ray_intersect_POM (inout vec3 dp, in vec3 ds, in float lerping);

void main(void)
{
   vec4 t,c;
   vec3 l,s;
   vec3 pt_eye, pt_light;
   float a;

   // ray intersect in view direction
   a  = -depth / vertex_pos.z;
   s = vertex_pos * a;
   s.z = 1.0;
  
   //	find the distance to the actualy heightfield
   pt_eye = vec3 (texCoord, 0.0);
   ray_intersect_POM (pt_eye, s, -normalize(vertex_pos).z);
  
   /*
   gl_FragColor = vec4(pt_eye.z, 0, 0, 0);
   return;//*/
  
   // get rm and color texture points
   c=texture2D(texmap,pt_eye.xy);

   // expand normal from normal map in local polygon space
   // blue = df/dx
   // alpha = df/dy (image coords are no longer backward!)
   // note: I _need_ the texture size to scale the normal properly!
   t=texture2D(stepmap, pt_eye.xy);
   t = vec4 ((t.ba-0.5) * (-depth * texsize), 1.0, 0.0);
   t=normalize(t);

   // adjust the hit-position
   // (only useful if the light is near relative
   // to the depth)
   //p -= v*d*a;
   
   // compute attenuation
   float att = gl_LightSource[0].linearAttenuation;
   att = min (1.0, 1.0 / (light_dist*att));
   
   // rescale the light vector
   l = att * normalize(light_pos);

   // compute the final color
   gl_FragColor = vec4(
   			gl_LightSource[0].ambient.xyz*c.xyz
   			+gl_LightSource[0].diffuse.xyz*c.xyz*max(0.0,dot(l,t.xyz)), 
   			1.0);
}

//  vanilla Relief Mapping
void ray_intersect_POM (inout vec3 dp, in vec3 ds, in float lerping)
{
   // number of steps (between 25% and 100% of conesteps)
   // note that (lerping squared looks a bit better...slower)
   //int nSteps = 1 + int(mix (1.0, 0.25, lerping) * float(linear_search_steps));
   int nSteps = 1 + int(mix (2.0, 0.5, lerping) * float(linear_search_steps));
   //int nSteps = linear_search_steps;
   // minimum feature size parameter (along ds)
   float dsc = 1.0 / float(nSteps);
   // my starting location (is at z=1, 
   // and moving down so I don't have 
   // to invert height maps)
   // and how high above the surface am I?
   float ht = 1.0, old_ht = 2.0;
   
   //	find the starting location and height
   for (int i = nSteps; (i > 0) && (ht > 0.0); --i)
   {
     // and take the step
     dp += dsc * ds;

     // remember the old location
     old_ht = ht;
     
	   //	find the new location and height
	   vec4 t=texture2D(stepmap,dp.xy);
     ht = t.r - dp.z;
   }
   
   //return;
      
   // _Now_ take one linear step
   dsc *= clamp (ht / (ht-old_ht), 0.0, 1.0);
   dp -= dsc * ds;
   
   // return the vector length needed to hit the height-map
   return;
}
