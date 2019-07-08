#pragma once
#include "stdafx.h"
#include "Samples/TreeRedBlack_WorkInProgress.h"

BEGIN_TEST(TestRedBlackTree)
		typedef RedBlackTree<int> TRedBlackTree;
		TRedBlackTree redBlackTree;

		/*
		for(int i = 0; i<100;++i)
		{
			redBlackTree.Push( rand() % 100 );
		}
		*/
		redBlackTree.Push( 50 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 25 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 100 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 10 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 75 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 150 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 5 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 200 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 60 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 90 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 125 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 30 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 1 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 7 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Push( 20 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);

		redBlackTree.Delete( 90 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 100 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 75 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 60 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 150 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 10 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 5 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 7 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 25 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 125 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 200 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		redBlackTree.Delete( 20 ); TreeRedBlackPrintHelpers::PrintTree(redBlackTree);


		int inputValue = INT_MAX;
		while( inputValue != -1 )
		{
			COutColor( CoutColors::yellow );
			cin >> inputValue;
			redBlackTree.Push( inputValue ); 
			TreeRedBlackPrintHelpers::PrintTree(redBlackTree);
		}
END_TEST()
