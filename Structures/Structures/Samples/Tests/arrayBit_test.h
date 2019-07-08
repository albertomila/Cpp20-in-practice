#include "stdafx.h"
#include "Samples/arrayBit.h"

BEGIN_TEST(TestArrayBit)
		typedef BitArray<char> TBitArray;
		TBitArray bitArray;
		
		for( int i =0; i<32; ++i)
		{
			bitArray.SetBit( i, 1 );
			BitArrayPrintHelpers::Print( bitArray );
		}

		for( int i =0; i<32; i+=8)
		{
			bitArray.SetBit( i, 0 );
			BitArrayPrintHelpers::Print( bitArray );
		}

		for( int i =0; i<32; ++i)
		{
			cout << bitArray.GetBit( i);
		}

		cout << "iterator" << endl;
		BitArrayPrintHelpers::PrintIterative( bitArray );
		cout << endl;

		cout << "iterator" << endl;
		for( TBitArray::iterator it = bitArray.begin(), endit = bitArray.end(); it != endit; ++it )
		{
			cout << it->GetBit();
		}
		cout << endl;

		cout << "const_iterator" << endl;
		for( TBitArray::const_iterator it = bitArray.cbegin(), endit = bitArray.cend(); it != endit; ++it )
		{
			cout << (*it).GetBit();
		}
		cout << endl;

		cout << "reverse iterator" << endl;
		for( TBitArray::reverse_iterator it = bitArray.rbegin(), endit = bitArray.rend(); it != endit; ++it )
		{
			cout << it->GetBit();
		}
		cout << endl;

		cout << "const reverse iterator" << endl;
		for( TBitArray::const_reverse_iterator it = bitArray.crbegin(), endit = bitArray.crend(); it != endit; ++it )
		{
			cout << (*it).GetBit();
		}
		cout << endl;

		cout << "Clean all bits one by one" << endl;
		for( TBitArray::iterator it = bitArray.begin(), endit = bitArray.end(); it != endit; ++it )
		{
			it->SetBit(false);
			cout << it->GetBit();
		}
		cout << endl;
END_TEST()