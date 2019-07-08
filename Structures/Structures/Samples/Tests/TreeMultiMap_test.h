#pragma once
#include "stdafx.h"
#include "Samples/TreeMultiMap.h"

BEGIN_TEST(TestTreeMultiMap)
		typedef TreeMultiMap<int, int> TTreeMultiMap;
		TTreeMultiMap multiMapTree;

		multiMapTree.Push( 50, 1 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 25, 2 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 75, 3 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 15, 4 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 30, 5 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 60, 6 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 80, 7 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 65, 8 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 80, 9 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Push( 80, 10 );
		multiMapTree.PrintAVLTree();

		multiMapTree.DeleteAll( 80 );
		multiMapTree.PrintAVLTree();

		multiMapTree.Delete( 80 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Delete( 75 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Delete( 65 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Delete( 60 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Delete( 55 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Delete( 80 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Delete( 78 );
		multiMapTree.PrintAVLTree();
		multiMapTree.Delete( 85 );
		multiMapTree.PrintAVLTree();
END_TEST()