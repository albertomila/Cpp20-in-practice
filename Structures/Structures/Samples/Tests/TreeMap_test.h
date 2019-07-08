#pragma once
#include "stdafx.h"
#include "Samples/TreeMap.h"

BEGIN_TEST(TestTreeMap)
		typedef TreeMap<int, int> TTreeMap;
		TTreeMap mapTree;

		mapTree[80] = 1;
		mapTree.PrintAVLTree();
		mapTree[80] = 2;
		mapTree.PrintAVLTree();
		mapTree[80] = 3;
		mapTree.PrintAVLTree();
		mapTree[80] = 4;
		mapTree.PrintAVLTree();
		mapTree[50] = 5;
		mapTree.PrintAVLTree();
		mapTree.Push( 50, 1 );
		mapTree.PrintAVLTree();
		mapTree.Push( 25, 2 );
		mapTree.PrintAVLTree();
		mapTree.Push( 75, 3 );
		mapTree.PrintAVLTree();
		mapTree.Push( 15, 4 );
		mapTree.PrintAVLTree();
		mapTree.Push( 30, 5 );
		mapTree.PrintAVLTree();
		mapTree.Push( 60, 6 );
		mapTree.PrintAVLTree();
		mapTree.Push( 80, 7 );
		mapTree.PrintAVLTree();
		mapTree.Push( 65, 8 );
		mapTree.PrintAVLTree();
		mapTree.Push( 80, 9 );
		mapTree.PrintAVLTree();
		mapTree.Push( 80, 10 );
		mapTree.PrintAVLTree();

		int& val = mapTree.Get( 80 );
	
		mapTree.Delete( 75 );
		mapTree.PrintAVLTree();
		mapTree.Delete( 65 );
		mapTree.PrintAVLTree();
		mapTree.Delete( 60 );
		mapTree.PrintAVLTree();
		mapTree.Delete( 55 );
		mapTree.PrintAVLTree();
		mapTree.Delete( 80 );
		mapTree.PrintAVLTree();
		mapTree.Delete( 78 );
		mapTree.PrintAVLTree();
		mapTree.Delete( 85 );
		mapTree.PrintAVLTree();
		/*
		for( unsigned int i = 0; i<1000; ++i)
		{
		int value = rand() % 100;
		mapTree.Push( value );
		mapTree.PrintTree();
		++value;
		}

		mapTree.PrintBFS();
		mapTree.PrintDFSStack();

		mapTree.PrintDFSRecursive();
		bool b0 = mapTree.Exist(0);
		bool b1 = mapTree.Exist(1);
		bool b2 = mapTree.Exist(2);
		bool b3 = mapTree.Exist(3);
		bool b4 = mapTree.Exist(4);
		bool b5 = mapTree.Exist(5);*/
END_TEST()
