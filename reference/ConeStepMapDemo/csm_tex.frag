uniform float depth;
uniform float texsize;
uniform float csm_gain;
uniform float csm_offset;

varying vec2 texCoord;
varying vec3 vertex_pos;
varying vec3 light_pos;
varying float vertex_dist;
varying float light_dist;
varying float dist_val;

uniform sampler2D stepmap;
uniform sampler2D texmap;

void intersect_square_cone_exp (inout vec3 dp, in vec3 ds, in float dist_factor);

void main(void)
{
   vec4 t,c;
   vec3 l,s;
   vec3 pt_eye, pt_light;
   float a, df;

   // ray intersect in view direction
   a  = -depth / vertex_pos.z;
   s = vertex_pos * a;
   s.z = 1.0;
  
   // doing LOD based on the texture deltas
   df = 0.05 * sqrt(length (fwidth (texCoord))) 
        * csm_gain + csm_offset / texsize;
  
   //	find the distance to the actualy heightfield
   pt_eye = vec3 (texCoord, 0.0);
   intersect_square_cone_exp (pt_eye, s, df);
  
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

// experimental (distance is taken into account)
void intersect_square_cone_exp (inout vec3 dp, in vec3 ds, in float dist_factor)
{
   // the "not Z" component of the direction vector (for a square cone)
   float iz = max(abs(ds.x),abs(ds.y));
   // my starting location (is at z=0)
   // texture lookup
   vec4 t;
   // and how high above the surface am I?
   float ht, old_ht;
   float CR = 0.0;
  
   //	find the starting location and height
   t=texture2D(stepmap,dp.xy);
   while (t.r > dp.z)
   {
     CR = t.g * t.g;

	   // right, I need to take one step.
	   // I use the current height above the texture,
	   // and the information about the cone-ratio
	   // to size a single step.  So it is fast and 
	   // precise!  (like a coneified version of
	   // "space leaping", but adapted from voxels)
     
     // experimental!!!
     // and take the step
     dp += ds * (dist_factor + (t.r - dp.z)*CR) / (iz + CR);
     
	   //	find the new location and height
	   t=texture2D(stepmap,dp.xy);
   }
   
   // back out to where the cone was (remove the w component)
   //*
   ht = (t.r - dp.z);
   dist_factor /= (iz + CR);
   dp -= ds * dist_factor;
   //*/
   // and sample it
   //*
   t=texture2D(stepmap,dp.xy);
   old_ht = t.r - dp.z;
   // linear interpolation
   dp += ds * dist_factor * (1.0 - clamp (ht / (ht - old_ht), 0.0, 1.0));
   //*/
   
   
   // and a nice cone step
   //*
   t=texture2D(stepmap,dp.xy);
   dp += ds * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);
   //*/
   
   // all done
   return;
}
