#pragma once
#include "stdafx.h"

#include "Samples/HashTable.h"
#include "Samples/LinkedStack.h"
#include "Samples/TreeBinaryInterface.h"

template<typename T>
struct AVLTreeTypeOperations
{
	static bool IsLess( const T& value1, const T& value2 )
	{
		return value1 < value2;
	}

	static void Print( const T& value1 )
	{
		cout << value1;
	}
};


template<class T, typename TYPEOPERATIONS = AVLTreeTypeOperations<T> >
class AVLTree : public BinaryTreeInterface<T>
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
	typedef TYPEOPERATIONS TTypeOperations;

public:
	AVLTree()
	{
	}

	virtual void Push( const TypeValue& value ) override
	{
		m_nodeHeights.Clear();
		m_nodeDiffHeights.Clear();
		m_historyMap.Clear();
		Add( value, NULL, &m_root );
	}

	virtual void Delete( const TypeValue& value ) override
	{
		m_nodeHeights.Clear();
		m_nodeDiffHeights.Clear();
		Remove( value, NULL, &m_root );
	}

	void PrintAVLTree() const
	{
		HashTable<TNode*, int > highNodeMap;
		LinkedQueue<TNode*> queue;
		queue.Push( m_root );

		highNodeMap[m_root] = 0;
		int previousHigh = -1;
		COutColor( CoutColors::yellow );
		while( !queue.IsEmpty() )
		{
			TNode* value = queue.GetHead();
			queue.Pop();

			if( value->m_left )
			{
				highNodeMap[value->m_left] = highNodeMap[value] + 1;
				queue.Push( value->m_left );
			}

			if( value->m_right )
			{
				highNodeMap[value->m_right] = highNodeMap[value] + 1;
				queue.Push( value->m_right );
			}

			int currentHigh = highNodeMap[value];

			if( previousHigh < currentHigh )
			{
				COutColor( CoutColors::red );
				previousHigh = currentHigh;
				cout << endl;
			}
			else
			{
				COutColor( CoutColors::yellow );
			}

			TYPEOPERATIONS::Print( value->m_value );
			cout << ",";
		} 

		cout << endl;
		cout << endl;
	}

private:
	void Add( const TypeValue& value, TNode* parent, TNode** currentNode )
	{
		if( *currentNode == NULL )
		{
			*currentNode = new TNode();
			(*currentNode)->m_value = value;
			m_nodeHeights.Push( (*currentNode), 1 );
			m_nodeDiffHeights.Push( (*currentNode), 0 );
		}
		else if( TYPEOPERATIONS::IsLess( value, (*currentNode)->m_value )  ) // (*currentNode)->m_value > value
		{
			RegisterInsertionHistory( (*currentNode), EDirection_Left );
			Add( value, (*currentNode), &((*currentNode)->m_left) );
			ComputeHeights( (*currentNode) );
			int diffHeight = m_nodeDiffHeights[ *currentNode ];
			if( abs(diffHeight) == 2 )
			{
				DispatchRotation( parent, (*currentNode) );
				ComputeHeights( (*currentNode), true );
			}
		}
		else //  (*currentNode)->m_value < value   or   (*currentNode)->m_value == value
		{
			RegisterInsertionHistory( (*currentNode), EDirection_Right );
			Add( value, (*currentNode), &((*currentNode)->m_right) );
			ComputeHeights( (*currentNode) );
			int diffHeight = m_nodeDiffHeights[ *currentNode ];
			if( abs(diffHeight) == 2 )
			{
				DispatchRotation( parent, (*currentNode) );
				ComputeHeights( (*currentNode), true );
			}
		}
	}

	TNode* ProcessMaxNode( TNode* parentNode, TNode* currentNode )
	{
		if( !currentNode->m_left && !currentNode->m_right )
		{
			if( parentNode->m_right == currentNode )
			{
				parentNode->m_right = NULL;
			}
			else if( parentNode->m_left == currentNode )
			{
				parentNode->m_left = NULL;
			}
			return currentNode;
		}
		else if( currentNode->m_right )
		{
			return ProcessMaxNode( currentNode, currentNode->m_right );
		}
		else
		{
			if( parentNode->m_right == currentNode )
			{
				parentNode->m_right = currentNode->m_left;
			}
			else if( parentNode->m_left == currentNode )
			{
				parentNode->m_left = currentNode->m_left;
			}

			return currentNode;
		}

		return NULL;
	}

	void Remove( const TypeValue& value, TNode* parentNode, TNode** currentNode )
	{
		if( *currentNode == NULL )
		{
			return;
		}
		else if( TYPEOPERATIONS::IsLess( (*currentNode)->m_value, value)  ) //(*currentNode)->m_value < value
		{
			RegisterInsertionHistory( (*currentNode), EDirection_Right );
			Remove( value, (*currentNode), &((*currentNode)->m_right) );
			ComputeHeights( (*currentNode) );
			int diffHeight = m_nodeDiffHeights[ *currentNode ];
			if( abs(diffHeight) == 2 )
			{
				DispatchSimpleRotation( parentNode, (*currentNode) );
				ComputeHeights( (*currentNode), true );
			}
		}
		else if( TYPEOPERATIONS::IsLess( value, (*currentNode)->m_value ) ) //(*currentNode)->m_value > value
		{
			RegisterInsertionHistory( (*currentNode), EDirection_Left );
			Remove( value, (*currentNode), &((*currentNode)->m_left) );
			ComputeHeights( (*currentNode) );
			int diffHeight = m_nodeDiffHeights[ *currentNode ];
			if( abs(diffHeight) == 2 )
			{
				DispatchSimpleRotation( parentNode, (*currentNode) );
				ComputeHeights( (*currentNode), true );
			}
		}
		else// is equal, (*currentNode)->m_value == value
		{
			if( (*currentNode)->m_left )
			{
				TNode* maxNode = ProcessMaxNode( (*currentNode), (*currentNode)->m_left );
				maxNode->m_left = (*currentNode)->m_left;
				maxNode->m_right = (*currentNode)->m_right;

				if( m_root == (*currentNode) )
				{
					delete (*currentNode);
					m_root = maxNode;
					(*currentNode) = m_root;
				}
				else
				{
					if( parentNode->m_right == (*currentNode) )
					{
						delete (*currentNode);
						parentNode->m_right = &(*maxNode);
						(*currentNode) = parentNode->m_right;
					}
					else if( parentNode->m_left == (*currentNode) )
					{
						delete (*currentNode);
						parentNode->m_left = &(*maxNode);
						(*currentNode) = parentNode->m_left;
					}
				}
			}
			else
			{
				if( parentNode->m_right == (*currentNode) )
				{
					TNode* deleteNode = (*currentNode);
					parentNode->m_right = (*currentNode)->m_right;
					(*currentNode) = parentNode->m_right;
					delete deleteNode;
				}
				else if( parentNode->m_left == (*currentNode) )
				{
					TNode* deleteNode = (*currentNode);
					parentNode->m_left = (*currentNode)->m_right;
					(*currentNode) = parentNode->m_left;
					delete deleteNode;
				}
			}

			if( parentNode )
			{
				if( parentNode->m_right == (*currentNode) )
				{
					RegisterInsertionHistory( (*currentNode), EDirection_Right );
				}
				else if( parentNode->m_left == (*currentNode) )
				{
					RegisterInsertionHistory( (*currentNode), EDirection_Left );
				}
			}

			ComputeHeights( (*currentNode), true );
			int diffHeight = m_nodeDiffHeights[ *currentNode ];
			if( abs(diffHeight) == 2 )
			{
				DispatchSimpleRotation( parentNode, (*currentNode) );
				ComputeHeights( (*currentNode), true );
			}
		}
	}

	int ComputeHeights( TNode* node, bool recompute = false )
	{
		if( !node )
		{
			return 0;
		}

		if( !recompute )
		{
			if( m_nodeHeights.Exist( node ) )
			{
				return m_nodeHeights[node];
			}
		}

		int leftHeight = ComputeHeights( node->m_left, recompute);
		int rightHeight= ComputeHeights( node->m_right, recompute );

		int height = 1 + max(leftHeight, rightHeight );

		//create if doesn't exist, update if exist.
		m_nodeHeights[node] = height;

		int difHeight = leftHeight - rightHeight;

		//create if doesn't exist, update if exist.
		m_nodeDiffHeights[node] = difHeight;

		return height;
	}

	void RegisterInsertionHistory(TNode* currentNode, EInsertionDirection direction )
	{
		m_historyMap.Push( currentNode, direction );
	}

	void DispatchSimpleRotation( TNode* parentNode, TNode* currentNode )
	{
		ERotationType rotationType = ERotationType_Invalid;
		int diffHeight = m_nodeDiffHeights[ currentNode ];
		if( diffHeight >= 2 )
		{
			rotationType = ERotationType_LL;
		}
		else if( diffHeight <= -2 )
		{
			rotationType = ERotationType_RR;
		}

		switch(rotationType)
		{
		case ERotationType_LL:
			{
				//rotation
				TNode* childLVL0 = currentNode;
				TNode* childLVL1 = currentNode->m_left;

				childLVL0->m_left = childLVL1->m_right;
				childLVL1->m_right = childLVL0;

				//update parent
				if( parentNode == NULL )
				{
					m_root = childLVL1;
				}
				else
				{
					if( parentNode->m_right == childLVL0 )
					{
						parentNode->m_right = childLVL1;
					}
					else if( parentNode->m_left == childLVL0 )
					{
						parentNode->m_left = childLVL1;
					}
				}
			}
			break;
		case ERotationType_RR:
			{
				//rotation
				TNode* childLVL0 = currentNode;
				TNode* childLVL1 = currentNode->m_right;

				childLVL0->m_right = childLVL1->m_left ;
				childLVL1->m_left = childLVL0;

				//update parent
				if( parentNode == NULL )
				{
					m_root = childLVL1;
				}
				else
				{
					if( parentNode->m_right == childLVL0 )
					{
						parentNode->m_right = childLVL1;
					}
					else if( parentNode->m_left == childLVL0 )
					{
						parentNode->m_left = childLVL1;
					}
				}
			}
			break;
		}
	}

	void DispatchRotation( TNode* parentNode, TNode* currentNode )
	{
		ERotationType rotationType = GetRotationType( currentNode );

		switch(rotationType)
		{
		case ERotationType_LL:
			{
				//rotation
				TNode* childLVL0 = currentNode;
				TNode* childLVL1 = currentNode->m_left;

				childLVL0->m_left = childLVL1->m_right;
				childLVL1->m_right = childLVL0;

				//update parent
				if( parentNode == NULL )
				{
					m_root = childLVL1;
				}
				else
				{
					if( parentNode->m_right == childLVL0 )
					{
						parentNode->m_right = childLVL1;
					}
					else if( parentNode->m_left == childLVL0 )
					{
						parentNode->m_left = childLVL1;
					}
				}
			}
			break;
		case ERotationType_RR:
			{
				//rotation
				TNode* childLVL0 = currentNode;
				TNode* childLVL1 = currentNode->m_right;

				childLVL0->m_right = childLVL1->m_left ;
				childLVL1->m_left = childLVL0;

				//update parent
				if( parentNode == NULL )
				{
					m_root = childLVL1;
				}
				else
				{
					if( parentNode->m_right == childLVL0 )
					{
						parentNode->m_right = childLVL1;
					}
					else if( parentNode->m_left == childLVL0 )
					{
						parentNode->m_left = childLVL1;
					}
				}
			}
			break;
		case ERotationType_LR:
			{
				//rotation 1
				TNode* childLVL0 = currentNode;
				TNode* childLVL1 = currentNode->m_left;
				TNode* childLVL2 = childLVL1->m_right;

				childLVL1->m_right = childLVL2->m_left;
				childLVL2->m_left = childLVL1;
				childLVL0->m_left = childLVL2;

				//rotation 2
				childLVL0 = currentNode;
				childLVL1 = currentNode->m_left;
				childLVL2 = childLVL1->m_right;

				childLVL0->m_left = childLVL2;
				childLVL1->m_right = childLVL0;

				//update parent
				if( parentNode == NULL )
				{
					m_root = childLVL1;
				}
				else
				{
					if( parentNode->m_right == childLVL0 )
					{
						parentNode->m_right = childLVL1;
					}
					else if( parentNode->m_left == childLVL0 )
					{
						parentNode->m_left = childLVL1;
					}
				}
			}
			break;
		case ERotationType_RL:
			{
				//rotation 1
				TNode* childLVL0 = currentNode;
				TNode* childLVL1 = currentNode->m_right;
				TNode* childLVL2 = childLVL1->m_left;

				childLVL1->m_left = childLVL2->m_right;
				childLVL2->m_right = childLVL1;
				childLVL0->m_right = childLVL2;

				//rotation 2
				childLVL0 = currentNode;
				childLVL1 = currentNode->m_right;
				childLVL2 = childLVL1->m_left;

				childLVL0->m_right = childLVL2;
				childLVL1->m_left = childLVL0;

				if( parentNode == NULL )
				{
					m_root = childLVL1;
				}
				else
				{
					//update parent
					if( parentNode->m_right == childLVL0 )
					{
						parentNode->m_right = childLVL1;
					}
					else if( parentNode->m_left == childLVL0 )
					{
						parentNode->m_left = childLVL1;
					}
				}
			}
			break;
		}
	}

	ERotationType GetRotationType( TNode* node)
	{
		EInsertionDirection rotation1 = m_historyMap[node];
		EInsertionDirection rotation2 = EDirection_Invalid;
		if( rotation1 == EDirection_Left )
		{
			rotation2 = m_historyMap[node->m_left];
		}
		else if( rotation1 == EDirection_Right)
		{
			rotation2 = m_historyMap[node->m_right];
		}

		switch( rotation1 )
		{
		case EDirection_Left:
			switch( rotation2 )
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
			switch( rotation2 )
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

protected:
	HashTable<TNode*, int> m_nodeHeights;
	HashTable<TNode*, int> m_nodeDiffHeights;
	HashTable<TNode*, EInsertionDirection> m_historyMap;
};