#pragma once
#include "stdafx.h"


class RadixSort
{
	typedef int TypeValue;

public:
	static void Execute(int* data, int size )
	{
		if( size <= 0 )
		{
			return;
		}

		ExecuteRadixSort( data, size );
	}

	static void Print(int* data, int size )
	{
		for( int i = 0; i<size; ++i)
		{
			TypeValue val = data[i];
			cout << val;
			if( size < 30 )
			{
				cout << ",";
			}
			else
			{
				cout << endl;
			}
		}
		cout << endl;
	}

private:
	static void ExecuteRadixSort(int* data, int size )
	{
		int maxValue = 0;
		for( int i = 0; i<size; ++i)
		{
			if( data[i] > maxValue) 
			{
				maxValue = data[i];
			}
		}

		int numDigits = 0;
		while( maxValue > 0 )
		{
			maxValue /= 10;
			++numDigits;
		}

		std::vector<int> buckets[10];

		unsigned int powOfTen = 1;
		for(int i = 0; i< numDigits; ++i )
		{
			for( int i = 0; i<size; ++i)
			{
				int bucketIndex = (data[i] / powOfTen) % 10; 
				buckets[bucketIndex].push_back( data[i] );
			}

			unsigned int count( 0 );
			for( int i = 0; i<10; ++i)
			{
				std::vector<int>& vectorBucket = buckets[i];
				for( std::vector<int>::iterator it = vectorBucket.begin(); 
					 it != vectorBucket.end();
					 ++it)
				{
					data[count] = *it;
					++count;
				}
			}

			for( int i = 0; i<10; ++i)
			{
				buckets[i].resize( 0 );
			}
			powOfTen *= 10;
		}
	}
};