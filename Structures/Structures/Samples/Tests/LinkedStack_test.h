#pragma once
#include "stdafx.h"
#include "Samples/LinkedStack.h"

BEGIN_TEST(TestLinkedStack)
		typedef LinkedStack<int> TLinkedStack;

		TLinkedStack linkedStack;
		linkedStack.Push( 0 );
		linkedStack.Push( 1 );
		linkedStack.Push( 2 );
		linkedStack.Push( 3 );
		linkedStack.Push( 4 );
		linkedStack.Push( 5 );
		LinkedStackPrintHelpers::Print(linkedStack);

		linkedStack.Push( 6 );
		linkedStack.Push( 7 );
		linkedStack.Push( 8 );
		linkedStack.Push( 9 );
		linkedStack.Push( 10 );
		LinkedStackPrintHelpers::Print(linkedStack);

		linkedStack.Pop();
		linkedStack.Pop();
		linkedStack.Pop();
		LinkedStackPrintHelpers::Print(linkedStack);
		linkedStack.Pop();
		linkedStack.Pop();
		linkedStack.Pop();
		LinkedStackPrintHelpers::Print(linkedStack);
		linkedStack.Pop();
		linkedStack.Pop();
		linkedStack.Pop();
		LinkedStackPrintHelpers::Print(linkedStack);
		linkedStack.Pop();
		linkedStack.Pop();
		linkedStack.Pop();
		LinkedStackPrintHelpers::Print(linkedStack);
END_TEST()