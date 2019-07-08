// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <assert.h>
#include "ITest.h"
#include <windows.h>

using namespace std;

namespace CoutColors
{
	enum EColors
	{
		blue = 1
		, green
		, cyan
		, red
		, purple
		, yellow
		, grey
		, dgrey
		, hblue
		, hgreen
		, hred
		, hpurple
		, hyellow
		, hwhite
	};
}

static void COutColor(CoutColors::EColors color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
}


// TODO: reference additional headers your program requires here
