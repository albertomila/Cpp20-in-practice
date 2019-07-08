#pragma once
#include "stdafx.h"

struct LinkedQueuePrintHelpers;

template<class T>
class LinkedQueue
{
private:
	friend struct LinkedQueuePrintHelpers;

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

public:
	LinkedQueue()
		: m_first( NULL )
		, m_last( NULL )
	{
	}

	void Push( const TypeValue& value )
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

	TypeValue& GetHead()
	{
		return m_first->m_value;
	}

	void Pop()
	{
		if( !m_first )
		{
			assert( false );
			return;
		}

		TNode* nextNode = m_first->m_next;
		delete m_first;
		m_first = nextNode;
	}

	bool IsEmpty() const
	{
		return m_first == NULL;
	}

	void Clean()
	{
		while( !IsEmpty() )
		{
			Pop()
		}
	}

private:
	TNode* m_first;
	TNode* m_last;
};



struct LinkedQueuePrintHelpers
{
	template< class T >
	static void Print( const T& linkedQueue)
	{
		COutColor( CoutColors::yellow );

		T::TNode* currentNode = linkedQueue.m_first;
		while( currentNode != NULL )
		{
			if( currentNode == linkedQueue.m_first )
			{
				COutColor( CoutColors::red );
			}
			else if( currentNode == linkedQueue.m_last )
			{
				COutColor( CoutColors::yellow );
			}
			else
			{
				COutColor( CoutColors::grey );
			}

			if( currentNode != linkedQueue.m_last )
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