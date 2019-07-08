#pragma once
#include "stdafx.h"
#include "Samples/array.h"

BEGIN_TEST(TestArray)
		typedef StaticArray<int, 10> TStaticArray;

		TStaticArray myArray;
		for( int i = 0; i < myArray.Size(); ++i )
		{
			myArray[i] = i;
		}

		cout << "iterator" << endl;
		for( TStaticArray::iterator it = myArray.begin(); it!=myArray.end(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "const iterator" << endl;
		for( TStaticArray::const_iterator it = myArray.cbegin(); it!=myArray.cend(); ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "reverse iterator" << endl;
		for( TStaticArray::iterator it = myArray.rbegin(); it!=myArray.rend(); --it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "reverse const iterator" << endl;
		for( TStaticArray::const_iterator it = myArray.crbegin(); it!=myArray.crend(); --it )
		{
			cout << *it << ",";
		}
END_TEST()

/*
//tests
int main(void)
{
	typedef StaticArray<int, 10> TStaticArray;

	TStaticArray myArray;
	for( int i = 0; i < myArray.Size(); ++i )
	{
		myArray[i] = i;
	}

	cout << "iterator" << endl;
	for( TStaticArray::iterator it = myArray.begin(); it!=myArray.end(); ++it )
	{
		cout << *it << ",";
	}
	cout << endl;
	
	cout << "const iterator" << endl;
	for( TStaticArray::const_iterator it = myArray.cbegin(); it!=myArray.cend(); ++it )
	{
		cout << *it << ",";
	}
	cout << endl;

	cout << "reverse iterator" << endl;
	for( TStaticArray::iterator it = myArray.rbegin(); it!=myArray.rend(); --it )
	{
		cout << *it << ",";
	}
	cout << endl;

	cout << "reverse const iterator" << endl;
	for( TStaticArray::const_iterator it = myArray.crbegin(); it!=myArray.crend(); --it )
	{
		cout << *it << ",";
	}
}*/