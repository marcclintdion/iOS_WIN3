vOUT2 MainVS2(APP_INPUT IN)
{
	vOUT2 OUT;

	half3 tangent  = IN.Tangent.xyz;
	half3 normal   = IN.Normal.xyz;
	half3 binormal = IN.Binormal.xyz;

	// position ,uvs
	OUT.Position	= mul(IN.Position,wvpMatrix);
	OUT.TexCoord.xy = IN.TexCoord;
	
	half3 EyePos = half3(wvMatrixI[3].xyz);//<---------------Point of interest(eyePos is being taken from modelViewMatrix

	half3 EyeDir = normalize(EyePos - IN.Position.xyz);
	OUT.EyeDir.xyz = mul(half4(EyeDir.xyz, 0.0),wMatrix).xyz;

	half3 wPos = mul(IN.Position,wMatrix).xyz;
	half3 LightDir = normalize(LightPos.xyz - wPos);
	OUT.LightDir.xyz = LightDir;

	OUT.Tgt = mul(half4(tangent, 0),wMatrix).xyz;
	OUT.Bnl = mul(half4(binormal, 0),wMatrix).xyz;
	OUT.Nml = mul(half4(normal, 0),wMatrix).xyz;

	OUT.Color = IN.Color;
	return OUT;
}
