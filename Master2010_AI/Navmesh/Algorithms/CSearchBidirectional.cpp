
#include "stdAfx.h"
#include "CSearchBidirectional.h"

CSearchBidirectional::CSearchBidirectional(void)
{
}

CSearchBidirectional::~CSearchBidirectional(void)
{
}
Triangle* CSearchBidirectional::GetSearchPath(Triangle* pTriangleInit, Triangle* pTriangleEnd)
{
	bool bFinded = false;
	vector<Triangle*> vCurrentTriangleListInit;
	vector<Triangle*> vNextTriangleListInit;
	vNextTriangleListInit.push_back(pTriangleInit);

	vector<Triangle*> vCurrentTriangleListEnd;
	vector<Triangle*> vNextTriangleListEnd;
	vNextTriangleListEnd.push_back(pTriangleEnd);

	while( !bFinded)
	{
		for(int i=0; i<vCurrentTriangleListInit.size(); i++)
		{
			for(int j=0; j< 3; j++)
			{
				if(vCurrentTriangleListInit[i]->GetNeighbor(j) != NULL)
				{
					if(vCurrentTriangleListInit[i]->GetNeighbor(j)->IsInterior())
					{
						if( !vCurrentTriangleListInit[i]->GetNeighbor(j)->GetVisited())
						{
							if(vCurrentTriangleListInit[i]->GetNeighbor(j)->_pPrevTriangle == NULL)
							{
								vCurrentTriangleListInit[i]->GetNeighbor(j)->_pPrevTriangle = vCurrentTriangleListInit[i];
							}
							else
							{
								bFinded = true;
								break;
							}
							if( vCurrentTriangleListInit[i]->GetNeighbor(j) == pTriangleEnd)
							{
								bFinded = true;
								break;
							}
							else
							{
								vCurrentTriangleListInit[i]->GetNeighbor(j)->SetVisited(true);
								vNextTriangleListInit.push_back(vCurrentTriangleListInit[i]->GetNeighbor(j));
							}
						}
					}
				}
			}
			if(bFinded)break;
		}
		if(bFinded)break;
		vCurrentTriangleListInit = vNextTriangleListInit;
		vNextTriangleListInit.clear();


		for(int i=0; i<vCurrentTriangleListEnd.size(); i++)
		{
			for(int j=0; j< 3; j++)
			{
				if(vCurrentTriangleListEnd[i]->GetNeighbor(j) != NULL)
				{
					if(vCurrentTriangleListEnd[i]->GetNeighbor(j)->IsInterior())
					{
						if( !vCurrentTriangleListEnd[i]->GetNeighbor(j)->GetVisited())
						{
							if(vCurrentTriangleListEnd[i]->GetNeighbor(j)->_pPrevTriangle == NULL)
							{
								vCurrentTriangleListEnd[i]->GetNeighbor(j)->_pPrevTriangle = vCurrentTriangleListEnd[i];
							}
							else
							{
								bFinded = true;
								break;
							}
							if( vCurrentTriangleListEnd[i]->GetNeighbor(j) == pTriangleEnd)
							{
								bFinded = true;
								break;
							}
							else
							{
								vCurrentTriangleListEnd[i]->GetNeighbor(j)->SetVisited(true);
								vNextTriangleListEnd.push_back(vCurrentTriangleListEnd[i]->GetNeighbor(j));
							}
						}
					}
				}
			}
			if(bFinded)break;
		}
		if(bFinded)break;
		vCurrentTriangleListEnd = vCurrentTriangleListEnd;
		vNextTriangleListEnd.clear();
	}
	return pTriangleEnd;
}
