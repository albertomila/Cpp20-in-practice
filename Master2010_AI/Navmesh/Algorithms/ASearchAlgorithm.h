#pragma once
#include<vector>
#include<d3d9.h> 
#include<d3dx9.h> 
#include "CStructures.h"
#include "poly2tri/poly2tri.h"
#include "stdAfx.h"
using namespace std;
using namespace p2t;

class ASearchAlgorithm
{
protected:
	typedef vector<Point*>	node;
	vector<node>		_vTree;
	vector<Triangle*>	_vListTriangles;
	Point*				_pPosInit;
	Point*				_pPosEnd;
	vector<Point*>		_vListTargets;
	vector<Triangle*>	_vTrianglePath;
	
	IDirect3DVertexBuffer9* _pVB;
	IDirect3DVertexBuffer9* _pVBTriangles;
	OURCUSTOMVERTEX			_squareVertices[6];
	D3DMATERIAL9			_materiau;
	DWORD					_currentColor;
	D3DXVECTOR2* lines;
	vector<Point*>			_vListLines;

	int						_iNumTriangles;
	int						_iNumPoints;

public:
	~ASearchAlgorithm(void);
	void SetMesh(vector<Triangle*>	vListTriangles);
	void SetPosInit(Point* pPosInit);	
	void SetDestinyTargets(vector<Point*> vListTargets);
	void SetEndPoint(Point* pPosEnd);
	vector<Triangle*> GetPath();
	virtual Triangle* GetSearchPath(Triangle* pTriangleInit, Triangle* pTriangleEnd) = 0;
	void Draw(LPDIRECT3DDEVICE9 pDXDevice);
	void Update(LPDIRECT3DDEVICE9 p_dx_Device);
};
