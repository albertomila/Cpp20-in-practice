#pragma once
#include "stdafx.h"
#include "Samples/SortHelpers.h"


template< typename T
	, typename CONTAINER = T*
	, typename ELEMENT_AT = ElementAtArray >
class BubbleSort
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

		ExecuteBubbleSort( data, size );
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
	static void ExecuteBubbleSort(CONTAINER& data, int size )
	{
		for( int i = 1; i<size; ++i)
		{
			for( int j = 0; j < size-i; ++j)
			{
				TypeValue& currentValue = TElementAt::Get<T, CONTAINER>(data,j+1);
				TypeValue& valueJ = TElementAt::Get<T, CONTAINER>(data,j);
				if( valueJ > currentValue )
				{
					Swap(currentValue, valueJ);
					//Print( data, size );
				}
			}
		}
	}
};