#pragma once

#include<windows.h> 
#include <windowsx.h>


class OURCUSTOMVERTEX
{
public:
     float x,y,z;
     DWORD color;
};

class Point2
{
public:
	 int X;
	 int Y;
	 Point2()
	 {
		X = 0;
		Y = 0;
	 }
	 Point2(int x, int y)
	 {
		X = x;
		Y = y;
	 }
	 Point2(float x, float y)
	 {
		X = (int)x;
		Y = (int)y;
	 }
	 bool operator == (const Point2& p)
	 {
		 return X==p.X && Y==p.Y;
	 }
	 bool operator != (const Point2& p)
	 {
		 return X!=p.X || Y!=p.Y;
	 }
};

class CEdge
{
public:
	 int p1;
	 int p2;
	 CEdge(int P1, int P2)
	 {
		p1 = P1;
		p2 = P2;
	 }
	 bool operator == (const CEdge& e)
	 {
		 return (p1 == e.p1 && p2 == e.p2) || (p1 == e.p2 && p2 == e.p1);
	 }
};

class CTriangle
{
public:
	 int p1;
	 int p2;
	 int p3;
	 bool b;

	 CTriangle(int P1, int P2, int P3)
	 {
		p1 = P1;
		p2 = P2;
		p3 = P3;
	 }
};


struct SOMMETMESH
{
	D3DXVECTOR3 position; // Les coordonnées 3-D du sommet.
	SOMMETMESH(){};
	SOMMETMESH(D3DXVECTOR3 _position);
};

// Description FVF, de notre type de vecteur
#define D3DFVF_SOMMETMESH (D3DFVF_XYZ|D3DFVF_NORMAL)

inline SOMMETMESH::SOMMETMESH(D3DXVECTOR3 _position)
{
	position = _position;
}

struct ITEM{ Point2 p; int type;};