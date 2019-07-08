#pragma once
#include "stdafx.h"

#include <vector>

template< typename T >
void Swap( T& value1, T& value2 )
{
	if( value1 != value2)
	{
		T tmp = value1;
		value1 = value2;
		value2 = tmp;
	}
}

struct ElementAtArray
{
	template<typename T, typename CONTAINER >
	static T& Get( CONTAINER& values, int index )
	{
		return values[index];
	}

	template<typename T, typename CONTAINER >
	static void Set( CONTAINER& values, int index, const T& value )
	{ 
		values[index] = value;
	}

	template<typename T, typename CONTAINER >
	static bool IsLess( CONTAINER& values, int index, int index2 )
	{ 
		return values[index] <= values[index];
	}
};

struct ElementAtVector
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
	static bool IsLess( std::vector<T>& values, int index, int index2 )
	{ 
		return values.at( index ) <= values.at( index );
	}
};
