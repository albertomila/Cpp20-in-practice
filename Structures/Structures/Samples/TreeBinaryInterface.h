#pragma once
#include "stdafx.h"

#include "Samples/LinkedQueue.h"
#include "Samples/LinkedStack.h"

template< typename TypeValue, typename TypeNodeValue >
class BinaryTreeIterator
{
private:
	typedef BinaryTreeIterator<TypeValue, TypeNodeValue> TBinaryTreeIterator;

public:
	BinaryTreeIterator(TypeNodeValue* ptr)
		: m_ptr(ptr)
	{
		m_stack.Push( ptr );
	}

	TBinaryTreeIterator& operator = (const TBinaryTreeIterator& rawIterator)
	{
		m_ptr = rawIterator.ptr;
		return *this;
	}

	bool operator == (const TBinaryTreeIterator& rawIterator) const
	{
		return (m_ptr == rawIterator.getConstPtr());
	}

	bool operator != (const TBinaryTreeIterator& rawIterator) const
	{
		return (m_ptr != rawIterator.getConstPtr());
	}

	TBinaryTreeIterator& operator++()
	{
		m_ptr = m_stack.GetTop();
		m_stack.Pop();
		if( m_ptr )
		{
			if( m_ptr->m_right )
			{
				m_stack.Push( m_ptr->m_right );
			}

			if( m_ptr->m_left )
			{
				m_stack.Push( m_ptr->m_left );
			}
		}
		if( !m_stack.IsEmpty() )
		{
			m_ptr = m_stack.GetTop();
		}
		else
		{
			m_ptr = m_ptr->m_right;
		}
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
	LinkedStack<TypeNodeValue*> m_stack;
};

struct TreeBinaryPrintHelpers;

template<class T>
class BinaryTreeInterface
{
private:
	friend struct TreeBinaryPrintHelpers;

public:
	template<class T>
	struct Node
	{
		Node()
			: m_left( NULL )
			, m_right( NULL )
		{
		}
		T m_value;
		Node* m_left;
		Node* m_right;
	};

public:
	typedef T TypeValue;
	typedef Node<TypeValue> TNode;

	typedef BinaryTreeIterator<TypeValue, TNode> iterator;
	typedef BinaryTreeIterator<const TypeValue, const TNode> const_iterator;

public:
	iterator begin(){return iterator(m_root);}
	iterator end()
	{
		TNode* endNode = m_root;
		while( endNode )
		{
			//recover last node, always right node first
			if( endNode->m_right )
			{
				endNode = endNode->m_right;
			}
			else if( endNode->m_left )
			{
				endNode = endNode->m_left;
			}
			else
			{
				endNode = endNode->m_right;
			}
		}
		return iterator(endNode);
	}
	const_iterator cbegin(){return const_iterator(m_root);}
	const_iterator cend()
	{
		TNode* endNode = m_root;
		while( endNode )
		{
			//recover last node, always right node first
			if( endNode->m_right )
			{
				endNode = endNode->m_right;
			}
			else if( endNode->m_left )
			{
				endNode = endNode->m_left;
			}
			else
			{
				endNode = endNode->m_right;
			}
		}
		return const_iterator(endNode);
	}

public:
	BinaryTreeInterface()
		: m_root( NULL )
	{
	}

	virtual void Push( const TypeValue& value ) = 0;
	virtual void Delete( const TypeValue& value ) = 0;

	bool Exist( const TypeValue& value )
	{
		return ExistInternal( value, m_root );
	}
	
private:
	bool ExistInternal( const TypeValue& value, TNode* currentNode ) const
	{
		if( !currentNode )
		{
			return false;
		}

		if( currentNode->m_value == value )
		{
			return true;
		}
		else if( currentNode->m_value > value  )
		{
			return ExistInternal( value, currentNode->m_left );
		}
		else if( currentNode->m_value < value  )
		{
			return ExistInternal( value, currentNode->m_right );
		}

		return false;
	}
protected:
	TNode* m_root;
};

struct TreeBinaryPrintHelpers
{
	template< class T >
	static void PrintBFS( const T& tree )
	{
		LinkedQueue<T::TNode*> queue;
		queue.Push( tree.m_root );

		COutColor( CoutColors::yellow );
		while( !queue.IsEmpty() )
		{
			T::TNode* value = queue.GetHead();
			queue.Pop();

			if( value->m_left )
			{
				queue.Push( value->m_left );
			}

			if( value->m_right )
			{
				queue.Push( value->m_right );
			}

			cout << value->m_value << ",";
		}

		cout << endl;
	}

	template< class T >
	static void PrintDFSStack( const T& tree )
	{
		LinkedStack<T::TNode*> stack;
		stack.Push( tree.m_root );

		COutColor( CoutColors::yellow );
		while( !stack.IsEmpty() )
		{
			T::TNode* value = stack.GetTop();
			stack.Pop();

			if( value->m_right )
			{
				stack.Push( value->m_right );
			}
			if( value->m_left )
			{
				stack.Push( value->m_left );
			}

			cout << value->m_value << ",";
		}

		cout << endl;
	}

	template< class T >
	static void PrintDFSRecursive( const T& tree )
	{
		DoPrintDFSRecursive<T>( tree.m_root );

		cout << endl;
	}

private:
	template< class T >
	static void DoPrintDFSRecursive( typename T::TNode* currentNode )
	{
		if( currentNode )
		{
			cout << currentNode->m_value << ",";

			DoPrintDFSRecursive<T>( currentNode->m_left );
			DoPrintDFSRecursive<T>( currentNode->m_right );
		}
	}
};
