#pragma once
#include "stdafx.h"


template<typename TypeValue>
class ArrayVectorIterator
{
public:
	ArrayVectorIterator(TypeValue* ptr)
		: m_ptr(ptr)
	{
	}

	ArrayVectorIterator<TypeValue>& operator = (const ArrayVectorIterator<TypeValue>& rawIterator)
	{
		m_ptr = rawIterator.ptr;
		return *this;
	}

	bool operator == (const ArrayVectorIterator<TypeValue>& rawIterator) const
	{
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator != (const ArrayVectorIterator<TypeValue>& rawIterator) const
	{
		return (m_ptr != rawIterator.getConstPtr());
	}

	ArrayVectorIterator<TypeValue>& operator++()
	{
		++m_ptr;
		return *this;
	}
	ArrayVectorIterator<TypeValue>& operator--()
	{
		--m_ptr;
		return *this;
	}

	ArrayVectorIterator<TypeValue>& operator+( const int amount )
	{
		m_ptr += amount;
		return *this;
	}
	ArrayVectorIterator<TypeValue>& operator-( const int amount )
	{
		m_ptr -= amount;
		return *this;
	}

	TypeValue& operator*()
	{
		return *m_ptr;
	}

	const TypeValue& operator*()const
	{
		return *m_ptr;
	}

	TypeValue* operator->()
	{
		return m_ptr;
	}

private:
	TypeValue* getPtr()const{return m_ptr;}
	const TypeValue* getConstPtr()const{return m_ptr;}

private:
	TypeValue* m_ptr;
};

template<typename TypeValue>
class ArrayVectorReverseIterator : public ArrayVectorIterator<TypeValue>
{
	typedef ArrayVectorIterator<TypeValue> super;

public:
	ArrayVectorReverseIterator(TypeValue* ptr)
		: super(ptr)
	{
	}

	ArrayVectorReverseIterator<TypeValue>& operator++()
	{
		super::operator--();
		return *this;
	}

	ArrayVectorReverseIterator<TypeValue>& operator--()
	{
		super::operator++();
		return *this;
	}
};

template<class T>
class ArrayVector
{
public:
	typedef T TypeValue;

	typedef ArrayVectorIterator<TypeValue> iterator;
	typedef ArrayVectorIterator<const TypeValue> const_iterator;
	typedef ArrayVectorReverseIterator<TypeValue> reverse_iterator;
	typedef ArrayVectorReverseIterator<const TypeValue> const_reverse_iterator;

public:
	iterator begin(){return iterator(m_data);}
	iterator end(){return iterator(m_data + Size());}

	const_iterator cbegin(){return const_iterator(m_data);}
	const_iterator cend(){return const_iterator(m_data + Size());}

	reverse_iterator rbegin(){return reverse_iterator(m_data + Size() - 1);}
	reverse_iterator rend(){return reverse_iterator(m_data - 1);}

	const_reverse_iterator crbegin(){return const_reverse_iterator(m_data + Size() - 1);}
	const_reverse_iterator crend(){return const_reverse_iterator(m_data - 1);}

	ArrayVector()
		: m_size( 0 )
		, m_data( new TypeValue[0] )
		, m_lastIndex( -1 )
	{
	}

	ArrayVector( unsigned int size )
		: m_size( size )
		, m_data( new TypeValue[size] )
		, m_lastIndex( -1 )
	{
	}

	~ArrayVector()
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
	void PushBack( const TypeValue& value )
	{
		if( m_lastIndex == m_size - 1 )
		{
			DoubleCapacity();
		}

		++m_lastIndex;
		m_data[m_lastIndex] = value;
	}

	TypeValue PopBack()
	{
		TypeValue& value = m_data[ m_lastIndex ];
		--m_lastIndex;

		return value;
	}

	void Remove( unsigned int index )
	{
		assert( index < Size() );

		for( unsigned int i = index; i< Size() - 1; ++i)
		{
			m_data[i] = m_data[ i + 1 ];
		}
		--m_lastIndex;
	}

	void RemoveElement( const TypeValue& value )
	{
		for( unsigned int i = 0; i< Size(); ++i)
		{
			if( value == m_data[i] )
			{
				Remove( i );
			}
		}
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
