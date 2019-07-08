#pragma once
#include "stdafx.h"
#include "Samples/LinkedList.h"

struct Test
{
	Test()
	{
	}

	Test( int x )
		: m_x(x)
	{
	}

	Test( const Test& t )
		:m_x(t.m_x)
	{
	}

	int m_x;
};

BEGIN_TEST(TestLinkedList)
		typedef LinkedList<Test> TLinkedList1;
		TLinkedList1 linkedList1;
		linkedList1.PushBack( Test(0) );
		linkedList1.PushBack( Test(1) );
		linkedList1.PushBack( Test(2) );
		linkedList1.PushBack( Test(3) );
		linkedList1.PushBack( Test(4) );
		linkedList1.PushBack( Test(5) );
		linkedList1.PushBack( Test(6) );
		linkedList1.PushBack( Test(7) );
		linkedList1.PushBack( Test(8) );
		linkedList1.PushBack( Test(9) );
		linkedList1.PushBack( Test(10) );

		cout << "iterator" << endl;
		for( TLinkedList1::iterator it = linkedList1.begin(); it!=linkedList1.end(); ++it )
		{
			cout << it->m_x << ",";
		}
		cout << endl;

		cout << "const iterator" << endl;
		for( TLinkedList1::const_iterator it = linkedList1.cbegin(); it!=linkedList1.cend(); ++it )
		{
			cout << it->m_x << ",";
		}
		cout << endl;

		typedef LinkedList<Test*> TLinkedList2;
		TLinkedList2 linkedList2;
		linkedList2.PushBack( new Test(0) );
		linkedList2.PushBack( new Test(1) );
		linkedList2.PushBack( new Test(2) );
		linkedList2.PushBack( new Test(3) );
		linkedList2.PushBack( new Test(4) );
		linkedList2.PushBack( new Test(5) );
		linkedList2.PushBack( new Test(6) );
		linkedList2.PushBack( new Test(7) );
		linkedList2.PushBack( new Test(8) );
		linkedList2.PushBack( new Test(9) );
		linkedList2.PushBack( new Test(10) );

		cout << "iterator" << endl;
		for( TLinkedList2::iterator it = linkedList2.begin(); it!=linkedList2.end(); ++it )
		{
			cout << (*it)->m_x << ",";
		}
		cout << endl;

		cout << "const iterator" << endl;
		for( TLinkedList2::const_iterator it = linkedList2.cbegin(); it!=linkedList2.cend(); ++it )
		{
			cout << (*it)->m_x << ",";
		}
		cout << endl;


		typedef LinkedList<int> TLinkedList;

		TLinkedList linkedList;
		linkedList.PushBack( 0 );
		linkedList.PushBack( 1 );
		linkedList.PushBack( 2 );
		linkedList.PushBack( 3 );
		linkedList.PushBack( 4 );
		linkedList.PushBack( 5 );
		LinkedListPrintHelpers::Print( linkedList );

		linkedList.PushBack( 6 );
		linkedList.PushBack( 7 );
		linkedList.PushBack( 8 );
		linkedList.PushBack( 9 );
		linkedList.PushBack( 10 );
		LinkedListPrintHelpers::Print( linkedList );

		linkedList.PushFront( 11 );
		linkedList.PushFront( 12 );
		linkedList.PushFront( 13 );
		LinkedListPrintHelpers::Print( linkedList );

		linkedList.Remove(2);
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.Remove(4);
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.Remove(6);
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.Remove(8);
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.Remove(10);
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.Remove(12);
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.Remove(13);
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.Remove(11);
		LinkedListPrintHelpers::Print( linkedList );

		linkedList.RemoveAtIndex( 20 );
		LinkedListPrintHelpers::Print( linkedList );

		linkedList.RemoveAtIndex( 0 );
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListPrintHelpers::Print( linkedList );
		linkedList.RemoveAtIndex( 0 );
		LinkedListPrintHelpers::Print( linkedList );

		cout << "iterator" << endl;
		for( TLinkedList::iterator it = linkedList.begin(); it!=linkedList.end(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "const iterator" << endl;
		for( TLinkedList::const_iterator it = linkedList.cbegin(); it!=linkedList.cend(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;
END_TEST()