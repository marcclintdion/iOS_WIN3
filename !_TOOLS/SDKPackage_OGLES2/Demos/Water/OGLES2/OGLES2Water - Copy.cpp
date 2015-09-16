
//================================================================================================================    
    GLuint m_uiNormalisationCubeMap;
//================================================================================================================    	
    



//=================================================================================================================================================	
    bool GenerateNormalisationCubeMap(int uiTextureSize = 32);
//=================================================================================================================================================


//==========================================================================================================================================
	//Create normalisation cube map
	glGenTextures(1, &m_uiNormalisationCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiNormalisationCubeMap);
	GenerateNormalisationCubeMap(8);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//==========================================================================================================================================


//==========================================================================================================================================
	glUniform1i(glGetUniformLocation(m_SkyboxShader.uiId, "CubeMap"),0);
//==========================================================================================================================================


//==========================================================================================================================================	
    glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiNormalisationCubeMap);
//==========================================================================================================================================

//==========================================================================================================================================
bool OGLES2Water::GenerateNormalisationCubeMap(int uiTextureSize)
{
	// variables
	float fOffset = 0.5f;
	float fHalfSize = uiTextureSize *0.5f;
	PVRTVec3 vTemp;
	unsigned char* pByte;
	unsigned char* pData = new unsigned char[uiTextureSize*uiTextureSize*3];
    if(!pData)
    {
        PVRShellOutputDebug("Unable to allocate memory for texture data for cube map\n");
        return false;
    }

	// Positive X
	pByte = pData;

	for(int j = 0; j < uiTextureSize; ++j)
	{
		for(int i = 0; i < uiTextureSize; ++i)
		{
			vTemp.x = fHalfSize;
			vTemp.y = -(j + fOffset - fHalfSize);
			vTemp.z = -(i + fOffset - fHalfSize);

			// normalize, pack 0 to 1 here, and normalize again
			vTemp = vTemp.normalize() *0.5 + 0.5;

			pByte[0] = (unsigned char)(vTemp.x * 255);
			pByte[1] = (unsigned char)(vTemp.y * 255);
			pByte[2] = (unsigned char)(vTemp.z * 255);

			pByte += 3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB /*GL_RGBA8*/, uiTextureSize, uiTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);

	// Negative X
	pByte = pData;

	for(int j = 0; j < uiTextureSize; ++j)
	{
		for(int i = 0; i < uiTextureSize; ++i)
		{
			vTemp.x = -fHalfSize;
			vTemp.y = -(j + fOffset - fHalfSize);
			vTemp.z = (i + fOffset - fHalfSize);


			// normalize, pack 0 to 1 here, and normalize again
			vTemp = vTemp.normalize() *0.5 + 0.5;

			pByte[0] = (unsigned char)(vTemp.x * 255);
			pByte[1] = (unsigned char)(vTemp.y * 255);
			pByte[2] = (unsigned char)(vTemp.z * 255);

			pByte += 3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB /*GL_RGBA8*/, uiTextureSize, uiTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);

	// Positive Y
	pByte = pData;

	for(int j = 0; j < uiTextureSize; ++j)
	{
		for(int i = 0; i < uiTextureSize; ++i)
		{
			vTemp.x = i + fOffset - fHalfSize;
			vTemp.y = fHalfSize;
			vTemp.z = j + fOffset - fHalfSize;

			// normalize, pack 0 to 1 here, and normalize again
			vTemp = vTemp.normalize() *0.5 + 0.5;

			pByte[0] = (unsigned char)(vTemp.x * 255);
			pByte[1] = (unsigned char)(vTemp.y * 255);
			pByte[2] = (unsigned char)(vTemp.z * 255);

			pByte += 3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB /*GL_RGBA8*/, uiTextureSize, uiTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);

	// Negative Y
	pByte = pData;

	for(int j = 0; j < uiTextureSize; ++j)
	{
		for(int i = 0; i < uiTextureSize; ++i)
		{
			vTemp.x = i + fOffset - fHalfSize;
			vTemp.y = -fHalfSize;
			vTemp.z = -(j + fOffset - fHalfSize);

			// normalize, pack 0 to 1 here, and normalize again
			vTemp = vTemp.normalize() *0.5 + 0.5;

			pByte[0] = (unsigned char)(vTemp.x * 255);
			pByte[1] = (unsigned char)(vTemp.y * 255);
			pByte[2] = (unsigned char)(vTemp.z * 255);

			pByte += 3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB /*GL_RGBA8*/, uiTextureSize, uiTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);

	// Positive Z
	pByte = pData;

	for(int j = 0; j < uiTextureSize; ++j)
	{
		for(int i = 0; i < uiTextureSize; ++i)
		{
			vTemp.x = i + fOffset - fHalfSize;
			vTemp.y = -(j + fOffset - fHalfSize);
			vTemp.z = fHalfSize;

			// normalize, pack 0 to 1 here, and normalize again
			vTemp = vTemp.normalize() *0.5 + 0.5;

			pByte[0] = (unsigned char)(vTemp.x * 255);
			pByte[1] = (unsigned char)(vTemp.y * 255);
			pByte[2] = (unsigned char)(vTemp.z * 255);

			pByte += 3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB /*GL_RGBA8*/, uiTextureSize, uiTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);

	// Negative Z
	pByte = pData;

	for(int j = 0; j < uiTextureSize; ++j)
	{
		for(int i = 0; i < uiTextureSize; ++i)
		{
			vTemp.x = -(i + fOffset - fHalfSize);
			vTemp.y = -(j + fOffset - fHalfSize);
			vTemp.z = -fHalfSize;

			// normalize, pack 0 to 1 here, and normalize again
			vTemp = vTemp.normalize() *0.5 + 0.5;

			pByte[0] = (unsigned char)(vTemp.x * 255);
			pByte[1] = (unsigned char)(vTemp.y * 255);
			pByte[2] = (unsigned char)(vTemp.z * 255);

			pByte += 3;
		}
	}
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB /*GL_RGBA8*/, uiTextureSize, uiTextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);


	delete[] pData;

	return true;
}
//==========================================================================================================================================



