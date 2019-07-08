#pragma once
#include "stdafx.h"
#include "Samples/SortHelpers.h"


template< typename T
	, unsigned int MAXIMUM_ARRAY_VALUE
	, typename CONTAINER = T*
	, typename ELEMENT_AT = ElementAtArray >
class BucketSort
{
	typedef T TypeValue;
	typedef CONTAINER TContainerType;
	typedef ELEMENT_AT TElementAt;

	struct BucketSortNode
	{
		BucketSortNode()
			: m_next( NULL )
		{
		}
		TypeValue m_value;
		BucketSortNode* m_next;
	};

public:
	static void Execute(CONTAINER& data, int size )
	{
		if( size <= 0 )
		{
			return;
		}

		ExecuteBucketSort( data, size );
	}

	static void Print(CONTAINER& data, int size )
	{
		for( int i = 0; i<size; ++i)
		{
			/*
			if( i < size -2 )
			{
				TypeValue val1 = TElementAt::Get<T, CONTAINER>(data,i);
				TypeValue val2 = TElementAt::Get<T, CONTAINER>(data,i+1);
				if( val1 > val2 )
				{
					assert( false );
				}
			}
			*/
			TypeValue val = TElementAt::Get<T, CONTAINER>(data,i);
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
	static void ExecuteBucketSort(CONTAINER& data, int size )
	{
		BucketSortNode** bucketBuffer = new BucketSortNode*[size]();

		//Dump all values into a table of linked lists
		for( int i = 0; i<size; ++i)
		{
			TypeValue& currentValue = TElementAt::Get<T, CONTAINER>(data,i);
			unsigned int index = currentValue * size / (MAXIMUM_ARRAY_VALUE + 1);

			if( bucketBuffer[index] == NULL )
			{
				bucketBuffer[index] = new BucketSortNode();
				bucketBuffer[index]->m_value = currentValue;
			}
			else
			{
				if( bucketBuffer[index]->m_value > currentValue )
				{
					BucketSortNode* newNode = new BucketSortNode();
					newNode->m_value = currentValue;
					newNode->m_next = bucketBuffer[index];
					bucketBuffer[index] = newNode;
				}
				else
				{
					BucketSortNode* currentNode = bucketBuffer[index];

					while( currentNode->m_next != NULL 
						&& currentNode->m_next->m_value < currentValue)
					{
						currentNode = currentNode->m_next;
					}

					BucketSortNode* newNode = new BucketSortNode();
					newNode->m_value = currentValue;
					newNode->m_next = currentNode->m_next;
					currentNode->m_next = newNode;
				}
			}
		}

		//Dump all the table back into the array.
		unsigned int count = 0;
		for( int i = 0; i<size; ++i)
		{
			BucketSortNode* currentNode = bucketBuffer[i];
			if( currentNode != NULL )
			{
				TElementAt::Set<T, CONTAINER>(data,count, currentNode->m_value );
				++count;

				while( currentNode->m_next != NULL )
				{
					currentNode = currentNode->m_next;

					TElementAt::Set<T, CONTAINER>(data,count, currentNode->m_value );
					++count;
				}
			}
		}

		//Release memory
		for( int i = 0; i<size; ++i)
		{
			BucketSortNode* currentNode = bucketBuffer[i];
			if( currentNode != NULL )
			{
				BucketSortNode* prevNode = currentNode;
				while( currentNode->m_next != NULL )
				{
					currentNode = currentNode->m_next;
					delete prevNode;
					prevNode = currentNode;
				}
				delete prevNode;
			}
		}
		delete[] bucketBuffer;
	}
};