#pragma once
#include "stdafx.h"
#include "Samples/TreeBinaryBalanced.h"

BEGIN_TEST(TestAVLTree)
		typedef AVLTree<int> TAVLTreeTree;
		TAVLTreeTree avlTree;

		for( unsigned int i = 0; i<1000; ++i)
		{
			int value = rand() % 100;
			avlTree.Push( value );
			avlTree.PrintAVLTree();
			++value;
		}

		avlTree.Push( 50 );
		avlTree.PrintAVLTree();
		avlTree.Push( 25 );
		avlTree.PrintAVLTree();
		avlTree.Push( 75 );
		avlTree.PrintAVLTree();
		avlTree.Push( 15 );
		avlTree.PrintAVLTree();
		avlTree.Push( 30 );
		avlTree.PrintAVLTree();
		avlTree.Push( 60 );
		avlTree.PrintAVLTree();
		avlTree.Push( 80 );
		avlTree.PrintAVLTree();
		avlTree.Push( 10 );
		avlTree.PrintAVLTree();
		avlTree.Push( 20 );
		avlTree.PrintAVLTree();
		avlTree.Push( 27 );
		avlTree.PrintAVLTree();
		avlTree.Push( 35 );
		avlTree.PrintAVLTree();
		avlTree.Push( 55 );
		avlTree.PrintAVLTree();
		avlTree.Push( 65 );
		avlTree.PrintAVLTree();
		avlTree.Push( 78 );
		avlTree.PrintAVLTree();
		avlTree.Push( 85 );
		avlTree.PrintAVLTree();

		avlTree.Delete( 75 );
		avlTree.PrintAVLTree();
		avlTree.Delete( 65 );
		avlTree.PrintAVLTree();
		avlTree.Delete( 60 );
		avlTree.PrintAVLTree();
		avlTree.Delete( 55 );
		avlTree.PrintAVLTree();
		avlTree.Delete( 80 );
		avlTree.PrintAVLTree();
		avlTree.Delete( 78 );
		avlTree.PrintAVLTree();
		avlTree.Delete( 85 );
		avlTree.PrintAVLTree();
	
		for( unsigned int i = 0; i<1000; ++i)
		{
			int value = rand() % 100;
			avlTree.Push( value );
			avlTree.PrintAVLTree();
			++value;
		}
		//binaryTree.PrintBFS();
		//binaryTree.PrintDFSStack();
	
		TreeBinaryPrintHelpers::PrintDFSRecursive( avlTree );
		bool b0 = avlTree.Exist(0);
		bool b1 = avlTree.Exist(1);
		bool b2 = avlTree.Exist(2);
		bool b3 = avlTree.Exist(3);
		bool b4 = avlTree.Exist(4);
		bool b5 = avlTree.Exist(5);
END_TEST()