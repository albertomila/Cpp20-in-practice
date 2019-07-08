// stdafx.cpp : source file that includes just the standard includes
// ConcurrencyInAction.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void sleep(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock()); 
}

void PressEnterToContinue()
{
	std::cout << "Press ENTER to continue\n";
	std::cin.get();
}