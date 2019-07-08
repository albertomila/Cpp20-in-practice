#include "stdAfx.h"
#include "CNavmesh.h"

CNavmesh::CNavmesh(void)
{
	_iNumPoints = 0;
}
CNavmesh::CNavmesh(vector<Point2> vListPoints)
{
	_iNumPoints = 0;
	 //_vListPoints2.clear();
	 //_vListPoints = vListPoints;
	if(vListPoints.size() >= 3)
	{		
		//look if the last edges insertions are replied.
		for (int i = 0; i< vListPoints.size(); i++)
		{
			Point* p = new Point(vListPoints[i].X, vListPoints[i].Y);
			if(i ==  vListPoints.size() - 1)
			{
				_vListPoints2.push_back(p);
				for (int j = 0; j< _vListPoints2.size()-1; j++)
				{
					if(	vListPoints[i].X == (int)_vListPoints2[j]->x && vListPoints[i].Y == (int)_vListPoints2[j]->y)
					{
						_vListPoints2.pop_back();
						break;
					}
				}
			}
			else
			{
				_vListPoints2.push_back(p);
			}
		}
		_pCTD = new CDT(_vListPoints2);
	}
	else
	{
		for (int i = 0; i< vListPoints.size(); i++)
		{
			Point* p = new Point(vListPoints[i].X, vListPoints[i].Y);
			_vListPoints2.push_back(p);
		}
	}
	 _currentColor = 0xff000000;
	 /*if(_vListPoints.size()>3)
	 {
		for(int i=0; i<_vListPoints.size()-1;i++)
		{
			if(_vListPoints[i] == _vListPoints[_vListPoints.size()-1])
			{
				_vListPoints.pop_back();
				_currentColor = 0xffffff00;
			}
		}
	 }*/
     _squareVertices[0].x = 0.0f;
     _squareVertices[0].y = 10.0f;
     _squareVertices[0].z = 0.0f;
     _squareVertices[0].color = _currentColor;
 
     _squareVertices[1].x = 10.0f;
     _squareVertices[1].y = 0.0f;
     _squareVertices[1].z = 0.0f;
     _squareVertices[1].color = _currentColor;
 
     _squareVertices[2].x = 0.0f;
     _squareVertices[2].y = 0.0f;
     _squareVertices[2].z = 0.0f;
     _squareVertices[2].color = _currentColor;
 
     _squareVertices[3].x = 10.0f;
     _squareVertices[3].y = 10.0f;
     _squareVertices[3].z = 0.0f;
     _squareVertices[3].color = _currentColor;

     _squareVertices[4].x = 10.0f;
     _squareVertices[4].y = 0.0f;
     _squareVertices[4].z = 0.0f;
     _squareVertices[4].color = _currentColor;

     _squareVertices[5].x = 0.0f;
     _squareVertices[5].y = 10.0f;
     _squareVertices[5].z = 0.0f;
     _squareVertices[5].color = _currentColor;
}
CNavmesh::~CNavmesh(void)
{
}

void CNavmesh::setPoints(vector<Point2> vListPoints)
{
	/*
	for(int i=0; i<vListPoints.size(); i++)
	{
		_vListPoints.push_back(vListPoints[i]);
	}
	*/
	
	 for (int i = 0; i < vListPoints.size(); i++)
	 {
		 Point* p = new Point(_vListPoints[i].X, _vListPoints[i].Y);
		 _vListPoints2.push_back(p);
	 }
	_pCTD = new CDT(_vListPoints2);
}
void CNavmesh::addObstacle(vector<obstacle> obstacles)
{
	_obstacles = obstacles;
	if(obstacles.size()>0)
	{	
		obstacle obs;
		for(int i=0; i<_obstacles.size(); i++)
		{
			obstacle ob = _obstacles[i];
			
				vector<Point*> pObstacle;
				pObstacle.clear();
		
				bool bSamePoint = false;
				for (int i = 0; i< _vListPoints2.size(); i++)
				{
					for(int j=0; j<ob.size(); j++)
					{
						if(	ob[j].X == (int)_vListPoints2[i]->x && ob[j].Y == (int)_vListPoints2[i]->y)
						{
							bSamePoint = true;
							break;
						}
					}
					if(bSamePoint) break;
				}
				if(!bSamePoint)
				{
					bool bAllInside = true;
					for(int j=0; j<ob.size(); j++)
					{
						
						int iX = IsPointInsidePolygon(ob[j]);
						
						if(iX == 0)
						{
							bAllInside = false;
							break;
						}
					}

					if(bAllInside)
					{
						for(int j=0; j<ob.size(); j++)
						{
							Point* p = new Point(ob[j].X, ob[j].Y);
							pObstacle.push_back(p);
						}
						_pCTD->AddHole(pObstacle);
					}
				}
			}
	}
}
void CNavmesh::Update(LPDIRECT3DDEVICE9 p_dx_Device)
{
	VOID* p_Vertices;
	p_dx_Device->CreateVertexBuffer(
								6*sizeof(OURCUSTOMVERTEX), 
								0, 
								D3DFVF_XYZ|D3DFVF_NORMAL, 
								D3DPOOL_DEFAULT, 
								&_pVB, 
								NULL );
	_pVB->Lock(0, 6*sizeof(OURCUSTOMVERTEX), (void**)&p_Vertices, 0);
	memcpy(p_Vertices, _squareVertices, 6*sizeof(OURCUSTOMVERTEX));
	_pVB->Unlock();
	//delete p_Vertices;

	if(_vListPoints2.size() >= 3)
	{
		_pCTD->Triangulate();

		_vListTriangles2.clear();
		_vListTriangles2 = _pCTD->GetTriangles();

		_iNumTriangles =  _vListTriangles2.size();
		_iNumPoints = _vListTriangles2.size() * 3;

		D3DXVECTOR3 *point = new D3DXVECTOR3[_iNumPoints];

		int k = 0;
		for(int i=0; i<_iNumTriangles; i++)
		{
			Triangle* t = _vListTriangles2[i];
			point[k] = D3DXVECTOR3(t->GetPoint(0)->x, t->GetPoint(0)->y, 0);
			k++;
			point[k] = D3DXVECTOR3(t->GetPoint(1)->x, t->GetPoint(1)->y, 0);
			k++;
			point[k] = D3DXVECTOR3(t->GetPoint(2)->x, t->GetPoint(2)->y, 0);
			k++;
		}

		if(_iNumPoints > 0)
		{
			p_dx_Device->CreateVertexBuffer(
										_iNumPoints*sizeof(OURCUSTOMVERTEX),
                       					0, 
										D3DFVF_XYZ|D3DFVF_NORMAL,
                       					D3DPOOL_DEFAULT, 
										&_pVBTriangles,
										NULL );

			// Bloquer la "mémoire du dispositif" et obtenir un pointeur sur le VB

			OURCUSTOMVERTEX* sommets = new OURCUSTOMVERTEX[_iNumPoints];
			_pVBTriangles->Lock(0,0, (void**)&sommets, 0 );
			for (int i=0;i<_iNumPoints;i++)
			{
				sommets[i].x = point[i].x;
				sommets[i].y = point[i].y;
				sommets[i].z = point[i].z;
				sommets[i].color = _currentColor;
			}
			// Relâcher le VB
			_pVBTriangles->Unlock();

			//delete[] point;
			//delete[] sommets;
		}
	}
 }
	

void CNavmesh::Draw(LPDIRECT3DDEVICE9 p_dx_Device)
{
	D3DXMATRIX Position;
	ZeroMemory( &_materiau, sizeof(D3DMATERIAL9) );
	_materiau.Ambient.r = 0.0f; 
	_materiau.Ambient.g = 1.0f; 
	_materiau.Ambient.b = 0.0f; 
	_materiau.Ambient.a = 1.0f; 

	if(_iNumPoints >= 3)
	{
		p_dx_Device->SetMaterial(&_materiau);
		// Source des sommets
		p_dx_Device->SetStreamSource( 0, _pVBTriangles, 0, sizeof(OURCUSTOMVERTEX) );

		// Type des sommets
		p_dx_Device->SetFVF( D3DFVF_XYZ| D3DFVF_DIFFUSE);

		// Affichage
		p_dx_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME );
		p_dx_Device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, _iNumTriangles);
	
		//delete _pVBTriangles;
	}
	
	for(int i=0; i<_vListTriangles2.size();i++)
	{
		_vListTriangles2[i]->SetMiddlePoint();
		D3DXMatrixTranslation(&Position, _vListTriangles2[i]->GetMiddlePoint()->x - 640 - 5,  _vListTriangles2[i]->GetMiddlePoint()->y -384 - 5, 0.0f);
		p_dx_Device->SetTransform(D3DTS_WORLD, &Position);

		p_dx_Device->SetStreamSource(0, _pVB, 0, sizeof(OURCUSTOMVERTEX));
		p_dx_Device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
		p_dx_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );
		p_dx_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		D3DXMatrixTranslation(&Position, -1280.0f/2,-768.0f/2, 0.0f);
		p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
		
		//delete _vListTriangles2[i];
	}
	for(int i=0; i<_vListPoints2.size();i++)
	{
		D3DXMatrixTranslation(&Position, _vListPoints2[i]->x - 640 - 5,  _vListPoints2[i]->y -384 - 5, 0.0f);
		p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
		
		 p_dx_Device->SetStreamSource(0, _pVB, 0, sizeof(OURCUSTOMVERTEX));
		 p_dx_Device->SetFVF(D3DFVF_XYZ|D3DFVF_DIFFUSE);
		 p_dx_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );
		 p_dx_Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		
		D3DXMatrixTranslation(&Position, -1280.0f/2,-768.0f/2, 0.0f);
		p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
		
		//delete _vListPoints2[i];
		//delete _pVB;
	}
	
}

vector<Triangle*> CNavmesh::GetMesh()
{
	return _vListTriangles2;
}
int CNavmesh::IsPointInsidePolygon (Point2 center)
{
	vector<Point*> p = _vListPoints2;
	/*
	for(int j=0; j<_obstacles.size(); j++)
	{
		obstacle ob = _obstacles[j];
		for(int k=0; k<ob.size(); k++)
		{
			Point2 pnt = ob[k];
			for (int i = p.size()-1; i >= 0; i--)
			{
				if(pnt == p[i])
				{
					p.erase(p.begin() + i);
				}
			}
		}
	}
	*/

	int i1, i2, n, N, S, S1, S2, S3;
	int flag = 0;
	N = p.size();
	for (n=0; n<N; n++)
	{
		flag = 0;
		i1 = (n < N-1) ? (n + 1) : 0;
		while (flag == 0)
		{
			i2 = i1 + 1;
			if (i2 >= N) i2 = 0;
			if (i2 == (n < N-1 ? n + 1 : 0)) break;

			S =  abs (p[i1]->x* (p[i2]->y - p[n ]->y) + p[i2]->x * (p[n ]->y - p[i1]->y) + p[n]->x  * (p[i1]->y - p[i2]->y));
			S1 = abs (p[i1]->x * (p[i2]->y - center.Y) + p[i2]->x * (center.Y- p[i1]->y) + center.X * (p[i1]->y - p[i2]->y));
			S2 = abs (p[n ]->x * (p[i2]->y- center.Y) + p[i2]->x * (center.Y - p[n ]->y) + center.X * (p[n ]->y - p[i2]->y));
			S3 = abs (p[i1]->x * (p[n ]->y - center.Y) + p[n ]->x * (center.Y       - p[i1]->y) + center.X * (p[i1]->y - p[n ]->y));
			if (S == S1 + S2 + S3)
			{
				flag = 1;
				break;
			}
			i1 = i1 + 1;
			if (i1 >= N) i1 = 0;
		}
		if (flag == 0)
		break;
	}
	return flag;
}


/*
void CNavmesh::Triangulate() throw()
{
	int nv = _vListPoints.size();
	if (nv < 3)
	{
		throw;
	}

	//create the supertriangle
	float xmin = _vListPoints[0].X;
	float ymin = _vListPoints[0].Y;
	float xmax = xmin;
	float ymax = ymin;
	for (int i = 1; i < nv; i++)
	{
		if (_vListPoints[i].X < xmin) xmin = _vListPoints[i].X;
		if (_vListPoints[i].X > xmax) xmax = _vListPoints[i].X;
		if (_vListPoints[i].Y < ymin) ymin = _vListPoints[i].Y;
		if (_vListPoints[i].Y > ymax) ymax = _vListPoints[i].Y;
	}
	float dx = xmax - xmin;
	float dy = ymax - ymin;
	float dmax = (dx > dy) ? dx : dy;
	float xmid = (xmax + xmin) * 0.5;
	float ymid = (ymax + ymin) * 0.5;

	_vListPoints.push_back(Point2((xmid - 2 * dmax),(ymid - dmax)));
	_vListPoints.push_back(Point2(xmid,				(ymid + 2 * dmax)));
	_vListPoints.push_back(Point2((xmid + 2 * dmax),(ymid - dmax) ));
	_vListTriangles.push_back(CTriangle(nv, nv + 1, nv + 2)); //SuperTriangle placed at index 0
	
	for (int i = 0; i < nv; i++)
	{
		_vListEdges.clear();
		//for each point loook if are inside of each triangle 
		for (int j = 0; j < _vListTriangles.size(); j++)
		{
				if (InCircle(
					_vListPoints[i], 
					_vListPoints[_vListTriangles[j].p1], 
					_vListPoints[_vListTriangles[j].p2], 
					_vListPoints[_vListTriangles[j].p3]))
				{
					//then push de edges of the tree points of the triangle that belongs
					_vListEdges.push_back(CEdge(_vListTriangles[j].p1, _vListTriangles[j].p2));
					_vListEdges.push_back(CEdge(_vListTriangles[j].p2, _vListTriangles[j].p3));
					_vListEdges.push_back(CEdge(_vListTriangles[j].p3, _vListTriangles[j].p1));
					_vListTriangles.erase(_vListTriangles.begin() + j);
					j--;
				}
		}
		
		//look if the last edges insertions are replied.
		for (int j = _vListEdges.size() - 2; j >= 0; j--)
		{
			for (int k = _vListEdges.size() - 1; k > j; k--)
			{
				if (_vListEdges[j] == _vListEdges[k])
				{
					_vListEdges.erase(_vListEdges.begin() + k);
					_vListEdges.erase(_vListEdges.begin() + j);
					k--;
				}
			}
		}
		
		for (int j = 0; j < _vListEdges.size(); j++)
		{
			_vListTriangles.push_back( CTriangle( _vListEdges[j].p1, _vListEdges[j].p2, i));
		}
	}

	//delete triangles linked to supertriangle
	for (int i = _vListTriangles.size() - 1; i >= 0; i--)
	{
		if (_vListTriangles[i].p1 >= nv || _vListTriangles[i].p2 >= nv ||_vListTriangles[i].p3 >= nv)
		{
			_vListTriangles.erase(_vListTriangles.begin() + i);
		}
	}
	//delete points of supertriangle
	_vListPoints.erase(_vListPoints.begin() + _vListPoints.size() - 1);
	_vListPoints.erase(_vListPoints.begin() + _vListPoints.size() - 1);
	_vListPoints.erase(_vListPoints.begin() + _vListPoints.size() - 1);

	
	
	bool bDeleted = true;
	while(bDeleted)
	{
		bDeleted = false;
		for (int k = 0; k < _vListTriangles.size(); k++)
		{
			Point2 p1 = _vListPoints[_vListTriangles[k].p1];
			Point2 p2 = _vListPoints[_vListTriangles[k].p2];
			Point2 p3 = _vListPoints[_vListTriangles[k].p3];
			
			float fMidX = ((float)p1.X + (float)p2.X + (float)p3.X) / 3.0f;
			float fMidY = ((float)p1.Y + (float)p2.Y + (float)p3.Y) / 3.0f;
			Point2 center = Point2(fMidX,fMidY);

			int iX = IsPointInsidePolygon(center);
			
			if(iX == 0)
			{
				_vListTriangles.erase(_vListTriangles.begin() + k);
				bDeleted = true;
				break;
			}
		}
	}

	bDeleted = true;
	while(bDeleted)
	{
		bDeleted = false;
		for (int i = 0; i < _vListTriangles.size(); i++)
		{
			Point2 p1 = _vListPoints[_vListTriangles[i].p1];
			Point2 p2 = _vListPoints[_vListTriangles[i].p2];
			Point2 p3 = _vListPoints[_vListTriangles[i].p3];

			for(int j=0; j<_obstacles.size(); j++)
			{
				obstacle ob = _obstacles[j];

				int iCountEquals = 0;

				for(int k=0; k<ob.size(); k++)
				{
					Point2 p = ob[k];
					if(p == p1 || p== p2 || p == p3)
					{
						iCountEquals++;
					}
				}
				if(iCountEquals == 3)
				{
					_vListTriangles.erase(_vListTriangles.begin() + i);
					bDeleted = true;
					break;
				}
			}
			if(bDeleted) break;
		}
	}
}

bool CNavmesh::InCircle(Point2 p, Point2 p1, Point2 p2, Point2 p3)
{
	float m1, m2;
	float mx1, mx2;
	float my1, my2;
	float xc, yc;
				
	if (abs((float)p2.Y - (float)p1.Y) < 0.0001f)
	{
		m2 = -((float)p3.X - (float)p2.X) / ((float)p3.Y - (float)p2.Y);
		mx2 = ((float)p2.X + (float)p3.X) * 0.5;
		my2 = ((float)p2.Y + (float)p3.Y) * 0.5;
		//Calculate CircumCircle center (xc,yc)
		xc = ((float)p2.X + (float)p1.X) * 0.5;
		yc = m2 * (xc - mx2) + my2;
	}
	else if (abs((float)p3.Y - (float)p2.Y) < 0.0001f)
	{
		m1 = -((float)p2.X - (float)p1.X) / ((float)p2.Y - (float)p1.Y);
		mx1 = ((float)p1.X + (float)p2.X) * 0.5;
		my1 = ((float)p1.Y + (float)p2.Y) * 0.5;
		//Calculate CircumCircle center (xc,yc)
		xc = ((float)p3.X + (float)p2.X) * 0.5;
		yc = m1 * (xc - mx1) + my1;
	}
	else
	{
		m1 = -((float)p2.X - (float)p1.X) / ((float)p2.Y - (float)p1.Y);
		m2 = -((float)p3.X - (float)p2.X) / ((float)p3.Y - (float)p2.Y);
		mx1 = ((float)p1.X + (float)p2.X) * 0.5;
		mx2 = ((float)p2.X + (float)p3.X) * 0.5;
		my1 = ((float)p1.Y + (float)p2.Y) * 0.5;
		my2 = ((float)p2.Y + (float)p3.Y) * 0.5;
		//Calculate CircumCircle center (xc,yc)
		xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
		yc = m1 * (xc - mx1) + my1;
	}

	float dx = p2.X - xc;
	float dy = p2.Y - yc;
	float rsqr = dx * dx + dy * dy;

	dx = p.X - xc;
	dy = p.Y - yc;
	float drsqr = dx * dx + dy * dy;

	return (drsqr <= rsqr);
}


*/