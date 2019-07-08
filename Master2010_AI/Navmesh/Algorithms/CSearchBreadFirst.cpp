
#include "stdAfx.h"
#include "CSearchBreadFirst.h"

CSearchBreadFirst::CSearchBreadFirst(void)
{
}

CSearchBreadFirst::~CSearchBreadFirst(void)
{
}

Triangle* CSearchBreadFirst::GetSearchPath(Triangle* pTriangleInit, Triangle* pTriangleEnd)
{
	bool bFinded = false;
	vector<Triangle*> vCurrentTriangleList;
	vCurrentTriangleList.clear();
	vCurrentTriangleList.push_back(pTriangleInit);
	vector<Triangle*> vNextTriangleList;
	vNextTriangleList.clear();

	while( !bFinded)
	{
		for(int i=0; i<vCurrentTriangleList.size(); i++)
		{
			for(int j=0; j< 3; j++)
			{
				if(vCurrentTriangleList[i]->GetNeighbor(j) != NULL)
				{
					if(vCurrentTriangleList[i]->GetNeighbor(j)->IsInterior())
					{
						if( !vCurrentTriangleList[i]->GetNeighbor(j)->GetVisited())
						{
							vCurrentTriangleList[i]->GetNeighbor(j)->_pPrevTriangle = vCurrentTriangleList[i];
							if( vCurrentTriangleList[i]->GetNeighbor(j) == pTriangleEnd)
							{
								bFinded = true;
								break;
							}
							else
							{
								vCurrentTriangleList[i]->GetNeighbor(j)->SetVisited(true);
								vNextTriangleList.push_back(vCurrentTriangleList[i]->GetNeighbor(j));
							}
						}
					}
				}
			}
			if(bFinded)break;
		}
		if(bFinded)break;
		vCurrentTriangleList = vNextTriangleList;
		vNextTriangleList.clear();
	}
	return pTriangleEnd;
}
