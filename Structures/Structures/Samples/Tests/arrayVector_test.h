#pragma once
#include "stdafx.h"
#include "Samples/arrayVector.h"

//tests
struct Element
{
	Element( int value )
		: m_value( value )
	{
	}
	int m_value;
};

BEGIN_TEST(TestArrayVector)
		typedef ArrayVector<Element*> TArrayVectorPtr;

		Element* element = new Element(8);

		TArrayVectorPtr myArrayptr(40);
		myArrayptr.PushBack( new Element(0) );
		//myArray.Reserve( 50 );
		myArrayptr.PushBack( new Element(1) );
		myArrayptr.PushBack( new Element(2) );
		myArrayptr.PushBack( new Element(3) );
		myArrayptr.PushBack( new Element(4) );
		myArrayptr.PushBack( new Element(5) );
		myArrayptr.PushBack( new Element(6) );
		myArrayptr.PushBack( new Element(7) );
		myArrayptr.PushBack( element );
		myArrayptr.PushBack( new Element(9) );
		myArrayptr.Remove( 5 );
		myArrayptr.PushBack( new Element(10) );
		myArrayptr.PushBack( new Element(11) );
		myArrayptr.PushBack( new Element(12) );
		myArrayptr.RemoveElement( element );


		typedef ArrayVector<int> TArrayVector;

		TArrayVector myArray;
		myArray.PushBack( 0 );
		//myArray.Reserve( 50 );
		myArray.PushBack( 1 );
		myArray.PushBack( 2 );
		myArray.PushBack( 3 );
		myArray.PushBack( 4 );
		myArray.PushBack( 5 );
		myArray.PushBack( 6 );
		myArray.PushBack( 7 );
		myArray.PushBack( 8 );
		myArray.PushBack( 9 );
		myArray.Remove( 5 );
		myArray.PushBack( 10 );
		myArray.PushBack( 11 );
		myArray.RemoveElement( 10 );
		myArray.PushBack( 12 );


		cout << "iterator" << endl;
		for( TArrayVector::iterator it = myArray.begin(); it!=myArray.end(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "const iterator" << endl;
		for( TArrayVector::const_iterator it = myArray.cbegin(); it!=myArray.cend(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "reverse iterator" << endl;
		for( TArrayVector::iterator it = myArray.rbegin(); it!=myArray.rend(); --it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "reverse const iterator" << endl;
		for( TArrayVector::const_iterator it = myArray.crbegin(); it!=myArray.crend(); --it )
		{
			cout << *it << ",";
		}
END_TEST()