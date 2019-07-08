#pragma once
#include "stdafx.h"
#include "Samples/SortHelpers.h"

template< typename T
	, typename CONTAINER = T*
	, typename ELEMENT_AT = ElementAtArray >
class InsertionSort
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

		ExecuteInsertionSort( data, size );
	}

	static void Print(CONTAINER& data, int size )
	{
		for( int i = 0; i<size; ++i)
		{
			TypeValue val = TElementAt::Get<T, CONTAINER>(data,i);
			cout << val;
			if( size < 30 )
			{
				cout << ",";
			}
			else
			{
				cout << endl;
			}
		}
		cout << endl;
	}

private:
	static void ExecuteInsertionSort(CONTAINER& data, int size )
	{
		for( int i = 0; i<size; ++i)
		{
			for( int j = i-1; j>=0; --j)
			{
				TypeValue& currentValue = TElementAt::Get<T, CONTAINER>(data,j+1);
				TypeValue& valueJ = TElementAt::Get<T, CONTAINER>(data,j);
				if( currentValue < valueJ )
				{
					Swap(currentValue, valueJ);
				}
				else
				{
					break;
				}
			}
		}
	}
};