#pragma once
#include "stdafx.h"



template<typename T>
struct HashSetHash
{
	static unsigned int GetHash( const T& key, unsigned int TABLE_SIZE )
	{
		return static_cast<unsigned int>(key) % TABLE_SIZE;
	}
};

template<typename T>
struct HashSetHash<T*>
{
	static unsigned int GetHash( const T* key, unsigned int TABLE_SIZE )
	{
		return reinterpret_cast<unsigned int>( &(*key) ) % TABLE_SIZE;
	}
};

template<>
struct HashSetHash<char*>
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


template< unsigned int TABLE_SIZE, typename TypeValue, typename TypeNodeValue, typename TypeHashData >
class HashSetIterator
{
private:
	typedef HashSetIterator<TABLE_SIZE, TypeValue, TypeNodeValue,TypeHashData> THashSetIterator;

public:
	HashSetIterator(unsigned int pos, TypeHashData* data, TypeNodeValue* ptr)
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

	THashSetIterator& operator = (const THashSetIterator& rawIterator)
	{
		m_data = rawIterator.m_data;
		m_ptr = rawIterator.ptr;
		return *this;
	}

	bool operator == (const THashSetIterator& rawIterator) const
	{
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator != (const THashSetIterator& rawIterator) const
	{
		return (m_ptr != rawIterator.getConstPtr());
	}

	THashSetIterator& operator++()
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

	TypeValue& operator*()
	{
		return m_ptr->m_key;
	}

	const TypeValue& operator*()const
	{
		return m_ptr->m_key;
	}

	TypeValue* operator->()
	{
		return &(m_ptr->m_key);
	}

private:
	TypeNodeValue* getPtr()const{return m_ptr;}
	const TypeNodeValue* getConstPtr()const{return m_ptr;}

private:
	TypeHashData* m_data;
	TypeNodeValue* m_ptr;
	unsigned int m_pos;
};

struct HashSetPrintHelpers;

template< class KEY
		, unsigned int TABLE_SIZE = 200
		, typename HASH_FUNCTION = HashSetHash<KEY> >
class HashSet
{
private:
	friend struct HashSetPrintHelpers;

	template<class KEY>
	struct HashSetElement
	{
		typedef KEY TypeKey;

		HashSetElement()
			: m_next(NULL)
		{
		}

		TypeKey m_key;
		HashSetElement<TypeKey>* m_next;
	};

public:
	typedef KEY TypeKey;
	typedef HashSetElement<TypeKey> THashSetElement;

	typedef HashSetIterator<TABLE_SIZE, TypeKey, THashSetElement, THashSetElement* > iterator;
	typedef HashSetIterator<TABLE_SIZE, const TypeKey, const THashSetElement, const THashSetElement *const> const_iterator;
	
public:
	iterator begin()
	{
		return iterator( 0, m_data, *m_data );
	}

	iterator end()
	{
		THashSetElement** endList = (m_data + GetSize());
		THashSetElement* endElement = *endList;
		return iterator( GetSize(), endList, endElement);
	}

	const_iterator cbegin()
	{
		return const_iterator( 0, m_data,  *m_data  );
	}

	const_iterator cend()
	{
		const THashSetElement*const * endList = (m_data + GetSize());
		const THashSetElement* endElement = *endList;
		return const_iterator( GetSize(), endList, endElement);
	}
	
public:
	HashSet()
	{
		//Using the parenthesis it initializes to NULL all pointers 
		m_data = new HashSetElement<TypeKey>*[TABLE_SIZE]();
	}
	~HashSet()
	{
		for( int i = 0; i<TABLE_SIZE; ++i )
		{
			HashSetElement<TypeKey>* currentKeyNode = m_data[i];
			while( currentKeyNode != NULL )
			{
				HashSetElement<TypeKey>* nextNode = currentKeyNode->m_next;
				delete currentKeyNode;
				currentKeyNode = nextNode;
			}
		}

		delete[] m_data;
	}

	void Set( const TypeKey& key)
	{
		unsigned int hashValue = GetHash( key );

		HashSetElement<TypeKey>* currentNode = m_data[ hashValue ];
		if( !currentNode )
		{
			currentNode = new HashSetElement<TypeKey>();
			currentNode->m_key = key;
			m_data[ hashValue ] = currentNode;
			return;
		}

		while( currentNode->m_next )
		{
			currentNode = currentNode->m_next;
		}

		HashSetElement<TypeKey>* newNode = new HashSetElement<TypeKey>();
		newNode->m_key = key;
		currentNode->m_next = newNode;
	}

	bool Exist( const TypeKey& key )
	{
		HashSetElement<TypeKey>* currentNode = m_data[ GetHash( key )];

		HashSetElement<TypeKey>* prevNode = NULL;
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

		HashSetElement<TypeKey>* currentNode = m_data[ hashValue ];

		HashSetElement<TypeKey>* prevNode = NULL;
		while( currentNode )
		{
			if( currentNode->m_key == key )
			{
				HashSetElement<TypeKey>* nextNode = currentNode->m_next;
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

private:
	
	unsigned int GetHash( const TypeKey& key )
	{
		return HASH_FUNCTION::GetHash( key, GetSize() );
	}

private:
	HashSetElement<TypeKey>** m_data;
};

struct HashSetPrintHelpers
{
	template< class T >
	static void Print( const T& hashSet)
	{
		COutColor( CoutColors::yellow );

		for( unsigned int i = 0; i<hashSet.GetSize(); ++i )
		{
			T::HashSetElement<T::TypeKey>* currentKeyNode = hashSet.m_data[i];
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

				cout << "(" << currentKeyNode->m_key << ") ";

				currentKeyNode = currentKeyNode->m_next;
				++count;
			}
		}

		cout << endl;
	}
};