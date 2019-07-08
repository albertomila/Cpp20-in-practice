#pragma once
#include "stdafx.h"

namespace nsIterator
{
	template<class TypeValue>
	class CustomArrayIterator
	{
	public:
		CustomArrayIterator(TypeValue* ptr)
			: m_ptr(ptr)
		{
		}

		CustomArrayIterator<TypeValue>& operator = (const CustomArrayIterator<TypeValue>& rawIterator)
		{
			m_ptr = rawIterator.ptr;
			return *this;
		}

		CustomArrayIterator<TypeValue>& operator++()
		{
			++m_ptr;
			return *this;
		}
		CustomArrayIterator<TypeValue>& operator--()
		{
			--m_ptr;
			return *this;
		}

		bool operator == (const CustomArrayIterator<TypeValue>& other) const
		{
			return (m_ptr == other.getConstPtr());
		}

		bool operator != (const CustomArrayIterator<TypeValue>& other) const
		{
			return (m_ptr != other.getConstPtr());
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
		TypeValue* getPtr()const { return m_ptr; }
		const TypeValue* getConstPtr()const { return m_ptr; }

	private:
		TypeValue* m_ptr;
	};

	template<class T, int SIZE>
	class CCustomArray
	{
	public:
		typedef CustomArrayIterator<T> iterator;

		T& GetValue(int i)
		{
			return _data[i];
		}

		int GetSize() const
		{
			return SIZE;
		}

		iterator begin() { return iterator(_data); }
		iterator end() { return iterator(_data + SIZE); }

	private:
		T _data[SIZE];
	};
}

BEGIN_TEST(Iterator)
	using namespace nsIterator;

	using TCustomArray = CCustomArray<int, 10>;
	TCustomArray customArray;

	for (int& value : customArray)
	{
		value = 99;
	}

	for (TCustomArray::iterator it = customArray.begin(); it != customArray.end(); ++it)
	{
		UNUSED(*it);
	}

END_TEST()