#pragma once
#include "stdafx.h"
#include "Samples/arrayCircularQueue.h"

BEGIN_TEST(TestArrayQueue)
		typedef ArrayQueue<int> TArrayQueue;

		TArrayQueue myArray;
		myArray.Push( 0 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 1 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 2 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 3 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 4 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 5 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 6 );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 7 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 8 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 9 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 10 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 11 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 12 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 13 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 14 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 15 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Pop();
		ArrayCircularQueuePrintHelpers::Print( myArray );

		myArray.Push( 16 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 17 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 18 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 19 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 20 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 21 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 22 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 23 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 24 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 25 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 26 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 27 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 28 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 29 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
		myArray.Push( 30 );
		ArrayCircularQueuePrintHelpers::Print( myArray );
END_TEST()