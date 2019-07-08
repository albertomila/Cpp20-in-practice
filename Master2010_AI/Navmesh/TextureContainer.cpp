#include "stdAfx.h"
#include "TextureContainer.h"

TextureContainer::TextureContainer(void)
{
	_bHasTexture = false;
}

TextureContainer::~TextureContainer(void)
{
}

TextureContainer::TextureContainer(float fX, float fY, float fWidth, float fHeight) : _texture(fWidth, fHeight)
{
	X = fX;
	Y =  fY;
	WIDTH = fWidth;
	HEIGHT = fHeight;
	_bHasTexture = false;
}

TextureContainer::TextureContainer(float fX, float fY, float fWidth, float fHeight, float fWidthTexture, float fHeightTexture) : _texture(fWidthTexture, fHeightTexture)
{
	X = fX;
	Y =  fY;
	WIDTH = fWidth;
	HEIGHT = fHeight;
	_bHasTexture = false;
}

bool TextureContainer::PointInside(float fX, float fY)
{
	if(fX >= X && fX <= X + WIDTH && fY >= Y && fY <= Y + HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TextureContainer::LoadTexture(LPDIRECT3DDEVICE9 p_dx_Device,LPCWSTR file)
{
	_texture.LoadTexture(p_dx_Device,file);
	_bHasTexture = true;
}
void TextureContainer::Draw(LPDIRECT3DDEVICE9 p_dx_Device)
{
	if(_bHasTexture)
		_texture.Draw(p_dx_Device,X,Y);
}
void TextureContainer::Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY)
{
	if(_bHasTexture)
	{
		_texture.Draw(p_dx_Device,fX,fY);
	}
}
void TextureContainer::Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY, int n, int m)
{
	if(_bHasTexture)
		_texture.Draw(p_dx_Device,fX,fY,n,m);
}