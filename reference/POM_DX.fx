texture g_DiffuseTexture : DIFFUSE
<
    string Name = "D.png";
    string UIName = "DiffuseTexture";
    string TextureType = "2D";
>;
sampler2D tBase = sampler_state
{
    Texture = <g_DiffuseTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

texture g_NormalTexture : NORMAL
<
    string Name = "N.png";
    string UIName = "NormalTexture";
    string TextureType = "2D";
>;
sampler2D tNormalHeightMap = sampler_state
{
    Texture = <g_NormalTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float4x4 m_world		: World < string UIWidget="None"; >;
float4x4 m_worldInv : 	WorldInverse < string UIWidget="None"; >;	
float4x4 m_wvp		: WorldViewProjection < string UIWidget="None"; >;
float4x4 m_worldView : 	WorldView < string UIWidget="None"; >;
float4x4 m_viewInv    :   ViewInverse < string UIWidget="None"; >;

float4 g_materialAmbientColor <
    string UIWidget = "mat Amb Color";
> = {0.0f, 0.0f, 0.0f, 0.0f};     // Material's ambient color

float4 g_materialDiffuseColor <
    string UIWidget = "mat Diff Color";
> = {1.0f, 1.0f, 1.0f, 1.0f};      // Material's diffuse color

float4 g_materialSpecularColor <
    string UIWidget = "mat Spec Color";
> = {1.0f, 1.0f, 1.0f, 1.0f};     // Material's specular color

float  g_fSpecularExponent <
    string UIWidget = "slider";
    float UIMin = 1;
    float UIMax = 256;
    float UIStep = 1;
    string UIName = "Glossiness";
> = 32;         // Material's specular exponent

float3 g_LightDir : POSITION 
< 
    string UIName = "Light Position"; 
    string Object = "PointLight"; 
    string Space = "World"; 
    int refID = 1; 
> = {100.0f, 100.0f, 100.0f}; 
 
float4 g_LightColor : LIGHTCOLOR 
< 
		int LightRef = 1; 
		string UIType = "None"; 
> = { 1.0f, 1.0f, 1.0f, 1.0f}; 

float    g_fHeightMapScale <
    string UIWidget = "slider";
    float UIMin = 0;
    float UIMax = 1;
    float UIStep = .01;
    string UIName = "height scale";
> = 0;

int    g_nMinSamples <
    string UIWidget = "slider";
    int UIMin = 1;
    int UIMax = 200;
    int UIStep = 1;
    string UIName = "min samples";
> = 20;

int    g_nMaxSamples <
    string UIWidget = "slider";
    int UIMin = 2;
    int UIMax = 201;
    int UIStep = 1;
    string UIName = "max samples";
> = 60;

/////STRUCTS///////////
struct VS_IN
{
    float4 Position : POSITION0;
    float2 texCoord      : TEXCOORD0;
    float3 Normal   : NORMAL0;
    float3 Binormal : BINORMAL0;
    float3 Tangent  : TANGENT0;
};
 
struct VS_OUT
{
    float4 position          : POSITION;
    float2 texCoord          : TEXCOORD0;
    float3 vLightTS          : TEXCOORD1;   // light vector in tangent space, denormalized
    float3 vViewTS           : TEXCOORD2;   // view vector in tangent space, denormalized
    float2 vParallaxOffsetTS : TEXCOORD3;   // Parallax offset vector in tangent space
    float3 vNormalWS         : TEXCOORD4;   // Normal vector in world space
    float3 vViewWS           : TEXCOORD5;   // View vector in world space
    
};

/////VERTEX SHADER////////////
VS_OUT pomVS( VS_IN In)
{
    VS_OUT Out;
        
    // Transform and output input position 
    Out.position = mul( In.Position, m_wvp );
       
    // Propagate texture coordinate through:
    Out.texCoord = In.texCoord;

    // Transform the normal, tangent and binormal vectors from object space to homogeneous projection space:
    float3 vNormalWS   = mul( In.Normal,   m_world );
    float3 vTangentWS  = mul( In.Tangent,  m_world );
    float3 vBinormalWS = mul( In.Binormal, m_world );
    
    // Propagate the world space vertex normal through:   
    Out.vNormalWS = vNormalWS;
    
    vNormalWS   = normalize( vNormalWS );
    vTangentWS  = normalize( vTangentWS );
    vBinormalWS = normalize( vBinormalWS );
    
    // Compute position in world space:
    float4 vPositionWS = mul( In.Position, m_world );
                 
    // Compute and output the world view vector (unnormalized):
    float3 g_vEye = m_viewInv[3].xyz;
    float3 vViewWS = g_vEye - vPositionWS;
    Out.vViewWS = vViewWS;

    // Compute denormalized light vector in world space:
    float3 vLightWS = g_LightDir;
       
    // Normalize the light and view vectors and transform it to the tangent space:
    float3x3 mWorldToTangent = float3x3( vTangentWS, vBinormalWS, vNormalWS );
       
    // Propagate the view and the light vectors (in tangent space):
    Out.vLightTS = mul( vLightWS, mWorldToTangent );
    Out.vViewTS  = mul( mWorldToTangent, vViewWS  );
       
    // Compute the ray direction for intersecting the height field profile with 
    // current view ray. See the above paper for derivation of this computation.
         
    // Compute initial parallax displacement direction:
    float2 vParallaxDirection = normalize(  Out.vViewTS.xy );
       
    // The length of this vector determines the furthest amount of displacement:
    float fLength         = length( Out.vViewTS );
    float fParallaxLength = sqrt( fLength * fLength - Out.vViewTS.z * Out.vViewTS.z ) / Out.vViewTS.z; 
       
    // Compute the actual reverse parallax displacement vector:
    Out.vParallaxOffsetTS = vParallaxDirection * fParallaxLength;
       
    // Need to scale the amount of displacement to account for different height ranges
    // in height maps. This is controlled by an artist-editable parameter:
    Out.vParallaxOffsetTS *= g_fHeightMapScale;

   return Out;
}

//--------------------------------------------------------------------------------------
// Function:    ComputeIllumination
// 
// Description: Computes phong illumination for the given pixel using its attribute 
//              textures and a light vector.
//--------------------------------------------------------------------------------------
float4 ComputeIllumination( float2 texCoord, float3 vLightTS, float3 vViewTS, float fOcclusionShadow )
{
   // Sample the normal from the normal map for the given texture sample:
   float3 vNormalTS = normalize( tex2D( tNormalHeightMap, texCoord ) * 2 - 1 );
   
   // Sample base map:
   float4 cBaseColor = tex2D( tBase, texCoord );
   
   // Compute diffuse color component:
   float3 vLightTSAdj = float3( vLightTS.x, -vLightTS.y, vLightTS.z );
   
   float4 cDiffuse = saturate( dot( vNormalTS, vLightTSAdj )) * g_materialDiffuseColor;
   
   // Compute the specular component if desired:  
   float4 cSpecular = 0;
    float3 vReflectionTS = normalize( 2 * dot( vViewTS, vNormalTS ) * vNormalTS - vViewTS );
       
    float fRdotL = saturate( dot( vReflectionTS, vLightTSAdj ));
    cSpecular = saturate( pow( fRdotL, g_fSpecularExponent )) * g_materialSpecularColor;
   
   // Composite the final color:
   float4 cFinalColor = (( g_materialAmbientColor + cDiffuse ) * cBaseColor + cSpecular ) * fOcclusionShadow; 
   
   return cFinalColor;  
}   

//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;  // Pixel color    
};

struct PS_INPUT
{
   float2 texCoord          : TEXCOORD0;
   float3 vLightTS          : TEXCOORD1;   // light vector in tangent space, denormalized
   float3 vViewTS           : TEXCOORD2;   // view vector in tangent space, denormalized
   float2 vParallaxOffsetTS : TEXCOORD3;   // Parallax offset vector in tangent space
   float3 vNormalWS         : TEXCOORD4;   // Normal vector in world space
   float3 vViewWS           : TEXCOORD5;   // View vector in world space
};

//--------------------------------------------------------------------------------------
// Parallax occlusion mapping pixel shader
//
// Note: this shader contains several educational modes that would not be in the final
//       game or other complicated scene rendering. The blocks of code in various "if"
//       statements for turning off visual qualities (such as visual level of detail
//       or specular or shadows, etc), can be handled differently, and more optimally.
//       It is implemented here purely for educational purposes.
//--------------------------------------------------------------------------------------
float4 RenderSceneParallaxMappingPS( PS_INPUT i ) : COLOR0
{ 

   //  Normalize the interpolated vectors:
   float3 vViewTS   = normalize( i.vViewTS  );
   float3 vViewWS   = normalize( i.vViewWS  );
   float3 vLightTS  = normalize( i.vLightTS );
   float3 vNormalWS = normalize( i.vNormalWS );
     
   float4 cResultColor = float4( 0, 0, 0, 1 );

   // Adaptive in-shader level-of-detail system implementation. Compute the 
   // current mip level explicitly in the pixel shader and use this information 
   // to transition between different levels of detail from the full effect to 
   // simple bump mapping. See the above paper for more discussion of the approach
   // and its benefits.
   
   // Compute the current gradients:
   float2 g_vTextureDims = float2(1,1);
   float2 fTexCoordsPerSize = i.texCoord * g_vTextureDims;

   // Compute all 4 derivatives in x and y in a single instruction to optimize:
   float2 dxSize, dySize;
   float2 dx, dy;

   float4( dxSize, dx ) = ddx( float4( fTexCoordsPerSize, i.texCoord ) );
   float4( dySize, dy ) = ddy( float4( fTexCoordsPerSize, i.texCoord ) );
                  
   float  fMipLevel;      
   float  fMipLevelInt;    // mip level integer portion
   float  fMipLevelFrac;   // mip level fractional amount for blending in between levels

   float  fMinTexCoordDelta;
   float2 dTexCoords;

   // Find min of change in u and v across quad: compute du and dv magnitude across quad
   dTexCoords = dxSize * dxSize + dySize * dySize;

   // Standard mipmapping uses max here
   fMinTexCoordDelta = max( dTexCoords.x, dTexCoords.y );

   // Compute the current mip level  (* 0.5 is effectively computing a square root before )
   fMipLevel = max( 0.5 * log2( fMinTexCoordDelta ), 0 );
    
   // Start the current sample located at the input texture coordinate, which would correspond
   // to computing a bump mapping result:
   float2 texSample = i.texCoord;
   
   // Multiplier for visualizing the level of detail (see notes for 'nLODThreshold' variable
   // for how that is done visually)
   float4 cLODColoring = float4( 1, 1, 3, 1 );

   float fOcclusionShadow = 1.0;

   float g_nLODThreshold = 4000;
   if ( fMipLevel <= (float) g_nLODThreshold )
   {
      //===============================================//
      // Parallax occlusion mapping offset computation //
      //===============================================//

      // Utilize dynamic flow control to change the number of samples per ray 
      // depending on the viewing angle for the surface. Oblique angles require 
      // smaller step sizes to achieve more accurate precision for computing displacement.
      // We express the sampling rate as a linear function of the angle between 
      // the geometric normal and the view direction ray:
      int nNumSteps = (int) lerp( g_nMaxSamples, g_nMinSamples, dot( vViewWS, vNormalWS ) );

      // Intersect the view ray with the height field profile along the direction of
      // the parallax offset ray (computed in the vertex shader. Note that the code is
      // designed specifically to take advantage of the dynamic flow control constructs
      // in HLSL and is very sensitive to specific syntax. When converting to other examples,
      // if still want to use dynamic flow control in the resulting assembly shader,
      // care must be applied.
      // 
      // In the below steps we approximate the height field profile as piecewise linear
      // curve. We find the pair of endpoints between which the intersection between the 
      // height field profile and the view ray is found and then compute line segment
      // intersection for the view ray and the line segment formed by the two endpoints.
      // This intersection is the displacement offset from the original texture coordinate.
      // See the above paper for more details about the process and derivation.
      //

      float fCurrHeight = 0.0;
      float fStepSize   = 1.0 / (float) nNumSteps;
      float fPrevHeight = 1.0;
      float fNextHeight = 0.0;

      int    nStepIndex = 0;
      bool   bCondition = true;

      float2 vTexOffsetPerStep = fStepSize * i.vParallaxOffsetTS;
      float2 vTexCurrentOffset = i.texCoord;
      float  fCurrentBound     = 1.0;
      float  fParallaxAmount   = 0.0;

      float2 pt1 = 0;
      float2 pt2 = 0;
       
      float2 texOffset2 = 0;

      while ( nStepIndex < nNumSteps ) 
      {
         vTexCurrentOffset -= vTexOffsetPerStep;

         // Sample height map which in this case is stored in the alpha channel of the normal map:
         fCurrHeight = tex2Dgrad( tNormalHeightMap, vTexCurrentOffset, dx, dy ).a;

         fCurrentBound -= fStepSize;

         if ( fCurrHeight > fCurrentBound ) 
         {   
            pt1 = float2( fCurrentBound, fCurrHeight );
            pt2 = float2( fCurrentBound + fStepSize, fPrevHeight );

            texOffset2 = vTexCurrentOffset - vTexOffsetPerStep;

            nStepIndex = nNumSteps + 1;
            fPrevHeight = fCurrHeight;
         }
         else
         {
            nStepIndex++;
            fPrevHeight = fCurrHeight;
         }
      }   

      float fDelta2 = pt2.x - pt2.y;
      float fDelta1 = pt1.x - pt1.y;
      
      float fDenominator = fDelta2 - fDelta1;
      
      // SM 3.0 requires a check for divide by zero, since that operation will generate
      // an 'Inf' number instead of 0, as previous models (conveniently) did:
      if ( fDenominator == 0.0f )
      {
         fParallaxAmount = 0.0f;
      }
      else
      {
         fParallaxAmount = (pt1.x * fDelta2 - pt2.x * fDelta1 ) / fDenominator;
      }
      
      float2 vParallaxOffset = i.vParallaxOffsetTS * (1 - fParallaxAmount );

      // The computed texture offset for the displaced point on the pseudo-extruded surface:
      float2 texSampleBase = i.texCoord - vParallaxOffset;
      texSample = texSampleBase;

   }   

   // Compute resulting color for the pixel:
   cResultColor = ComputeIllumination( texSample, vLightTS, vViewTS, fOcclusionShadow );
              
   // If using HDR rendering, make sure to tonemap the resuld color prior to outputting it.
   // But since this example isn't doing that, we just output the computed result color here:
   return cResultColor;
}   

float4 bumpPS (VS_OUT In) : COLOR
{ 
   //  Normalize the interpolated vectors:
   float3 vViewTS   = normalize( In.vViewTS  );
   float3 vLightTS  = normalize( In.vLightTS );
     
   float4 cResultColor = float4( 0, 0, 0, 1 );

   // Start the current sample located at the input texture coordinate, which would correspond
   // to computing a bump mapping result:
   float2 texSample = In.texCoord;

   // Compute resulting color for the pixel:
   cResultColor = ComputeIllumination( texSample, vLightTS, vViewTS, 1.0f );
              
   // If using HDR rendering, make sure to tonemap the resuld color prior to outputting it.
   // But since this example isn't doing that, we just output the computed result color here:
   return cResultColor;
} 

technique tileRenderer
{
    pass P0
    {          
        VertexShader = compile vs_3_0 pomVS();
        PixelShader  = compile ps_3_0 RenderSceneParallaxMappingPS(); 
    } 
}