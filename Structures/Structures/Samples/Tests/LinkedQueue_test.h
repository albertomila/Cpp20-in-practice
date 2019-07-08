#pragma once
#include "stdafx.h"
#include "Samples/LinkedQueue.h"

BEGIN_TEST(TestLinkedQueue)
		typedef LinkedQueue<int> TLinkedQueue;

		TLinkedQueue linked;
		linked.Push( 0 );
		linked.Push( 1 );
		linked.Push( 2 );
		linked.Push( 3 );
		linked.Push( 4 );
		linked.Push( 5 );
		LinkedQueuePrintHelpers::Print(linked);

		linked.Push( 6 );
		linked.Push( 7 );
		linked.Push( 8 );
		linked.Push( 9 );
		linked.Push( 10 );
		LinkedQueuePrintHelpers::Print(linked);

		linked.Pop();
		linked.Pop();
		linked.Pop();
		LinkedQueuePrintHelpers::Print(linked);
		linked.Pop();
		linked.Pop();
		linked.Pop();
		LinkedQueuePrintHelpers::Print(linked);
		linked.Pop();
		linked.Pop();
		linked.Pop();
		LinkedQueuePrintHelpers::Print(linked);
		linked.Push( 6 );
		linked.Push( 7 );
		linked.Push( 8 );
		linked.Push( 9 );
		linked.Push( 10 );
		LinkedQueuePrintHelpers::Print(linked);
END_TEST()