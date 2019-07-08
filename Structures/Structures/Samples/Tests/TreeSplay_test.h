#pragma once
#include "stdafx.h"
#include "Samples/TreeSplay.h"

BEGIN_TEST(TestBinarySplayTree)
		typedef BinarySplayTree<int> TBinarySplayTree;
		TBinarySplayTree binarySplayTree;
		/*
		for(int i = 0; i<100;++i)
		{
			binarySplayTree.Push( 100-i );
			TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		}
		*/
		
		binarySplayTree.Push( 50 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 100 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 20 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 86 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 15 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 53 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 5 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 52 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 1 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Push( 18 );
		TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );

		bool exist = binarySplayTree.Exist(19); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		exist = binarySplayTree.Exist(20); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );

		binarySplayTree.Delete(19); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(18); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(100); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(86); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(20); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(52); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(1); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(15); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(53); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(5); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(50); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
		binarySplayTree.Delete(50); TreeBinaryPrintHelpers::PrintBFS( binarySplayTree );
END_TEST()