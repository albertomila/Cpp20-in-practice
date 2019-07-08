#pragma once
#include "stdafx.h"

#include "math.h"


struct HeapArrayPrintHelpers;

template< typename T
		, bool IS_MAX_HEAP = true
		, unsigned int SIZE = 256>
class HeapArray
{
private:
	friend struct HeapArrayPrintHelpers;
	typedef T TTypeValue;

public:
	HeapArray()
		: m_lastIndex(0)
	{
		for( unsigned int i = 0; i<SIZE; ++i )
		{
			m_data[i] = TTypeValue();
		}
	}

	~HeapArray()
	{
	}

	void PushValue( const TTypeValue& value )
	{
		assert( m_lastIndex + 1 < SIZE );

		m_data[m_lastIndex] = value;

		Heapify();

		++m_lastIndex;
	}
	
	void RemoveLast()
	{
		assert( m_lastIndex > 0);

		--m_lastIndex;
		m_data[m_lastIndex] = TTypeValue();
	}

	void RemoveTop()
	{
		Swap( 0, m_lastIndex - 1);
		RemoveLast();
		HeapifyTop();
	}
	bool Comparator( const TTypeValue& value1, const TTypeValue& value2 )
	{
		if( IS_MAX_HEAP )
		{
			return value1 < value2;
		}
		else
		{
			return value1 > value2;
		}
	}

	void HeapifyTop()
	{
		unsigned int currentIndex = 0;
		while( currentIndex < m_lastIndex)
		{
			unsigned int leftChildIndex = GetLeftChildIndex(currentIndex);
			unsigned int rightChildIndex = GetRightChildIndex(currentIndex);
			unsigned int childIndex = leftChildIndex;

			if( leftChildIndex < m_lastIndex )
			{
				if( rightChildIndex < m_lastIndex )
				{
					childIndex = Comparator( m_data[leftChildIndex], m_data[rightChildIndex] )
								? rightChildIndex 
								: leftChildIndex;
				}
			}
			else
			{
				break;
			}

			if( Comparator(m_data[currentIndex],  m_data[childIndex]) )
			{
				Swap(currentIndex, childIndex);
			}
			currentIndex = childIndex;
		}
	}



private:
	void Heapify()
	{
		if( m_lastIndex == 0 )
		{
			return;
		}

		unsigned int currentIndex = m_lastIndex;
		unsigned int parentIndex = GetParentIndex(currentIndex);
		while( Comparator(m_data[parentIndex], m_data[currentIndex]) )
		{
			Swap( parentIndex, currentIndex);

			currentIndex = parentIndex;
			parentIndex = GetParentIndex(currentIndex);
			if( currentIndex == 0 )
			{
				break;
			}
		}
	}

	void Swap( unsigned int index1, unsigned int index2 )
	{
		TTypeValue tempValue = m_data[index2];
		m_data[index2] = m_data[index1];
		m_data[index1] = tempValue;
	}

	unsigned int GetParentIndex( unsigned int index )
	{
		return (index-1) / 2;
	}
	unsigned int GetLeftChildIndex( unsigned int index )
	{
		return (index * 2) + 1;
	}
	unsigned int GetRightChildIndex( unsigned int index )
	{
		return (index * 2) + 2;
	}

private:
	TTypeValue m_data[SIZE];
	unsigned int m_lastIndex;
};

typedef HeapArray<int, true> TMaxHeapArray;
typedef HeapArray<int, false> TMinHeapArray;

struct HeapArrayPrintHelpers
{
	template< class T >
	static void Print( const T& heapArray )
	{
		if( heapArray.m_lastIndex == 0)
		{
			cout << "EMPTY"  << endl;
		}
		unsigned int currentIndex = 0;
		unsigned int currentLevel = 0;
		int level = 0;

		while( currentIndex < heapArray.m_lastIndex )
		{
			int maxIteration = static_cast<int>(pow( 2.f, static_cast<int>(currentLevel) ));
			for( int i = 0; i<maxIteration; ++i)
			{
				if( currentIndex + i == heapArray.m_lastIndex )
				{
					break;
				}
				else if( i % 2 == 0)
				{
					COutColor( CoutColors::yellow );
				}
				else
				{
					COutColor( CoutColors::grey );
				}

				cout << heapArray.m_data[currentIndex + i] << ",";
			}

			currentIndex += maxIteration; 
			++currentLevel;
			cout << endl;
		}
		cout << endl;
	}

	template< class T >
	void PrintArray(const T& heapArray )
	{
		if( heapArray.m_lastIndex == 0)
		{
			cout << "EMPTY"  << endl;
		}
		for( unsigned int i = 0; i<heapArray.m_lastIndex; ++i )
		{
			cout << heapArray.m_data[i] << ",";
		}

		cout << endl;
	}
};