#pragma once
#include "stdafx.h"

template<typename TypeValue>
class StaticArrayIterator
{
public:
	StaticArrayIterator(TypeValue* ptr)
		: m_ptr(ptr)
	{
	}

	StaticArrayIterator<TypeValue>& operator = (const StaticArrayIterator<TypeValue>& rawIterator)
	{
		m_ptr = rawIterator.ptr;
		return *this;
	}

	bool operator == (const StaticArrayIterator<TypeValue>& rawIterator) const
	{
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator != (const StaticArrayIterator<TypeValue>& rawIterator) const
	{
		return (m_ptr != rawIterator.getConstPtr());
	}

	StaticArrayIterator<TypeValue>& operator++()
	{
		++m_ptr;
		return *this;
	}
	StaticArrayIterator<TypeValue>& operator--()
	{
		--m_ptr;
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
class StaticArrayReverseIterator : public StaticArrayIterator<TypeValue>
{
	typedef StaticArrayIterator<TypeValue> super;

public:
	StaticArrayReverseIterator(TypeValue* ptr)
		: super(ptr)
	{
	}

	StaticArrayReverseIterator<TypeValue>& operator++()
	{
		super::operator--();
		return *this;
	}

	StaticArrayReverseIterator<TypeValue>& operator--()
	{
		super::operator++();
		return *this;
	}
};

template<typename T, unsigned int SIZE>
class StaticArray
{
public:
	typedef T TypeValue;
	typedef StaticArrayIterator<TypeValue> iterator;
	typedef StaticArrayIterator<const TypeValue> const_iterator;

	typedef StaticArrayReverseIterator<TypeValue> reverse_iterator;
	typedef StaticArrayReverseIterator<const TypeValue> const_reverse_iterator;

public:
	StaticArray()
	{
	}

	~StaticArray()
	{
	}

	iterator begin(){return iterator(m_data);}
	iterator end(){return iterator(m_data + Capacity());}

	const_iterator cbegin(){return const_iterator(m_data);}
	const_iterator cend(){return const_iterator(m_data + Capacity());}

	reverse_iterator rbegin(){return reverse_iterator(m_data + Capacity() - 1);}
	reverse_iterator rend(){return reverse_iterator(m_data - 1);}

	const_reverse_iterator crbegin(){return const_reverse_iterator(m_data + Capacity() - 1);}
	const_reverse_iterator crend(){return const_reverse_iterator(m_data - 1);}

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

	void SetValue( TypeValue& value, int index )
	{
		assert( index < Capacity() );
		m_data[index] = value;
	}

	TypeValue& operator [] (int index)
	{
		return GetValue(index);
	}

	void operator = (TypeValue& value)
	{
		SetValue( value, index );
	}

	TypeValue& operator * ()
	{
		return m_data;
	}

	const TypeValue& operator * () const
	{
		return m_data;
	}

	int Size() const { return SIZE; }
	int Capacity() const { return SIZE; }

private:
	TypeValue m_data[SIZE];
};