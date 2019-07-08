#include "stdAfx.h"
#include "Texture.h"

CTexture::CTexture(void)
{
}

CTexture::CTexture(float fWidth, float fHeight)
{
	WIDTH = fWidth;
	HEIGHT = fHeight;
	generateRectTexture();
}


CTexture::~CTexture(void)
{
}
void CTexture::generateRectTexture()
{
	 DWORD _currentColor = 0xffffffff;
	 pTextureCoords[0].X = 0.0f;
	 pTextureCoords[0].Y = HEIGHT;
     pTextureCoords[0].Z = 0.0f;
     pTextureCoords[0].COLOR = _currentColor;
	 pTextureCoords[0].U = 0.0f;
	 pTextureCoords[0].V = 0.0f;
 
	 pTextureCoords[1].X = WIDTH;
     pTextureCoords[1].Y = 0.0f;
     pTextureCoords[1].Z = 0.0f;
     pTextureCoords[1].COLOR = _currentColor;
	 pTextureCoords[1].U = 1.0f;
	 pTextureCoords[1].V = 1.0f;
 
     pTextureCoords[2].X = 0.0f;
     pTextureCoords[2].Y = 0.0f;
     pTextureCoords[2].Z = 0.0f;
     pTextureCoords[2].COLOR = _currentColor;
	 pTextureCoords[2].U = 0.0f;
	 pTextureCoords[2].V = 1.0f;


     pTextureCoords[3].X = WIDTH;
     pTextureCoords[3].Y = HEIGHT;
     pTextureCoords[3].Z = 0.0f;
     pTextureCoords[3].COLOR = _currentColor;
	 pTextureCoords[3].U = 1.0f;
	 pTextureCoords[3].V = 0.0f;

     pTextureCoords[4].X = WIDTH;
     pTextureCoords[4].Y = 0.0f;
     pTextureCoords[4].Z = 0.0f;
     pTextureCoords[4].COLOR = _currentColor;
	 pTextureCoords[4].U = 1.0f;
	 pTextureCoords[4].V = 1.0f;

	 pTextureCoords[5].X = 0.0f;
     pTextureCoords[5].Y = HEIGHT;
     pTextureCoords[5].Z = 0.0f;
     pTextureCoords[5].COLOR = _currentColor;
	 pTextureCoords[5].U = 0.0f;
	 pTextureCoords[5].V = 0.0f;
}

void CTexture::LoadTexture(LPDIRECT3DDEVICE9 p_dx_Device,LPCWSTR file)
{
	VOID* pVertices;
	D3DXCreateTextureFromFile(p_dx_Device,file, &pTexture);
	p_dx_Device->CreateVertexBuffer(
							6*sizeof(CUSTOMVERTEX), 
							0, 
							CUSTOMFVF, 
							D3DPOOL_DEFAULT, 
							&pVB, 
							NULL );
	pVB->Lock(0, 6*sizeof(CUSTOMVERTEX), (void**)&pVertices, 0);
	memcpy(pVertices, pTextureCoords, 6*sizeof(CUSTOMVERTEX));
	pVB->Unlock();
}
/*
void CTexture::Draw(LPDIRECT3DDEVICE9 p_dx_Device)
{
	Draw(p_dx_Device,X,Y);
}
*/
void CTexture::Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY)
{
	D3DXMATRIX Position;
	p_dx_Device->SetTexture(0, pTexture);
	D3DXMatrixTranslation(&Position, fX - 640,  fY -384, 0.0f);
	p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
	p_dx_Device->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
	p_dx_Device->SetFVF(CUSTOMFVF);
	p_dx_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );
	p_dx_Device->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x0000008f);
	p_dx_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
	p_dx_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	//p_dx_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	//p_dx_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);

	p_dx_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	D3DXMatrixTranslation(&Position, -1280.0f/2,-768.0f/2, 0.0f);
	p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
	p_dx_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); 
}

void CTexture::Draw(LPDIRECT3DDEVICE9 p_dx_Device, float fX, float fY, int n, int m)
{
	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j< m; j++)
		{	
			D3DXMATRIX Position;
			p_dx_Device->SetTexture(0, pTexture);
			D3DXMatrixTranslation(&Position, fX + i*WIDTH- 640,  fY + j*HEIGHT -384, 0.0f);
			p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
			p_dx_Device->SetStreamSource(0, pVB, 0, sizeof(CUSTOMVERTEX));
			p_dx_Device->SetFVF(CUSTOMFVF);
			p_dx_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );
			p_dx_Device->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x0000008f);
			p_dx_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
			p_dx_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
			//p_dx_Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
			//p_dx_Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);

			p_dx_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
			D3DXMatrixTranslation(&Position, -1280.0f/2,-768.0f/2, 0.0f);
			p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
			p_dx_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); 
		}
	}
}