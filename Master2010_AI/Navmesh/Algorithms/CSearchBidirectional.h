#pragma once
#include "ASearchAlgorithm.h"

class CSearchBidirectional : public ASearchAlgorithm
{
public:
	CSearchBidirectional(void);
	~CSearchBidirectional(void);
	Triangle* GetSearchPath(Triangle* pTriangleInit, Triangle* pTriangleEnd);
};
