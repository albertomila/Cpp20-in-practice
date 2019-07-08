#include "stdafx.h"
#include "Samples/TreeBinaryInterface.h"
#include "Samples/LinkedQueue.h"
#include "Samples/LinkedStack.h"

template<class T>
class BinarySplayTree : public BinaryTreeInterface<T>
{
private:
	enum EInsertionDirection
	{
		  EDirection_Invalid
		, EDirection_Left
		, EDirection_Right
	};

	enum ERotationType
	{
		  ERotationType_Invalid
		, ERotationType_LL
		, ERotationType_RR
		, ERotationType_LR
		, ERotationType_RL
	};

public:
	BinarySplayTree()
	{
	}

	virtual void Push( const TypeValue& value ) override
	{
		LinkedStack<TNode*> stackTreeNodes;
		Add( value, stackTreeNodes, &m_root );
	}

	virtual void Delete( const TypeValue& value ) override
	{
		if( m_root == NULL )
		{
			return;
		}

		LinkedStack<TNode*> stackTreeNodes;
		DeleteInternal( value, stackTreeNodes, m_root );
	}

private:
	void DeleteInternal( const TypeValue& value, LinkedStack<TNode*>& stackTreeNodes, TNode* currentNode )
	{
		if( currentNode )
		{
			if( currentNode->m_value == value )
			{
				Splay( stackTreeNodes, currentNode );
				
				TNode* leftNode = m_root->m_left;
				TNode* rightNode = m_root->m_right;

				delete m_root;
				m_root = NULL;

				if( !leftNode )
				{
					m_root = rightNode;
				}
				else if( !rightNode )
				{
					m_root = leftNode;
				}
				else if( leftNode && rightNode)
				{
					LinkedStack<TNode*> stackTreeNodesMax;
					FindMaxValue( leftNode->m_value, stackTreeNodesMax, leftNode);

					TNode* maxNode = stackTreeNodesMax.GetTop();
					stackTreeNodesMax.Pop();
					Splay( stackTreeNodesMax, maxNode );

					assert( m_root->m_right == NULL );

					m_root->m_right = rightNode;
				}
			}
			else if( currentNode->m_value > value )
			{
				stackTreeNodes.Push( currentNode );
				if( currentNode->m_left )
				{
					DeleteInternal( value, stackTreeNodes, currentNode->m_left );
				}
				else
				{
					//node not found
					TNode* lastNode = stackTreeNodes.GetTop();
					stackTreeNodes.Pop();
					Splay( stackTreeNodes, lastNode );
				}
			}
			else if( currentNode->m_value < value )
			{
				stackTreeNodes.Push( currentNode );
				if( currentNode->m_right )
				{
					DeleteInternal( value, stackTreeNodes, currentNode->m_right );
				}
				else
				{
					//node not found
					TNode* lastNode = stackTreeNodes.GetTop();
					stackTreeNodes.Pop();
					Splay( stackTreeNodes, lastNode );
				}
			}
		}
	}

	void FindMaxValue( TypeValue maxValue, LinkedStack<TNode*>& stackTreeNodes, TNode* currentNode ) const
	{
		if( !currentNode )
		{
			return;
		}

		if( currentNode->m_value >= maxValue  )
		{
			stackTreeNodes.Push( currentNode );

			FindMaxValue( currentNode->m_value
						, stackTreeNodes
						, currentNode->m_right );
		}
	}
	
	void Add( const TypeValue& value, LinkedStack<TNode*>& stackTreeNodes, TNode** currentNode )
	{
		if( *currentNode == NULL )
		{
			*currentNode = new TNode();
			(*currentNode)->m_value = value;

			//case no nodes in the tree
			if( m_root != (*currentNode) )
			{
				Splay( stackTreeNodes, (*currentNode) );
			}
		}
		else if(	(*currentNode)
				&&	(*currentNode)->m_value > value  )
		{
			stackTreeNodes.Push( (*currentNode) );
			Add( value, stackTreeNodes, &((*currentNode)->m_left) );
		}
		else if(	(*currentNode)
				&&	(*currentNode)->m_value <= value  )
		{
			stackTreeNodes.Push( (*currentNode) );
			Add( value, stackTreeNodes, &((*currentNode)->m_right) );
		}
	}

	void Splay( LinkedStack<TNode*>& stackTreeNodes, TNode* currentNode  )
	{
		if( stackTreeNodes.IsEmpty() )
		{
			m_root = currentNode;
		}
		else
		{
			DoSplay( stackTreeNodes, currentNode );
		}
	}

	void DoSplay( LinkedStack<TNode*>& stackTreeNodes, TNode* currentNode  )
	{
		while( !stackTreeNodes.IsEmpty() )
		{
			TNode* childLVL0 = NULL;
			TNode* childLVL1 = NULL;
			TNode* childLVL2 = NULL;

			if( !stackTreeNodes.IsEmpty() )
			{
				childLVL2 = stackTreeNodes.GetTop();
				stackTreeNodes.Pop();
			}
			if( !stackTreeNodes.IsEmpty() )
			{
				childLVL1 = stackTreeNodes.GetTop();
				stackTreeNodes.Pop();
			}
			if( !stackTreeNodes.IsEmpty() )
			{
				childLVL0 = stackTreeNodes.GetTop();
				//stackTreeNodes.Pop();
			}

			//case only one node to add
			if( childLVL1 == NULL )
			{
				childLVL0 = childLVL2;

				if( childLVL0->m_left == currentNode )
				{
					childLVL0->m_left = currentNode->m_right;
					currentNode->m_right = childLVL0;
				}
				else if( childLVL0->m_right == currentNode )
				{
					childLVL0->m_right = currentNode->m_left;
					currentNode->m_left = childLVL0;
				}

				m_root = currentNode;

				continue;
			}

			//case two nodes to add
			if( childLVL0 == NULL )
			{
				childLVL0 = childLVL1;
				childLVL1 = childLVL2;

				ERotationType typeRotation = GetRotationType( childLVL0, childLVL1, currentNode );
			
				DispatchRotation( typeRotation, NULL, childLVL0, childLVL1, currentNode );

				continue;
			}

			ERotationType typeRotation = GetRotationType( childLVL1, childLVL2, currentNode );
			DispatchRotation( typeRotation, childLVL0, childLVL1, childLVL2, currentNode );
		}
	}

	ERotationType GetRotationType( TNode* childLVL0, TNode* childLVL1, TNode* childLVL2)
	{
		EInsertionDirection insertionDirection1( EDirection_Invalid );
		EInsertionDirection insertionDirection2( EDirection_Invalid );

		if( childLVL0->m_left == childLVL1 )
		{
			insertionDirection1 = EDirection_Left;
		}
		else if( childLVL0->m_right == childLVL1 )
		{
			insertionDirection1 = EDirection_Right;
		}

		if( childLVL1->m_left == childLVL2 )
		{
			insertionDirection2 = EDirection_Left;
		}
		else if( childLVL1->m_right == childLVL2 )
		{
			insertionDirection2 = EDirection_Right;
		}

		switch( insertionDirection1 )
		{
		case EDirection_Left:
			switch( insertionDirection2 )
			{
			case EDirection_Left:
				return ERotationType_LL;
				break;
			case EDirection_Right:
				return ERotationType_LR;
				break;
			}
			break;
		case EDirection_Right:
			switch( insertionDirection2 )
			{
			case EDirection_Left:
				return ERotationType_RL;
				break;
			case EDirection_Right:
				return ERotationType_RR;
				break;
			}
			break;
		}

		return ERotationType_Invalid;
	}

	void DispatchRotation( ERotationType rotationType, TNode* parent, TNode* childLVL0, TNode* childLVL1, TNode* childLVL2)
	{
		switch( rotationType )
		{
		case ERotationType_LL:
			DispatchRotation_LL( parent, childLVL0, childLVL1, childLVL2);
			break;
		case ERotationType_RR:
			DispatchRotation_RR( parent, childLVL0, childLVL1, childLVL2);
			break;
		case ERotationType_LR:
			DispatchRotation_LR( parent, childLVL0, childLVL1, childLVL2);
			break;
		case ERotationType_RL:
			DispatchRotation_RL( parent, childLVL0, childLVL1, childLVL2);
			break;
		}

	}

	void DispatchRotation_LL( TNode* parent, TNode* childLVL0, TNode* childLVL1, TNode* childLVL2)
	{
		childLVL1->m_left = childLVL2->m_right;
		childLVL2->m_right = childLVL1;

		childLVL0->m_left = childLVL1->m_right;
		childLVL1->m_right = childLVL0;

		UpdateParent( parent, childLVL0, childLVL2);
	}

	void DispatchRotation_RR( TNode* parent, TNode* childLVL0, TNode* childLVL1, TNode* childLVL2)
	{
		childLVL1->m_right = childLVL2->m_left;
		childLVL2->m_left = childLVL1;

		childLVL0->m_right = childLVL1->m_left;
		childLVL1->m_left = childLVL0;

		UpdateParent( parent, childLVL0, childLVL2);
	}

	void DispatchRotation_LR( TNode* parent, TNode* childLVL0, TNode* childLVL1, TNode* childLVL2)
	{
		childLVL1->m_right = childLVL2->m_left;
		childLVL0->m_left = childLVL2->m_right;

		childLVL2->m_left = childLVL1;
		childLVL2->m_right = childLVL0;

		UpdateParent( parent, childLVL0, childLVL2);
	}

	void DispatchRotation_RL( TNode* parent, TNode* childLVL0, TNode* childLVL1, TNode* childLVL2)
	{
		childLVL1->m_left = childLVL2->m_right;
		childLVL0->m_right = childLVL2->m_left;

		childLVL2->m_right = childLVL1;
		childLVL2->m_left = childLVL0;

		UpdateParent( parent, childLVL0, childLVL2);
	}

	void UpdateParent( TNode* parent, TNode* childLVL0, TNode* childLVL2)
	{
		if( parent )
		{
			if( parent->m_left == childLVL0 )
			{
				parent->m_left = childLVL2;
			}
			else if( parent->m_right == childLVL0 )
			{
				parent->m_right = childLVL2;
			}
		}
		else
		{
			m_root = childLVL2;
		}
	}
};