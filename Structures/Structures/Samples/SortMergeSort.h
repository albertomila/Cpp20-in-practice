#pragma once
#include "stdafx.h"


struct MergeSortElementAtVectorString
{
	template<typename T, typename CONTAINER >
	static T& Get( std::vector<T>& values, int index )
	{
		return values.at( index ) ;
	}

	template<typename T, typename CONTAINER >
	static void Set( std::vector<T>& values, int index, const T& value )
	{ 
		values.at( index ) = value;
	}

	template<typename T, typename CONTAINER >
	static bool IsLess( std::vector<std::string>& values, int index, int index2 )
	{ 
		return values.at( index ).compare( values.at( index2 ) ) <= 0;
	}
};
template< typename T
		, typename CONTAINER = T*
		, typename ELEMENT_AT = ElementAtArray >
class MergerSort
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

		MergeSort( data, 0, size - 1 );
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
	static void MergeSort(CONTAINER& data, int left, int right )
	{
		if (right>left)
		{
			int pivot = left + ((right - left)/2);

			MergeSort(data, left, pivot);
			MergeSort(data, pivot+1, right);
			merge(data, left, pivot, right);
		}
	}

	static void merge(CONTAINER& data, int left, int pivot, int right)
	{
		// Variables declaration. 
		TypeValue* b = new TypeValue[right+1-left];
		int h,i,j,k;
		h=left;
		i=0;
		j=pivot+1;
		// Merges the two array's into b[] until the first one is finish
		while( (h<=pivot) && (j<=right) )
		{
			if( TElementAt::IsLess<T, CONTAINER>(data,h,j ) ) 
			//if( TElementAt::Get<T, CONTAINER>(data,h) <= TElementAt::Get<T, CONTAINER>(data,j) )
			{
				b[i]=TElementAt::Get<T, CONTAINER>(data,h);
				h++;
			}
			else
			{
				b[i]=TElementAt::Get<T, CONTAINER>(data,j);
				j++;
			}
			i++;
		}
		// Completes the array filling in it the missing values
		if(h>pivot)
		{
			for(k=j;k<=right;k++)
			{
				b[i]=TElementAt::Get<T, CONTAINER>(data,k);
				i++;
			}
		}
		else
		{
			for(k=h;k<=pivot;k++)
			{
				b[i]=TElementAt::Get<T, CONTAINER>(data,k);
				i++;
			}
		}

		// Prints into the original array
		for( int i = 0; i<(right+1-left); ++i) 
		{
			TElementAt::Set<T, CONTAINER>(data,i + left, b[i] );
		}

		delete[] b;
	}
};