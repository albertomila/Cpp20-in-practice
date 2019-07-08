#pragma once
#include "stdAfx.h"
#include "ASearchAlgorithm.h"

class CSearchDeepFirst : public ASearchAlgorithm
{
public:
	CSearchDeepFirst(void);
	~CSearchDeepFirst(void);
	Triangle* GetSearchPath(Triangle* pTriangleInit, Triangle* pTriangleEnd);
};
