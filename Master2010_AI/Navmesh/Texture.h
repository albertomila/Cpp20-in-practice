#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <windows.h> 
#include <d3dx9.h>
#include <string>
#include <iostream>
using namespace std ;
#include <locale>
#include <iostream>
#include <string>
#include <sstream>

#include "./poly2tri/poly2tri.h"
using namespace p2t;
struct CUSTOMVERTEX {FLOAT X, Y, Z; DWORD COLOR; FLOAT U, V;};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
class CTexture
{
public:
	float WIDTH;
	float HEIGHT;
	CUSTOMVERTEX pTextureCoords[6];
	LPDIRECT3DTEXTURE9 pTexture;
	LPDIRECT3DVERTEXBUFFER9 pVB; 

	CTexture(void);
	CTexture(float fWidth, float fHeight);
	~CTexture(void);
	void generateRectTexture();
	void LoadTexture(LPDIRECT3DDEVICE9 p_dx_Device,LPCWSTR file);
	//void Draw(LPDIRECT3DDEVICE9 p_dx_Device);
	void Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY);
	void Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY, int i, int j);	
};

