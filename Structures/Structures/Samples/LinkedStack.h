#pragma once
#include "stdafx.h"

struct LinkedStackPrintHelpers;

template<class T>
class LinkedStack
{
private:
	friend struct LinkedStackPrintHelpers;

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
	LinkedStack()
		: m_first( NULL )
	{
	}

	void Push( const TypeValue& value )
	{
		TNode* newNode = new TNode();
		newNode->m_value = value;

		if( m_first == NULL )
		{
			m_first = newNode;
			return;
		}

		newNode->m_next = m_first;
		m_first = newNode;
	}

	TypeValue& GetTop()
	{
		return m_first->m_value;
	}

	TypeValue Pop()
	{
		if( !m_first )
		{
			assert( false );
			return TypeValue();
		}

		TNode* nextNode = m_first->m_next;
		TypeValue value = m_first->m_value;
		delete m_first;
		m_first = nextNode;

		return value;
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
};

struct LinkedStackPrintHelpers
{
	template< class T >
	static void Print( const T& linkedStack)
	{
		COutColor( CoutColors::yellow );

		T::TNode* currentNode = linkedStack.m_first;
		while( currentNode != NULL )
		{
			if( currentNode == linkedStack.m_first )
			{
				COutColor( CoutColors::red );
			}
			else
			{
				COutColor( CoutColors::grey );
			}

			cout << currentNode->m_value << "->";

			currentNode = currentNode->m_next;
		}

		cout << endl;
	}
};