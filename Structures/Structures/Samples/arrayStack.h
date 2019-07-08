#pragma once
#include "stdafx.h"

template<class T>
class ArrayStack
{
	typedef T TypeValue;
public:
	ArrayStack()
		: m_size( 0 )
		, m_data( new TypeValue[0] )
		, m_lastIndex( -1 )
	{
	}

	ArrayStack( unsigned int size )
		: m_size( size )
		, m_data( new TypeValue[size] )
		, m_lastIndex( -1 )
	{
	}

	~ArrayStack()
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
		for( unsigned int i = 0; i< m_size; ++i)
		{
			buffer[i] = m_data[i];
		}

		delete[] m_data;
		m_data = new TypeValue[newSize];

		for( unsigned int i = 0; i< m_size; ++i)
		{
			m_data[i] = buffer[i];
		}
		delete[] buffer;
		m_size = newSize;
	}
	void Push( const TypeValue& value )
	{
		if( m_lastIndex == m_size - 1 )
		{
			DoubleCapacity();
		}

		++m_lastIndex;
		m_data[m_lastIndex] = value;
	}

	TypeValue Pop()
	{
		TypeValue& value = m_data[ m_lastIndex ];
		--m_lastIndex;

		return value;
	}

	void Insert( const TypeValue& value, unsigned int index )
	{
		assert( index < Size() );

		if( IsFull() )
		{
			DoubleCapacity();
		}

		unsigned int bufferSize = Size() - index;
		TypeValue* buffer = new TypeValue[bufferSize];
		for( unsigned int i = 0; i< bufferSize; ++i)
		{
			buffer[i] = m_data[ index + i ];
		}

		m_data[index] = value;
		++m_lastIndex;

		for( unsigned int i = 0; i < bufferSize; ++i)
		{
			m_data[index + 1 + i] = buffer[i];
		}
	}

	TypeValue& Last()
	{
		return m_data[ m_lastIndex ];
	}

	const TypeValue& Last() const
	{
		return m_data[ m_lastIndex ];
	}

	unsigned int Size() const { return m_lastIndex + 1; }
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

private:
	TypeValue* m_data;
	int m_lastIndex;
	unsigned int m_size;
};