#pragma once
#include "stdafx.h"
#include "Samples/TreeMultiSet.h"

BEGIN_TEST(TestTreeMultiSet)
		typedef TreeMultiSet<int> TTreeMultiSet;
		TTreeMultiSet setTree;

		setTree.Push( 50 );
		setTree.PrintAVLTree();
		setTree.Push( 25 );
		setTree.PrintAVLTree();
		setTree.Push( 75 );
		setTree.PrintAVLTree();
		setTree.Push( 15 );
		setTree.PrintAVLTree();
		setTree.Push( 30 );
		setTree.PrintAVLTree();
		setTree.Push( 60 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();
		setTree.Push( 65 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();
		setTree.Push( 80 );
		setTree.PrintAVLTree();

		setTree.Delete( 75 );
		setTree.PrintAVLTree();
		setTree.Delete( 65 );
		setTree.PrintAVLTree();
		setTree.Delete( 60 );
		setTree.PrintAVLTree();
		setTree.Delete( 55 );
		setTree.PrintAVLTree();
		setTree.Delete( 80 );
		setTree.PrintAVLTree();
		setTree.Delete( 78 );
		setTree.PrintAVLTree();
		setTree.Delete( 85 );
		setTree.PrintAVLTree();
END_TEST()