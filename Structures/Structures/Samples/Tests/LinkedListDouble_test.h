#pragma once
#include "stdafx.h"
#include "Samples/LinkedListDouble.h"

BEGIN_TEST(TestDoubleLinkedList)
		typedef DoubleLinkedList<int> TDoubleLinkedList;

		TDoubleLinkedList linkedList1;
		linkedList1.PushBack( 0 );
		linkedList1.PushBack( 1 );
		linkedList1.PushBack( 2 );
		linkedList1.PushBack( 3 );
		linkedList1.PushBack( 4 );
		linkedList1.PushBack( 5 );
		linkedList1.PushBack( 6 );
		linkedList1.PushBack( 7 );
		linkedList1.PushBack( 8 );
		linkedList1.PushBack( 9 );
		linkedList1.PushBack( 10 );

		cout << "iterator" << endl;
		for( TDoubleLinkedList::iterator it = linkedList1.begin(); it!=linkedList1.end(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "const iterator" << endl;
		for( TDoubleLinkedList::const_iterator it = linkedList1.cbegin(); it!=linkedList1.cend(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "reverse iterator" << endl;
		for( TDoubleLinkedList::reverse_iterator it = linkedList1.rbegin(); it!=linkedList1.rend(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "const reverse iterator" << endl;
		for( TDoubleLinkedList::const_reverse_iterator it = linkedList1.crbegin(); it!=linkedList1.crend(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;


		TDoubleLinkedList linkedList;
		linkedList.PushBack( 0 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.PushBack( 1 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.PushBack( 2 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.PushBack( 3 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.PushBack( 4 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.PushBack( 5 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.RemoveFront();
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.RemoveFront();
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.RemoveFront();
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.RemoveBack();
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.RemoveBack();
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.RemoveBack();
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );


		linkedList.Clean();
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );

		linkedList.PushBack( 6 );
		linkedList.PushBack( 7 );
		linkedList.PushBack( 8 );
		linkedList.PushBack( 9 );
		linkedList.PushBack( 10 );
		LinkedListDoublePrintHelpers::Print( linkedList );

		linkedList.PushFront( 11 );
		linkedList.PushFront( 12 );
		linkedList.PushFront( 13 );
		LinkedListDoublePrintHelpers::Print( linkedList );

		linkedList.Remove(10);
		LinkedListDoublePrintHelpers::Print( linkedList );
		linkedList.Remove(12);
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.Remove(13);
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );
		linkedList.Remove(11);
		LinkedListDoublePrintHelpers::Print( linkedList );
		LinkedListDoublePrintHelpers::PrintBackwards( linkedList );

		linkedList.RemoveAtIndex( 0 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListDoublePrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListDoublePrintHelpers::Print( linkedList );
END_TEST()