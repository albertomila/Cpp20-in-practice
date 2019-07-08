#include "stdAfx.h"
#include "SelectItem.h"

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include <vector>
CSelectItem::CSelectItem(void)
{     
	_bVisible = true;
	_bReset = false;
	_iStateInterface = 0;
	_iMouseState = 0;
	_iSelectedAlgorithm = 0;
	//_TextureInterfaceBase = TextureContainer(0,0,300,1050);
	_TextureInterfaceBase = TextureContainer(0,0,219,768);
	_TextureReset = TextureContainer(150,600,60,20);
	_TextureInfo1 = TextureContainer(15,455,187,94);
	_TextureInfo2 = TextureContainer(15,455,187,94);
	_TextureSelectAlgorithm = TextureContainer(60,80,8,8);

	_TextureObstacle1 = TextureContainer(20,250,	117,61,		117,61);
	_TextureObstacle2 = TextureContainer(20,330,	78, 61,		78,61);
	_TextureObstacle3 = TextureContainer(100,330,	47, 59,		47, 59);
	_TextureObstacle4 = TextureContainer(150,330,	47, 59,		47, 59);

	_TextureLink = TextureContainer(40,150,16*2,32*2);
	_TexturePower = TextureContainer(130,150,16*2,16*2);
	_TextureGround = TextureContainer(0,0,256*2,256*2);
	
	_TextureAlgBreadFirst		= TextureContainer(70,80,117,15);
	_TextureAlgDeepFirst		= TextureContainer(70,63,117,15);
	_TextureAlgBidirectional	= TextureContainer(70,46,117,15);
	_TextureAlgAStar			= TextureContainer(70,29,117,15);
	_TextureAlgGreedy			= TextureContainer(70,12,117,15);
	
	_TextureMap1				= TextureContainer(23,650,50,50);
	_TextureMap2				= TextureContainer(88,650,50,50);
	_TextureMap3				= TextureContainer(150,650,50,50);
	_iSelectedMap = -1;
}

CSelectItem::~CSelectItem(void)
{
}

void CSelectItem::SetStateInterfae(int iState)
{
	_iStateInterface = iState;
}
void CSelectItem::InitTexture(LPDIRECT3DDEVICE9 p_dx_Device)
{
	_TextureInterfaceBase.LoadTexture(p_dx_Device,L"./Assets/Textures/interface.png");

	_TextureObstacle1.LoadTexture(p_dx_Device,L"./Assets/Textures/obstacle_house1.png");
	_TextureObstacle2.LoadTexture(p_dx_Device,L"./Assets/Textures/obstacle_house2.png");
	_TextureObstacle3.LoadTexture(p_dx_Device,L"./Assets/Textures/obstacle_tree1.png");
	_TextureObstacle4.LoadTexture(p_dx_Device,L"./Assets/Textures/obstacle_tree2.png");

	_TextureInfo1.LoadTexture(p_dx_Device,L"./Assets/Textures/info1.png");
	_TextureInfo2.LoadTexture(p_dx_Device,L"./Assets/Textures/info2.png");
	_TextureLink.LoadTexture(p_dx_Device,L"./Assets/Textures/zeldabase.png");
	_TexturePower.LoadTexture(p_dx_Device,L"./Assets/Textures/power.png");
	_TextureGround.LoadTexture(p_dx_Device,L"./Assets/Textures/ground.png");
	_TextureSelectAlgorithm.LoadTexture(p_dx_Device,L"./Assets/Textures/select_algorithm.png");

}
void CSelectItem::Draw(LPDIRECT3DDEVICE9 p_dx_Device)
{
	_TextureGround.Draw(p_dx_Device, _TextureGround.X, _TextureGround.Y, 4,3);
	_TextureInterfaceBase.Draw(p_dx_Device);
	_TextureReset.Draw(p_dx_Device);
	_TextureSelectAlgorithm.Draw(p_dx_Device);

	switch(_iStateInterface)
	{
		case 0:
			_TextureInfo1.Draw(p_dx_Device);
			break;
		case 1:
			_TextureInfo2.Draw(p_dx_Device);
			if(_bVisible)
			{
				_TextureObstacle1.Draw(p_dx_Device);
				_TextureObstacle2.Draw(p_dx_Device);
				_TextureObstacle3.Draw(p_dx_Device);
				_TextureObstacle4.Draw(p_dx_Device);
				_TextureLink.Draw(p_dx_Device);
				_TexturePower.Draw(p_dx_Device);
				for(int i=0; i<_vElements.size(); i++)
				{
					switch(_vElements[i].type)
					 {
						 case 0:
							 _TextureObstacle1.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
							break;
						 case 1:
							 _TextureObstacle2.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
							break;
						 case 2:
							 _TextureObstacle3.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
							break;
						 case 3:
							 _TextureObstacle4.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
							break;
					 }
				}
			}
			break;
		case 2:
				_TextureLink.Draw(p_dx_Device, _pStartPoint->x, _pStartPoint->y);
		case 3:
			_TextureInfo1.Draw(p_dx_Device);
			for(int i=0; i<_vElements.size(); i++)
			{
				switch(_vElements[i].type)
				 {
				case 0:
					_TextureObstacle1.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
					break;
				case 1:
					_TextureObstacle2.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
					break;
				case 2:
					_TextureObstacle3.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
					break;
				case 3:
					_TextureObstacle4.Draw(p_dx_Device, _vElements[i].p.X,  _vElements[i].p.Y);
					break;
				 }
			}
			break;
	}
}

void CSelectItem::SetReset(bool bReset)
{
	_bReset = bReset;
}
bool CSelectItem::GetReset()
{
	return _bReset;
}
void CSelectItem::MouseEventNavMesh(UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
{
	 int iX = GET_X_LPARAM(parameter2);
	 int iY = -GET_Y_LPARAM(parameter2) + 768;
	 switch(uint_Message)
	 {
		 case WM_LBUTTONDOWN: 

			 if(_TextureMap1.PointInside(iX, iY))
			 {
				 _iSelectedMap = 0;
			 }
			 else if(_TextureMap2.PointInside(iX, iY))
			 {
				 _iSelectedMap = 1;
			 }
			 else if(_TextureMap3.PointInside(iX, iY))
			 {
				 _iSelectedMap = 2;
			 }
			 if(_TextureReset.PointInside(iX, iY))
			 {
				 _bReset = true;
			 }
			 break;
	 }
}
void CSelectItem::MouseEventPutItems(UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
{
	 int iX = GET_X_LPARAM(parameter2);
	 int iY = -GET_Y_LPARAM(parameter2) + 768;

	switch(uint_Message)
	{
			 case WM_LBUTTONDOWN: 
				 if(_TextureObstacle1.PointInside(iX, iY))
				 {
					_iMouseState = 1;
					_iTypeItemSelected = 0;
				 }
				 else if(_TextureObstacle2.PointInside(iX, iY))
				 {
					_iMouseState = 1;
					_iTypeItemSelected = 1;
				 }
				 else if(_TextureObstacle3.PointInside(iX, iY))
				 {
					_iMouseState = 1;
					_iTypeItemSelected = 2;
				 }
				 else if(_TextureObstacle3.PointInside(iX, iY))
				 {
					_iMouseState = 1;
					_iTypeItemSelected = 2;
				 }
				 else if(_TextureObstacle4.PointInside(iX, iY))
				 {
					_iMouseState = 1;
					_iTypeItemSelected = 3;
				 }
				 else if(_TextureLink.PointInside(iX,iY))
				 {
					_iMouseState = 1;
					_iTypeItemSelected = 4;
				 }
				 else if(_TexturePower.PointInside(iX,iY))
				 {
					_iMouseState = 1;
					_iTypeItemSelected = 5;
				 }
				 else if(_TextureAlgBreadFirst.PointInside(iX, iY))
				 {
					 _iSelectedAlgorithm = 0;
					 _TextureSelectAlgorithm.Y = 80 - 16*_iSelectedAlgorithm;

				 }
				 else if(_TextureAlgDeepFirst.PointInside(iX, iY))
				 {
					 _iSelectedAlgorithm = 1;
					 _TextureSelectAlgorithm.Y = 80 - 16*_iSelectedAlgorithm;
				 }
				 else if(_TextureAlgBidirectional.PointInside(iX, iY))
				 {
					 _iSelectedAlgorithm = 2;
					 _TextureSelectAlgorithm.Y = 80 - 16*_iSelectedAlgorithm;
				 }
				 else if(_TextureAlgAStar.PointInside(iX, iY))
				 {
					 _iSelectedAlgorithm = 3;
					 _TextureSelectAlgorithm.Y = 80 - 16*_iSelectedAlgorithm;
				 }
				 else if(_TextureAlgGreedy.PointInside(iX, iY))
				 {
					 _iSelectedAlgorithm = 4;
					 _TextureSelectAlgorithm.Y = 80 - 16*_iSelectedAlgorithm;
				 }
				 else if(_TextureMap1.PointInside(iX, iY))
				 {
					 _iSelectedMap = 0;
				 }
				 else if(_TextureMap2.PointInside(iX, iY))
				 {
					 _iSelectedMap = 1;
				 }
				 else if(_TextureMap3.PointInside(iX, iY))
				 {
					 _iSelectedMap = 2;
				 }
				 if(_TextureReset.PointInside(iX, iY))
				 {
					 _bReset = true;
				 }

				 

				 break;
			 case WM_MOUSEMOVE: 
				 if(_iMouseState == 1)
				 {
					 _iMouseState = 2;
					 ITEM it;
					 it.p = Point2(iX,iY);
					 obstacle ob;
					 switch(_iTypeItemSelected)
					 {
						 case 0:
							 it.type = 0;
							 _vElements.push_back(it);							 
							 ob.push_back(Point2(iX,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle1.WIDTH,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle1.WIDTH,iY + (int)_TextureObstacle1.HEIGHT));
							 ob.push_back(Point2(iX,iY + (int)_TextureObstacle1.HEIGHT));
							 break;
						 case 1:
							 it.type = 1;
							 _vElements.push_back(it);							 
							 ob.push_back(Point2(iX,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle2.WIDTH,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle2.WIDTH,iY + (int)_TextureObstacle2.HEIGHT));
							 ob.push_back(Point2(iX,iY + (int)_TextureObstacle2.HEIGHT));
							 break;
						 case 2:
							 it.type = 2;
							 _vElements.push_back(it);							 
							 ob.push_back(Point2(iX,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle3.WIDTH,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle3.WIDTH,iY + (int)_TextureObstacle3.HEIGHT));
							 ob.push_back(Point2(iX,iY + (int)_TextureObstacle3.HEIGHT));
							 break;
						 case 3:
							 it.type = 3;
							 _vElements.push_back(it);							 
							 ob.push_back(Point2(iX,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle4.WIDTH,iY));
							 ob.push_back(Point2(iX + (int)_TextureObstacle4.WIDTH,iY + (int)_TextureObstacle4.HEIGHT));
							 ob.push_back(Point2(iX,iY + (int)_TextureObstacle4.HEIGHT));
							 break;
						 case 4:
							 _TextureLink.X = iX;
							 _TextureLink.Y = iY;
							 break;
						 case 5:
							 _TexturePower.X = iX;
							 _TexturePower.Y = iY;
							 break;
					 }
					 _obstacles.push_back(ob);

				 }
				 else if(_iMouseState == 2)
				 {
					int iIntersectOtherObstacle = -1;
					int m = _obstacles.size()-1;
					obstacle ob =_obstacles[m];
					
					int iXMax1 = 0;
					int iXMin1 = 100000;
					int iYMax1 = 0;
					int iYMin1 = 100000;
					int iWidth = 0;
					int iHeight = 0;
					for(int k=0; k<ob.size(); k++)
					{
							if(ob[k].X > iXMax1) iXMax1 = ob[k].X;
							if(ob[k].X < iXMin1) iXMin1 = ob[k].X;
							if(ob[k].Y > iYMax1) iYMax1 = ob[k].Y;
							if(ob[k].Y < iYMin1) iYMin1 = ob[k].Y;
					}
					iWidth  =iXMax1 - iXMin1;
					iHeight  =iYMax1 - iYMin1;

					for(int j=0; j<_obstacles.size()-1; j++)
					{			
						int iXMax = 0;
						int iXMin = 100000;
						int iYMax = 0;
						int iYMin = 100000;	
						for(int k=0; k<_obstacles[j].size(); k++)
						{
							if(_obstacles[j][k].X > iXMax) iXMax = _obstacles[j][k].X;
							if(_obstacles[j][k].X < iXMin) iXMin = _obstacles[j][k].X;
							if(_obstacles[j][k].Y > iYMax) iYMax = _obstacles[j][k].Y;
							if(_obstacles[j][k].Y < iYMin) iYMin = _obstacles[j][k].Y;
						}

						if( ((iXMax1 >= iXMin && iXMax1 <= iXMax) || (iXMin1 >= iXMin && iXMin1 <= iXMax)) && 
							((iYMax1 >= iYMin && iYMax1 <= iYMax) || (iYMin1 >= iYMin && iYMin1 <= iYMax)))
						{
							if((iXMin1 >= iXMin && iXMin1 <= iXMax))
							{
								iX = iXMax + 1;
							}
							else if((iXMax1 >= iXMin && iXMax1 <= iXMax))
							{
								iX = iXMin - iWidth - 1;
							}
							else if((iYMin1 >= iYMin && iYMin1 <= iYMax))
							{
								iY = iYMax + 1;
							}
							else if((iYMax1 >= iYMin && iYMax1 <= iYMax))
							{
								iY = iYMin - iHeight - 1;
							}
						}
					}

					int n = ob.size();
					switch(_iTypeItemSelected)
					{
					case 0:
						_vElements[_vElements.size()-1].p = Point2(iX,iY);
						_obstacles[m][n-4] = Point2(iX,iY);
						_obstacles[m][n-3] = Point2(iX + (int)_TextureObstacle1.WIDTH,iY);
						_obstacles[m][n-2] = Point2(iX + (int)_TextureObstacle1.WIDTH,iY + (int)_TextureObstacle1.HEIGHT);
						_obstacles[m][n-1] = Point2(iX,iY + (int)_TextureObstacle1.HEIGHT);
						break;
					case 1:
						_vElements[_vElements.size()-1].p = Point2(iX,iY);
						_obstacles[m][n-4] = Point2(iX,iY);
						_obstacles[m][n-3] = Point2(iX + (int)_TextureObstacle2.WIDTH,iY);
						_obstacles[m][n-2] = Point2(iX + (int)_TextureObstacle2.WIDTH,iY + (int)_TextureObstacle2.HEIGHT);
						_obstacles[m][n-1] = Point2(iX,iY + (int)_TextureObstacle2.HEIGHT);
						break;
					case 2:
						_vElements[_vElements.size()-1].p = Point2(iX,iY);
						_obstacles[m][n-4] = Point2(iX,iY);
						_obstacles[m][n-3] = Point2(iX + (int)_TextureObstacle3.WIDTH,iY);
						_obstacles[m][n-2] = Point2(iX + (int)_TextureObstacle3.WIDTH,iY + (int)_TextureObstacle3.HEIGHT);
						_obstacles[m][n-1] = Point2(iX,iY + (int)_TextureObstacle3.HEIGHT);
						break;
					case 3:
						_vElements[_vElements.size()-1].p = Point2(iX,iY);
						_obstacles[m][n-4] = Point2(iX,iY);
						_obstacles[m][n-3] = Point2(iX + (int)_TextureObstacle4.WIDTH,iY);
						_obstacles[m][n-2] = Point2(iX + (int)_TextureObstacle4.WIDTH,iY + (int)_TextureObstacle4.HEIGHT);
						_obstacles[m][n-1] = Point2(iX,iY + (int)_TextureObstacle4.HEIGHT);
						break;
					case 4:
						_TextureLink.X = iX;
						_TextureLink.Y = iY;
						break;
					case 5:
						_TexturePower.X = iX;
						_TexturePower.Y = iY;
						break;
					}
				 }
				 break;
			 case WM_LBUTTONUP: 
				 _iMouseState = 0;
				/* if(_obstacles.size() >= 4)
				 {
					_iStateInterface = 2;
				 }*/
				 break;
			 case WM_RBUTTONUP:
				 _bVisible = !_bVisible;
				 break;
	}
}
void CSelectItem::MouseEventPutStartPoint(UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
{
	 int iX = GET_X_LPARAM(parameter2);
	 int iY = -GET_Y_LPARAM(parameter2) + 768;
	switch(uint_Message)
	{
		 case WM_LBUTTONDOWN: 
			 _iMouseState = 1;
			 break;
		 case WM_LBUTTONUP: 
			if(	 _iMouseState ==1)
			{
				//_pStartPoint = new Point((float)iX, (float)iY);
				_iStateInterface = 3;
				_iMouseState = 0;
			}
			break;
	}
}
void CSelectItem::MouseEventPutEndPoint(UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
{
	 int iX = GET_X_LPARAM(parameter2);
	 int iY = -GET_Y_LPARAM(parameter2) + 768;
	switch(uint_Message)
	{
		 case WM_LBUTTONDOWN: 
			 _iMouseState = 1;
			 break;
		 case WM_MOUSEMOVE: 
			 if( _iMouseState == 0)
			 {
				// _pEndPoint = new Point((float)iX, (float)iY);
				_iStateInterface = 4;
			 }
			 break;
		 case WM_LBUTTONUP: 
			if(	 _iMouseState ==1)
			{
				//_pEndPoint = new Point((float)iX, (float)iY);
				_iStateInterface = 4;
				_iMouseState = 2;
			}
			break;
	}
}

void CSelectItem::OurWindowProcedure(UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
{
	 
	 switch(_iStateInterface)
	 {
		 case 0:
			 MouseEventNavMesh(uint_Message, parameter1, parameter2);
			 break;
		 case 1:
			 MouseEventPutItems(uint_Message, parameter1, parameter2);
			 break;
		/* case 2:
			 MouseEventPutStartPoint(uint_Message, parameter1, parameter2);
			 break;
		 case 3:
		 case 4:
			 MouseEventPutEndPoint(uint_Message, parameter1, parameter2);
			 break;*/
	 }
}

vector<obstacle> CSelectItem::GetObstacles()
{
	return _obstacles;
}

int CSelectItem::GetState()
{
	return _iStateInterface;
}
Point* CSelectItem::GetStartPoint()
{
	return new Point(_TextureLink.X, _TextureLink.Y);
}
Point* CSelectItem::GetEndPoint()
{
	return new Point(_TexturePower.X, _TexturePower.Y);
}

int CSelectItem::GetSelectedAlgorithm()
{
	return _iSelectedAlgorithm;
}
int CSelectItem::GetSelectedMap()
{
	int iMap = _iSelectedMap;
	_iSelectedMap = -1;
	return iMap;
}

void CSelectItem::SetObstacles(vector<obstacle> obstacles)
{
	/*string s ="";
	for(int i=0; i<_obstacles.size(); i++)
	{
		for(int j=0; j<_obstacles[j].size(); j++)
		{
			s+= "ob.push_back(Point2(";
			std::stringstream out;
			out << _obstacles[i][j].X;
			s += out.str();

			s+= ",";
			std::stringstream out2;
			out2 << _obstacles[i][j].Y;
			s += out2.str();
			s+= "));";
		}
		
		s+= "obstacles.push_back(ob);";
		s+= "ob.clear();";
	}*/

	_obstacles = obstacles;
}
void CSelectItem::SetObstaclesTypes(vector<ITEM> vElements)
{
	_vElements = vElements;
}

