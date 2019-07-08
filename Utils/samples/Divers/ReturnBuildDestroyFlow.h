#pragma once
#include "stdafx.h"

namespace nsReturnBuildDestroyFlow
{
	struct CTest
	{
		CTest( const int& value ) 
			: m_x( value )
		{
			std::cout << "CTest()" << std::endl;
		}
		CTest( const CTest& value ) 
			: m_x( value.m_x )
		{
			std::cout << "CTest( const CTest& )" << std::endl;
		}
		~CTest () 
		{
			std::cout << "~CTest ()" << std::endl;
		}
		void operator == ( const CTest& value ) 
		{
			m_x = value.m_x;
			std::cout << "operator == " << std::endl;
		}

		int m_x;
	};

	CTest GetValue()
	{
		CTest test1(10);
		return test1;
	}

	CTest GetValue2()
	{
		return CTest(10);
	}

}


BEGIN_TEST(ReturnBuildDestroyFlow)
using namespace nsReturnBuildDestroyFlow;

    //Build test1
    //copy test1 into test2
    //destroy test1
    CTest test2 = GetValue();
    test2.m_x = 30;
    //destroy test2

    //Build test1
    CTest test3 = GetValue2();
    test3.m_x = 30;
    //destroy test3

	END_TEST()