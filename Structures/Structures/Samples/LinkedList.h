#pragma once
#include "stdafx.h"


template< typename TypeValue, typename TypeNodeValue >
class LinkedListIterator
{
private:
	typedef LinkedListIterator<TypeValue, TypeNodeValue> TLinkedListIterator;

public:
	LinkedListIterator(TypeNodeValue* ptr)
		: m_ptr(ptr)
	{
	}

	TLinkedListIterator& operator = (const TLinkedListIterator& rawIterator)
	{
		m_ptr = rawIterator.ptr;
		return *this;
	}

	bool operator == (const TLinkedListIterator& rawIterator) const
	{
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator != (const TLinkedListIterator& rawIterator) const
	{
		return (m_ptr != rawIterator.getConstPtr());
	}

	TLinkedListIterator& operator++()
	{
		m_ptr = m_ptr->m_next;
		return *this;
	}
	
	TypeValue& operator*()
	{
		return m_ptr->m_value;
	}

	const TypeValue& operator*()const
	{
		return m_ptr->m_value;
	}
	
	TypeValue* operator->()
	{
		return &(m_ptr->m_value);
	}
	
private:
	TypeNodeValue* getPtr()const{return m_ptr;}
	const TypeNodeValue* getConstPtr()const{return m_ptr;}

private:
	TypeNodeValue* m_ptr;
};

struct LinkedListPrintHelpers;

template<class T>
class LinkedList
{
private:
	friend struct LinkedListPrintHelpers;

public:
	template<class T>
	struct Node
	{
		Node()
			: m_next( NULL )
		{
		}
		T m_value;
		Node* m_next;
	};

public:
	typedef T TypeValue;
	typedef Node<TypeValue> TNode;

	typedef LinkedListIterator<TypeValue, TNode> iterator;
	typedef LinkedListIterator<const TypeValue, const TNode> const_iterator;

public:
	iterator begin(){return iterator(m_first);}
	iterator end(){return iterator(m_last->m_next);}

	const_iterator cbegin(){return const_iterator(m_first);}
	const_iterator cend(){return const_iterator(m_last->m_next);}

	LinkedList()
		: m_first( NULL )
		, m_last( NULL )
	{
	}
	TNode* GetFirst()
	{
		return m_first;
	}

	void PushBack( const TypeValue& value )
	{
		TNode* newNode = new TNode();
		newNode->m_value = value;
		
		if( m_first == NULL )
		{
			m_first = newNode;
			m_last = m_first;
		}
		else
		{
			m_last->m_next = newNode;
			m_last = m_last->m_next;
		}
	}

	void PushFront( const TypeValue& value )
	{
		TNode* newNode = new TNode();
		newNode->m_value = value;

		if( m_first == NULL )
		{
			m_first = newNode;
			m_last = m_first;
		}
		else
		{
			newNode->m_next = m_first;
			m_first = newNode;
		}
	}

	void Remove( const TypeValue& value )
	{
		if( !m_first )
		{
			assert( false );
			return;
		}

		if( m_first->m_value == value )
		{
			TNode* nextNode = m_first->m_next;
			delete m_first;
			m_first = nextNode;
			return;
		}

		TNode* previousNode = m_first;
		TNode* currentNode = m_first->m_next;
		
		while( currentNode != NULL )
		{
			if( currentNode->m_value == value )
			{
				TNode* nextNode = currentNode->m_next;
				if( currentNode == m_last )
				{
					m_last = previousNode;
				}
				delete currentNode;
				previousNode->m_next = nextNode;
				return;
			}

			previousNode = previousNode->m_next;
			currentNode = currentNode->m_next;
		}

		assert( false );
	}

	void RemoveAtIndex( int index )
	{
		if( !m_first )
		{
			assert( false );
			return;
		}

		if( index == 0 )
		{
			TNode* nextNode = m_first->m_next;
			delete m_first;
			m_first = nextNode;
			return;
		}

		TNode* previousNode = m_first;
		TNode* currentNode = m_first->m_next;

		int count = 0;
		while( currentNode != NULL )
		{
			if( count == index )
			{
				TNode* nextNode = currentNode->m_next;
				if( currentNode == m_last )
				{
					m_last = previousNode;
				}
				delete currentNode;
				previousNode->m_next = nextNode;
				return;
			}
			previousNode = previousNode->m_next;
			currentNode = currentNode->m_next;
			++count;
		}

		assert( false );
	}

	bool IsEmpty() const
	{
		return m_first == NULL;
	}

	void Clean()
	{
		TNode* currentNode = m_first;
		while( currentNode )
		{
			TNode* nextNode = currentNode->m_next;
			delete currentNode;
			currentNode = nextNode;
		}
		m_first = NULL;
		m_last = NULL;
	}

private:
	TNode* m_first;
	TNode* m_last;
};

struct LinkedListPrintHelpers
{
	template< class T >
	static void Print( const T& linkedList)
	{
		COutColor( CoutColors::yellow );

		T::TNode* currentNode = linkedList.m_first;
		while( currentNode != NULL )
		{
			if( currentNode == linkedList.m_first )
			{
				COutColor( CoutColors::red );
			}
			else if( currentNode == linkedList.m_last )
			{
				COutColor( CoutColors::yellow );
			}
			else
			{
				COutColor( CoutColors::grey );
			}

			if( currentNode != linkedList.m_last )
			{
				cout << currentNode->m_value << "->";
			}
			else
			{
				cout << currentNode->m_value;
			}

			currentNode = currentNode->m_next;
		}

		cout << endl;
	}
};