#pragma once
#include "stdafx.h"

namespace nsEraseRemove
{
	class CTest
	{
	public:
		CTest()
			: m_x( 10 )
		{
		}

		~CTest()
		{
			m_x = 0;
		}

		int GetValue() const{ return m_x; }
	private:
		int m_x;
	};

	bool RemovePredicate ( const CTest& value ) 
	{ 
		return value.GetValue() == 10;
	}
}

BEGIN_TEST(EraseRemove)
	using namespace nsEraseRemove;
    std::vector<CTest> list;

    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );
    list.push_back( CTest() );

    
    list.erase( std::remove_if( list.begin(), list.end(), RemovePredicate ) //returns iterator
                , list.end() );
END_TEST()