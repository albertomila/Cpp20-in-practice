// Navmesh.cpp : Defines the entry point for the application.
//

#include "stdAfx.h"
#include "Navmesh.h"
#include<windows.h> 
#include <windowsx.h>
#include<d3d9.h> 
#include<d3dx9.h> 
#include "ComposeFloor.h"
#include "CNavmesh.h"
#include "SelectItem.h"
#include "./poly2tri/poly2tri.h"
#include "./Algorithms/CSearchBreadFirst.h"
#include "./Algorithms/CSearchDeepFirst.h"
#include "./Algorithms/CSearchBidirectional.h"
#include "./Algorithms/CSearchGreedy.h"
#include "./Algorithms/CSearchAStar.h"



#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768


int iStateGame = 0;
CComposeFloor* _floor;
CNavmesh* _navMesh;
CSelectItem* _selectItem;
ASearchAlgorithm* _pSearchAlgorithm;

int int_AppRunning = 1;
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main w


 LRESULT CALLBACK OurWindowProcedure(HWND han_Wind,UINT uint_Message,WPARAM parameter1,LPARAM parameter2)
 {
     switch(uint_Message)
     {
         case WM_KEYDOWN:
         {
             int_AppRunning = 0;
             break;
         }
		 case WM_RBUTTONUP:
		{
		}
     }

	 switch(iStateGame)
     {
         case 1:
         {
			_floor->OurWindowProcedure(uint_Message, parameter1, parameter2);
			_selectItem->OurWindowProcedure(uint_Message, parameter1, parameter2);
            break;
         }
		 case 2:
		 {		 
			_selectItem->OurWindowProcedure(uint_Message, parameter1, parameter2);
		 }
		 case 3:
		 {		 
			_selectItem->OurWindowProcedure(uint_Message, parameter1, parameter2);
		 }
     }
     return DefWindowProc(han_Wind,uint_Message,parameter1,parameter2);
 }
 
 HWND NewWindow(LPCTSTR str_Title,int int_XPos, int int_YPos, int int_Width, int int_Height)
 {
     WNDCLASSEX wnd_Structure;
 
     wnd_Structure.cbSize = sizeof(WNDCLASSEX);
     wnd_Structure.style = CS_HREDRAW | CS_VREDRAW;
     wnd_Structure.lpfnWndProc = OurWindowProcedure;
     wnd_Structure.cbClsExtra = 0;
     wnd_Structure.cbWndExtra = 0;
     wnd_Structure.hInstance = GetModuleHandle(NULL);
     wnd_Structure.hIcon = NULL;
     wnd_Structure.hCursor = NULL;
     wnd_Structure.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
     wnd_Structure.lpszMenuName = NULL;
     wnd_Structure.lpszClassName = L"WindowClassName";
     wnd_Structure.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
 
     RegisterClassEx(&wnd_Structure);
 
     return CreateWindowEx(WS_EX_CONTROLPARENT, L"WindowClassName", str_Title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, int_XPos, int_YPos, int_Width, int_Height, NULL, NULL, GetModuleHandle(NULL), NULL);
 }
 
 LPDIRECT3DDEVICE9 InitializeDevice(HWND han_WindowToBindTo)
 {
     LPDIRECT3D9 p_dx_Object;
     LPDIRECT3DDEVICE9 p_dx_Device;
 
     p_dx_Object = Direct3DCreate9(D3D_SDK_VERSION);
     if (p_dx_Object == NULL)
     {
         MessageBox(han_WindowToBindTo,L"DirectX Runtime library not installed!",L"InitializeDevice()",MB_OK);
     }
 
     D3DPRESENT_PARAMETERS dx_PresParams;
     ZeroMemory( &dx_PresParams, sizeof(dx_PresParams) );
     dx_PresParams.Windowed = TRUE;
     dx_PresParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
     dx_PresParams.BackBufferFormat = D3DFMT_UNKNOWN;
 
     if (FAILED(p_dx_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, han_WindowToBindTo, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dx_PresParams, &p_dx_Device)))
     {
         if (FAILED(p_dx_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, han_WindowToBindTo, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &dx_PresParams, &p_dx_Device)))
         {
             MessageBox(han_WindowToBindTo,L"Failed to create even the reference device!",L"InitializeDevice()",MB_OK);
         }
	}
 
     p_dx_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
     p_dx_Device->SetRenderState(D3DRS_LIGHTING,false);
 
     return p_dx_Device;
 }
 
 void DrawScene(LPDIRECT3DDEVICE9 p_dx_Device)
 {
     p_dx_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
     p_dx_Device->BeginScene();
 
	 switch(iStateGame)
	 {
		 case 0://init floor
			 break;
		 case 1:
			_selectItem->Draw(p_dx_Device);
			_navMesh->Draw(p_dx_Device);
			 break;
		 case 2:
			_selectItem->Draw(p_dx_Device);
			_navMesh->Draw(p_dx_Device);
			_pSearchAlgorithm->Draw(p_dx_Device);
			 break;
		 case 3:
			_selectItem->Draw(p_dx_Device);
			_navMesh->Draw(p_dx_Device);
			
			 if(_selectItem->GetState() >= 4)
			 {
				 _pSearchAlgorithm->Draw(p_dx_Device);
			 }
			 break;
	 }
     p_dx_Device->EndScene();
     p_dx_Device->Present(NULL, NULL, NULL, NULL);
 }
 
 void Update(LPDIRECT3DDEVICE9 p_dx_Device)
 {
	 int iSelectedMap;
	 switch(iStateGame)
	 {
		 case 0://init floor
			 _floor = new CComposeFloor;
			 _navMesh = new CNavmesh(_floor->getListPoints());
			 _navMesh->Update(p_dx_Device);
			 _selectItem = new CSelectItem();
			 _selectItem->InitTexture(p_dx_Device);
			 iStateGame = 1;
			 break;
		 case 1:
			 iSelectedMap  =_selectItem->GetSelectedMap();
			 if(iSelectedMap >= 0)
			 {
				 _floor->SetDefaultMap(iSelectedMap);
				 _selectItem->SetObstacles(_floor->GetObstacles(iSelectedMap));
				 _selectItem->SetObstaclesTypes(_floor->GetObstaclesTypes(iSelectedMap));
				 _selectItem->SetStateInterfae(1);
				 iStateGame = 2;
			 }
			 else
			 {
				 if(_floor->complete())
				 {
					 _selectItem->SetStateInterfae(1);
					 iStateGame = 2;
				 }
				 _navMesh = new CNavmesh(_floor->getListPoints());
				 _navMesh->Update(p_dx_Device);
				 switch(_selectItem->GetSelectedAlgorithm())
				 {
					 case 0:
						 _pSearchAlgorithm = new CSearchBreadFirst();
						 break;
					 case 1:
						 _pSearchAlgorithm = new CSearchDeepFirst();
						 break;
					 case 2:
						 _pSearchAlgorithm = new CSearchBidirectional();
						 break;
					 case 3:
						 _pSearchAlgorithm = new CSearchAStar();
						 break;
					 case 4:
						 _pSearchAlgorithm = new CSearchGreedy();
						 break;
				 }
				 _pSearchAlgorithm->SetMesh(_navMesh->GetMesh());
				 _pSearchAlgorithm->SetPosInit(_selectItem->GetStartPoint());
				 _pSearchAlgorithm->SetEndPoint(_selectItem->GetEndPoint());
				 _pSearchAlgorithm->GetPath();
				 _pSearchAlgorithm->Update(p_dx_Device);
				 if(_selectItem->GetReset())
				 {
					 iStateGame = 0;
					 _selectItem->SetReset(false);
				 }
			 }
			 break;
		 case 2:
			 iSelectedMap  =_selectItem->GetSelectedMap();
			 if(iSelectedMap >= 0)
			 {
				 _floor->SetDefaultMap(iSelectedMap);
				 _selectItem->SetObstacles(_floor->GetObstacles(iSelectedMap));
				 _selectItem->SetObstaclesTypes(_floor->GetObstaclesTypes(iSelectedMap));
				 _selectItem->SetStateInterfae(1);
			 }
			 else
			 {
				 _navMesh = new CNavmesh(_floor->getListPoints());
				 _navMesh->addObstacle(_selectItem->GetObstacles());
				 _navMesh->Update(p_dx_Device);
				 if(_selectItem->GetReset())
				 {
					 iStateGame = 0;
					 _selectItem->SetReset(false);
				 }
				 switch(_selectItem->GetSelectedAlgorithm())
				 {
				 case 0:
					 _pSearchAlgorithm = new CSearchBreadFirst();
					 break;
				 case 1:
					 _pSearchAlgorithm = new CSearchDeepFirst();
					 break;
				 case 2:
					 _pSearchAlgorithm = new CSearchBidirectional();
					 break;
				 case 3:
					 _pSearchAlgorithm = new CSearchAStar();
					 break;
				 case 4:
					 _pSearchAlgorithm = new CSearchGreedy();
					 break;
				 }
				 _pSearchAlgorithm->SetMesh(_navMesh->GetMesh());
				 _pSearchAlgorithm->SetPosInit(_selectItem->GetStartPoint());
				 _pSearchAlgorithm->SetEndPoint(_selectItem->GetEndPoint());
				 _pSearchAlgorithm->GetPath();
				 _pSearchAlgorithm->Update(p_dx_Device);
			 }
			 break;
	 }
 }
 
 
 void SetUpCamera(LPDIRECT3DDEVICE9 p_dx_Device)
 {
	D3DXMATRIX Ortho2D;	
	D3DXMATRIX Identity;

	D3DXMatrixOrthoLH(&Ortho2D, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f);
	D3DXMatrixIdentity(&Identity);

	p_dx_Device->SetTransform(D3DTS_PROJECTION, &Ortho2D);
	p_dx_Device->SetTransform(D3DTS_WORLD, &Identity);
	p_dx_Device->SetTransform(D3DTS_VIEW, &Identity);

	D3DXMATRIX Position;
	D3DXMatrixTranslation(&Position, -SCREEN_WIDTH/2,-SCREEN_HEIGHT/2, 0.0f);
	p_dx_Device->SetTransform(D3DTS_WORLD, &Position);
 }
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	 MSG msg_Message;
 
     HWND han_Window = NewWindow(L"Navmesh",0,0,SCREEN_WIDTH+7,SCREEN_HEIGHT+29);
     LPDIRECT3DDEVICE9 p_Device = InitializeDevice(han_Window);
     SetUpCamera(p_Device);
	
     while(int_AppRunning)
     {
         if(PeekMessage(&msg_Message,han_Window,0,0,PM_REMOVE))
         {
             DispatchMessage(&msg_Message);
         }
		 Update(p_Device);
         DrawScene(p_Device);
     }
 
     p_Device->Release();
     DestroyWindow(han_Window);
 
     return 0;
}