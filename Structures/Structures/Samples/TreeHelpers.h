#pragma once
#include "stdafx.h"

template<class T, class V>
struct PairTypeOperations
{
	typedef T TypeKey;
	typedef V TypeValue;
	typedef std::pair< T, V > TypeValuePair;

	static bool IsLess( const TypeValuePair& value1, const TypeValuePair& value2 )
	{
		return value1.first < value2.first;
	}

	static void Print( const TypeValuePair& value1 )
	{
		cout << "[" << value1.first << "]" << value1.second;
	}
};
