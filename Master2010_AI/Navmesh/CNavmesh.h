#pragma once
#include<windows.h> 
#include <windowsx.h>
#include<d3d9.h> 
#include<d3dx9.h> 
#include<vector>
#include "CStructures.h"
#include "./poly2tri/poly2tri.h"
using namespace std;
using namespace p2t;

class CNavmesh
{
	CDT*						_pCTD;
	typedef vector<Point2>	obstacle;
	vector<obstacle>		_obstacles;
	vector<Point2>			_vListPoints;	
	vector<Point*>			_vListPoints2;
	vector<CTriangle>		_vListTriangles;	
	vector<Triangle*>		_vListTriangles2;
	vector<CEdge>			_vListEdges;
	IDirect3DVertexBuffer9* _pVB;
	IDirect3DVertexBuffer9* _pVBTriangles;
	OURCUSTOMVERTEX			_squareVertices[6];
	D3DMATERIAL9			_materiau;
	DWORD					_currentColor;

	int						_iNumTriangles;
	int						_iNumPoints;

public:
	CNavmesh(void);
	CNavmesh(vector<Point2> vListPoints);
	~CNavmesh(void);
	void setPoints(vector<Point2> obstacles);
	void addObstacle(vector<obstacle> vListPoints);
	void Update(LPDIRECT3DDEVICE9 p_dx_Device);
	void Draw(LPDIRECT3DDEVICE9 p_dx_Device);
	void Triangulate() throw();
	bool InCircle(Point2 p, Point2 p1, Point2 p2, Point2 p3);
	int IsPointInsidePolygon(Point2 center);
	vector<Triangle*> GetMesh();
};
