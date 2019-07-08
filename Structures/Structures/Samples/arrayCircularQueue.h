#pragma once
#include "stdafx.h"

struct ArrayCircularQueuePrintHelpers;

template<class T>
class ArrayQueue
{
private:
	friend struct ArrayCircularQueuePrintHelpers; //debug purposes

	typedef T TypeValue;

public:
	ArrayQueue()
		: m_size( 2 )
		, m_data( new TypeValue[2] )
		, m_lastIndex( -1 )
		, m_headIndex( -1 )
	{
		for( unsigned int i = 0; i<m_size; ++i)
		{
			 m_data[i] = -1;
		}
	}

	ArrayQueue( unsigned int size )
		: m_size( size )
		, m_data( new TypeValue[size] )
		, m_lastIndex( -1 )
		, m_headIndex( -1 )
	{
	}

	~ArrayQueue()
	{
		if( m_data )
		{
			delete[] m_data;
		}
	}

	void Clear()
	{
		m_lastIndex = -1;
	}

	void Reserve( unsigned int newSize )
	{
		TypeValue* buffer = new TypeValue[m_size];

		int bufferCount = 0;
		for( int i = m_headIndex; i<= m_lastIndex; ++i)
		{
			buffer[bufferCount] = m_data[ i % Capacity() ];
			++bufferCount;
		}
		delete[] m_data;
		m_data = new TypeValue[newSize];

		for( unsigned int i = 0; i< m_size; ++i)
		{
			m_data[i] = buffer[i];
		}
		for( unsigned int i = m_size; i< newSize; ++i)
		{
			m_data[i] = -1;
		}
		delete[] buffer;
		m_headIndex = -1;
		if( m_lastIndex != -1 )
		{
			m_lastIndex = m_size - 1;
		}
		m_size = newSize;
	}
	void Push( const TypeValue& value )
	{
		if( Size() == Capacity() )
		{
			DoubleCapacity();
		}

		++m_lastIndex;
		m_data[GetLastIndex()] = value;

		if( m_headIndex == -1 )
		{
			m_headIndex = 0;
		}
	}

	TypeValue Pop()
	{
		TypeValue value = m_data[ GetHeadIndex() ];
		m_data[ GetHeadIndex() ] = -1;
		++m_headIndex;

		return value;
	}

	TypeValue& Last()
	{
		return m_data[ m_lastIndex ];
	}

	const TypeValue& Last() const
	{
		return m_data[ m_lastIndex ];
	}

	const TypeValue& GetValue( int index ) const
	{
		assert( index < Capacity() );
		return m_data[index];
	}

	TypeValue& GetValue( int index )
	{
		assert( index < Capacity() );
		return m_data[index];
	}

	unsigned int Size() const 
	{ 
		if( m_lastIndex == -1 && m_headIndex == -1 )
		{
			return 0;
		}

		return m_lastIndex - m_headIndex + 1;
	}

	unsigned int Capacity() const { return m_size; }
	bool IsFull() const{ return Size() == Capacity(); }

private:
	void DoubleCapacity()
	{
		if( m_size == 0 )
		{
			m_size = 1;
		}
		unsigned int newSize = m_size * 2;
		Reserve( newSize );
	}

	int GetHeadIndex() const
	{
		int headIndex = m_headIndex % m_size;
		return headIndex;
	}

	int GetLastIndex() const
	{
		int lastIndex = m_lastIndex % m_size;
		return lastIndex;
	}

private:
	TypeValue* m_data;
	int m_headIndex;
	int m_lastIndex;
	unsigned int m_size;
};

struct ArrayCircularQueuePrintHelpers
{
	template< class T >
	static void Print( const T& arrayQueue)
	{
		const T::TypeValue* bitArrayData = arrayQueue.m_data;

		COutColor( CoutColors::yellow );
		cout << "S(" << arrayQueue.Size() << "),C("<< arrayQueue.Capacity()<<") ";
		for( unsigned int i = 0; i< arrayQueue.Size() ; ++i)
		{
			if( i == arrayQueue.GetHeadIndex() )
			{
				COutColor( CoutColors::red );
				cout << "[H]";
			}
			if( i == arrayQueue.GetLastIndex() )
			{
				COutColor( CoutColors::red );
				cout << "[L]";
			}
			COutColor( CoutColors::grey );
			cout << bitArrayData[i] << ", ";
		}
		cout << endl;
	}
};
