#ifndef MESH_H
#define MESH_H

#include "Common/dxstdafx.h"

const int s_iDECL_SIZE       = 56;

HRESULT LoadMesh( IDirect3DDevice9* pd3dDevice, WCHAR* strFileName, ID3DXMesh** ppMesh );

#endif