

//ENVO realtime environment shader for 3d studio max by Aurel Manea //  
//Generated using ShaderFX  http://www.lumonix.net/shaderfx.html    //  

//                  WWW.AURELM.COM/ENVO                             //  


bool title
<
	string UIName = "ENVO environment shader by Aurel Manea   ";
> = false;
bool titl2
<
	string UIName = "www.aurelm.com                                                     ";
> = false;


float3 diffuse_color
<
	string UIName = "Diffuse color";
	string UIType = "ColorSwatch";
> = {0.345098f, 0.345098f, 0.345098f};

 
float3 shadow_color
<
	string UIName = "Ambient color";
	string UIType = "ColorSwatch";
> = {0.0f, 0.0980392f, 0.14902f};

 
bool use_diffuse_map_bool
<
	string UIName = "Use diffuse texture";
> = false;
 

 
texture TextureMap_374
<
	string Name = "JR_ground_02.tga";
	string UIName = "   Diffuse texture";
	string ResourceType = "2D";
>;
 
sampler2D TextureMap_374Sampler = sampler_state
{
	Texture = <TextureMap_374>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};
 

bool use_normal_map_bool
<
	string UIName = "Use normal map";
> = false;

texture nrm1 : NormalMap
<
	string Name = "N_cobblestones_ati.dds";
	string UIName = "   Normal Map";
	string ResourceType = "2D";
>;
 
sampler2D nrm1Sampler = sampler_state
{
	Texture = <nrm1>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

float NM_power
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 1.0;
	float UIStep = 0.1;
	string UIName = "   Normal_map_power";
> = 1.0;



 
texture detail_tex
<
	string Name = "JR_sand_001.tga";
	string UIName = "Detail texture";
	string ResourceType = "2D";
>;
 
sampler2D detail_texSampler = sampler_state
{
	Texture = <detail_tex>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
float detail_texture_power
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 1.0;
	float UIStep = 0.1;
	string UIName = "   Detail texture power";
> = 0.0;

float detail_texture_uv_tile
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 40.0;
	float UIStep = 0.1;
	string UIName = "   Detail texture UV multiplier";
> = 3.0;


texture mask1
<
	string Name = "";
	string UIName = "Mask texture";
	string ResourceType = "2D";
>;
 
sampler2D mask1Sampler = sampler_state
{
	Texture = <mask1>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
 



 bool usemasktex_Rfor_ref_bool
<
	string UIName = "   Mask texture red for reflection";
> = false;
 
 
 bool mask_tex_green_gloss_bool
<
	string UIName = "   Mask texture green for reflection gloss";
> = false;
 
 
 bool use_mask_tex_blue_for_blow_bool
<
	string UIName = "   Mask texture blue for glow";
> = false;


float3 glow_color
<
	string UIName = "Glow color (self illumination)";
	string UIType = "ColorSwatch";
> = {0.0f, 0.0f, 0.0f};
 
bool use_vcblue_for_glow
<
	string UIName = "  Glow intensity from vertex color BLUE";
> = false;


bool Use_parallax
<
	string UIName = "Use parallax map";
> = false;


texture parallax_map
<
	string Name = "";
	string UIName = "   Parallax map";
	string ResourceType = "2D";
>;
 
sampler2D parallax_mapSampler = sampler_state
{
	Texture = <parallax_map>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

 
int texcoord0 : Texcoord 
<
	int Texcoord = 0;
	int MapChannel = 1;
	string UIType = "None"; 
>;

bool use_global_paralax
<
	string UIName = "   Parallax global map (UV 2)";
> = false;
 
int texcoord1 : Texcoord 
<
	int Texcoord = 1;
	int MapChannel = 2;
	string UIType = "None"; 
>;

float paralla_bias
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 0.2;
	float UIStep = 0.001;
	string UIName = "   Parallax power";
> = 0.0;
 
bool use_vc_a_for_parallax_button
<
	string UIName = "   Paralax multiplied from vertex alpha";
> = false;

 
  
bool use_texture_blend
<
	string UIName = "Use texture blend";
> = false;
 
 
 bool use_mask_blend_bool
<
	string UIName = "   Texture blend mask texture";
> = false;


texture TextureMap_7444
<
	string Name = "";
	string UIName = "   Blend mask";
	string ResourceType = "2D";
>;
 
sampler2D TextureMap_7444Sampler = sampler_state
{
	Texture = <TextureMap_7444>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
bool Use_uv3_for_blend_tex
<
	string UIName = "   Blend mask uses UV 3";
> = false;
 

 
float UIConst_6655
<
	string UIType = "FloatSpinner";
	float UIMin = -999.0;
	float UIMax = 999.0;
	float UIStep = 0.1;
	string UIName = "   Texture blend contrast";
> = 10.0;
 

 bool use_uvr_for_second_tex
<
	string UIName = "   Use UV3 for second texture set";
> = false;






texture TextureMap_8119
<
	string Name = "JR_sand_001.tga";
	string UIName = "   Diffuse 2";
	string ResourceType = "2D";
>;
 
sampler2D TextureMap_8119Sampler = sampler_state
{
	Texture = <TextureMap_8119>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};
 



 
texture nrm2 : NormalMap
<
	string Name = "N_cobblestones_ati.dds";
	string UIName = "   Normal Map 2";
	string ResourceType = "2D";
>;
 
sampler2D nrm2Sampler = sampler_state
{
	Texture = <nrm2>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

texture mask2
<
	string Name = "JR_ground_02.tga";
	string UIName = "   Mask tex 2";
	string ResourceType = "2D";
>;
 
sampler2D mask2Sampler = sampler_state
{
	Texture = <mask2>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};

 
 
 
 
 
 





bool use_lightmap
<
	string UIName = "Use Lightmap";
> = false;
 
 
 texture lightmap
<
	string Name = "";
	string UIName = "   LightMap";
	string ResourceType = "2D";
>;
 
sampler2D lightmapSampler = sampler_state
{
	Texture = <lightmap>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};




 
 bool use_directional_lm
<
	string UIName = "Use directional lightmaps";
> = false;
 

 
texture LightMap1
<
	string Name = "";
	string UIName = "   LightMap 1";
	string ResourceType = "2D";
>;
 
sampler2D LightMap1Sampler = sampler_state
{
	Texture = <LightMap1>;
	MinFilter = ANISOTROPIC;
	MagFilter = ANISOTROPIC;
	MipFilter = ANISOTROPIC;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture lightmap2
<
	string Name = "";
	string UIName = "   Lightmap 2";
	string ResourceType = "2D";
>;
 
sampler2D lightmap2Sampler = sampler_state
{
	Texture = <lightmap2>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};
 
texture lightmap3
<
	string Name = "";
	string UIName = "   Lightmap 3";
	string ResourceType = "2D";
>;
 
sampler2D lightmap3Sampler = sampler_state
{
	Texture = <lightmap3>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};


bool use_ref_butt
<
	string UIName = "Use reflections";
> = false;



texture cubemap : environment
<
	string Name = "c_bensBackyard16M.dds";
	string UIName = "   Reflection map";
	string type = "Cube";
>;
 
samplerCUBE cubemapSampler = sampler_state
{
	Texture = <cubemap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

float reflection_gloss_multiplier
<
	string UIType = "FloatSpinner";
	float UIMin = 1.0;
	float UIMax = 10.0;
	float UIStep = 0.1;
	string UIName = "   Reflection gloss multiplication";
> = 1.0;
 
float global_reflection_blur
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10.0;
	float UIStep = 0.1;
	string UIName = "   Reflection global blur";
> = 0.0;
 


float Reflection_power
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 1.0;
	float UIStep = 0.1;
	string UIName = "   Reflections power";
> = 0.0;


bool use_blended_reflections_butt
<
	string UIName = "   Use blended reflections";
> = false;



 
bool vc_col_green_for_ref
<
	string UIName = "   Reflections from vertex color GREEN";
> = false;
 

 
bool use_fres_forr_add_ref
<
	string UIName = "   Reflections use fresnel";
> = false;
 
float reflection_fresnel_power
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 100.0;
	float UIStep = 0.01;
	string UIName = "   Reflections Fresnel Power";
> = 1.0;
 
float ref_fres_scale
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 100.0;
	float UIStep = 0.01;
	string UIName = "   Reflections Fresnel Scale";
> = 1.0;
 
float ref_fres_bias
<
	string UIType = "FloatSpinner";
	float UIMin = -100.0;
	float UIMax = 100.0;
	float UIStep = 0.01;
	string UIName = "   Reflections Fresnel Bias";
> = 0.0;
 
bool lm_as_ref_msk
<
	string UIName = "   Reflections use lightmap mask";
> = false;

float lightmap_mask_brightness
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10.0;
	float UIStep = 0.1;
	string UIName = "   Lightmap mask brightness";
> = 0.0;
 
float lightmap_mask_contrast
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10.0;
	float UIStep = 0.1;
	string UIName = "   Lightmap mask contrast";
> = 1.0;


bool inv_lm_mask
<
	string UIName = "   Invert lightmap mask";
> = false;


bool use_fresnel_button
<
	string UIName = "Use fresnel color";
> = false;
 

 
float3 fresnel_color
<
	string UIName = "   Fresnel color";
	string UIType = "ColorSwatch";
> = {0.392157f, 0.623529f, 0.913726f};
 
float FresnelPower
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10.0;
	float UIStep = 0.01;
	string UIName = "   Fresnel Power";
> = 1.0;
 
float FresnelScale
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10.0;
	float UIStep = 0.01;
	string UIName = "   Fresnel Scale";
> = 2.0;
 
float FresnelBias
<
	string UIType = "FloatSpinner";
	float UIMin = -10.0;
	float UIMax = 10.0;
	float UIStep = 0.01;
	string UIName = "   Fresnel Bias";
> = 0.0;
 

 
 
bool use_lm_mask_fresnel_bool
<
	string UIName = "   Use lightmap mask for fresnel";
> = false;































bool usefog
<
	string UIName = "Use fog";
> = false;
 
float3 fog_color
<
	string UIName = "   Fog color";
	string UIType = "ColorSwatch";
> = {1.0f, 1.0f, 1.0f};
 
float fogalpha
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 1.0;
	float UIStep = 0.1;
	string UIName = "   Fog alpha";
> = 0.0;
 
float fog_near
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 9999.0;
	float UIStep = 0.1;
	string UIName = "   Fog near";
> = 1.0;
 
float fog_far
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 9999.0;
	float UIStep = 0.1;
	string UIName = "   Fog Far";
> = 1.0;
 
float fog_altitude_scale
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 9999.0;
	float UIStep = 0.1;
	string UIName = "   Fog altitude scale";
> = 1.0;
 
float fog_altitude_start
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 9999.0;
	float UIStep = 0.1;
	string UIName = "   Fog altitude start";
> = 1.0;
 
float fog_altitude_end
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 9999.0;
	float UIStep = 0.1;
	string UIName = "   Fog altitude end";
> = 1.0;
 
float fog_altitude_base
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 9999.0;
	float UIStep = 0.1;
	string UIName = "   Fog altitude base";
> = 1.0;
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 


 
//Vertex Color and Alpha in from Max 
int texcoord2 : Texcoord 
<
	int Texcoord = 2;
	int MapChannel = 3;
	string UIType = "None"; 
>;

int texcoord3 : Texcoord 
<
	int Texcoord = 3;
	int MapChannel = 0;
	string UIType = "None"; 
>;

int texcoord4 : Texcoord 
<
	int Texcoord = 4;
	int MapChannel = -2;
	string UIType = "None"; 
>;


 

 

 

 
bool use_dynamic_light
<
	string UIName = "Use dynamic light";
> = true;
 
float3 SpecularColor : Specular
<
	string UIName = "Light specular color";
	string UIType = "ColorSwatch";
> = {0.447059f, 0.447059f, 0.447059f};
 
float glossiness
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 100.0;
	float UIStep = 0.1;
	string UIName = "   Light glossiness";
> = 32.0;
 
float3 DiffuseColor : Diffuse
<
	string UIName = "   Light diffuse color";
	string UIType = "ColorSwatch";
> = {0.866667f, 0.866667f, 0.866667f};
 
bool Use_attenuation_bool
<
	string UIName = "Use light attenuation";
> = false;
 
float Attenuation3
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10000.0;
	float UIStep = 0.1;
	string UIName = "   Light Attenuation 3";
> = 0;
 
float Attenuation2
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10000.0;
	float UIStep = 0.1;
	string UIName = "   Light Attenuation 2";
> = 1;
 
float Attenuation1
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10000.0;
	float UIStep = 0.1;
	string UIName = "   Light Attenuation 1";
> = 0;
 
float AttenuationScale
<
	string UIType = "FloatSpinner";
	float UIMin = 0.0;
	float UIMax = 10000.0;
	float UIStep = 1.0;
	string UIName = "   Light Attenuation Scale";
> = 50.0;
 



 

 

 


 



 



 

 



// this function does the different types of light attenuation 
float attenuation_funcT1(int lightattenType, float4 lightAttenuation, float3 lightVec) 
{ 
	float att = 1.0; 
	return att; 
} 
	 
// this function does the different types of cone angle 
float coneangle_funcT1(int lightconeType, float lightHotspot, float lightFalloff, float3 lightVec, float3 lightDir) 
{ 
	float cone = 1.0; 
	return cone; 
} 

/************** light info **************/ 

float3 light1Dir : Direction 
< 
	string UIName = "Light 1 Direction"; 
	string Object = "TargetLight"; 
	string Space = "World"; 
		int refID = 1; 
> = {100.0f, 100.0f, 100.0f}; 

float3 light1Pos : POSITION 
< 
	string UIName = "Light 1 Position"; 
	string Object = "PointLight"; 
	string Space = "World"; 
		int refID = 1; 
> = {100.0f, 100.0f, 100.0f}; 

float4 light1Color : LIGHTCOLOR <int LightRef = 1; string UIWidget = "None"; > = { 1.0f, 1.0f, 1.0f, 1.0f}; 
float4 light1Attenuation : LightAttenuation <int LightRef = 1; string UIWidget = "None"; > = { 20.0f, 30.0f, 0.0f, 100.0f}; 
float light1Hotspot : LightHotSpot <int LightRef = 1; string UIWidget = "None"; > = { 43.0f }; 
float light1Falloff : LightFallOff <int LightRef = 1; string UIWidget = "None"; > = { 45.0f }; 

#define light1Type 1
#define light1attenType 0
#define light1coneType 0
#define light1CastShadows false

//---------------------------------- 

float4x4 wvp : WorldViewProjection < string UIType = "None"; >;  
float4x4 worldI : WorldInverse < string UIType = "None"; >;  
float4x4 worldIT : WorldInverseTranspose < string UIType = "None"; >;  
float4x4 viewInv : ViewInverse < string UIType = "None"; >;  
float4x4 world : World < string UIType = "None"; >;  
// create the light vector 
float3 lightVec_funcT1(float3 worldSpacePos, float3 lightVector, float3x3 objTangentXf, int lightType) 
{ 
	float3 lightVec = mul(objTangentXf, (mul((lightVector - worldSpacePos), worldI).xyz)); 
	return lightVec; 
} 



// input from application 
	struct a2vT1 { 
	float4 position		: POSITION; 

	float4 tangent		: TANGENT; 
	float4 binormal		: BINORMAL; 
	float4 normal		: NORMAL; 
	float2 texCoord		: TEXCOORD0; 
	float2 texCoord1	: TEXCOORD1; 
	float3 vertcol		: TEXCOORD3; 
	float vertalpha 	: TEXCOORD4; 
	float2 texCoord2	: TEXCOORD2; 

}; 

// output to fragment program 
struct v2fT1 { 
        float4 position    		: POSITION; 

        float3 eyeVec	    	: TEXCOORD0; 
	float2 texCoord			: TEXCOORD1; 
	float2 texCoord1		: TEXCOORD2; 
        float4 color    		: COLOR0; 
	float2 texCoord2		: TEXCOORD3; 
        float3 lightVec    		: TEXCOORD4; 
        float4 worldBinormal 	: TEXCOORD5; 
        float4 worldNormal   	: TEXCOORD6; 
        float3 viewDir	    	: TEXCOORD7; 
        float4 oposition	    	: TEXCOORD8; 

}; 

//Ambient and Self-Illum Pass Vertex Shader
v2fT1 avT1(a2vT1 In, uniform float3 lightPos, uniform int lightType, uniform float3 lightDir) 
{ 
    v2fT1 Out = (v2fT1)0; 
	Out.position = mul(In.position, wvp);				//transform vert position to homogeneous clip space 

	//this code was added by the Eye Vector Node 
	float3x3 objTangentXf;								//build object to tangent space transform matrix 
	#ifdef YUP 
	objTangentXf[0] = In.tangent.xyz; 
	objTangentXf[1] = -In.binormal.xyz; 
	#else 
	objTangentXf[0] = In.binormal.xyz; 
	objTangentXf[1] = -In.tangent.xyz; 
	#endif 
	objTangentXf[2] = In.normal.xyz; 
	//these three lines were added by the Eye Vector Node 
	float4 osIPos = mul(viewInv[3], worldI);			//put world space eye position in object space 
	float3 osIVec = osIPos.xyz - In.position.xyz;		//object space eye vector 
	Out.eyeVec = mul(objTangentXf, osIVec);				//tangent space eye vector passed out 
	In.texCoord += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord = In.texCoord;						//pass through texture coordinates from channel 1 
	In.texCoord1 += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord1 = In.texCoord1;						//pass through texture coordinates from channel 2 
	//this code was added by the Vertex Color Node 
	Out.color = float4(In.vertcol.rgb, In.vertalpha.r); 

	In.texCoord2 += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord2 = In.texCoord2;						//pass through texture coordinates from channel 3 
	float3 wsLPos = mul(In.position, world).xyz;			//put the vert position in world space 
	float3 wsLVec = lightPos - wsLPos;    //cast a ray to the light 
	float3 osLVec = mul(wsLVec, worldI).xyz;  //transform the world space light vector to object space 
	Out.lightVec = mul(objTangentXf, osLVec);			//tangent space light vector passed out 
	//this code was added by the World Space Transform Node 
	Out.worldNormal = float4( mul(In.normal, worldIT).xyz, In.normal.w );		//compute world space normal 
	Out.worldBinormal = float4(mul(In.binormal, worldIT).xyz, 1);	//compute world space binormal 
	if (dot(cross(In.binormal, In.normal), In.tangent) < 0.0) Out.worldBinormal.w = -1; //detect mirrored UV space 
	Out.viewDir = mul(In.position, world) - viewInv[3]; 
	//this code was added by the Vertex Position Node 
	#ifdef YUP 
	Out.oposition = In.position.xzyw;		//Output vertex position in object space 
	Out.oposition.y = -Out.oposition.y; 
	#else 
	Out.oposition = In.position;		//Output vertex position in object space 
	#endif 

	return Out; 
} 

//Ambient and Self-Illum Pass Pixel Shader
float4 afT1(v2fT1 In, uniform float3 lightDir, uniform float4 lightColor, uniform float4 lightAttenuation, uniform float lightHotspot, uniform float lightFalloff, uniform int lightType, uniform int lightattenType, uniform int lightconeType, uniform bool lightCastShadows, uniform int shadowPassCount) : COLOR 
{ 

	float usefob_bool = 0.0; 
	float use_ref_bool = 0.0; 
	float use_blended_reflections_bool = 0.0; 
	float use_fresnel_bool = 0.0; 
	float fresnamsk = 0.0; 
	float3 V = normalize(In.eyeVec.xyz);		//normalized eye vector 
	float4 Normal = float4(0,0,1,0);	//tangent space normal vector 
	float usenrmbool = 1.0; 
	float blend_bool = 1.0; 
	float parallax_use_bool = 0.0; 
	float2 OriginalTexCoords = In.texCoord.xy; 
	float UIConst_5325 = 0.0; 
	float2 uv1 = In.texCoord.xy; 
	float2 uv2 = In.texCoord1.xy; 
	float2 if_use_parallax_uv2;
	if (use_global_paralax == UIConst_5325) if_use_parallax_uv2 = uv1; else if_use_parallax_uv2 = uv2; 
	float4 parallax_map = tex2D(parallax_mapSampler, if_use_parallax_uv2.xy);
	float Two = 2.0; 
	float One = 1.0; 
	float3 INEyeVec_851 = In.eyeVec.xyz;		//unnormalized eye vector 
	INEyeVec_851 = normalize(INEyeVec_851); 
	INEyeVec_851.y = -INEyeVec_851.y; //invert eye vector Y
	float use_vc_a_for_parallax = 1.0; 
	float UIConst_3496 = 0.0; 
	float4 VertColor = In.color; 		//bringing in the vertex color 
	float if_use_vc_a_for_parallax;
	if (use_vc_a_for_parallax_button != use_vc_a_for_parallax) if_use_vc_a_for_parallax = UIConst_3496; else if_use_vc_a_for_parallax = VertColor.a; 
	float2 If_use_parallax_map;
	if (Use_parallax == parallax_use_bool) If_use_parallax_map = OriginalTexCoords; else If_use_parallax_map = (((((parallax_map.r * Two) - One) * INEyeVec_851) * (paralla_bias * if_use_vc_a_for_parallax)) + OriginalTexCoords); 
	float4 nrm1 = tex2D(nrm1Sampler, If_use_parallax_map.xy);
	nrm1.xyz = nrm1.xyz * 2 - 1;		//expand to -1 to 1 range 
	nrm1.rgb = normalize(nrm1.rgb); 		//normalized the normal vector 
	float use_uv3_for_second_tex_bool = 0.0; 
	float2 uv3 = In.texCoord2.xy; 
	float2 uv_tex_2;
	if (use_uvr_for_second_tex == use_uv3_for_second_tex_bool) uv_tex_2 = If_use_parallax_map; else uv_tex_2 = uv3; 
	float4 nrm2 = tex2D(nrm2Sampler, uv_tex_2.xy);
	nrm2.xyz = nrm2.xyz * 2 - 1;		//expand to -1 to 1 range 
	nrm2.rgb = normalize(nrm2.rgb); 		//normalized the normal vector 
	float use_mask_blend = 0.0; 
	float UIConst_7743 = 0.0; 
	float2 if_use_uv3_for_blend_mask;
	if (Use_uv3_for_blend_tex == UIConst_7743) if_use_uv3_for_blend_mask = If_use_parallax_map; else if_use_uv3_for_blend_mask = uv3; 
	float4 TextureMap_7444 = tex2D(TextureMap_7444Sampler, if_use_uv3_for_blend_mask.xy);
	float if_use_mask_blend;
	if (use_mask_blend_bool != use_mask_blend) if_use_mask_blend = ((VertColor.r * TextureMap_7444.r) * UIConst_6655); else if_use_mask_blend = VertColor.r; 
	float UIConst_6436 = 0.0; 
	float UIConst_824 = 1.0; 
	float MathClamp_3346 = clamp(if_use_mask_blend, UIConst_6436, UIConst_824); 
	float3 normal_blend = lerp(nrm1.rgb, nrm2.rgb, MathClamp_3346); 
	float3 if_tex_blend;
	if (use_texture_blend == blend_bool) if_tex_blend = normal_blend; else if_tex_blend = nrm1.rgb; 
	float3 if_use_normal_map;
	if (use_normal_map_bool != usenrmbool) if_use_normal_map = Normal; else if_use_normal_map = if_tex_blend; 
	float3 NM_power_blend = lerp(Normal, if_use_normal_map, NM_power); 
	float NdotV_fresnel = saturate(dot(V,(Normal * NM_power_blend))); 		//clamped dot product 
	float Pow_NdotV = pow(NdotV_fresnel,FresnelPower);		//x to the power of y 
	float clamp_fresnel = (clamp(1-((Pow_NdotV * FresnelScale) + FresnelBias),0.0,1.0)
);
	float3 Fresnel = fresnel_color.rgb * clamp_fresnel;
	float inv_lm_mask_bool = 0.0; 
	float use_dyn_l_on = 0.0; 
	float3 L = normalize(In.lightVec.xyz);	//normalized light vector 
	float3 NormalizedHalfAngle = normalize((L + V));		//Normalize 
	float NdotH_specular = saturate(dot(NormalizedHalfAngle,NM_power_blend)); 		//clamped dot product 
	float NdotH_pow_Glossiness = pow(NdotH_specular,glossiness);		//x to the power of y 
	float NdotL_diffuse = saturate(dot(L,NM_power_blend)); 		//clamped dot product 
	float UIConst_2380 = 0.0; 
	float One_ = 1.0; 
	float3 L_4377 = In.lightVec.xyz;		//unnormalized light vector 
	float LengthOfLightVector = length(L_4377);		//Measure the length of the vector 
	float UIConst_8429 = 1.0; 
	float if_use_attenaution;
	if (Use_attenuation_bool != UIConst_2380) if_use_attenaution = ((One_ / ((((LengthOfLightVector * LengthOfLightVector) * Attenuation3) + (LengthOfLightVector * Attenuation2)) + Attenuation1)) * AttenuationScale); else if_use_attenaution = UIConst_8429; 
	float3 UIColor_3328 = float3(0.0f, 0.0f, 0.0f );
	float3 If_use_dyn_l;
	if (use_dynamic_light != use_dyn_l_on) If_use_dyn_l = ((((SpecularColor.rgb * NdotH_pow_Glossiness) * 1.0) + (NdotL_diffuse * DiffuseColor.rgb)) * if_use_attenaution); else If_use_dyn_l = UIColor_3328.rgb; 
	float lightmap_off = 0.0; 
	float UIConst_8749 = 0.0; 
	float4 lightmap = tex2D(lightmapSampler, In.texCoord1.xy);
	float3 x2 = (lightmap.rgb*2.0
);
	float4 LightMap1 = tex2D(LightMap1Sampler, In.texCoord1.xy);
	float UIConst_2271 = 2.0; 
	float3 bumpBasis0 = float3(0.796875, 0.0, 0.570313); 
	float MathDotProduct_620 = saturate(dot(NM_power_blend,bumpBasis0)); 		//clamped dot product 
	float MathMinMax_5910 = saturate(MathDotProduct_620); 
	float3 bumpBasis1 = float3(-0.24, 0.710938, 0.570313); 
	float MathDotProduct_2523 = saturate(dot(NM_power_blend,bumpBasis1)); 		//clamped dot product 
	float MathMinMax_5376 = saturate(MathDotProduct_2523); 
	float3 bumpBasis2 = float3(-0.40625, -0.710938, 0.570313); 
	float MathDotProduct_8309 = saturate(dot(NM_power_blend,bumpBasis2)); 		//clamped dot product 
	float MathMinMax_9943 = saturate(MathDotProduct_8309); 
	float3 dp = float3(MathMinMax_5910, MathMinMax_5376, MathMinMax_9943);
	float3 dpSquared = dp * dp;
	float3 MathVecConstuct_9780 = dpSquared;
	float4 lightmap2 = tex2D(lightmap2Sampler, In.texCoord1.xy);
	float4 lightmap3 = tex2D(lightmap3Sampler, In.texCoord1.xy);
	float3 oneVector = float3(1.0, 1.0, 1.0); 
	float sum = saturate(dot(dpSquared,oneVector)); 		//clamped dot product 
	float3 MathIf_5772;
	if (use_directional_lm == UIConst_8749) MathIf_5772 = x2; else MathIf_5772 = (((((LightMap1.rgb * UIConst_2271) * MathVecConstuct_9780.r) + ((lightmap2.rgb * UIConst_2271) * MathVecConstuct_9780.g)) + (MathVecConstuct_9780.b * (lightmap3.rgb * UIConst_2271))) / sum); 
	float3 if_lightmap;
	if (use_lightmap != lightmap_off) if_lightmap = MathIf_5772; else if_lightmap = shadow_color.rgb; 
	float3 add_light_to_lm = If_use_dyn_l + if_lightmap;
	float luminance = (add_light_to_lm.r*0.2126 + add_light_to_lm.g*0.7152 + add_light_to_lm.b*0.0722
);
	float MathBrightnessContrast_129 = (luminance - 0.5) * lightmap_mask_contrast + 0.5 + lightmap_mask_brightness;
	float CustomCode_7830 = (clamp(MathBrightnessContrast_129,0.0,1.0)
);
	float one_minus = (1 - CustomCode_7830
);
	float if_in_lm_mask;
	if (inv_lm_mask != inv_lm_mask_bool) if_in_lm_mask = one_minus; else if_in_lm_mask = CustomCode_7830; 
	float3 use_fres_mask;
	if (use_lm_mask_fresnel_bool != fresnamsk) use_fres_mask = (Fresnel * if_in_lm_mask); else use_fres_mask = Fresnel; 
	float3 If_use_fresnel;
	if (use_fresnel_button != use_fresnel_bool) If_use_fresnel = (use_fres_mask + add_light_to_lm); else If_use_fresnel = add_light_to_lm; 
	float UIConst_5728 = 1.0; 
	float masktex_white = 1.0; 
	float4 mask1 = tex2D(mask1Sampler, If_use_parallax_map.xy);
	float4 mask2 = tex2D(mask2Sampler, uv_tex_2.xy);
	float4 MathLerp_3777 = lerp(mask1, mask2, MathClamp_3346); 
	float4 ifuseblend;
	if (use_texture_blend == blend_bool) ifuseblend = MathLerp_3777; else ifuseblend = mask1; 
	float4 MathVecConstuct_5512 = ifuseblend;
	float masktexref_blue;
	if (use_mask_tex_blue_for_blow_bool != UIConst_5728) masktexref_blue = masktex_white; else masktexref_blue = MathVecConstuct_5512.b; 
	float3 MathVecConstuct_3825 = float3(masktexref_blue, masktexref_blue, masktexref_blue);
	float usevcgreen_for_glow = 1.0; 
	float useglow_vc_green = 1.0; 
	float if_use_vc_b_for_glow;
	if (use_vcblue_for_glow != usevcgreen_for_glow) if_use_vc_b_for_glow = useglow_vc_green; else if_use_vc_b_for_glow = VertColor.b; 
	float use_diffuse_bool = 1.0; 
	float4 TextureMap_374 = tex2D(TextureMap_374Sampler, If_use_parallax_map.xy);
	float4 TextureMap_8119 = tex2D(TextureMap_8119Sampler, uv_tex_2.xy);
	float3 blend_diffuse = lerp(TextureMap_374.rgb, TextureMap_8119.rgb, MathClamp_3346); 
	float3 if_use_blend;
	if (use_texture_blend == blend_bool) if_use_blend = blend_diffuse; else if_use_blend = TextureMap_374.rgb; 
	float3 if_use_diffuse_map;
	if (use_diffuse_map_bool != use_diffuse_bool) if_use_diffuse_map = diffuse_color.rgb; else if_use_diffuse_map = if_use_blend; 
	float2 d_tex_uv_mul = (If_use_parallax_map*detail_texture_uv_tile
);
	float4 detail_tex = tex2D(detail_texSampler, d_tex_uv_mul.xy);
	float detailtex_normalize = ((detail_tex.r-0.5)*detail_texture_power
);
	float UIConst_7380 = 1.0; 
	float3 MathOperator_969 = ((If_use_fresnel + ((MathVecConstuct_3825 * glow_color.rgb) * if_use_vc_b_for_glow)) * (if_use_diffuse_map + detailtex_normalize)) * UIConst_7380;
	//this code was added by the World Space Transform Node 
	float3 Nn = normalize(In.worldNormal.xyz); 		//input the vectors required for tangent to world space transform 
	float3 Bn = normalize(cross(In.worldBinormal.xyz, In.worldNormal.xyz)); 
	float3 Tn = cross(Nn, Bn); 
	Bn *= In.worldBinormal.w; 
	#ifdef YUP 
		float3 WorldSpaceXform = ( Nn * NM_power_blend.z ) + (NM_power_blend.x * Tn ) + ( NM_power_blend.y * -Bn); 
	#else 
		float3 WorldSpaceXform = ( Nn * NM_power_blend.z ) + (NM_power_blend.x * Bn ) + ( NM_power_blend.y * -Tn); 
	#endif 
	float3 Reflection = reflect(In.viewDir, WorldSpaceXform);		//Compute the reflection vector 
	float masktex_green_gloss = 1.0; 
	float masktexref_green;
	if (mask_tex_green_gloss_bool != masktex_green_gloss) masktexref_green = masktex_white; else masktexref_green = MathVecConstuct_5512.g; 
	float gloss = ((1.0 -masktexref_green) * reflection_gloss_multiplier + global_reflection_blur
);
	float3 cubemapInputVector = Reflection.xyz;
	#ifdef YUP 
	#else 
	cubemapInputVector.xyz = cubemapInputVector.xzy;  //swizzle required for Max 
	#endif 
	float4 cubemap = texCUBElod(cubemapSampler, float4(cubemapInputVector, gloss));
	float lm_as_ref_msk_bool = 0.0; 
	float lm_as_ref_msk_true = 1.0; 
	float lightmap_reflect;
	if (lm_as_ref_msk == lm_as_ref_msk_bool) lightmap_reflect = lm_as_ref_msk_true; else lightmap_reflect = if_in_lm_mask; 
	float vc_col_green_ref = 1.0; 
	float vc_green_one = 0.0; 
	float if_use_vc_g_for_ref;
	if (vc_col_green_for_ref != vc_col_green_ref) if_use_vc_g_for_ref = vc_green_one; else if_use_vc_g_for_ref = VertColor.g; 
	float invert_vcg = (1 - if_use_vc_g_for_ref
);
	float usemasktex_Rfor_ref = 1.0; 
	float masktexref_red;
	if (usemasktex_Rfor_ref_bool != usemasktex_Rfor_ref) masktexref_red = masktex_white; else masktexref_red = MathVecConstuct_5512.r; 
	float UIConst_5349 = 0.0; 
	float UIConst_4343 = 1.0; 
	float MathPow_1681 = pow(NdotV_fresnel,reflection_fresnel_power);		//x to the power of y 
	float clamp_fresn = (clamp(1-((MathPow_1681 * ref_fres_scale) + ref_fres_bias),0.0,1.0)
);
	float IF_use_fres_for_blend_ref;
	if (use_fres_forr_add_ref == UIConst_5349) IF_use_fres_for_blend_ref = UIConst_4343; else IF_use_fres_for_blend_ref = clamp_fresn; 
	float3 reflection_blend = lerp(MathOperator_969, cubemap.rgb, ((lightmap_reflect * (Reflection_power * (invert_vcg * masktexref_red))) * IF_use_fres_for_blend_ref)); 
	float3 MathOperator_5296 = cubemap.rgb * ((Reflection_power * masktexref_red) * invert_vcg);
	float3 if_use_fres_add_ref;
	if (use_fres_forr_add_ref == UIConst_5349) if_use_fres_add_ref = MathOperator_5296; else if_use_fres_add_ref = (MathOperator_5296 * clamp_fresn); 
	float3 lightmap_ref;
	if (lm_as_ref_msk == lm_as_ref_msk_bool) lightmap_ref = if_use_fres_add_ref; else lightmap_ref = (if_in_lm_mask * if_use_fres_add_ref); 
	float3 If_use_reflection_blend;
	if (use_blended_reflections_butt != use_blended_reflections_bool) If_use_reflection_blend = reflection_blend; else If_use_reflection_blend = (lightmap_ref + MathOperator_969); 
	float3 If_use_ref;
	if (use_ref_butt != use_ref_bool) If_use_ref = If_use_reflection_blend; else If_use_ref = MathOperator_969; 
	float3 INEyeVec_6276 = In.eyeVec.xyz;		//unnormalized eye vector 
	float MathLength_8975 = length(INEyeVec_6276);		//Measure the length of the vector 
	float3 INVertPos_1048 = In.oposition.xyz;		//Incoming vertex position in object space 
	float MathClamp_7628 = clamp((fog_altitude_start + (INVertPos_1048.z / fog_altitude_scale)), fog_altitude_base, fog_altitude_end); 
	float MathMinMax_4145 = saturate((((MathLength_8975 - fog_near) / (fog_far - fog_near)) / MathClamp_7628)); 
	float3 fog_blend = lerp(If_use_ref, fog_color.rgb, (fogalpha * MathMinMax_4145)); 
	float3 If_use_fog;
	if (usefog == usefob_bool) If_use_fog = If_use_ref; else If_use_fog = fog_blend; 
	float3 input1 = If_use_fog; 

	float4 ret =  float4(0,0,0,1); 
	ret = float4(input1, 1); 
	return ret; 
} 

technique Opaque  
{  
	pass ambient  
    {		 
		VertexShader = compile vs_3_0 avT1(light1Pos,  light1Type, light1Dir); 
		ZEnable = true; 
		ZWriteEnable = true; 
		CullMode = cw; 
		ShadeMode = Gouraud;
		AlphaBlendEnable = false; 
		AlphaTestEnable = FALSE; 
	PixelShader = compile ps_3_0 afT1(light1Dir, light1Color, light1Attenuation, light1Hotspot, light1Falloff, light1Type, light1attenType, light1coneType, light1CastShadows, 1); 
	}  

}  



/*============================================================================
 ============= Alpha_test TECHNIQUE ============= 
============================================================================*/



// this function does the different types of light attenuation 
float attenuation_funcT2(int lightattenType, float4 lightAttenuation, float3 lightVec) 
{ 
	float att = 1.0; 
	return att; 
} 
	 
// this function does the different types of cone angle 
float coneangle_funcT2(int lightconeType, float lightHotspot, float lightFalloff, float3 lightVec, float3 lightDir) 
{ 
	float cone = 1.0; 
	return cone; 
} 

/************** light info **************/ 

// create the light vector 
float3 lightVec_funcT2(float3 worldSpacePos, float3 lightVector, float3x3 objTangentXf, int lightType) 
{ 
	float3 lightVec = mul(objTangentXf, (mul((lightVector - worldSpacePos), worldI).xyz)); 
	return lightVec; 
} 



// input from application 
	struct a2vT2 { 
	float4 position		: POSITION; 

	float4 tangent		: TANGENT; 
	float4 binormal		: BINORMAL; 
	float4 normal		: NORMAL; 
	float2 texCoord		: TEXCOORD0; 
	float2 texCoord1	: TEXCOORD1; 
	float3 vertcol		: TEXCOORD3; 
	float vertalpha 	: TEXCOORD4; 
	float2 texCoord2	: TEXCOORD2; 

}; 

// output to fragment program 
struct v2fT2 { 
        float4 position    		: POSITION; 

        float3 eyeVec	    	: TEXCOORD0; 
	float2 texCoord			: TEXCOORD1; 
	float2 texCoord1		: TEXCOORD2; 
        float4 color    		: COLOR0; 
	float2 texCoord2		: TEXCOORD3; 
        float3 lightVec    		: TEXCOORD4; 
        float4 worldBinormal 	: TEXCOORD5; 
        float4 worldNormal   	: TEXCOORD6; 
        float3 viewDir	    	: TEXCOORD7; 
        float4 oposition	    	: TEXCOORD8; 

}; 

//Ambient and Self-Illum Pass Vertex Shader
v2fT2 avT2(a2vT2 In, uniform float3 lightPos, uniform int lightType, uniform float3 lightDir) 
{ 
    v2fT2 Out = (v2fT2)0; 
	Out.position = mul(In.position, wvp);				//transform vert position to homogeneous clip space 

	//this code was added by the Eye Vector Node 
	float3x3 objTangentXf;								//build object to tangent space transform matrix 
	#ifdef YUP 
	objTangentXf[0] = In.tangent.xyz; 
	objTangentXf[1] = -In.binormal.xyz; 
	#else 
	objTangentXf[0] = In.binormal.xyz; 
	objTangentXf[1] = -In.tangent.xyz; 
	#endif 
	objTangentXf[2] = In.normal.xyz; 
	//these three lines were added by the Eye Vector Node 
	float4 osIPos = mul(viewInv[3], worldI);			//put world space eye position in object space 
	float3 osIVec = osIPos.xyz - In.position.xyz;		//object space eye vector 
	Out.eyeVec = mul(objTangentXf, osIVec);				//tangent space eye vector passed out 
	In.texCoord += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord = In.texCoord;						//pass through texture coordinates from channel 1 
	In.texCoord1 += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord1 = In.texCoord1;						//pass through texture coordinates from channel 2 
	//this code was added by the Vertex Color Node 
	Out.color = float4(In.vertcol.rgb, In.vertalpha.r); 

	In.texCoord2 += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord2 = In.texCoord2;						//pass through texture coordinates from channel 3 
	float3 wsLPos = mul(In.position, world).xyz;			//put the vert position in world space 
	float3 wsLVec = lightPos - wsLPos;    //cast a ray to the light 
	float3 osLVec = mul(wsLVec, worldI).xyz;  //transform the world space light vector to object space 
	Out.lightVec = mul(objTangentXf, osLVec);			//tangent space light vector passed out 
	//this code was added by the World Space Transform Node 
	Out.worldNormal = float4( mul(In.normal, worldIT).xyz, In.normal.w );		//compute world space normal 
	Out.worldBinormal = float4(mul(In.binormal, worldIT).xyz, 1);	//compute world space binormal 
	if (dot(cross(In.binormal, In.normal), In.tangent) < 0.0) Out.worldBinormal.w = -1; //detect mirrored UV space 
	Out.viewDir = mul(In.position, world) - viewInv[3]; 
	//this code was added by the Vertex Position Node 
	#ifdef YUP 
	Out.oposition = In.position.xzyw;		//Output vertex position in object space 
	Out.oposition.y = -Out.oposition.y; 
	#else 
	Out.oposition = In.position;		//Output vertex position in object space 
	#endif 

	return Out; 
} 

//Ambient and Self-Illum Pass Pixel Shader
float4 afT2(v2fT2 In, uniform float3 lightDir, uniform float4 lightColor, uniform float4 lightAttenuation, uniform float lightHotspot, uniform float lightFalloff, uniform int lightType, uniform int lightattenType, uniform int lightconeType, uniform bool lightCastShadows, uniform int shadowPassCount) : COLOR 
{ 

	float usefob_bool = 0.0; 
	float use_ref_bool = 0.0; 
	float use_blended_reflections_bool = 0.0; 
	float use_fresnel_bool = 0.0; 
	float fresnamsk = 0.0; 
	float3 V = normalize(In.eyeVec.xyz);		//normalized eye vector 
	float4 Normal = float4(0,0,1,0);	//tangent space normal vector 
	float usenrmbool = 1.0; 
	float blend_bool = 1.0; 
	float parallax_use_bool = 0.0; 
	float2 OriginalTexCoords = In.texCoord.xy; 
	float UIConst_5325 = 0.0; 
	float2 uv1 = In.texCoord.xy; 
	float2 uv2 = In.texCoord1.xy; 
	float2 if_use_parallax_uv2;
	if (use_global_paralax == UIConst_5325) if_use_parallax_uv2 = uv1; else if_use_parallax_uv2 = uv2; 
	float4 parallax_map = tex2D(parallax_mapSampler, if_use_parallax_uv2.xy);
	float Two = 2.0; 
	float One = 1.0; 
	float3 INEyeVec_851 = In.eyeVec.xyz;		//unnormalized eye vector 
	INEyeVec_851 = normalize(INEyeVec_851); 
	INEyeVec_851.y = -INEyeVec_851.y; //invert eye vector Y
	float use_vc_a_for_parallax = 1.0; 
	float UIConst_3496 = 0.0; 
	float4 VertColor = In.color; 		//bringing in the vertex color 
	float if_use_vc_a_for_parallax;
	if (use_vc_a_for_parallax_button != use_vc_a_for_parallax) if_use_vc_a_for_parallax = UIConst_3496; else if_use_vc_a_for_parallax = VertColor.a; 
	float2 If_use_parallax_map;
	if (Use_parallax == parallax_use_bool) If_use_parallax_map = OriginalTexCoords; else If_use_parallax_map = (((((parallax_map.r * Two) - One) * INEyeVec_851) * (paralla_bias * if_use_vc_a_for_parallax)) + OriginalTexCoords); 
	float4 nrm1 = tex2D(nrm1Sampler, If_use_parallax_map.xy);
	nrm1.xyz = nrm1.xyz * 2 - 1;		//expand to -1 to 1 range 
	nrm1.rgb = normalize(nrm1.rgb); 		//normalized the normal vector 
	float use_uv3_for_second_tex_bool = 0.0; 
	float2 uv3 = In.texCoord2.xy; 
	float2 uv_tex_2;
	if (use_uvr_for_second_tex == use_uv3_for_second_tex_bool) uv_tex_2 = If_use_parallax_map; else uv_tex_2 = uv3; 
	float4 nrm2 = tex2D(nrm2Sampler, uv_tex_2.xy);
	nrm2.xyz = nrm2.xyz * 2 - 1;		//expand to -1 to 1 range 
	nrm2.rgb = normalize(nrm2.rgb); 		//normalized the normal vector 
	float use_mask_blend = 0.0; 
	float UIConst_7743 = 0.0; 
	float2 if_use_uv3_for_blend_mask;
	if (Use_uv3_for_blend_tex == UIConst_7743) if_use_uv3_for_blend_mask = If_use_parallax_map; else if_use_uv3_for_blend_mask = uv3; 
	float4 TextureMap_7444 = tex2D(TextureMap_7444Sampler, if_use_uv3_for_blend_mask.xy);
	float if_use_mask_blend;
	if (use_mask_blend_bool != use_mask_blend) if_use_mask_blend = ((VertColor.r * TextureMap_7444.r) * UIConst_6655); else if_use_mask_blend = VertColor.r; 
	float UIConst_6436 = 0.0; 
	float UIConst_824 = 1.0; 
	float MathClamp_3346 = clamp(if_use_mask_blend, UIConst_6436, UIConst_824); 
	float3 normal_blend = lerp(nrm1.rgb, nrm2.rgb, MathClamp_3346); 
	float3 if_tex_blend;
	if (use_texture_blend == blend_bool) if_tex_blend = normal_blend; else if_tex_blend = nrm1.rgb; 
	float3 if_use_normal_map;
	if (use_normal_map_bool != usenrmbool) if_use_normal_map = Normal; else if_use_normal_map = if_tex_blend; 
	float3 NM_power_blend = lerp(Normal, if_use_normal_map, NM_power); 
	float NdotV_fresnel = saturate(dot(V,(Normal * NM_power_blend))); 		//clamped dot product 
	float Pow_NdotV = pow(NdotV_fresnel,FresnelPower);		//x to the power of y 
	float clamp_fresnel = (clamp(1-((Pow_NdotV * FresnelScale) + FresnelBias),0.0,1.0)
);
	float3 Fresnel = fresnel_color.rgb * clamp_fresnel;
	float inv_lm_mask_bool = 0.0; 
	float use_dyn_l_on = 0.0; 
	float3 L = normalize(In.lightVec.xyz);	//normalized light vector 
	float3 NormalizedHalfAngle = normalize((L + V));		//Normalize 
	float NdotH_specular = saturate(dot(NormalizedHalfAngle,NM_power_blend)); 		//clamped dot product 
	float NdotH_pow_Glossiness = pow(NdotH_specular,glossiness);		//x to the power of y 
	float NdotL_diffuse = saturate(dot(L,NM_power_blend)); 		//clamped dot product 
	float UIConst_2380 = 0.0; 
	float One_ = 1.0; 
	float3 L_4377 = In.lightVec.xyz;		//unnormalized light vector 
	float LengthOfLightVector = length(L_4377);		//Measure the length of the vector 
	float UIConst_8429 = 1.0; 
	float if_use_attenaution;
	if (Use_attenuation_bool != UIConst_2380) if_use_attenaution = ((One_ / ((((LengthOfLightVector * LengthOfLightVector) * Attenuation3) + (LengthOfLightVector * Attenuation2)) + Attenuation1)) * AttenuationScale); else if_use_attenaution = UIConst_8429; 
	float3 UIColor_3328 = float3(0.0f, 0.0f, 0.0f );
	float3 If_use_dyn_l;
	if (use_dynamic_light != use_dyn_l_on) If_use_dyn_l = ((((SpecularColor.rgb * NdotH_pow_Glossiness) * 1.0) + (NdotL_diffuse * DiffuseColor.rgb)) * if_use_attenaution); else If_use_dyn_l = UIColor_3328.rgb; 
	float lightmap_off = 0.0; 
	float UIConst_8749 = 0.0; 
	float4 lightmap = tex2D(lightmapSampler, In.texCoord1.xy);
	float3 x2 = (lightmap.rgb*2.0
);
	float4 LightMap1 = tex2D(LightMap1Sampler, In.texCoord1.xy);
	float UIConst_2271 = 2.0; 
	float3 bumpBasis0 = float3(0.796875, 0.0, 0.570313); 
	float MathDotProduct_620 = saturate(dot(NM_power_blend,bumpBasis0)); 		//clamped dot product 
	float MathMinMax_5910 = saturate(MathDotProduct_620); 
	float3 bumpBasis1 = float3(-0.24, 0.710938, 0.570313); 
	float MathDotProduct_2523 = saturate(dot(NM_power_blend,bumpBasis1)); 		//clamped dot product 
	float MathMinMax_5376 = saturate(MathDotProduct_2523); 
	float3 bumpBasis2 = float3(-0.40625, -0.710938, 0.570313); 
	float MathDotProduct_8309 = saturate(dot(NM_power_blend,bumpBasis2)); 		//clamped dot product 
	float MathMinMax_9943 = saturate(MathDotProduct_8309); 
	float3 dp = float3(MathMinMax_5910, MathMinMax_5376, MathMinMax_9943);
	float3 dpSquared = dp * dp;
	float3 MathVecConstuct_9780 = dpSquared;
	float4 lightmap2 = tex2D(lightmap2Sampler, In.texCoord1.xy);
	float4 lightmap3 = tex2D(lightmap3Sampler, In.texCoord1.xy);
	float3 oneVector = float3(1.0, 1.0, 1.0); 
	float sum = saturate(dot(dpSquared,oneVector)); 		//clamped dot product 
	float3 MathIf_5772;
	if (use_directional_lm == UIConst_8749) MathIf_5772 = x2; else MathIf_5772 = (((((LightMap1.rgb * UIConst_2271) * MathVecConstuct_9780.r) + ((lightmap2.rgb * UIConst_2271) * MathVecConstuct_9780.g)) + (MathVecConstuct_9780.b * (lightmap3.rgb * UIConst_2271))) / sum); 
	float3 if_lightmap;
	if (use_lightmap != lightmap_off) if_lightmap = MathIf_5772; else if_lightmap = shadow_color.rgb; 
	float3 add_light_to_lm = If_use_dyn_l + if_lightmap;
	float luminance = (add_light_to_lm.r*0.2126 + add_light_to_lm.g*0.7152 + add_light_to_lm.b*0.0722
);
	float MathBrightnessContrast_129 = (luminance - 0.5) * lightmap_mask_contrast + 0.5 + lightmap_mask_brightness;
	float CustomCode_7830 = (clamp(MathBrightnessContrast_129,0.0,1.0)
);
	float one_minus = (1 - CustomCode_7830
);
	float if_in_lm_mask;
	if (inv_lm_mask != inv_lm_mask_bool) if_in_lm_mask = one_minus; else if_in_lm_mask = CustomCode_7830; 
	float3 use_fres_mask;
	if (use_lm_mask_fresnel_bool != fresnamsk) use_fres_mask = (Fresnel * if_in_lm_mask); else use_fres_mask = Fresnel; 
	float3 If_use_fresnel;
	if (use_fresnel_button != use_fresnel_bool) If_use_fresnel = (use_fres_mask + add_light_to_lm); else If_use_fresnel = add_light_to_lm; 
	float UIConst_5728 = 1.0; 
	float masktex_white = 1.0; 
	float4 mask1 = tex2D(mask1Sampler, If_use_parallax_map.xy);
	float4 mask2 = tex2D(mask2Sampler, uv_tex_2.xy);
	float4 MathLerp_3777 = lerp(mask1, mask2, MathClamp_3346); 
	float4 ifuseblend;
	if (use_texture_blend == blend_bool) ifuseblend = MathLerp_3777; else ifuseblend = mask1; 
	float4 MathVecConstuct_5512 = ifuseblend;
	float masktexref_blue;
	if (use_mask_tex_blue_for_blow_bool != UIConst_5728) masktexref_blue = masktex_white; else masktexref_blue = MathVecConstuct_5512.b; 
	float3 MathVecConstuct_3825 = float3(masktexref_blue, masktexref_blue, masktexref_blue);
	float usevcgreen_for_glow = 1.0; 
	float useglow_vc_green = 1.0; 
	float if_use_vc_b_for_glow;
	if (use_vcblue_for_glow != usevcgreen_for_glow) if_use_vc_b_for_glow = useglow_vc_green; else if_use_vc_b_for_glow = VertColor.b; 
	float use_diffuse_bool = 1.0; 
	float4 TextureMap_374 = tex2D(TextureMap_374Sampler, If_use_parallax_map.xy);
	float4 TextureMap_8119 = tex2D(TextureMap_8119Sampler, uv_tex_2.xy);
	float3 blend_diffuse = lerp(TextureMap_374.rgb, TextureMap_8119.rgb, MathClamp_3346); 
	float3 if_use_blend;
	if (use_texture_blend == blend_bool) if_use_blend = blend_diffuse; else if_use_blend = TextureMap_374.rgb; 
	float3 if_use_diffuse_map;
	if (use_diffuse_map_bool != use_diffuse_bool) if_use_diffuse_map = diffuse_color.rgb; else if_use_diffuse_map = if_use_blend; 
	float2 d_tex_uv_mul = (If_use_parallax_map*detail_texture_uv_tile
);
	float4 detail_tex = tex2D(detail_texSampler, d_tex_uv_mul.xy);
	float detailtex_normalize = ((detail_tex.r-0.5)*detail_texture_power
);
	float UIConst_7380 = 1.0; 
	float3 MathOperator_969 = ((If_use_fresnel + ((MathVecConstuct_3825 * glow_color.rgb) * if_use_vc_b_for_glow)) * (if_use_diffuse_map + detailtex_normalize)) * UIConst_7380;
	//this code was added by the World Space Transform Node 
	float3 Nn = normalize(In.worldNormal.xyz); 		//input the vectors required for tangent to world space transform 
	float3 Bn = normalize(cross(In.worldBinormal.xyz, In.worldNormal.xyz)); 
	float3 Tn = cross(Nn, Bn); 
	Bn *= In.worldBinormal.w; 
	#ifdef YUP 
		float3 WorldSpaceXform = ( Nn * NM_power_blend.z ) + (NM_power_blend.x * Tn ) + ( NM_power_blend.y * -Bn); 
	#else 
		float3 WorldSpaceXform = ( Nn * NM_power_blend.z ) + (NM_power_blend.x * Bn ) + ( NM_power_blend.y * -Tn); 
	#endif 
	float3 Reflection = reflect(In.viewDir, WorldSpaceXform);		//Compute the reflection vector 
	float masktex_green_gloss = 1.0; 
	float masktexref_green;
	if (mask_tex_green_gloss_bool != masktex_green_gloss) masktexref_green = masktex_white; else masktexref_green = MathVecConstuct_5512.g; 
	float gloss = ((1.0 -masktexref_green) * reflection_gloss_multiplier + global_reflection_blur
);
	float3 cubemapInputVector = Reflection.xyz;
	#ifdef YUP 
	#else 
	cubemapInputVector.xyz = cubemapInputVector.xzy;  //swizzle required for Max 
	#endif 
	float4 cubemap = texCUBElod(cubemapSampler, float4(cubemapInputVector, gloss));
	float lm_as_ref_msk_bool = 0.0; 
	float lm_as_ref_msk_true = 1.0; 
	float lightmap_reflect;
	if (lm_as_ref_msk == lm_as_ref_msk_bool) lightmap_reflect = lm_as_ref_msk_true; else lightmap_reflect = if_in_lm_mask; 
	float vc_col_green_ref = 1.0; 
	float vc_green_one = 0.0; 
	float if_use_vc_g_for_ref;
	if (vc_col_green_for_ref != vc_col_green_ref) if_use_vc_g_for_ref = vc_green_one; else if_use_vc_g_for_ref = VertColor.g; 
	float invert_vcg = (1 - if_use_vc_g_for_ref
);
	float usemasktex_Rfor_ref = 1.0; 
	float masktexref_red;
	if (usemasktex_Rfor_ref_bool != usemasktex_Rfor_ref) masktexref_red = masktex_white; else masktexref_red = MathVecConstuct_5512.r; 
	float UIConst_5349 = 0.0; 
	float UIConst_4343 = 1.0; 
	float MathPow_1681 = pow(NdotV_fresnel,reflection_fresnel_power);		//x to the power of y 
	float clamp_fresn = (clamp(1-((MathPow_1681 * ref_fres_scale) + ref_fres_bias),0.0,1.0)
);
	float IF_use_fres_for_blend_ref;
	if (use_fres_forr_add_ref == UIConst_5349) IF_use_fres_for_blend_ref = UIConst_4343; else IF_use_fres_for_blend_ref = clamp_fresn; 
	float3 reflection_blend = lerp(MathOperator_969, cubemap.rgb, ((lightmap_reflect * (Reflection_power * (invert_vcg * masktexref_red))) * IF_use_fres_for_blend_ref)); 
	float3 MathOperator_5296 = cubemap.rgb * ((Reflection_power * masktexref_red) * invert_vcg);
	float3 if_use_fres_add_ref;
	if (use_fres_forr_add_ref == UIConst_5349) if_use_fres_add_ref = MathOperator_5296; else if_use_fres_add_ref = (MathOperator_5296 * clamp_fresn); 
	float3 lightmap_ref;
	if (lm_as_ref_msk == lm_as_ref_msk_bool) lightmap_ref = if_use_fres_add_ref; else lightmap_ref = (if_in_lm_mask * if_use_fres_add_ref); 
	float3 If_use_reflection_blend;
	if (use_blended_reflections_butt != use_blended_reflections_bool) If_use_reflection_blend = reflection_blend; else If_use_reflection_blend = (lightmap_ref + MathOperator_969); 
	float3 If_use_ref;
	if (use_ref_butt != use_ref_bool) If_use_ref = If_use_reflection_blend; else If_use_ref = MathOperator_969; 
	float3 INEyeVec_6276 = In.eyeVec.xyz;		//unnormalized eye vector 
	float MathLength_8975 = length(INEyeVec_6276);		//Measure the length of the vector 
	float3 INVertPos_1048 = In.oposition.xyz;		//Incoming vertex position in object space 
	float MathClamp_7628 = clamp((fog_altitude_start + (INVertPos_1048.z / fog_altitude_scale)), fog_altitude_base, fog_altitude_end); 
	float MathMinMax_4145 = saturate((((MathLength_8975 - fog_near) / (fog_far - fog_near)) / MathClamp_7628)); 
	float3 fog_blend = lerp(If_use_ref, fog_color.rgb, (fogalpha * MathMinMax_4145)); 
	float3 If_use_fog;
	if (usefog == usefob_bool) If_use_fog = If_use_ref; else If_use_fog = fog_blend; 
	float3 input1 = If_use_fog; 
	float alpha_blend = lerp(TextureMap_374.a, TextureMap_8119.a, MathClamp_3346); 
	float if_use_blend2;
	if (use_texture_blend == blend_bool) if_use_blend2 = alpha_blend; else if_use_blend2 = TextureMap_374.a; 
	float valpha_mul = if_use_blend2 * VertColor.a;
	float input7 = valpha_mul; 

	float4 ret =  float4(0,0,0,1); 
	ret = float4(input1, 1); 
	ret.a = input7; 
	return ret; 
} 

technique Alpha_test  
{  
	pass ambient  
    {		 
		VertexShader = compile vs_3_0 avT2(light1Pos,  light1Type, light1Dir); 
		ZEnable = true; 
		ZWriteEnable = true; 
		CullMode = cw; 
		ShadeMode = Gouraud;
		AlphaBlendEnable = false; 
		AlphaTestEnable = TRUE; 
		AlphaRef = 64; 
		AlphaFunc = GREATER; 
	PixelShader = compile ps_3_0 afT2(light1Dir, light1Color, light1Attenuation, light1Hotspot, light1Falloff, light1Type, light1attenType, light1coneType, light1CastShadows, 1); 
	}  

}  



/*============================================================================
 ============= Alpha_blend TECHNIQUE ============= 
============================================================================*/



// this function does the different types of light attenuation 
float attenuation_funcT3(int lightattenType, float4 lightAttenuation, float3 lightVec) 
{ 
	float att = 1.0; 
	return att; 
} 
	 
// this function does the different types of cone angle 
float coneangle_funcT3(int lightconeType, float lightHotspot, float lightFalloff, float3 lightVec, float3 lightDir) 
{ 
	float cone = 1.0; 
	return cone; 
} 

/************** light info **************/ 

// create the light vector 
float3 lightVec_funcT3(float3 worldSpacePos, float3 lightVector, float3x3 objTangentXf, int lightType) 
{ 
	float3 lightVec = mul(objTangentXf, (mul((lightVector - worldSpacePos), worldI).xyz)); 
	return lightVec; 
} 



// input from application 
	struct a2vT3 { 
	float4 position		: POSITION; 

	float4 tangent		: TANGENT; 
	float4 binormal		: BINORMAL; 
	float4 normal		: NORMAL; 
	float2 texCoord		: TEXCOORD0; 
	float2 texCoord1	: TEXCOORD1; 
	float3 vertcol		: TEXCOORD3; 
	float vertalpha 	: TEXCOORD4; 
	float2 texCoord2	: TEXCOORD2; 

}; 

// output to fragment program 
struct v2fT3 { 
        float4 position    		: POSITION; 

        float3 eyeVec	    	: TEXCOORD0; 
	float2 texCoord			: TEXCOORD1; 
	float2 texCoord1		: TEXCOORD2; 
        float4 color    		: COLOR0; 
	float2 texCoord2		: TEXCOORD3; 
        float3 lightVec    		: TEXCOORD4; 
        float4 worldBinormal 	: TEXCOORD5; 
        float4 worldNormal   	: TEXCOORD6; 
        float3 viewDir	    	: TEXCOORD7; 
        float4 oposition	    	: TEXCOORD8; 

}; 

//Ambient and Self-Illum Pass Vertex Shader
v2fT3 avT3(a2vT3 In, uniform float3 lightPos, uniform int lightType, uniform float3 lightDir) 
{ 
    v2fT3 Out = (v2fT3)0; 
	Out.position = mul(In.position, wvp);				//transform vert position to homogeneous clip space 

	//this code was added by the Eye Vector Node 
	float3x3 objTangentXf;								//build object to tangent space transform matrix 
	#ifdef YUP 
	objTangentXf[0] = In.tangent.xyz; 
	objTangentXf[1] = -In.binormal.xyz; 
	#else 
	objTangentXf[0] = In.binormal.xyz; 
	objTangentXf[1] = -In.tangent.xyz; 
	#endif 
	objTangentXf[2] = In.normal.xyz; 
	//these three lines were added by the Eye Vector Node 
	float4 osIPos = mul(viewInv[3], worldI);			//put world space eye position in object space 
	float3 osIVec = osIPos.xyz - In.position.xyz;		//object space eye vector 
	Out.eyeVec = mul(objTangentXf, osIVec);				//tangent space eye vector passed out 
	In.texCoord += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord = In.texCoord;						//pass through texture coordinates from channel 1 
	In.texCoord1 += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord1 = In.texCoord1;						//pass through texture coordinates from channel 2 
	//this code was added by the Vertex Color Node 
	Out.color = float4(In.vertcol.rgb, In.vertalpha.r); 

	In.texCoord2 += float2(0.0,1.0);		//this fixes Max's V texcoord which is off by one 
	Out.texCoord2 = In.texCoord2;						//pass through texture coordinates from channel 3 
	float3 wsLPos = mul(In.position, world).xyz;			//put the vert position in world space 
	float3 wsLVec = lightPos - wsLPos;    //cast a ray to the light 
	float3 osLVec = mul(wsLVec, worldI).xyz;  //transform the world space light vector to object space 
	Out.lightVec = mul(objTangentXf, osLVec);			//tangent space light vector passed out 
	//this code was added by the World Space Transform Node 
	Out.worldNormal = float4( mul(In.normal, worldIT).xyz, In.normal.w );		//compute world space normal 
	Out.worldBinormal = float4(mul(In.binormal, worldIT).xyz, 1);	//compute world space binormal 
	if (dot(cross(In.binormal, In.normal), In.tangent) < 0.0) Out.worldBinormal.w = -1; //detect mirrored UV space 
	Out.viewDir = mul(In.position, world) - viewInv[3]; 
	//this code was added by the Vertex Position Node 
	#ifdef YUP 
	Out.oposition = In.position.xzyw;		//Output vertex position in object space 
	Out.oposition.y = -Out.oposition.y; 
	#else 
	Out.oposition = In.position;		//Output vertex position in object space 
	#endif 

	return Out; 
} 

//Ambient and Self-Illum Pass Pixel Shader
float4 afT3(v2fT3 In, uniform float3 lightDir, uniform float4 lightColor, uniform float4 lightAttenuation, uniform float lightHotspot, uniform float lightFalloff, uniform int lightType, uniform int lightattenType, uniform int lightconeType, uniform bool lightCastShadows, uniform int shadowPassCount) : COLOR 
{ 

	float usefob_bool = 0.0; 
	float use_ref_bool = 0.0; 
	float use_blended_reflections_bool = 0.0; 
	float use_fresnel_bool = 0.0; 
	float fresnamsk = 0.0; 
	float3 V = normalize(In.eyeVec.xyz);		//normalized eye vector 
	float4 Normal = float4(0,0,1,0);	//tangent space normal vector 
	float usenrmbool = 1.0; 
	float blend_bool = 1.0; 
	float parallax_use_bool = 0.0; 
	float2 OriginalTexCoords = In.texCoord.xy; 
	float UIConst_5325 = 0.0; 
	float2 uv1 = In.texCoord.xy; 
	float2 uv2 = In.texCoord1.xy; 
	float2 if_use_parallax_uv2;
	if (use_global_paralax == UIConst_5325) if_use_parallax_uv2 = uv1; else if_use_parallax_uv2 = uv2; 
	float4 parallax_map = tex2D(parallax_mapSampler, if_use_parallax_uv2.xy);
	float Two = 2.0; 
	float One = 1.0; 
	float3 INEyeVec_851 = In.eyeVec.xyz;		//unnormalized eye vector 
	INEyeVec_851 = normalize(INEyeVec_851); 
	INEyeVec_851.y = -INEyeVec_851.y; //invert eye vector Y
	float use_vc_a_for_parallax = 1.0; 
	float UIConst_3496 = 0.0; 
	float4 VertColor = In.color; 		//bringing in the vertex color 
	float if_use_vc_a_for_parallax;
	if (use_vc_a_for_parallax_button != use_vc_a_for_parallax) if_use_vc_a_for_parallax = UIConst_3496; else if_use_vc_a_for_parallax = VertColor.a; 
	float2 If_use_parallax_map;
	if (Use_parallax == parallax_use_bool) If_use_parallax_map = OriginalTexCoords; else If_use_parallax_map = (((((parallax_map.r * Two) - One) * INEyeVec_851) * (paralla_bias * if_use_vc_a_for_parallax)) + OriginalTexCoords); 
	float4 nrm1 = tex2D(nrm1Sampler, If_use_parallax_map.xy);
	nrm1.xyz = nrm1.xyz * 2 - 1;		//expand to -1 to 1 range 
	nrm1.rgb = normalize(nrm1.rgb); 		//normalized the normal vector 
	float use_uv3_for_second_tex_bool = 0.0; 
	float2 uv3 = In.texCoord2.xy; 
	float2 uv_tex_2;
	if (use_uvr_for_second_tex == use_uv3_for_second_tex_bool) uv_tex_2 = If_use_parallax_map; else uv_tex_2 = uv3; 
	float4 nrm2 = tex2D(nrm2Sampler, uv_tex_2.xy);
	nrm2.xyz = nrm2.xyz * 2 - 1;		//expand to -1 to 1 range 
	nrm2.rgb = normalize(nrm2.rgb); 		//normalized the normal vector 
	float use_mask_blend = 0.0; 
	float UIConst_7743 = 0.0; 
	float2 if_use_uv3_for_blend_mask;
	if (Use_uv3_for_blend_tex == UIConst_7743) if_use_uv3_for_blend_mask = If_use_parallax_map; else if_use_uv3_for_blend_mask = uv3; 
	float4 TextureMap_7444 = tex2D(TextureMap_7444Sampler, if_use_uv3_for_blend_mask.xy);
	float if_use_mask_blend;
	if (use_mask_blend_bool != use_mask_blend) if_use_mask_blend = ((VertColor.r * TextureMap_7444.r) * UIConst_6655); else if_use_mask_blend = VertColor.r; 
	float UIConst_6436 = 0.0; 
	float UIConst_824 = 1.0; 
	float MathClamp_3346 = clamp(if_use_mask_blend, UIConst_6436, UIConst_824); 
	float3 normal_blend = lerp(nrm1.rgb, nrm2.rgb, MathClamp_3346); 
	float3 if_tex_blend;
	if (use_texture_blend == blend_bool) if_tex_blend = normal_blend; else if_tex_blend = nrm1.rgb; 
	float3 if_use_normal_map;
	if (use_normal_map_bool != usenrmbool) if_use_normal_map = Normal; else if_use_normal_map = if_tex_blend; 
	float3 NM_power_blend = lerp(Normal, if_use_normal_map, NM_power); 
	float NdotV_fresnel = saturate(dot(V,(Normal * NM_power_blend))); 		//clamped dot product 
	float Pow_NdotV = pow(NdotV_fresnel,FresnelPower);		//x to the power of y 
	float clamp_fresnel = (clamp(1-((Pow_NdotV * FresnelScale) + FresnelBias),0.0,1.0)
);
	float3 Fresnel = fresnel_color.rgb * clamp_fresnel;
	float inv_lm_mask_bool = 0.0; 
	float use_dyn_l_on = 0.0; 
	float3 L = normalize(In.lightVec.xyz);	//normalized light vector 
	float3 NormalizedHalfAngle = normalize((L + V));		//Normalize 
	float NdotH_specular = saturate(dot(NormalizedHalfAngle,NM_power_blend)); 		//clamped dot product 
	float NdotH_pow_Glossiness = pow(NdotH_specular,glossiness);		//x to the power of y 
	float NdotL_diffuse = saturate(dot(L,NM_power_blend)); 		//clamped dot product 
	float UIConst_2380 = 0.0; 
	float One_ = 1.0; 
	float3 L_4377 = In.lightVec.xyz;		//unnormalized light vector 
	float LengthOfLightVector = length(L_4377);		//Measure the length of the vector 
	float UIConst_8429 = 1.0; 
	float if_use_attenaution;
	if (Use_attenuation_bool != UIConst_2380) if_use_attenaution = ((One_ / ((((LengthOfLightVector * LengthOfLightVector) * Attenuation3) + (LengthOfLightVector * Attenuation2)) + Attenuation1)) * AttenuationScale); else if_use_attenaution = UIConst_8429; 
	float3 UIColor_3328 = float3(0.0f, 0.0f, 0.0f );
	float3 If_use_dyn_l;
	if (use_dynamic_light != use_dyn_l_on) If_use_dyn_l = ((((SpecularColor.rgb * NdotH_pow_Glossiness) * 1.0) + (NdotL_diffuse * DiffuseColor.rgb)) * if_use_attenaution); else If_use_dyn_l = UIColor_3328.rgb; 
	float lightmap_off = 0.0; 
	float UIConst_8749 = 0.0; 
	float4 lightmap = tex2D(lightmapSampler, In.texCoord1.xy);
	float3 x2 = (lightmap.rgb*2.0
);
	float4 LightMap1 = tex2D(LightMap1Sampler, In.texCoord1.xy);
	float UIConst_2271 = 2.0; 
	float3 bumpBasis0 = float3(0.796875, 0.0, 0.570313); 
	float MathDotProduct_620 = saturate(dot(NM_power_blend,bumpBasis0)); 		//clamped dot product 
	float MathMinMax_5910 = saturate(MathDotProduct_620); 
	float3 bumpBasis1 = float3(-0.24, 0.710938, 0.570313); 
	float MathDotProduct_2523 = saturate(dot(NM_power_blend,bumpBasis1)); 		//clamped dot product 
	float MathMinMax_5376 = saturate(MathDotProduct_2523); 
	float3 bumpBasis2 = float3(-0.40625, -0.710938, 0.570313); 
	float MathDotProduct_8309 = saturate(dot(NM_power_blend,bumpBasis2)); 		//clamped dot product 
	float MathMinMax_9943 = saturate(MathDotProduct_8309); 
	float3 dp = float3(MathMinMax_5910, MathMinMax_5376, MathMinMax_9943);
	float3 dpSquared = dp * dp;
	float3 MathVecConstuct_9780 = dpSquared;
	float4 lightmap2 = tex2D(lightmap2Sampler, In.texCoord1.xy);
	float4 lightmap3 = tex2D(lightmap3Sampler, In.texCoord1.xy);
	float3 oneVector = float3(1.0, 1.0, 1.0); 
	float sum = saturate(dot(dpSquared,oneVector)); 		//clamped dot product 
	float3 MathIf_5772;
	if (use_directional_lm == UIConst_8749) MathIf_5772 = x2; else MathIf_5772 = (((((LightMap1.rgb * UIConst_2271) * MathVecConstuct_9780.r) + ((lightmap2.rgb * UIConst_2271) * MathVecConstuct_9780.g)) + (MathVecConstuct_9780.b * (lightmap3.rgb * UIConst_2271))) / sum); 
	float3 if_lightmap;
	if (use_lightmap != lightmap_off) if_lightmap = MathIf_5772; else if_lightmap = shadow_color.rgb; 
	float3 add_light_to_lm = If_use_dyn_l + if_lightmap;
	float luminance = (add_light_to_lm.r*0.2126 + add_light_to_lm.g*0.7152 + add_light_to_lm.b*0.0722
);
	float MathBrightnessContrast_129 = (luminance - 0.5) * lightmap_mask_contrast + 0.5 + lightmap_mask_brightness;
	float CustomCode_7830 = (clamp(MathBrightnessContrast_129,0.0,1.0)
);
	float one_minus = (1 - CustomCode_7830
);
	float if_in_lm_mask;
	if (inv_lm_mask != inv_lm_mask_bool) if_in_lm_mask = one_minus; else if_in_lm_mask = CustomCode_7830; 
	float3 use_fres_mask;
	if (use_lm_mask_fresnel_bool != fresnamsk) use_fres_mask = (Fresnel * if_in_lm_mask); else use_fres_mask = Fresnel; 
	float3 If_use_fresnel;
	if (use_fresnel_button != use_fresnel_bool) If_use_fresnel = (use_fres_mask + add_light_to_lm); else If_use_fresnel = add_light_to_lm; 
	float UIConst_5728 = 1.0; 
	float masktex_white = 1.0; 
	float4 mask1 = tex2D(mask1Sampler, If_use_parallax_map.xy);
	float4 mask2 = tex2D(mask2Sampler, uv_tex_2.xy);
	float4 MathLerp_3777 = lerp(mask1, mask2, MathClamp_3346); 
	float4 ifuseblend;
	if (use_texture_blend == blend_bool) ifuseblend = MathLerp_3777; else ifuseblend = mask1; 
	float4 MathVecConstuct_5512 = ifuseblend;
	float masktexref_blue;
	if (use_mask_tex_blue_for_blow_bool != UIConst_5728) masktexref_blue = masktex_white; else masktexref_blue = MathVecConstuct_5512.b; 
	float3 MathVecConstuct_3825 = float3(masktexref_blue, masktexref_blue, masktexref_blue);
	float usevcgreen_for_glow = 1.0; 
	float useglow_vc_green = 1.0; 
	float if_use_vc_b_for_glow;
	if (use_vcblue_for_glow != usevcgreen_for_glow) if_use_vc_b_for_glow = useglow_vc_green; else if_use_vc_b_for_glow = VertColor.b; 
	float use_diffuse_bool = 1.0; 
	float4 TextureMap_374 = tex2D(TextureMap_374Sampler, If_use_parallax_map.xy);
	float4 TextureMap_8119 = tex2D(TextureMap_8119Sampler, uv_tex_2.xy);
	float3 blend_diffuse = lerp(TextureMap_374.rgb, TextureMap_8119.rgb, MathClamp_3346); 
	float3 if_use_blend;
	if (use_texture_blend == blend_bool) if_use_blend = blend_diffuse; else if_use_blend = TextureMap_374.rgb; 
	float3 if_use_diffuse_map;
	if (use_diffuse_map_bool != use_diffuse_bool) if_use_diffuse_map = diffuse_color.rgb; else if_use_diffuse_map = if_use_blend; 
	float2 d_tex_uv_mul = (If_use_parallax_map*detail_texture_uv_tile
);
	float4 detail_tex = tex2D(detail_texSampler, d_tex_uv_mul.xy);
	float detailtex_normalize = ((detail_tex.r-0.5)*detail_texture_power
);
	float UIConst_7380 = 1.0; 
	float3 MathOperator_969 = ((If_use_fresnel + ((MathVecConstuct_3825 * glow_color.rgb) * if_use_vc_b_for_glow)) * (if_use_diffuse_map + detailtex_normalize)) * UIConst_7380;
	//this code was added by the World Space Transform Node 
	float3 Nn = normalize(In.worldNormal.xyz); 		//input the vectors required for tangent to world space transform 
	float3 Bn = normalize(cross(In.worldBinormal.xyz, In.worldNormal.xyz)); 
	float3 Tn = cross(Nn, Bn); 
	Bn *= In.worldBinormal.w; 
	#ifdef YUP 
		float3 WorldSpaceXform = ( Nn * NM_power_blend.z ) + (NM_power_blend.x * Tn ) + ( NM_power_blend.y * -Bn); 
	#else 
		float3 WorldSpaceXform = ( Nn * NM_power_blend.z ) + (NM_power_blend.x * Bn ) + ( NM_power_blend.y * -Tn); 
	#endif 
	float3 Reflection = reflect(In.viewDir, WorldSpaceXform);		//Compute the reflection vector 
	float masktex_green_gloss = 1.0; 
	float masktexref_green;
	if (mask_tex_green_gloss_bool != masktex_green_gloss) masktexref_green = masktex_white; else masktexref_green = MathVecConstuct_5512.g; 
	float gloss = ((1.0 -masktexref_green) * reflection_gloss_multiplier + global_reflection_blur
);
	float3 cubemapInputVector = Reflection.xyz;
	#ifdef YUP 
	#else 
	cubemapInputVector.xyz = cubemapInputVector.xzy;  //swizzle required for Max 
	#endif 
	float4 cubemap = texCUBElod(cubemapSampler, float4(cubemapInputVector, gloss));
	float lm_as_ref_msk_bool = 0.0; 
	float lm_as_ref_msk_true = 1.0; 
	float lightmap_reflect;
	if (lm_as_ref_msk == lm_as_ref_msk_bool) lightmap_reflect = lm_as_ref_msk_true; else lightmap_reflect = if_in_lm_mask; 
	float vc_col_green_ref = 1.0; 
	float vc_green_one = 0.0; 
	float if_use_vc_g_for_ref;
	if (vc_col_green_for_ref != vc_col_green_ref) if_use_vc_g_for_ref = vc_green_one; else if_use_vc_g_for_ref = VertColor.g; 
	float invert_vcg = (1 - if_use_vc_g_for_ref
);
	float usemasktex_Rfor_ref = 1.0; 
	float masktexref_red;
	if (usemasktex_Rfor_ref_bool != usemasktex_Rfor_ref) masktexref_red = masktex_white; else masktexref_red = MathVecConstuct_5512.r; 
	float UIConst_5349 = 0.0; 
	float UIConst_4343 = 1.0; 
	float MathPow_1681 = pow(NdotV_fresnel,reflection_fresnel_power);		//x to the power of y 
	float clamp_fresn = (clamp(1-((MathPow_1681 * ref_fres_scale) + ref_fres_bias),0.0,1.0)
);
	float IF_use_fres_for_blend_ref;
	if (use_fres_forr_add_ref == UIConst_5349) IF_use_fres_for_blend_ref = UIConst_4343; else IF_use_fres_for_blend_ref = clamp_fresn; 
	float3 reflection_blend = lerp(MathOperator_969, cubemap.rgb, ((lightmap_reflect * (Reflection_power * (invert_vcg * masktexref_red))) * IF_use_fres_for_blend_ref)); 
	float3 MathOperator_5296 = cubemap.rgb * ((Reflection_power * masktexref_red) * invert_vcg);
	float3 if_use_fres_add_ref;
	if (use_fres_forr_add_ref == UIConst_5349) if_use_fres_add_ref = MathOperator_5296; else if_use_fres_add_ref = (MathOperator_5296 * clamp_fresn); 
	float3 lightmap_ref;
	if (lm_as_ref_msk == lm_as_ref_msk_bool) lightmap_ref = if_use_fres_add_ref; else lightmap_ref = (if_in_lm_mask * if_use_fres_add_ref); 
	float3 If_use_reflection_blend;
	if (use_blended_reflections_butt != use_blended_reflections_bool) If_use_reflection_blend = reflection_blend; else If_use_reflection_blend = (lightmap_ref + MathOperator_969); 
	float3 If_use_ref;
	if (use_ref_butt != use_ref_bool) If_use_ref = If_use_reflection_blend; else If_use_ref = MathOperator_969; 
	float3 INEyeVec_6276 = In.eyeVec.xyz;		//unnormalized eye vector 
	float MathLength_8975 = length(INEyeVec_6276);		//Measure the length of the vector 
	float3 INVertPos_1048 = In.oposition.xyz;		//Incoming vertex position in object space 
	float MathClamp_7628 = clamp((fog_altitude_start + (INVertPos_1048.z / fog_altitude_scale)), fog_altitude_base, fog_altitude_end); 
	float MathMinMax_4145 = saturate((((MathLength_8975 - fog_near) / (fog_far - fog_near)) / MathClamp_7628)); 
	float3 fog_blend = lerp(If_use_ref, fog_color.rgb, (fogalpha * MathMinMax_4145)); 
	float3 If_use_fog;
	if (usefog == usefob_bool) If_use_fog = If_use_ref; else If_use_fog = fog_blend; 
	float3 input1 = If_use_fog; 
	float alpha_blend = lerp(TextureMap_374.a, TextureMap_8119.a, MathClamp_3346); 
	float if_use_blend2;
	if (use_texture_blend == blend_bool) if_use_blend2 = alpha_blend; else if_use_blend2 = TextureMap_374.a; 
	float valpha_mul = if_use_blend2 * VertColor.a;
	float input7 = valpha_mul; 

	float4 ret =  float4(0,0,0,1); 
	ret = float4(input1, 1); 
	ret.a = input7; 
	return ret; 
} 

technique Alpha_blend  
{  
	pass ambient  
    {		 
		VertexShader = compile vs_3_0 avT3(light1Pos,  light1Type, light1Dir); 
		ZEnable = true; 
		ZWriteEnable = false; 
		CullMode = cw; 
		ShadeMode = Gouraud;
		AlphaBlendEnable = true; 
		SrcBlend = SrcAlpha; 
		DestBlend = InvSrcAlpha; 
		AlphaTestEnable = FALSE; 
	PixelShader = compile ps_3_0 afT3(light1Dir, light1Color, light1Attenuation, light1Hotspot, light1Falloff, light1Type, light1attenType, light1coneType, light1CastShadows, 1); 
	}  

}    





//ENVO realtime environment shader for 3d studio max by Aurel Manea //  
//Generated using ShaderFX  http://www.lumonix.net/shaderfx.html    //  

//                  WWW.AURELM.COM/ENVO                             //  