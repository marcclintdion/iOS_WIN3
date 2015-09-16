//Simple Relief Mapping Shader
//Based on Fabio Policarpo's generous source code examples
//
//Adapted and extended by Drew Skillman, Technical Artist
//Email: drew@drewskillman.com
//
// accepts: 
// diffuse map
// normal map
// height map
// depth value
// specular value
// specular component
// 
//
// NOTE: REQUIRES PS_3_0 CAPABLE GRAPHICS CARD
//
//
///////////////////////////////////////////////////////////////////

string ParamID = "0x0001";

#define l_search_steps 64
#define b_search_steps 5

float Script : STANDARDSGLOBAL <
	string UIWidget = "none";
	string ScriptClass = "object";
	string ScriptOrder = "standard";
	string ScriptOutput = "color";
	string Script = "Technique=blend;";
> = 0.8; // version #

//float4x4 WorldIT : WorldInverseTranspose < string UIWidget="None"; >;
float4x4 WorldViewProj : WorldViewProjection < string UIWidget="None"; >;
//float4x4 World : World < string UIWidget="None"; >;
float4x4 View : View < string UIWidget="None"; >;
float4x4 WorldView : WorldView < string UIWidget="None"; >;


//these are uvs
int texcoord0 : Texcoord
<
	int Texcoord = 0;
	int MapChannel = 1;
	string UIWidget = "None";
>;


//these are mapchannel 5 colors
int texcoord1 : Texcoord
<
	int Texcoord = 5;
	int MapChannel = 5;
	bool ColorChannel = true;
	string UIWidget = "None";
>;



//these are mapchannel 6 colors
int texcoord2 : Texcoord
<
	int Texcoord = 6;
	int MapChannel = 6;
	bool ColorChannel = true;
	string UIWidget = "None";
>;

//these are mapchannel 6 colors
int texcoord3 : Texcoord
<
	int Texcoord = 7;
	int MapChannel = 7;
	bool ColorChannel = true;
	string UIWidget = "None";
>;

float3 LightPos : Position <
    string Object = "PointLight";
    string Space = "World";
> = {-10.0f, 10.0f, -10.0f};

Texture diffuseMap 
<
	string UIName = "Texture";
>;


Texture specularMap 
<
	string UIName = "Spec Map";
>;


Texture normalMap 
< 
	string UIName = "Normal Map";
>;

Texture heightMap 
< 
	string UIName = "Height Map";
>;


sampler2D diffuseSampler = sampler_state
{
	Texture = <diffuseMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};

sampler2D specularSampler = sampler_state
{
	Texture = <specularMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};


sampler2D heightSampler = sampler_state 
{
	Texture = <heightMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};


sampler2D normalSampler = sampler_state 
{
	Texture = <normalMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};





float shine
<
    string UIType = "FloatSpinner";
	string UIName = "Shine";
> = 128.0;

float specular
<
    string UIType = "FloatSpinner";
	string UIName = "Specular Amount";
> = 1.0;

float depth_fact <
 	string UIType = "FloatSpinner";
	string UIName = "Depth";
> = {0.1f};

bool overrideQuartics <
	string UIName = "Manual Quartics";
> = false;

float quadraticA <
 	string UIType = "FloatSpinner";
	string UIName = "quadratic A";
	float UIMin = -50.0f;
	float UIMax = 50.0f;	
> = {0.1f};

float quadraticB <
 	string UIType = "FloatSpinner";
	string UIName = "quadratic B";
	float UIMin = -50.0f;
	float UIMax = 50.0f;	
> = {0.1f};

float texelSizeA <
 	string UIType = "FloatSpinner";
	string UIName = "texel size A";
	float UIMin = -50.0f;
	float UIMax = 50.0f;	
> = {0.1f};

float texelSizeB <
 	string UIType = "FloatSpinner";
	string UIName = "texel size B";
	float UIMin = -50.0f;
	float UIMax = 50.0f;	
> = {0.1f};



struct appData
{
	float3 Position		: POSITION;
	float3 uv			: TEXCOORD0;
    float3 curvature 	: TEXCOORD1;
    float3 scale 	: TEXCOORD2;
    float3 colordepth 	: TEXCOORD3;
	//relief mapping vars
	float3 Normal	: NORMAL;
    float3 Tangent	: TANGENT;
    float3 Binormal : BINORMAL;	
};

struct vertexOutput
{
   	float2 uv		: TEXCOORD8;
   	//relief mapping vars
	float3 colordepth : TEXCOORD2;
	float4 hpos            : POSITION;
	float3 vpos 			:TEXCOORD7;
	float3 view			:TEXCOORD3;
	float2 curvature	:TEXCOORD6;
	float3 light		:TEXCOORD1;
	float3 scale		:TEXCOORD4;

};

struct PSOut
{
	float4 color		: COLOR0;
};

vertexOutput VS(appData IN) 
{
	vertexOutput OUT;    
	
	float4 pos=float4(IN.Position.x,IN.Position.y,IN.Position.z,1.0);   
	                                                                                                                                                                                                                                                                                                                            
   	OUT.hpos	= mul(pos, WorldViewProj);
   
     // pass through colors and uv's
 	 OUT.uv = IN.uv.xy;
 	 
 	/*********************************************************************/
   	//relief mapping vertex ops start here
   	/*********************************************************************/
    float3 lpos = mul(float4(LightPos.xyz,1), View).xyz;
   
   	OUT.vpos = mul(pos, WorldView).xyz;
   		
   	// compute modelview rotation only part
	float3x3 modelviewrot;
	modelviewrot[0]=WorldView[0].xyz;
	modelviewrot[1]=WorldView[1].xyz;
	modelviewrot[2]=WorldView[2].xyz;
	
		 	
    float3 tangent = mul(IN.Tangent, modelviewrot);
	float3 binormal = mul(IN.Binormal, modelviewrot);
	float3 normal =  mul(IN.Normal, modelviewrot);
   
	//	float3x3 tangentspace = float3x3(tangent, binormal,normal);
   //for some reason i always have to swap binormal and tangent
   //in max... must be something about the coordsys
   
   	float3x3 tangentspace = float3x3(binormal, tangent, normal);
   	
   	OUT.colordepth = IN.colordepth;
   	
   	if (!overrideQuartics) 
   		{
	   	OUT.curvature = IN.curvature.xy;
	   	OUT.scale = float3(IN.scale.x,IN.scale.y,depth_fact);
	   	}
   	else 
   		{
	   	OUT.curvature = float2(quadraticA,quadraticB);
	    OUT.scale = float3(texelSizeA, texelSizeB, depth_fact);

	   }
   	  	
   	OUT.view = mul(tangentspace, OUT.vpos);
   	OUT.light = mul(tangentspace, lpos.xyz-OUT.vpos);
   
   	
   	return OUT;
}


	////////////////////////////////////////////////////////////////////////////////
	//begin OLD raymarcher 
	////////////////////////////////////////////////////////////////////////////////
	//

float ray_intersect_rm(
		in sampler2D heightmap, 
		in float2 dp, 			
		in float2 ds)
{
	const int linear_search_steps=l_search_steps;	
	const int binary_search_steps=b_search_steps;
	float depth_step=1.0/linear_search_steps;

	// current size of search window
	float size=depth_step;
	// current depth position
	float depth=0.0;
	// best match found (starts with last position 1.0)
	float best_depth=1.0;

	// search front to back for first point inside object
	for( int i=0;i<linear_search_steps-1;i++ )
	{
		depth+=size;
		//I've inverted the heightmap to work with Max 
		//Autogenerated height maps
		float4 t=1-tex2D(heightmap,dp+ds*depth); 

		if (best_depth>0.996)	// if no depth found yet
		//if (depth>=t.w)
		if (depth>=t.x)
			best_depth=depth;	// store best depth
	}
	depth=best_depth;
	
	// recurse around first point (depth) for closest match
	for( int i=0;i<binary_search_steps;i++ )
	{
		size*=0.5;
		//I've inverted the heightmap to work with Max 
		//Autogenerated height maps
		float4 t=1-tex2D(heightmap,dp+ds*depth); 
		if (depth>=t.x)
		{
			best_depth=depth;
			depth-=2*size;
		}
		depth+=size;
	}

	return best_depth;
}
	//
	////////////////////////////////////////////////////////////////////////////////
	//end OLD raymarcher 
	////////////////////////////////////////////////////////////////////////////////
	
	
	
	////////////////////////////////////////////////////////////////////////////////
	//begin new raymarcher 
	////////////////////////////////////////////////////////////////////////////////
	//

/////////////////
// RELIEF MAPPING

float3 ray_position(
	in float t,		// search parameters
	in float2 tx,	// original pixel texcoord
	in float3 v,	// view vector in texture space
	in float dataz)		// data constants
{
	float3 r=v*t;
	r.z-=t*t*dataz;
	r.xy+=tx;
	return r;
}

float ray_intersect_rm_curved(
		in sampler2D reliefmap,
		in float2 tx,
		in float3 v,
		in float tmax,
		in float dataz)
{

   const int linear_search_steps=l_search_steps;


   float t=0.0;
   float size=(tmax+0.001)/linear_search_steps;

   // search front to back for first point inside object
   for( int i=0;i<linear_search_steps;i++ )
   {
		float3 p=ray_position(t,tx,v,dataz);
		float4 tex=1-tex2D(reliefmap,p.xy);
		if (p.z<tex.x)
			t+=size;
   }

   const int binary_search_steps=b_search_steps;

   // recurse around first point for closest match
   for( int i=0;i<binary_search_steps;i++ )
   {
      size*=0.5;
	  float3 p=ray_position(t,tx,v,dataz);
      float4 tex=1-tex2D(reliefmap,p.xy);
      if (p.z<tex.x)
         t+=2*size;
      t-=size;
   }

   return t;
}
	//
	////////////////////////////////////////////////////////////////////////////////
	//end raymarcher 
	////////////////////////////////////////////////////////////////////////////////
	
	


PSOut PS( vertexOutput IN )
{
	PSOut OUT;
	
	float3 v = normalize(IN.view);
	v.z *= -1;
	
	// vector perpendicular to view closest to (0,0,1)
	float3 u=normalize(2*v*v.z-float3(0,0,2));
	
	// mapping scale from object to texture space
	float3  mapping = 1.0/(IN.scale);
	
	
	// quadric constants
	float dataz=IN.curvature.x*v.x*v.x+IN.curvature.y*v.y*v.y; 
	dataz=sign(dataz)*max(abs(dataz),0.001);
	
	// compute max distance for search min(t(z=0),t(z=1))
	float d=v.z*v.z-4*dataz*IN.scale.z;
	float tmax=50;
	if (d>0)		// t when z=1
		tmax=min(tmax,(-v.z+sqrt(d))/(-2*dataz));
	d=v.z/dataz;	// t when z=0
	if (d>0)
		tmax=min(tmax,d);
		
		
	// transform view and quadric data to texture space
	v*=mapping;
	dataz*=mapping.z;	
		
	// ray intersect depth map
	float t=ray_intersect_rm_curved(heightSampler,IN.uv,v,tmax,dataz);
	float alpha=1;
	if (t>tmax)
		alpha=0; // no intesection, discard fragment	
		
	// compute intersected position
	float3 p=ray_position(t,IN.uv,v,dataz);
	float2 uv = p.xy;
				
	float3 l = normalize(IN.light);
	
	// parallax code
	//float height = -tex2D(heightSampler,uv).x * 0.06 - 0.03;
	//uv += height * v.xy;
	
	float3 normal=tex2D(normalSampler,uv).xyz;
	normal=normalize(normal-0.5);
	//my normal maps are slightly different than theirs...
	//normal.xy = normal.yx;
	normal.y *= -1;
	
	float4 color=tex2D(diffuseSampler,uv);
	
	// compute diffuse and specular terms
	float diff=saturate(dot(l,normal));
	float spec=saturate(dot(normalize(l-v),normal));
	
	// attenuation factor
	float att=1.0-max(0,l.z); att=1.0-att*att;
	
	float4 finalcolor;
	finalcolor.xyz = att*((color.xyz*diff) + float3(1,1,1)*pow(spec,90.0));
	finalcolor.w=alpha;

	OUT.color = finalcolor;  
	//OUT.color = float4(IN.scale.xy/2.0,1.0,1.0);
	return OUT;
}


technique Relief<
	string script = "Pass=p0;";
> {
    pass p0 <
		string script = "Draw=Geometry;";
    > {		
	    
	    Zenable = true;
		ZWriteEnable = true;
		CullMode = cw;
		
		AlphaBlendEnable	= TRUE;
		DestBlend		= InvSrcAlpha;  
		SrcBlend		= SrcAlpha;
		VertexShader	= compile vs_3_0 VS();
		PixelShader		= compile ps_3_0 PS();
    }
}