#pragma once
#include "stdafx.h"
#include "Samples/TreeBinary.h"

BEGIN_TEST(TestBinaryTree)
		typedef BinaryTree<int> TBinaryTree;
		TBinaryTree binaryTree;
		/*
		for(int i = 0; i<100;++i)
		{
			binaryTree.Push( rand() % 100 );
		}
		*/
		binaryTree.Push( 5 );
		binaryTree.Push( 8 );
		binaryTree.Push( 10 );
		binaryTree.Push( 9 );
		binaryTree.Push( 7 );
		binaryTree.Push( 6 );
		binaryTree.Push( 3 );
		binaryTree.Push( 4 );
		binaryTree.Push( 2 );
		binaryTree.Push( 1 );

		cout << "iterator" << endl;
		for( TBinaryTree::iterator it = binaryTree.begin(), endit = binaryTree.end(); it != endit; ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "const_iterator" << endl;
		for( TBinaryTree::const_iterator it = binaryTree.cbegin(), endit = binaryTree.cend(); it != endit; ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		//TODO: fix delete
		//binaryTree.Delete( 4 );

		TreeBinaryPrintHelpers::PrintDFSStack( binaryTree );

		bool b0 = binaryTree.Exist(0);
		bool b1 = binaryTree.Exist(1);
		bool b2 = binaryTree.Exist(2);
		bool b3 = binaryTree.Exist(3);
		bool b4 = binaryTree.Exist(4);
		bool b5 = binaryTree.Exist(5);
END_TEST()