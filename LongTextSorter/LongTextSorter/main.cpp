// LongTextSorter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LongTextSorter.h"


int main()
{
	LongTextSorter* longTextSorter = new LongTextSorter("VeryLongText.txt", "VeryLongText_sorted.txt");
	longTextSorter->Sort();
	
	return 0;
}

