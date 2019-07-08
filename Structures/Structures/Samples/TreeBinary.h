#pragma once
#include "stdafx.h"

#include "Samples/LinkedQueue.h"
#include "Samples/LinkedStack.h"
#include "Samples/TreeBinaryInterface.h"

template<class T>
class BinaryTree : public BinaryTreeInterface<T>
{
public:
	BinaryTree()
	{
	}

	virtual void Push( const TypeValue& value ) override
	{
		Add( value, &m_root );
	}
	
	virtual void Delete( const TypeValue& value ) override
	{
		if( m_root == NULL )
		{
			return;
		}

		DeleteInternal( value, NULL, &m_root );
	}

private:
	void DeleteInternal( const TypeValue& value, TNode** parentNode, TNode** currentNode )
	{
		if( *currentNode )
		{
			if( (*currentNode)->m_value == value )
			{
				TNode* deletedNode = (*currentNode);
				TNode* left = (*currentNode)->m_left;
				TNode* right = (*currentNode)->m_right;
				if( left != NULL && right == NULL)
				{
					if((*parentNode)->m_left == (*currentNode) )
					{
						(*parentNode)->m_left = left;
					}
					else if((*parentNode)->m_right == (*currentNode) )
					{
						(*parentNode)->m_right = left;
					}
				}
				else if( left == NULL && right != NULL )
				{
					if((*parentNode)->m_left == (*currentNode) )
					{
						(*parentNode)->m_left = right;
					}
					else if((*parentNode)->m_right == (*currentNode) )
					{
						(*parentNode)->m_right = right;
					}
				}
				else  if( left != NULL && right != NULL )
				{
					TNode* node = BFSDelete( *currentNode, (*currentNode)->m_right );

					node->m_left = (*currentNode)->m_left;
					node->m_right = (*currentNode)->m_right;

					if((*parentNode)->m_left == (*currentNode) )
					{
						(*parentNode)->m_left = node;
					}
					else if((*parentNode)->m_right == (*currentNode) )
					{
						(*parentNode)->m_right = node;
					}
				}

				delete deletedNode;
			}
			else if( value < (*currentNode)->m_value )
			{
				DeleteInternal( value, currentNode, &(*currentNode)->m_left );
			}
			else if( value >= (*currentNode)->m_value )
			{
				DeleteInternal( value, currentNode, &(*currentNode)->m_right );
			}
		}
	}

	TNode* BFSDelete( TNode* parentNode, TNode* currentNode )
	{
		if( currentNode )
		{
			if( currentNode->m_left )
			{
				BFSDelete( currentNode, currentNode->m_left );
			}
			else if( currentNode->m_right )
			{
				BFSDelete( currentNode, currentNode->m_right );
			}
			else
			{
				if(parentNode->m_left == currentNode )
				{
					parentNode->m_left = NULL;
				}
				else if(parentNode->m_right == currentNode )
				{
					parentNode->m_right = NULL;
				}

				return currentNode;
			}
		}

		return NULL;
	}

	void Add( const TypeValue& value, TNode** currentNode )
	{
		if( *currentNode == NULL )
		{
			*currentNode = new TNode();
			(*currentNode)->m_value = value;
		}
		else if(	(*currentNode)
				&&	(*currentNode)->m_value > value  )
		{
			Add( value, &((*currentNode)->m_left) );
		}
		else if(	(*currentNode)
				&&	(*currentNode)->m_value <= value  )
		{
			Add( value, &((*currentNode)->m_right) );
		}
	}
};