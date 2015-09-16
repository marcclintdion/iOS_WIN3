Cone Step Mapping
Jonathan "lonesock" Dummer

* Intro *

This demo uses a modified Irrlicht engine 
to show off the Cone Step Mapping method.
SM3.0 hardware is required to see the full
method.  GLSL capable drivers are required.

All source code is released under the MIT license,
(except the file relief.frag, which is a modified
version of the Relief Mapping shader that came with
TyphoonLabs Shader Design.  I don't know the 
license for that file.)


* ConeStepMap.exe *

Run this app to see the demo.  The demo shows dot3,
parallax, Relief Mapping, Parallax Occlusion Mapping, 
and different versions of Cone Step Mapping for
comparison.

Press F1 to see the keys
Alt-F4 to exit the program.

Regarding the CSM methods, _3step looks ugly but works
on older hardware (but still requires GLSL).  _fixed
uses 10 steps, no branching, so it's quick but shows
artifacts with sharp-edged or noisy heightmaps.  The
_dist and _tex variations use various metrics to do
LOD.  The _dist ones uses the distance from the camera
to the pixel as the metric.  The _tex ones use the
change of the texture coordinate (per screen pixel)
as the metric.  The values of "csm_gain" and "csm_offset"
will modify the workings of these LOD class CSM 
variants.  The value of "steps" will change the behavior
of the POM and RM methods only.

All shaders used by the demo share a common vertex
shader ("shared.vert", ironically).  The demo will
load all files ending with ".frag" and compiles
them as the acompanying fragment shaders.  So to
test any other methods just include a .frag file
in the same directory, and make sure it uses the 
same input/variables as come out of the shared.vert
vertex shader.

Running the program will load the default textures.
If you drag image files onto the app it will use
those images instead of the default textures.  The
app looks for the following naming convention:

*_base.*	=> main color texture (used by all methods)
*_height.*	=> heightmap (dot3 & parallax)
*_step.*	=> step map (RM & POM & CSM)


* HeightProc.exe *

This app is the preprocessor.  It takes a heightmap
(or many) as input (it just reads the height in the
Red component).  The preprocessor performs the 
following 4 functions:

Red:		inverted heightmap
Green:	sqrt (Cone_Ratio)
Blue:		df/dx
Alpha:	df/dy

If anyone codes up a better version of this, I'd
love to distribute it, with proper credit given.


enjoy,
Jonathan
