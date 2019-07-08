#pragma once
#include "stdafx.h"



template<typename T>
struct HashTableHash
{
	static unsigned int GetHash( const T& key, unsigned int TABLE_SIZE )
	{
		return static_cast<unsigned int>(key) % TABLE_SIZE;
	}
};

template<typename T>
struct HashTableHash<T*>
{
	static unsigned int GetHash( const T* key, unsigned int TABLE_SIZE )
	{
		return reinterpret_cast<unsigned int>( &(*key) ) % TABLE_SIZE;
	}
};

template<>
struct HashTableHash<char*>
{
	static unsigned int GetHash( const char* key, unsigned int TABLE_SIZE )
	{
		unsigned int h = 0;
		while (*key)
		{
			h = h << 1 ^ *key++;
		}
		return h % TABLE_SIZE;
	}
};


template< unsigned int TABLE_SIZE, typename TypeNodeValue, typename TypeHashData >
class HashTableIterator
{
private:
	typedef HashTableIterator<TABLE_SIZE, TypeNodeValue,TypeHashData> THashTableIterator;

public:
	HashTableIterator(unsigned int pos, TypeHashData* data, TypeNodeValue* ptr)
		: m_data( data )
		, m_ptr(ptr)
		, m_pos( pos )
	{
		//Search the first valid note from the indicated
		while( m_ptr == NULL )
		{
			if( m_pos < TABLE_SIZE )
			{
				++m_data;
				++m_pos;
				m_ptr = *m_data;
			}
			else
			{
				break;
			}
		}
	}

	THashTableIterator& operator = (const THashTableIterator& rawIterator)
	{
		m_data = rawIterator.m_data;
		m_ptr = rawIterator.ptr;
		return *this;
	}

	bool operator == (const THashTableIterator& rawIterator) const
	{
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator != (const THashTableIterator& rawIterator) const
	{
		return (m_ptr != rawIterator.getConstPtr());
	}

	THashTableIterator& operator++()
	{
		//Search the first valid note from the indicated
		m_ptr = m_ptr->m_next;
		while( m_ptr == NULL )
		{
			if( m_pos < TABLE_SIZE )
			{
				++m_data;
				++m_pos;
				m_ptr = *m_data;
			}
			else
			{
				break;
			}
		}
		return *this;
	}

	TypeNodeValue& operator*()
	{
		return *m_ptr;
	}

	const TypeNodeValue& operator*()const
	{
		return *m_ptr;
	}

	TypeNodeValue* operator->()
	{
		return m_ptr;
	}

private:
	TypeNodeValue* getPtr()const{return m_ptr;}
	const TypeNodeValue* getConstPtr()const{return m_ptr;}

private:
	TypeHashData* m_data;
	TypeNodeValue* m_ptr;
	unsigned int m_pos;
};


struct HashTablePrintHelpers;

template< class KEY
		, class VALUE
		, unsigned int TABLE_SIZE = 200
		, typename HASH_FUNCTION = HashTableHash<KEY> >
class HashTable
{
	friend struct HashTablePrintHelpers;

	template<class KEY, class VALUE>
	struct HashTableElement
	{
		typedef VALUE TypeValue;
		typedef KEY TypeKey;

		HashTableElement()
			: m_next(NULL)
		{
		}

		TypeKey m_key;
		TypeValue m_value;

		HashTableElement* m_next;
	};

public:
	typedef KEY TypeKey;
	typedef VALUE TypeValue;
	typedef HashTableElement<TypeKey, TypeValue> THashTableElement;

	typedef HashTableIterator<TABLE_SIZE, THashTableElement, THashTableElement* > iterator;
	typedef HashTableIterator<TABLE_SIZE, const THashTableElement, const THashTableElement *const> const_iterator;

public:
	iterator begin()
	{
		return iterator( 0, m_data, *m_data );
	}

	iterator end()
	{
		THashTableElement** endList = (m_data + GetSize());
		THashTableElement* endElement = *endList;
		return iterator( GetSize(), endList, endElement);
	}

	const_iterator cbegin()
	{
		return const_iterator( 0, m_data,  *m_data  );
	}

	const_iterator cend()
	{
		const THashTableElement*const * endList = (m_data + GetSize());
		const THashTableElement* endElement = *endList;
		return const_iterator( GetSize(), endList, endElement);
	}

public:
	HashTable()
	{
		//Using the parenthesis it initializes to NULL all pointers 
		m_data = new THashTableElement*[TABLE_SIZE]();
	}
	~HashTable()
	{
		for( int i = 0; i<TABLE_SIZE; ++i )
		{
			THashTableElement* currentKeyNode = m_data[i];
			while( currentKeyNode != NULL )
			{
				THashTableElement* nextNode = currentKeyNode->m_next;
				delete currentKeyNode;
				currentKeyNode = nextNode;
			}
		}

		delete[] m_data;
	}
	void Clear()
	{
		delete[] m_data;
		m_data = new THashTableElement*[TABLE_SIZE]();
	}

	void Push( const TypeKey& key, const TypeValue& value)
	{
		unsigned int hashValue = GetHash( key );

		THashTableElement* currentNode = m_data[ hashValue ];
		if( !currentNode )
		{
			currentNode = new THashTableElement();
			currentNode->m_key = key;
			currentNode->m_value = value;
			m_data[ hashValue ] = currentNode;
			return;
		}


		while( currentNode->m_next )
		{
			currentNode = currentNode->m_next;
		}

		THashTableElement* newNode = new THashTableElement();
		newNode->m_key = key;
		newNode->m_value = value;
		currentNode->m_next = newNode;
	}

	TypeValue& operator[]( const TypeKey& key ) 
	{
		return Get( key );
	}

	TypeValue& Get( const TypeKey& key )
	{
		unsigned int hashValue = GetHash( key );

		THashTableElement* currentNode = m_data[ hashValue ];
		if( !currentNode )
		{
			currentNode = new THashTableElement();
			currentNode->m_key = key;
			currentNode->m_value = TypeValue();
			m_data[ hashValue ] = currentNode;

			return currentNode->m_value;
		}

		THashTableElement* prevNode = NULL;
		while( currentNode )
		{
			if( currentNode->m_key == key )
			{
				return currentNode->m_value;
			}
			prevNode = currentNode;
			currentNode = currentNode->m_next;
		}

		currentNode = new THashTableElement();
		currentNode->m_key = key;
		currentNode->m_value = TypeValue();
		prevNode->m_next = currentNode;

		return currentNode->m_value;
	}

	bool Exist( const TypeKey& key )
	{
		THashTableElement* currentNode = m_data[ GetHash( key ) ];

		THashTableElement* prevNode = NULL;
		while( currentNode )
		{
			if( currentNode->m_key == key )
			{
				return true;
			}

			currentNode = currentNode->m_next;
		}

		return false;
	}

	void Remove( const TypeKey& key )
	{
		unsigned int hashValue = GetHash( key );

		THashTableElement* currentNode = m_data[ hashValue ];

		THashTableElement* prevNode = NULL;
		while( currentNode )
		{
			if( currentNode->m_key == key )
			{
				THashTableElement* nextNode = currentNode->m_next;
				delete currentNode;
				if( prevNode == NULL )
				{
					m_data[ hashValue ] = nextNode;
				}
				else
				{
					prevNode->m_next = nextNode;
				}
				return;
			}
			prevNode = currentNode;
			currentNode = currentNode->m_next;
		}
	}

	unsigned int GetSize() const{ return TABLE_SIZE; }

	bool IsEmpty() const
	{
		for( int i = 0; i<TABLE_SIZE; ++i )
		{
			if( m_data[i] != NULL )
			{
				return false;
			}
		}

		return true;
	}

private:
	unsigned int GetHash( const TypeKey& key )
	{
		return HASH_FUNCTION::GetHash( key, GetSize() );
	}

private:
	THashTableElement** m_data;
};

struct HashTablePrintHelpers
{
	template< class T >
	static void Print( const T& hashTable)
	{
		COutColor( CoutColors::yellow );

		for( unsigned int i = 0; i<hashTable.GetSize(); ++i )
		{
			T::THashTableElement* currentKeyNode = hashTable.m_data[i];
			int count = 0;
			while( currentKeyNode != NULL )
			{
				if( count == 0 )
				{
					COutColor( CoutColors::yellow );
					cout << "[" << i << "]"; 
					COutColor( CoutColors::red );
				}
				else
				{
					COutColor( CoutColors::grey );
				}

				cout << "(" << currentKeyNode->m_key << "," << currentKeyNode->m_value << ") ";

				currentKeyNode = currentKeyNode->m_next;
				++count;
			}
		}

		cout << endl;
	}
};