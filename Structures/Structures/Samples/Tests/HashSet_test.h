#pragma once
#include "stdafx.h"
#include "Samples/HashSet.h"

BEGIN_TEST(TestHashSet)
		typedef HashSet<float> THashSetFloat;
		THashSetFloat hashTable1;
		hashTable1.Set( 0.1f );
		hashTable1.Set( 0.2f );
		hashTable1.Set( 1.3f );
		hashTable1.Set( 1.2f );
		hashTable1.Set( 2.3f );
		hashTable1.Set( 2.2f );
		hashTable1.Set( 3.3f );
		hashTable1.Set( 3.2f );
		hashTable1.Set( 4.3f );
		hashTable1.Set( 4.2f );
		hashTable1.Set( 5.3f );
		hashTable1.Set( 5.2f );
		hashTable1.Set( 6.3f );
		hashTable1.Set( 100.f );
		hashTable1.Set( 150.f );
		HashSetPrintHelpers::Print( hashTable1 );


		cout << "iterator" << endl;
		for( THashSetFloat::iterator it = hashTable1.begin(), end = hashTable1.end() ; it != end; ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		cout << "const_iterator" << endl;
		for( THashSetFloat::const_iterator it = hashTable1.cbegin(), end = hashTable1.cend() ; it != end; ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		typedef HashSet<int, 3> THashSetInt;
		THashSetInt hashTable2;
		hashTable2.Set( 1 );
		hashTable2.Set( 2 );
		hashTable2.Set( 3 );
		hashTable2.Set( 4 );
		hashTable2.Set( 5 );
		hashTable2.Set( 6 );
		hashTable2.Set( 7 );
		hashTable2.Set( 8 );
		hashTable2.Set( 9 );
		hashTable2.Set( 10 );
		hashTable2.Set( 11 );
		hashTable2.Set( 12 );
		HashSetPrintHelpers::Print( hashTable2 );

		cout << "iterator" << endl;
		for( THashSetInt::iterator it = hashTable2.begin(), end = hashTable2.end() ; it != end; ++it )
		{
			cout << *it << ",";
		}
		cout << endl;

		typedef HashSet<char*> THashSetString;
		THashSetString hashTable3;
		hashTable3.Set( "test1" );
		hashTable3.Set( "test2" );
		hashTable3.Set( "test3" );
		hashTable3.Set( "test4" );
		hashTable3.Set( "test5" );
		hashTable3.Set( "test6" );
		hashTable3.Set( "test7" );
		hashTable3.Set( "test8" );
		hashTable3.Set( "test9" );
		hashTable3.Set( "test10" );
		hashTable3.Set( "test11" );
		hashTable3.Set( "test12" );
		hashTable3.Set( "test13" );
		hashTable3.Set( "test14" );
		hashTable3.Set( "test15" );
		hashTable3.Set( "test16" );
		hashTable3.Set( "test17" );
		hashTable3.Set( "test18" );
		HashSetPrintHelpers::Print( hashTable3 );

		cout << "iterator" << endl;
		for( THashSetString::iterator it = hashTable3.begin(), end = hashTable3.end() ; it != end; ++it )
		{
			cout << *it << ",";
		}
		cout << endl;
END_TEST()