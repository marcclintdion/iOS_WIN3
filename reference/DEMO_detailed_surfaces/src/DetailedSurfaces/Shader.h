#ifndef SHADER_H
#define SHADER_H

//#define DEBUG_VS   // Uncomment this line to debug vertex shaders 
//#define DEBUG_PS   // Uncomment this line to debug pixel shaders 

#include <d3d9.h>
#include <d3dx9.h>
#include "Common/dxstdafx.h"

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

HRESULT LoadShader(LPDIRECT3DDEVICE9 pd3dDevice, LPD3DXEFFECT *effect, TCHAR* fileName);

#endif