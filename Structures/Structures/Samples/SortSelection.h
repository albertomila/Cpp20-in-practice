#pragma once
#include "stdafx.h"
#include "Samples/SortHelpers.h"

template< typename T
	, typename CONTAINER = T*
	, typename ELEMENT_AT = ElementAtArray >
class SelectionSort
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

		ExecuteSelectionSort( data, size );
	}

	static void Print(CONTAINER& data, int size )
	{
		for( int i = 0; i<size; ++i)
		{
			TypeValue val = TElementAt::Get<T, CONTAINER>(data,i);
			cout << val << ",";
		}
		cout << endl;
	}

private:
	static void ExecuteSelectionSort(CONTAINER& data, int size )
	{
		for( int i = 0; i<size; ++i)
		{
			TypeValue& currentValue = TElementAt::Get<T, CONTAINER>(data,i);

			TypeValue minValue = currentValue;
			int minIndex = i;
			for( int j = i; j<size; ++j)
			{
				TypeValue valueJ = TElementAt::Get<T, CONTAINER>(data,j);
				if( valueJ <= minValue )
				{
					minValue = valueJ;
					minIndex = j;
				}
			}

			TypeValue& minValueFound = TElementAt::Get<T, CONTAINER>(data,minIndex);
			Swap(currentValue, minValueFound);
		}
	}
};