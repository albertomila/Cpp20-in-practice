#pragma once
#include "stdAfx.h"
#include "ASearchAlgorithm.h"

class CSearchBreadFirst : public ASearchAlgorithm
{
public:
	CSearchBreadFirst(void);
	~CSearchBreadFirst(void);
	Triangle* GetSearchPath(Triangle* pTriangleInit, Triangle* pTriangleEnd);
};
