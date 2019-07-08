#pragma once
#include "stdafx.h"
#include <type_traits>

///////////////////////////////////////////////////////////////
template <bool, class T>
struct enable_if_dispatcher
{
};

template <class T>
struct enable_if_dispatcher<true, T>
{
	typedef T type;
};


///////////////////////////////////////////////////////////////
template <class T>
typename enable_if_dispatcher<std::is_arithmetic<T>::value, T>::type Negate(const T& t)
{
	return -t;
}

///////////////////////////////////////////////////////////////
template <class T>
typename void Testcast(const T& t)
{
	typedef enable_if_dispatcher<std::is_arithmetic<T>::value, T>::type TTypeCast;
}

class EnableIfTest
{
	float m_f;
};

BEGIN_TEST(EnableIf)
	float f = Negate(99.f);
	int i = Negate(1);

	EnableIfTest eft;
	//Testcast(eft);  //error doesn't compile
END_TEST()