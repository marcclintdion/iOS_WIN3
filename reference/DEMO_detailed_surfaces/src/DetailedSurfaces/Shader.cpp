#include "Shader.h"

HRESULT LoadShader(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXEFFECT *effect, TCHAR* fileName)
{
	HRESULT hr;
	TCHAR fileStr[MAX_PATH];

	ID3DXBuffer *pErrors = NULL;
	V_RETURN(D3DXCreateBuffer(1024, &pErrors));

	// Shader flags
	DWORD dwFlags = D3DXFX_NOT_CLONEABLE;
	#ifdef DEBUG_VS
		dwFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
	#endif
	#ifdef DEBUG_PS
		dwFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
	#endif

	V_RETURN( DXUTFindDXSDKMediaFileCch( fileStr, MAX_PATH, fileName ) );
	hr = D3DXCreateEffectFromFile( pd3dDevice, fileStr, NULL, NULL,
		dwFlags, NULL, effect, &pErrors );

	if (FAILED(hr))
	{
		CHAR *pErrorStr = ( CHAR* ) pErrors->GetBufferPointer();
		printf( "%s\n", pErrorStr );
		return E_FAIL;
	}

	SAFE_RELEASE( pErrors );

	return hr;
}
