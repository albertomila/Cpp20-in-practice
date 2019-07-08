#pragma once
#include "stdafx.h"
#include "Samples/SortHelpers.h"


template< typename T
	, typename CONTAINER = T*
	, typename ELEMENT_AT = ElementAtArray >
class QuickSort
{
	typedef T TypeValue;
	typedef CONTAINER TContainerType;
	typedef ELEMENT_AT TElementAt;

public:
	static void Execute(CONTAINER& data, int size )
	{
		if( size <= 0 )
		{
			return;
		}

		quickSort( data, 0, size - 1 );
	}

	static void Print(CONTAINER& data, int size )
	{
		for( int i = 0; i<size; ++i)
		{
			TypeValue val = TElementAt::Get<T, CONTAINER>(data,i);
			cout << val << ",";
		}
		cout << endl;
		cout << endl;
	}

private:
	static void quickSort(CONTAINER& data, int left, int right)
	{
		int i = left;
		int j = right;

		int pivot = TElementAt::Get<T, CONTAINER>(data, (left + right) / 2 ); //middle element
		//partition
		while( i <= j ) 
		{
			while (TElementAt::Get<T, CONTAINER>(data, i) < pivot)
			{
				i++;
			}
			while (TElementAt::Get<T, CONTAINER>(data, j)> pivot) 
			{
				j--;
			}
			if ( i <= j ) 
			{
				Swap( TElementAt::Get<T, CONTAINER>(data, i), TElementAt::Get<T, CONTAINER>(data, j) );
				i++;
				j--;
			}
		}

		//recursion
		if ( left < j ) 
		{
			quickSort(data, left, j);
		}

		if ( i < right ) 
		{
			quickSort(data, i, right);
		}
	}
};