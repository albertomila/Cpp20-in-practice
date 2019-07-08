#pragma once
#include "stdafx.h"
#include "Samples/arrayStack.h"

BEGIN_TEST(TestArrayStack)
		typedef ArrayStack<int> TArrayStack;

		TArrayStack myArray;
		myArray.Push( 0 );
		//myArray.Reserve( 50 );
		myArray.Push( 1 );
		myArray.Push( 2 );
		myArray.Push( 3 );
		myArray.Push( 4 );
		myArray.Push( 5 );
		myArray.Push( 6 );
		myArray.Push( 7 );
		myArray.Push( 8 );
		myArray.Push( 9 );
		myArray.Push( 10 );
		myArray.Push( 11 );
		myArray.Pop();
		myArray.Pop();
		myArray.Pop();
		myArray.Pop();
		myArray.Pop();
END_TEST()