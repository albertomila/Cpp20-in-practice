#pragma once
#include "ASearchAlgorithm.h"

class CSearchGreedy : public ASearchAlgorithm
{
public:
	CSearchGreedy(void);
	~CSearchGreedy(void);
	Triangle* GetSearchPath(Triangle* pTriangleInit, Triangle* pTriangleEnd);
	bool IsInBucle(Triangle* pTriangleAnt, Triangle* pNeighbour);
};
