/******************************************************************************
HLSL Normal Map Car Paint Shader
by Ben Cloward
ben@bencloward.com
http://www.bencloward.com

This shader is based on several shaders written by Kevin Bjorke of Nvidia and 
included with the Cg plugin for 3DS Max.

It accepts the following inputs:

Ambient Color
Diffuse Color
Diffuse Texture
Specular Mask (alpha channel of diffuse texture)
Normal Map Texture
DXT5 Compressed Normal Map
Specular Color
Shininess
Point Light Position
Point Light Color

It requires hardware support for DirectX 9.

This shader has all of the features of the Normal Map Specular shader. It also
includes some features to imitate the look of tricked-out car paint. Some car
paint appears to change color based on your viewing angle. The paint looks like
one color when you're looking straight at the surface and another color when
the surface is parallel to your view. This shader imitates that effect.

To achieve the effect, the first thing we need is a color gradient. The shader
includes two colors. Surfaces on the model that are facing you will receive
the "Middle Color" while surfaces at glancing angles will receive the "Edge
Color." 

The amount of each color in the gadient is determined by the "Fresnel Power"
and "Fresnel Bias" values. These will allow you to tweek how much of each color
gets applied to the effect.

Finally, the two colors are subtracted from the per-pixel lighting result.
Because the colors are subtracted, you'll end up with the opposite colors from
the ones you selected and they'll darken the final result.

The fresnel term in this shader is a very useful shader component. Most objects
that are reflective are more reflective at glancing angles than straight on and
the fresnel term can be used to achieve that effect. It can also be used to
blend between reflection and refraction in water.

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
> = {0.25f, 0.25f, 0.25f, 1.0f};

half4 surfColor : Diffuse
<
    string UIName = "Diffuse Color";
> = {1.0f, 1.0f, 1.0f, 1.0f};

texture colorTexture : DiffuseMap
<
    string name = "default_color.dds";
	string UIName = "Diffuse Texture";
    string TextureType = "2D";
>;

half4 specularColor : Specular
<
    string UIName = "Specular Color";
> = { 0.2f, 0.2f, 0.2f, 1.0f };

half shininess <
	string UIWidget = "slider";
    float UIMin = 1;
    float UIMax = 128;
    string UIName = "Shininess";
> = 40;

texture normalMap : NormalMap
<
    string name = "default_bump_normal.dds";
	string UIName = "Normal Map";
    string TextureType = "2D";
>;

texture CnormalMap : CNormalMap
<
    string name = "default_bump_normal.dds";
	string UIName = "DXT5 Normal Map";
    string TextureType = "2D";
>;

bool direction
<
    string gui = "slider";
    string UIName = "Flip Normal Map Green Channel";
> = false;

half4 paintedge
<
    string UIName = "Edge Color";
> = { 0.0f, 1.0f, 0.0f, 1.0f };

half4 paintmiddle
<
    string UIName = "Middle Color";
> = { 1.0f, 0.0f, 0.0f, 1.0f };

half fresnelbias <
	string UIWidget = "slider";
    float UIMin = 0.0f;
    float UIMax = 2.0f;
    string UIName = "Fresnel Bias";
> = 0.07f;

half fresnelpower <
	string UIWidget = "slider";
    float UIMin = 0.0f;
    float UIMax = 10.0f;
    string UIName = "Fresnel Power";
> = 1.7f;

/************** light info **************/

half4 light1Pos : POSITION
<
	string UIName = "Light Position";
	string Object = "PointLight";
	string Space = "World";
	int refID = 0;
> = {100.0f, 100.0f, 100.0f, 0.0f};

half4 light1Color : LIGHTCOLOR
<
	int LightRef = 0;
> = { 1.0f, 1.0f, 1.0f, 0.0f };

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

sampler2D normalMapSampler = sampler_state
{
	Texture = <normalMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Anisotropic;
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
half4x4 viewInv : ViewInverse < string UIWidget = "None"; >;
half4x4 world : World < string UIWidget = "None"; >;

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
};

// output to fragment program
struct v2f {
        half4 position    	: POSITION;
		half2 texCoord    	: TEXCOORD0;
		half3 eyeVec		: TEXCOORD1;
		half3 lightVec   	: TEXCOORD2;
		half3 worldNormal	: TEXCOORD3;
		half3 worldTangent	: TEXCOORD4;
		half3 worldBinormal	: TEXCOORD5;
};;

// blinn lighting with lit function
half4 blinn2(half3 N,
		half3 L,
		half3 V,
		uniform half4 diffuseColor,
		uniform half4 specularColor,
		uniform half shininess
		)
	{
	half3 H = normalize(V+L);
	half4 lighting = lit(dot(L,N), dot(H,N), shininess);
	return diffuseColor*lighting.y + specularColor*lighting.z;
	}

/**************************************/
/***** VERTEX SHADER ******************/
/**************************************/

v2f v(a2v In, uniform half4 lightPosition)
{
	v2f Out;
    Out.worldNormal = mul(In.normal, worldIT).xyz;
    Out.worldTangent = mul(In.tangent, worldIT).xyz;
    Out.worldBinormal = mul(In.binormal, worldIT).xyz;
    //can use either positive or negative y format normal maps
    //comment out this if statement to save 6 instructions!
  	if (direction == true) Out.worldTangent = -Out.worldTangent;
    half3 worldSpacePos = mul(In.position, world);
    Out.lightVec = lightPosition - worldSpacePos;
	Out.texCoord.xy = In.texCoord;
    Out.eyeVec = viewInv[3].xyz - worldSpacePos;
    Out.position = mul(In.position, wvp);
    return Out;
}

/**************************************/
/***** FRAGMENT PROGRAM ***************/
/**************************************/

float4 f(v2f In,uniform half4 lightColor) : COLOR
{
  //fetch the diffuse and normal maps
  half4 colorMap = tex2D(colorTextureSampler, In.texCoord.xy);
  half3 normal = tex2D(normalMapSampler, In.texCoord).xyz * 2.0 - 1.0;

  //create tangent space vectors
  half3 Nn = In.worldNormal;
  half3 Tn = In.worldTangent;
  half3 Bn = In.worldBinormal;
  
  //these vectors could be normalized, but it costs 4 more instructions
  //and makes almost no difference to image quality
  //half3 Nn = normalize(In.worldNormal);
  //half3 Tn = normalize(In.worldTangent);
  //half3 Bn = normalize(In.worldBinormal);
  
  //offset world space normal with normal map values
  half3 N = (Nn * normal.z) + (normal.x * Bn + normal.y * -Tn);
  N = normalize(N);
  
  //create lighting vectors - view vector and light vector
  half3 V = normalize(In.eyeVec);
  half3 L = normalize(In.lightVec.xyz);
  
  //lighting
  
  //ambient light
  half4 C = ambient*colorMap;
  
  //diffuse and specular
  C += light1Color * blinn2(N, L, V, colorMap*surfColor, specularColor*colorMap.a, shininess);

  //calculate car paint color
  half NdotV = dot(N,V);
  half fresnel = fresnelbias + (1.0-fresnelbias)*pow(1.0 - max(NdotV, 0), fresnelpower);
  half4 paint = lerp(paintmiddle,paintedge,fresnel);
  
  //subtract car paint color from total
  C -= paint;

  return C;
}

float4 f2(v2f In,uniform half4 lightColor) : COLOR
{
  //fetch the diffuse and normal maps
  half4 colorMap = tex2D(colorTextureSampler, In.texCoord.xy);
  //swizzle the compressed dxt5 format
  half3 normal = tex2D(CnormalMapSampler, In.texCoord).wyz * 2.0 - 1.0;
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
  
  //offset world space normal with normal map values
  half3 N = (Nn * normal.z) + (normal.x * Bn + normal.y * -Tn);
  N = normalize(N);
  
  //create lighting vectors - view vector and light vector
  half3 V = normalize(In.eyeVec);
  half3 L = normalize(In.lightVec.xyz);
  
  //lighting
  
  //ambient light
  half4 C = ambient*colorMap;
  
  //diffuse and specular
  C += light1Color * blinn2(N, L, V, colorMap*surfColor, specularColor*colorMap.a, shininess);

  //calculate car paint color
  half NdotV = dot(N,V);
  half fresnel = fresnelbias + (1.0-fresnelbias)*pow(1.0 - max(NdotV, 0), fresnelpower);
  half4 paint = lerp(paintmiddle,paintedge,fresnel);
  
  //subtract car paint color from total
  C -= paint;

  return C;
}

/****************************************************/
/********** TECHNIQUES ******************************/
/****************************************************/

technique Complete
{ 
    pass envPass 
    {		
	VertexShader = compile vs_1_1 v(light1Pos);
	ZEnable = true;
	ZWriteEnable = true;
	CullMode = CW;
	AlphaBlendEnable = false;
	PixelShader = compile ps_2_0 f(light1Color);
    }
}

technique Compressed
{ 
    pass envPass 
    {		
	VertexShader = compile vs_1_1 v(light1Pos);
	ZEnable = true;
	ZWriteEnable = true;
	CullMode = CW;
	AlphaBlendEnable = false;
	PixelShader = compile ps_2_0 f2(light1Color);
    }
}

