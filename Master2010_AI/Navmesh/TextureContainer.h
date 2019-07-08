#pragma once

#include "Texture.h"
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <iostream>
using namespace std ;
#include <locale>
#include <iostream>
#include <string>
#include <sstream>
class TextureContainer
{
private:
	bool _bHasTexture;
	CTexture _texture;
public:
	float X;
	float Y;
	float WIDTH;
	float HEIGHT;
	TextureContainer(void);
	TextureContainer(float fX, float fY, float fWidth, float fHeight);
	TextureContainer(float fX, float fY,  float fWidth, float fHeight, float fWidthTexture, float fHeightTexture);
	~TextureContainer(void);
	bool PointInside(float fX, float fY);
		
	void LoadTexture(LPDIRECT3DDEVICE9 p_dx_Device,LPCWSTR file);
	void Draw(LPDIRECT3DDEVICE9 p_dx_Device);
	void Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY);
	void Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY, int i, int j);	
};
