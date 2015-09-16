/******************************************************************************
Global Illumination HLSL
by Ben Cloward
ben@bencloward.com
http://www.bencloward.com

This shader is based on several shaders written by Kevin Bjorke of Nvidia and 
included with the Cg plugin for 3DS Max.


It accepts the following inputs:

Ambient Color
Diffuse Texture
Normal Map Texture
DXT5 Compressed Normal Map
Ambient Occlusion (shadow map) Texture
Global Illumination (Diffusely Convolved Cube Map) Texture

It requires hardware support for DirectX 9.

I got the idea for this shader at a Siggraph session that was hosted by Dan Lemmon
of Weta Digital and Paul Debevec.  This shader is a simplified, real-time version
of the shaders that Dan described that he was using for the characters in the
Lord of the Rings movies.

For the lighting in this shader I use a diffusely convolved, high dynamic range
image (HDRI) and convert it to a cube map. This cube map simulates light coming
from every direction into each point on the model. Then I use the normal from the
normal map to look up in the cube map the light that comes from that dirrection.

To increas the realism, I also create an ambient occlusion map (sort of like a
shadow map) for the model. In 3DS Max, I apply a second set of texture coordinates
in map channel three. Then I add a skylight to the scene and use "Render to
Texture" to render out a "lighting-only" texture with Light Tracer. The resulting
image is an ambient occlusion map and shows the area where the model casts shadows
on itself.

The combination of the ambient occlusion map and the global illumination cube map
create very realistic looking lighting. Add in the normal map and the diffuse map
and you've got a pretty good real-time version of global illumination.

There are some drawbacks for this shader. The one that Dan Lemmon was using would
render out a new ambient occlusion map for every new frame. We can't really do that
in real-time, so the ambient occlusion map only works for rigid objects that don't
deform. You can still use the shader for characters, but the ambient occlusion map
won't be quite as realistic

Also, the global illumination map is only valid for the one spot in the environment
where it was created. If you apply the shader to a moving character, you need to
create a new cube map for each area of your world and come up with a method for
telling the shader which cube map to use based on proximity.

Finally, this shader has no support for dynamic (moving) light sources. That means
that it won't respond to torches moving by, bright explosions, etc.

I've only included a short description here of how to use this shader. If you're
interested in using it and want more details on how to create the
diffusely-convolved cube map and the ambient occlusion map, please send me an email
and I'll describe it in more detail.

Normal Map compression is an option that you can use with this shader.
Copy the red channel of your normal map to the alpha channel.  Then delete the
red and blue channels and save your normal map in DXT5 DDS format.  Put your
compressed normal map in the DXT5 Normal Map slot for the shader.  Then choose
"Compressed" as the technique instead of "complete."

This shader is intended to be used by the DirectX 9 shader of 3DS Max
but it could also be used in other applications that support the FX format.
	
******************************************************************************/

/************* TWEAKABLES **************/

half4 ambient : Ambient
<
    string UIName = "Ambient Color";
> = {0.5f, 0.5f, 0.5f, 1.0f};

texture cubeMap : EnvMap
<
    string name = "default_reflection.dds";
	string UIName = "Ambient Texture";
    string type = "Cube";
>;

texture shadowTexture : LightMap < 
	string UIName = "Lightmap Texture";
	int Texcoord = 1;
	int MapChannel = 3;	
>;

texture colorTexture : DiffuseMap
<
    string name = "default_color.dds";
	string UIName = "Diffuse Texture";
    string TextureType = "2D";
    int Texcoord = 0;
	int MapChannel = 1;	
>;

texture normalMap : NormalMap
<
    string name = "default_bump_normal.dds";
	string UIName = "Normal Map";
    string TextureType = "2D";
    int Texcoord = 0;
	int MapChannel = 1;	
>;

texture CnormalMap : CNormalMap
<
    string name = "default_bump_normal.dds";
	string UIName = "DXT5 Normal Map";
    string TextureType = "2D";
    int Texcoord = 0;
	int MapChannel = 1;
>;

bool direction
<
    string gui = "slider";
    string UIName = "Flip Normal Map Green Channel";
> = false;

/************** lighting textures **************/

/****************************************************/
/********** SAMPLERS ********************************/
/****************************************************/

sampler2D colorTextureSampler = sampler_state
{
	Texture = <colorTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Anisotropic;
	AddressU = Wrap;
	AddressV = Wrap;
};

samplerCUBE cubeMapSampler = sampler_state
{
    Texture = <cubeMap>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
    AddressU = Wrap;
	AddressV = Wrap;
};

sampler2D normalMapSampler = sampler_state
{
	Texture = <normalMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Anisotropic;
	AddressU = Wrap;
	AddressV = Wrap;
};

sampler2D shadowTextureSampler = sampler_state
{
	Texture = <shadowTexture>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = Wrap;
	AddressV = Wrap;
};

sampler2D CnormalMapSampler = sampler_state
{
	Texture = <CnormalMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Anisotropic;
	AddressU = Wrap;
	AddressV = Wrap;
};

/***********************************************/
/*** automatically-tracked "tweakables" ********/
/***********************************************/

half4x4 wvp : WorldViewProjection < string UIWidget = "None"; >;
half4x4 worldIT : WorldInverseTranspose < string UIWidget = "None"; >;

/****************************************************/
/********** CG SHADER FUNCTIONS *********************/
/****************************************************/

// input from application
	struct a2v {
	half4 position		: POSITION;
	half2 texCoord		: TEXCOORD0;
	half3 tangent		: TANGENT;
	half3 binormal		: BINORMAL;
	half3 normal		: NORMAL;
	half2 texCoord1	: TEXCOORD1;
};

// output to fragment program
struct v2f {
        half4 position    	: POSITION;
		half4 texCoord    	: TEXCOORD0;
		half3 worldNormal	: TEXCOORD3;
		half3 worldTangent	: TEXCOORD4;
		half3 worldBinormal	: TEXCOORD5;
};

/**************************************/
/***** VERTEX SHADER ******************/
/**************************************/

v2f v(a2v In,
		uniform half4x4 worldViewProj, // object to clip space
        uniform half4x4 world        // object to world space
        )
{
	v2f Out;
    Out.worldNormal = mul(In.normal, worldIT).xyz;
    Out.worldTangent = mul(In.tangent, worldIT).xyz;
    Out.worldBinormal = mul(In.binormal, worldIT).xyz;
    //can use either positive or negative y format normal maps
    //comment out this if statement to save 6 instructions!
  	if (direction == true) Out.worldTangent = -Out.worldTangent;
	Out.position = mul(In.position, worldViewProj);
	Out.texCoord.xy = In.texCoord;
	Out.texCoord.zw = In.texCoord1;
	return Out;
}

/**************************************/
/***** FRAGMENT PROGRAM ***************/
/**************************************/

float4 f(v2f In,
			uniform sampler2D colorTex,
            uniform sampler2D bumpTex,
            uniform samplerCUBE diffuseEnvMap,
            uniform half4 ambient,
			uniform sampler2D shadowTex
            ) : COLOR
{
  //fetch the diffuse shadow and normal map
  half4 colorMap = tex2D(colorTex, In.texCoord.xy);
  half4 shadowMap = tex2D(shadowTex, In.texCoord.zw);
  half3 normal = tex2D(bumpTex, In.texCoord).xyz * 2.0 - 1.0;

  //create tangent space vectors
  half3 Nn = In.worldNormal;
  half3 Tn = In.worldTangent;
  half3 Bn = In.worldBinormal;
  
  //these vectors could be normalized, but it costs 4 more instructions
  //and makes almost no difference to image quality
  //half3 Nn = normalize(In.worldNormal);
  //half3 Tn = normalize(In.worldTangent);
  //half3 Bn = normalize(In.worldBinormal);

  half3 worldNorm = Nn + (normal.x * Tn + normal.y * Bn);
  worldNorm.xyz = worldNorm.xzy;  //swizzle required for Max 
  
  //fetch the ambient lighting with the world normal
  half4 env = texCUBE(diffuseEnvMap, worldNorm);
  
  //lighting
  
  //ambient light
  half4 C = ambient*env*colorMap*shadowMap;
  
  return C;
}

float4 f2(v2f In,
			uniform sampler2D colorTex,
            uniform sampler2D bumpTex,
            uniform samplerCUBE diffuseEnvMap,
            uniform half4 ambient,
			uniform sampler2D shadowTex
            ) : COLOR
{
  //fetch the diffuse map
  half4 colorMap = tex2D(colorTex, In.texCoord.xy);

  //fetch the shadow map
  half4 shadowMap = tex2D(shadowTex, In.texCoord.zw);
  
  // fetch the bump normal from the normal map
  //swizzle the compressed dxt5 format
  half3 normal = tex2D(bumpTex, In.texCoord).wyz * 2.0 - 1.0;
  //generate the z component of the vector
  normal.z = sqrt(1 - normal.x * normal.x - normal.y * normal.y);

  //create tangent space vectors
  half3 Nn = In.worldNormal;
  half3 Tn = In.worldTangent;
  half3 Bn = In.worldBinormal;
  
  //these vectors could be normalized, but it costs 4 more instructions
  //and makes almost no difference to image quality
  //half3 Nn = normalize(In.worldNormal);
  //half3 Tn = normalize(In.worldTangent);
  //half3 Bn = normalize(In.worldBinormal);

	half3 worldNorm = Nn + (normal.x * Tn + normal.y * Bn);
  //corrects the reflection
  worldNorm.y = -worldNorm.y;
  
  //fetch the ambient lighting with the world normal
  half4 env = texCUBE(diffuseEnvMap, -worldNorm);
  
  //lighting
  
  //ambient light
  half4 C = ambient*env*colorMap*shadowMap;
  
  return C;
}

/****************************************************/
/********** TECHNIQUES ******************************/
/****************************************************/

technique Complete
{ 
    pass envPass 
    {		
	VertexShader = compile vs_1_1 v(wvp,worldIT);
	ZEnable = true;
	ZWriteEnable = true;
	CullMode = CW;
	AlphaBlendEnable = false;
	PixelShader = compile ps_2_0 f(colorTextureSampler,normalMapSampler,cubeMapSampler,ambient,shadowTextureSampler);
    }
}

technique Compressed
{ 
    pass envPass 
    {		
	VertexShader = compile vs_1_1 v(wvp,worldIT);
	ZEnable = true;
	ZWriteEnable = true;
	CullMode = CW;
	AlphaBlendEnable = false;
	PixelShader = compile ps_2_0 f2(colorTextureSampler,CnormalMapSampler,cubeMapSampler,ambient,shadowTextureSampler);
    }
}
