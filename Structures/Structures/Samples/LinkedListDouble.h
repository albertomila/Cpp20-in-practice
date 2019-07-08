#pragma once
#include "stdafx.h"


template< typename TypeValue, typename TypeNodeValue >
class DoubleLinkedListIterator
{
private:
	typedef DoubleLinkedListIterator<TypeValue, TypeNodeValue> TDoubleLinkedListIterator;

public:
	DoubleLinkedListIterator(TypeNodeValue* ptr)
		: m_ptr(ptr)
	{
	}

	TDoubleLinkedListIterator& operator = (const TDoubleLinkedListIterator& rawIterator)
	{
		m_ptr = rawIterator.ptr;
		return *this;
	}

	bool operator == (const TDoubleLinkedListIterator& rawIterator) const
	{
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator != (const TDoubleLinkedListIterator& rawIterator) const
	{
		return (m_ptr != rawIterator.getConstPtr());
	}

	TDoubleLinkedListIterator& operator++()
	{
		m_ptr = m_ptr->m_next;
		return *this;
	}

	TDoubleLinkedListIterator& operator--()
	{
		m_ptr = m_ptr->m_prev;
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

template< typename TypeValue, typename TypeNodeValue >
class DoubleLinkedListReverseIterator
	:public DoubleLinkedListIterator<TypeValue, TypeNodeValue>
{
	typedef DoubleLinkedListIterator<TypeValue, TypeNodeValue> super;
	typedef DoubleLinkedListReverseIterator<TypeValue, TypeNodeValue> TDoubleLinkedListReverseIterator;

public:
	DoubleLinkedListReverseIterator(TypeNodeValue* ptr)
		: super(ptr)
	{
	}

	TDoubleLinkedListReverseIterator& operator++()
	{
		super::operator--();
		return *this;
	}

	TDoubleLinkedListReverseIterator& operator--()
	{
		super::operator++();
		return *this;
	}
};

struct LinkedListDoublePrintHelpers;

template<class T>
class DoubleLinkedList
{
private:
	friend struct LinkedListDoublePrintHelpers;

public:
	template<class T>
	struct Node
	{
		Node()
			: m_next( NULL )
			, m_prev( NULL )
		{
		}
		T m_value;
		Node* m_next;
		Node* m_prev;
	};

public:
	typedef T TypeValue;
	typedef Node<TypeValue> TNode;

	typedef DoubleLinkedListIterator<TypeValue, TNode> iterator;
	typedef DoubleLinkedListIterator<const TypeValue, const TNode> const_iterator;

	typedef DoubleLinkedListReverseIterator<TypeValue, TNode> reverse_iterator;
	typedef DoubleLinkedListReverseIterator<const TypeValue, const TNode> const_reverse_iterator;

public:
	iterator begin(){return iterator(m_first);}
	iterator end(){return iterator(m_last->m_next);}

	const_iterator cbegin(){return const_iterator(m_first);}
	const_iterator cend(){return const_iterator(m_last->m_next);}

	reverse_iterator rbegin(){return reverse_iterator(m_last);}
	reverse_iterator rend(){return reverse_iterator(m_first->m_prev);}

	const_reverse_iterator crbegin(){return const_reverse_iterator(m_last);}
	const_reverse_iterator crend(){return const_reverse_iterator(m_first->m_prev);}

	DoubleLinkedList()
		: m_first( NULL )
		, m_last( NULL )
	{
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
			newNode->m_prev = m_last;
			m_last->m_next = newNode;
			m_last = m_last->m_next;
		}
	}

	void RemoveBack()
	{
		if( !m_last )
		{
			assert( false );
			return;
		}

		if( m_first == m_last)
		{
			delete m_first;
			m_first = NULL;
			m_last = NULL;
			return;
		}

		TNode* prevNode = m_last->m_prev;
		delete m_last;
		m_last = prevNode;
		m_last->m_next = NULL;
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
			m_first->m_prev = newNode;
			newNode->m_next = m_first;
			m_first = newNode;
		}
	}

	void RemoveFront()
	{
		if( !m_first )
		{
			assert( false );
			return;
		}

		if( m_first == m_last)
		{
			delete m_first;
			m_first = NULL;
			m_last = NULL;
			return;
		}

		TNode* nextNode = m_first->m_next;
		delete m_first;
		m_first = nextNode;
		m_first->m_prev = NULL;
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
			m_first->m_prev = NULL;
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
				else
				{
					nextNode->m_prev = previousNode;
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
			if( m_first != NULL )
			{
				m_first->m_prev = NULL;
			}
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
				else
				{
					nextNode->m_prev = previousNode;
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



struct LinkedListDoublePrintHelpers
{
	template< class T >
	static void Print( const T& linkedListDouble)
	{

		COutColor( CoutColors::yellow );

		T::TNode* currentNode = linkedListDouble.m_first;
		while( currentNode != NULL )
		{
			if( currentNode == linkedListDouble.m_first )
			{
				COutColor( CoutColors::red );
			}
			else if( currentNode == linkedListDouble.m_last )
			{
				COutColor( CoutColors::yellow );
			}
			else
			{
				COutColor( CoutColors::grey );
			}

			if( currentNode != linkedListDouble.m_last )
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

	template< class T >
	static void PrintBackwards( const T& linkedListDouble)
	{
		COutColor( CoutColors::yellow );

		T::TNode* currentNode = linkedListDouble.m_last;
		while( currentNode != NULL )
		{
			if( currentNode == linkedListDouble.m_first )
			{
				COutColor( CoutColors::red );
			}
			else if( currentNode == linkedListDouble.m_last )
			{
				COutColor( CoutColors::yellow );
			}
			else
			{
				COutColor( CoutColors::grey );
			}

			if( currentNode != linkedListDouble.m_first )
			{
				cout << currentNode->m_value << "->";
			}
			else
			{
				cout << currentNode->m_value;
			}

			currentNode = currentNode->m_prev;
		}

		cout << endl;
	}
};