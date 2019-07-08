#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CStructures.h"
#include<vector>
#include "Texture.h"
#include "TextureContainer.h"
#include "./poly2tri/poly2tri.h"
using namespace std;
using namespace p2t;

typedef vector<Point2> obstacle;
class CSelectItem
{
	TextureContainer			_TextureInterfaceBase;
	TextureContainer			_TextureInfo1;
	TextureContainer			_TextureInfo2;
	TextureContainer			_TextureObstacle1;
	TextureContainer			_TextureObstacle2;
	TextureContainer			_TextureObstacle3;
	TextureContainer			_TextureObstacle4;
	TextureContainer			_TextureReset;
	TextureContainer			_TextureLink;
	TextureContainer			_TexturePower;
	TextureContainer			_TextureGround;
	TextureContainer			_TextureSelectAlgorithm;

	TextureContainer			_TextureAlgBreadFirst;
	TextureContainer			_TextureAlgDeepFirst;
	TextureContainer			_TextureAlgBidirectional;
	TextureContainer			_TextureAlgAStar;
	TextureContainer			_TextureAlgGreedy;

	
	TextureContainer			_TextureMap1;
	TextureContainer			_TextureMap2;
	TextureContainer			_TextureMap3;



	int					_iMouseState;
	int					_iTypeItemSelected;
	vector<ITEM>		_vElements;
	vector<obstacle>	_obstacles;
	Point*				_pStartPoint;
	Point*				_pEndPoint;


	bool				_bVisible;
	bool				_bReset;
	int					_iStateInterface;
	int					_iSelectedAlgorithm;
	int					_iSelectedMap;
public:
	CSelectItem(void);
	~CSelectItem(void);
	void InitTexture(LPDIRECT3DDEVICE9 p_dx_Device);
	void Draw(LPDIRECT3DDEVICE9 p_dx_Device);
	void OurWindowProcedure(UINT uint_Message,WPARAM parameter1,LPARAM parameter2);
	void MouseEventNavMesh(UINT uint_Message,WPARAM parameter1,LPARAM parameter2);
	void MouseEventPutItems(UINT uint_Message,WPARAM parameter1,LPARAM parameter2);
	void MouseEventPutStartPoint(UINT uint_Message,WPARAM parameter1,LPARAM parameter2);
	void MouseEventPutEndPoint(UINT uint_Message,WPARAM parameter1,LPARAM parameter2);

	vector<obstacle> GetObstacles();
	void SetObstacles(vector<obstacle> obstacles);
	void SetObstaclesTypes(vector<ITEM> vElements);
	void SetStateInterfae(int iState);
	void SetReset(bool bReset);
	bool GetReset();
	int GetState();
	Point* GetStartPoint();
	Point* GetEndPoint();
	int GetSelectedAlgorithm();
	int GetSelectedMap();

};
