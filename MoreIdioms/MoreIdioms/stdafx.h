// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>
#include <ostream>
#include "ITest.h"

template <class T>
errno_t SafeStrCopy(T* szDest, const T* szSrc)
{
	return strcpy_s(szDest, sizeof(szDest), szSrc);
}




// TODO: reference additional headers your program requires here
