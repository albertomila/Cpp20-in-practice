#pragma once
#include "stdafx.h"
#include "Samples/HashTable.h"

BEGIN_TEST(TestHashTable)
		typedef HashTable<float, float> THashTableFloat;
		THashTableFloat hashTable1;
		hashTable1[0.1f] = 1.1f;
		hashTable1[0.2f] = 1.2f;
		hashTable1[0.3f] = 3.2f;
		hashTable1[0.4f] = 4.2f;
		hashTable1[0.5f] = 5.2f;
		hashTable1[1.3f] = 1.3f;
		hashTable1[1.4f] = 1.4f;
		hashTable1[2.5f] = 1.5f;
		hashTable1[2.6f] = 1.6f;
		hashTable1[3.7f] = 1.7f;
		hashTable1[3.8f] = 1.8f;
		HashTablePrintHelpers::Print( hashTable1 );

		cout << "iterator" << endl;
		for( THashTableFloat::iterator it = hashTable1.begin(), end = hashTable1.end() ; it != end; ++it )
		{
			cout << "[" << it->m_key << "," << it->m_value << "],";
		}
		cout << endl;

		cout << "const_iterator" << endl;
		for( THashTableFloat::const_iterator it = hashTable1.cbegin(), end = hashTable1.cend() ; it != end; ++it )
		{
			cout << "[" << (*it).m_key << "," << (*it).m_value << "],";
		}
		cout << endl;

		typedef HashTable<char*, char*> THashTableString;
		THashTableString hashTable2;
		hashTable2["test1"] = "test001";
		hashTable2["test2"] = "test002";
		hashTable2["test3"] = "test003";
		hashTable2["test4"] = "test004";
		hashTable2["test5"] = "test005";
		hashTable2["test6"] = "test006";
		hashTable2["test7"] = "test007";
		hashTable2["test8"] = "test008";
		hashTable2["test9"] = "test009";
		hashTable2["test10"] = "test010";
		hashTable2["test11"] = "test011";
		hashTable2["test12"] = "test012";
		hashTable2["test13"] = "test013";
		hashTable2["test14"] = "test014";
		hashTable2["test15"] = "test015";
		hashTable2["test16"] = "test016";
		HashTablePrintHelpers::Print( hashTable2 );


		typedef HashTable<int, int> THashTable;
		THashTable hashTable;
		hashTable.Push( 1, 10 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 201, 11 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 401, 11 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable[201] = 12;
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Remove( 201 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Remove( 1 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Remove( 401 );
		HashTablePrintHelpers::Print( hashTable );


		hashTable.Push( 2, 20 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 2, 21 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable[2] = 22;
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 3, 31 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 3, 32 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable[3] = 33;
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 4, 41 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 4, 42 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable[4] = 43;
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 5, 51 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable.Push( 5, 52 );
		HashTablePrintHelpers::Print( hashTable );
		hashTable[5] = 53;
		HashTablePrintHelpers::Print( hashTable );
END_TEST()