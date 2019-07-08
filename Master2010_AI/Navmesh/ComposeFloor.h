#pragma once

#include<windows.h> 
#include <windowsx.h>
#include<d3d9.h> 
#include<d3dx9.h> 
#include<vector>
#include "CStructures.h"
#include <sstream>
using namespace std;


typedef vector<Point2> obstacle;
class CComposeFloor
{
private:
	vector<Point2>	_vListPoints;
	bool			_bCompletePath;
	Point2			_currentPoint;
	bool			_bPointFollowAdded;
	int				_iIndexPointFollow;
public:
	CComposeFloor(void);
	~CComposeFloor(void);
	void OurWindowProcedure(UINT uint_Message,WPARAM parameter1,LPARAM parameter2);
	float Distance(Point2 p1, Point2 p2);
	bool complete() const;
	vector<Point2> getListPoints();
	void SetListPoints(vector<Point2> vListPoints);
	vector<obstacle> GetObstacles(int iDefaultMap);
	void SetDefaultMap(int iDefaultMap);
	vector<ITEM> GetObstaclesTypes(int iDefaultMap);
	int ChangeX(int iValue);
	int ChangeY(int iValue);
};
