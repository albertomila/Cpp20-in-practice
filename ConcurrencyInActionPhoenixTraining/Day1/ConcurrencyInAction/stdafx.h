// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <time.h>
#include "ITest.h"

using namespace std;

void DebugWait()
{
	for (int i = 0; i < 1000; i++);
}

void sleep(unsigned int mseconds);

void PressEnterToContinue();


// TODO: reference additional headers your program requires here
