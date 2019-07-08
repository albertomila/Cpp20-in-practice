#include "stdafx.h"
#include "Samples/HashTable.h"
#include "Samples/LinkedQueue.h"
#include "Samples/LinkedStack.h"

struct TreeRedBlackPrintHelpers;

template<class T>
class RedBlackTree
{
private:
	friend struct TreeRedBlackPrintHelpers;

	enum EInsertionDirection
	{
		  EDirection_Invalid
		, EDirection_Left
		, EDirection_Right
	};

	enum ENodeColor
	{
		  ENodeColor_Red
		, ENodeColor_Black
	};

	enum EInsertionCase
	{
		  EInsertionCase_Invalid
		, EInsertionCase_0
		, EInsertionCase_1
		, EInsertionCase_2
		, EInsertionCase_3LR
		, EInsertionCase_3RL
		, EInsertionCase_4LL
		, EInsertionCase_4RR
	};

public:
	template<class T>
	struct Node
	{
		Node()
			: m_color( ENodeColor_Red ) 
			, m_left( NULL )
			, m_right( NULL )
		{
		}
		T m_value;
		Node* m_left;
		Node* m_right;

		ENodeColor GetColor() const{ return m_color; }
		void SetColor( ENodeColor color ){ m_color = color;}
	private:
		ENodeColor m_color;
	};

public:
	typedef T TypeValue;
	typedef Node<TypeValue> TNode;
public:
	RedBlackTree()
		: m_root( NULL )
	{
	}

	void Push( const TypeValue& value )
	{
		LinkedStack<TNode*> stackTreeNodes;
		Add( value, stackTreeNodes, &m_root );
	}

	bool Exist( const TypeValue& value )
	{
		return ExistInternal( value, m_root );
	}
	
	void Delete( const TypeValue& value )
	{
		if( m_root == NULL )
		{
			return;
		}

		LinkedStack<TNode*> stackTreeNodes;
		Remove( value, stackTreeNodes, NULL, &m_root );
	}

private:

	void Remove( const TypeValue& value, LinkedStack<TNode*>& stackTreeNodes, TNode* parentNode, TNode** currentNode )
	{
		if( *currentNode == NULL )
		{
			return;
		}

		stackTreeNodes.Push( (*currentNode) );
		if(  (*currentNode)->m_value == value   )
		{
			TNode* deletedNode = (*currentNode);

			//case 0.1: Node to delete doesn't have left child to start looking max.
			if( !deletedNode->m_left && deletedNode->m_right )
			{
				if(parentNode->m_left == deletedNode  )
				{
					parentNode->m_left = deletedNode->m_right;
				}
				else if(parentNode->m_right == deletedNode )
				{
					parentNode->m_right = deletedNode->m_right;
				}

				deletedNode->m_right->SetColor( ENodeColor_Black );

				return;
			}

			//case 0.1: Node to delete doesn't have right child.
			if( deletedNode->m_left && !deletedNode->m_right )
			{
				if(parentNode->m_left == deletedNode  )
				{
					parentNode->m_left = deletedNode->m_left;
				}
				else if(parentNode->m_right == deletedNode )
				{
					parentNode->m_right = deletedNode->m_left;
				}

				deletedNode->m_left->SetColor( ENodeColor_Black );

				return;
			}

			//Find next max node of current node.
			//stackTreeNodes.Pop();
			TNode* foundNodeParent = parentNode;
			TNode* foundNode = GetMaxNode( stackTreeNodes, (*currentNode), foundNodeParent );

			//Put found node into current node
			if(foundNodeParent->m_left == foundNode )
			{
				foundNodeParent->m_left = foundNode->m_left;
			}
			else if(foundNodeParent->m_right == foundNode )
			{
				foundNodeParent->m_right = foundNode->m_left;
			}

			bool hasnotChildren = !foundNode->m_left && !foundNode->m_right;
			foundNode->m_left = deletedNode->m_left;
			foundNode->m_right = deletedNode->m_right;
			foundNode->SetColor( deletedNode->GetColor() );

			if( deletedNode->GetColor() == ENodeColor_Black 
				&& hasnotChildren)
			{
				stackTreeNodes.Pop();
				if( stackTreeNodes.IsEmpty() )
				{
					stackTreeNodes.Push( foundNode );
				}
				stackTreeNodes.Push( NULL );
			}
			else
			{
				UpdateDeletedNode( stackTreeNodes, deletedNode, foundNode );
			}

			//Update parent nodes and delete the final found node.
			if( parentNode )
			{
				if(parentNode->m_left == deletedNode  )
				{
					parentNode->m_left = foundNode;
				}
				else if(parentNode->m_right == deletedNode )
				{
					parentNode->m_right = foundNode;
				}
			}
			else
			{
				m_root = foundNode;
			}


			//cases:
			if( deletedNode->GetColor() == ENodeColor_Red )
			{
				if( foundNode )
				{
					if( !foundNode->m_left && !foundNode->m_right)
					{
						//nothing
					}
					else if( foundNode->m_left && foundNode->m_right)
					{
						foundNode->m_left->SetColor( ENodeColor_Black );
					}
					else if( foundNode->m_right)
					{
						stackTreeNodes.Push( NULL );
						DispatchDeleteCase( stackTreeNodes );
					}
					else if( foundNode->m_left )
					{
						foundNode->m_left->SetColor( ENodeColor_Black );
					}
				}
				return;
			}

			DispatchDeleteCase( stackTreeNodes );
			delete deletedNode;
		}
		else if( (*currentNode)->m_value > value )
		{
			Remove( value, stackTreeNodes, (*currentNode), &((*currentNode)->m_left) );
		}
		else if( (*currentNode)->m_value < value )
		{
			Remove( value, stackTreeNodes, (*currentNode), &((*currentNode)->m_right) );
		}
	}

	TNode* GetMaxNode( LinkedStack<TNode*>& stackTreeNodes, TNode* currentNode, TNode*& parentNode_out )
	{
		if( !currentNode->m_left && !currentNode->m_right )
		{
			return currentNode;
		}
		else
		{
			parentNode_out = currentNode;
			return GetMaxNodeInternal( stackTreeNodes, currentNode->m_left, parentNode_out );
		}
	}

	TNode* GetMaxNodeInternal( LinkedStack<TNode*>& stackTreeNodes, TNode* currentNode, TNode*& parentNode_out )
	{
		if( !currentNode->m_left && !currentNode->m_right )
		{
			return currentNode;
		}
		else if( currentNode->m_right )
		{
			stackTreeNodes.Push( currentNode );
			parentNode_out = currentNode;
			return GetMaxNode( stackTreeNodes, currentNode->m_right, parentNode_out );
		}
		else
		{
			return currentNode;
		}

		return NULL;
	}


	void UpdateDeletedNode(LinkedStack<TNode*>& stackTreeNodes, TNode* deletedNode, TNode* foundNode )
	{
		LinkedStack<TNode*> nodes;
		while( stackTreeNodes.GetTop() != deletedNode )
		{
			nodes.Push( stackTreeNodes.Pop() );
		}

		stackTreeNodes.Pop();
		stackTreeNodes.Push( foundNode );

		while( !nodes.IsEmpty() )
		{
			stackTreeNodes.Push( nodes.Pop() );
		}
	}

	void DispatchDeleteCase(LinkedStack<TNode*>& stackTreeNodes )
	{
		TNode* childLVL3 = stackTreeNodes.Pop();
		TNode* childLVL2 = stackTreeNodes.IsEmpty() ? NULL : stackTreeNodes.Pop();
		TNode* childLVL1 = stackTreeNodes.IsEmpty() ? NULL : stackTreeNodes.GetTop();

		//case 0: new child is red
		if( childLVL3 && childLVL3->GetColor() == ENodeColor_Red )
		{
			childLVL3->SetColor( ENodeColor_Black );
			return;
		}

		//recover sibling of new child.
		TNode* childLVL3Sibling = NULL;
		if( childLVL2 )
		{
			childLVL3Sibling =    childLVL2->m_left == childLVL3
								? childLVL2->m_right
								: childLVL2->m_left;
		}

		//case 1.1
		if(		childLVL3Sibling
			&&	childLVL3Sibling->GetColor() == ENodeColor_Red 
			&&  childLVL2->m_left == childLVL3Sibling )
		{
			//swap colors
			ENodeColor colorSwitch = childLVL2->GetColor();
			childLVL2->SetColor( childLVL3Sibling->GetColor() );
			childLVL3Sibling->SetColor( colorSwitch );

			//rotate right
			childLVL2->m_left = childLVL3Sibling->m_right;
			childLVL3Sibling->m_right = childLVL2;

			//update pointer LVL1
			if( childLVL1 )
			{
				if( childLVL1->m_left == childLVL2 )
				{
					childLVL1->m_left = childLVL3Sibling;
				}
				else if( childLVL1->m_right == childLVL2 )
				{
					childLVL1->m_right = childLVL3Sibling;
				}
			}
			else
			{
				m_root = childLVL3Sibling;
			}

			//Update levels for further cases
			childLVL1 = childLVL3Sibling;
			childLVL3Sibling = childLVL2->m_left;
		}

		//case 1.2
		else if(childLVL3Sibling
			&&	childLVL3Sibling->GetColor() == ENodeColor_Red 
			&&  childLVL2->m_right == childLVL3Sibling )
		{
			//swap colors
			ENodeColor colorSwitch = childLVL2->GetColor();
			childLVL2->SetColor( childLVL3Sibling->GetColor() );
			childLVL3Sibling->SetColor( colorSwitch );

			//rotate left
			childLVL2->m_right = childLVL3Sibling->m_left;
			childLVL3Sibling->m_left = childLVL2;

			//update pointer LVL1
			if( childLVL1 )
			{
				if( childLVL1->m_left == childLVL2 )
				{
					childLVL1->m_left = childLVL3Sibling;
				}
				else if( childLVL1->m_right == childLVL2 )
				{
					childLVL1->m_right = childLVL3Sibling;
				}
			}
			else
			{
				m_root = childLVL3Sibling;
			}

			//Update levels for further cases
			childLVL1 = childLVL3Sibling;
			childLVL3Sibling = childLVL2->m_right;
		}

		//case 2
		if(		childLVL3Sibling
			&&	childLVL3Sibling->GetColor() == ENodeColor_Black
			&&	(!childLVL3Sibling->m_left || childLVL3Sibling->m_left->GetColor() == ENodeColor_Black )
			&&	(!childLVL3Sibling->m_right || childLVL3Sibling->m_right->GetColor() == ENodeColor_Black )
			)
		{
			childLVL2->SetColor( ENodeColor_Black );
			childLVL3Sibling->SetColor( ENodeColor_Red );
		}

		//case 3.1
		else if(childLVL2->m_right == childLVL3
			&&	childLVL3Sibling
			&&	childLVL3Sibling->GetColor() == ENodeColor_Black
			&&	childLVL3Sibling->m_left
			&&	childLVL3Sibling->m_left->GetColor() == ENodeColor_Red
			)
		{
			//change colors
			childLVL2->SetColor( ENodeColor_Black );
			childLVL3Sibling->SetColor( ENodeColor_Red );
			if( childLVL3Sibling->m_left )
			{
				childLVL3Sibling->m_left->SetColor( ENodeColor_Black );
			}

			//rotate right
			childLVL2->m_left = childLVL3Sibling->m_right;
			childLVL3Sibling->m_right = childLVL2;

			//update pointer LVL1
			if( childLVL1 )
			{
				if( childLVL1->m_left == childLVL2 )
				{
					childLVL1->m_left = childLVL3Sibling;
				}
				else if( childLVL1->m_right == childLVL2 )
				{
					childLVL1->m_right = childLVL3Sibling;
				}
			}
			else
			{
				m_root = childLVL3Sibling;
			}
		}

		//case 3.2
		else if(childLVL2->m_left == childLVL3
			&&	childLVL3Sibling
			&&	childLVL3Sibling->GetColor() == ENodeColor_Black
			&&	childLVL3Sibling->m_right
			&&	childLVL3Sibling->m_right->GetColor() == ENodeColor_Red
			)
		{
			//change colors
			childLVL2->SetColor( ENodeColor_Black );
			childLVL3Sibling->SetColor( ENodeColor_Red );
			if( childLVL3Sibling->m_right )
			{
				childLVL3Sibling->m_right->SetColor( ENodeColor_Black );
			}

			//rotate left
			childLVL2->m_right = childLVL3Sibling->m_left;
			childLVL3Sibling->m_left = childLVL2;

			//update pointer LVL1
			if( childLVL1 )
			{
				if( childLVL1->m_left == childLVL2 )
				{
					childLVL1->m_left = childLVL3Sibling;
				}
				else if( childLVL1->m_right == childLVL2 )
				{
					childLVL1->m_right = childLVL3Sibling;
				}
			}
			else
			{
				m_root = childLVL3Sibling;
			}
		}

		//case 4.1
		if(		childLVL2->m_right == childLVL3
			&&	childLVL3Sibling
			&&	childLVL3Sibling->GetColor() == ENodeColor_Black
			&&	childLVL3Sibling->m_right
			&&	childLVL3Sibling->m_right->GetColor() == ENodeColor_Red
			)
		{
			//change colors
			childLVL2->SetColor( ENodeColor_Black );
			childLVL3Sibling->SetColor( ENodeColor_Red );
			if( childLVL3Sibling->m_left )
			{
				childLVL3Sibling->m_left->SetColor( ENodeColor_Black );
			}

			//rotate right
			childLVL2->m_left = childLVL3Sibling->m_right;
			childLVL3Sibling->m_right = childLVL2;

			//update pointer LVL1
			if( childLVL1 )
			{
				if( childLVL1->m_left == childLVL2 )
				{
					childLVL1->m_left = childLVL3Sibling;
				}
				else if( childLVL1->m_right == childLVL2 )
				{
					childLVL1->m_right = childLVL3Sibling;
				}
			}
			else
			{
				m_root = childLVL3Sibling;
			}
		}

		//case 4.2
		else if(childLVL2->m_left == childLVL3
			&&	childLVL3Sibling
			&&	childLVL3Sibling->GetColor() == ENodeColor_Black
			&&	childLVL3Sibling->m_left
			&&	childLVL3Sibling->m_left->GetColor() == ENodeColor_Red
			)
		{
			//change colors
			childLVL2->SetColor( ENodeColor_Black );
			childLVL3Sibling->SetColor( ENodeColor_Red );
			if( childLVL3Sibling->m_right )
			{
				childLVL3Sibling->m_right->SetColor( ENodeColor_Black );
			}

			//rotate left
			childLVL2->m_right = childLVL3Sibling->m_left;
			childLVL3Sibling->m_left = childLVL3Sibling->m_left->m_right;
			childLVL2->m_right->m_right = childLVL3Sibling;

			//update pointer LVL1
			if( childLVL1 )
			{
				if( childLVL1->m_left == childLVL2 )
				{
					childLVL1->m_left = childLVL3Sibling;
				}
				else if( childLVL1->m_right == childLVL2 )
				{
					childLVL1->m_right = childLVL3Sibling;
				}
			}
			else
			{
				m_root = childLVL3Sibling;
			}
		}
	}

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
	
	void ResolveConflicts( LinkedStack<TNode*>& stackTreeNodes )
	{
		while( !stackTreeNodes.IsEmpty() )
		{
			TNode* childLVL3 = stackTreeNodes.Pop();
			TNode* childLVL2 = stackTreeNodes.IsEmpty() ? NULL : stackTreeNodes.Pop();
			TNode* childLVL1 = stackTreeNodes.IsEmpty() ? NULL : stackTreeNodes.Pop();
			TNode* childLVL0 = stackTreeNodes.IsEmpty() ? NULL : stackTreeNodes.Pop();

			EInsertionCase insertionCase = GetInsertionCase( childLVL1, childLVL2, childLVL3 );

			DispatchCase( insertionCase, stackTreeNodes, childLVL0, childLVL1, childLVL2, childLVL3 );
		}
	}

	EInsertionCase GetInsertionCase( TNode* childLVL1, TNode* childLVL2, TNode* childLVL3 )
	{
		//case 0
		if( childLVL2 == NULL )
		{
			return EInsertionCase_0;
		}

		//case 1
		assert( childLVL3 && childLVL2 );
		if( childLVL2->GetColor() == ENodeColor_Black )
		{
			return EInsertionCase_1;
		}

		if( !childLVL1 )
		{
			return EInsertionCase_Invalid;
		}

		TNode* childUncle = ( childLVL1->m_left == childLVL2 )
			? childUncle = childLVL1->m_right
			: childUncle = childLVL1->m_left;

		//case 2
		assert( childLVL1 );
		if( childUncle && childUncle->GetColor() == ENodeColor_Red )
		{
			return EInsertionCase_2;
		}

		if( !childLVL2 )
		{
			return EInsertionCase_Invalid;
		}

		//case 3 & 4
		if( !childUncle || childUncle->GetColor() == ENodeColor_Black )
		{
			if(		childLVL1->m_left == childLVL2 
				&&	childLVL2->m_right == childLVL3 )
			{
				return EInsertionCase_3LR;
			}

			if(		childLVL1->m_right == childLVL2 
				&&	childLVL2->m_left == childLVL3 )
			{
				return EInsertionCase_3RL;
			}

			if(		childLVL1->m_left == childLVL2 
				&&	childLVL2->m_left == childLVL3 )
			{
				return EInsertionCase_4LL;
			}

			if(		childLVL1->m_right == childLVL2 
				&&	childLVL2->m_right == childLVL3 )
			{
				return EInsertionCase_4RR;
			}
		}

		assert( false );
		return EInsertionCase_Invalid;
	}

	void DispatchCase( EInsertionCase insertionCase, LinkedStack<TNode*>& stackTreeNodes, TNode* childLVL0, TNode* childLVL1, TNode* childLVL2, TNode* childLVL3 )
	{
		if( insertionCase == EInsertionCase_Invalid )
		{
			return;
		}

		if( insertionCase == EInsertionCase_0 )
		{
			m_root->SetColor( ENodeColor_Black );
			return;
		}

		if( insertionCase == EInsertionCase_1 )
		{
			//nothing
			return;
		}

		TNode* childUncle = ( childLVL1->m_left == childLVL2 )
							? childUncle = childLVL1->m_right
							: childUncle = childLVL1->m_left;


		switch( insertionCase )
		{	
			case EInsertionCase_2:
			{
				childLVL1->SetColor( ENodeColor_Red );
				childLVL2->SetColor( ENodeColor_Black );
				if( childUncle )
				{
					childUncle->SetColor( ENodeColor_Black );
				}
				
				if( childLVL0 )
				{
					if(		childLVL0->GetColor() == ENodeColor_Red 
						&&	childLVL1->GetColor() == ENodeColor_Red  )
					{
						stackTreeNodes.Push( childLVL0 );
						stackTreeNodes.Push( childLVL1 );
					}
				}
			}
			break;
			case EInsertionCase_3LR:
			{
				childLVL1->SetColor( ENodeColor_Red );
				childLVL2->SetColor( ENodeColor_Red );
				childLVL3->SetColor( ENodeColor_Black );
				if( childUncle )
				{
					childUncle->SetColor( ENodeColor_Black );
				}

				//rotate left;
				childLVL1->m_left = childLVL3;
				childLVL2->m_right = childLVL3->m_left;
				childLVL3->m_left = childLVL2;

				TNode* cLVL2 = childLVL3;
				TNode* cLVL3 = childLVL2; 

				if(childLVL0->m_left == childLVL1 )
				{
					childLVL0->m_left = cLVL2;
				}
				else if(childLVL0->m_right == childLVL1 )
				{
					childLVL0->m_right = cLVL2;
				}

				childLVL1->m_left = cLVL2->m_right;
				cLVL2->m_right = childLVL1;
			}
			break;

			case EInsertionCase_3RL:
			{
				childLVL1->SetColor( ENodeColor_Red );
				childLVL2->SetColor( ENodeColor_Red );
				childLVL3->SetColor( ENodeColor_Black );
				if( childUncle )
				{
					childUncle->SetColor( ENodeColor_Black );
				}

				//rotate left;
				childLVL1->m_right = childLVL3;
				childLVL2->m_left = childLVL3->m_right;
				childLVL3->m_right = childLVL2;

				TNode* cLVL2 = childLVL3;
				TNode* cLVL3 = childLVL2; 

				if(childLVL0->m_right == childLVL1 )
				{
					childLVL0->m_right = cLVL2;
				}
				else if(childLVL0->m_left == childLVL1 )
				{
					childLVL0->m_left = cLVL2;
				}

				childLVL1->m_right = cLVL2->m_left;
				cLVL2->m_left = childLVL1;
			}
			break;

			case EInsertionCase_4RR:
			{
				childLVL1->SetColor( ENodeColor_Red );
				childLVL2->SetColor( ENodeColor_Black );

				childLVL1->m_right = childLVL2->m_left;
				childLVL2->m_left = childLVL1;
				
				if(childLVL0->m_left == childLVL1 )
				{
					childLVL0->m_left = childLVL2;
				}
				else if(childLVL0->m_right == childLVL1 )
				{
					childLVL0->m_right = childLVL2;
				}

				if(		childLVL0->GetColor() == ENodeColor_Red 
					&&	childLVL2->GetColor() == ENodeColor_Red  )
				{
					stackTreeNodes.Push( childLVL0 );
					stackTreeNodes.Push( childLVL2 );
				}
			}
			break;

			case EInsertionCase_4LL:
			{
				assert( !childUncle || childUncle->GetColor() == ENodeColor_Black );

				childLVL1->SetColor( ENodeColor_Red );
				childLVL2->SetColor( ENodeColor_Black );

				childLVL1->m_left = childLVL2->m_right;
				childLVL2->m_right = childLVL1;

				if(childLVL0->m_left == childLVL1 )
				{
					childLVL0->m_left = childLVL2;
				}
				else if(childLVL0->m_right == childLVL1 )
				{
					childLVL0->m_right = childLVL2;
				}

				if(		childLVL0->GetColor() == ENodeColor_Red 
					&&	childLVL2->GetColor() == ENodeColor_Red  )
				{
					stackTreeNodes.Push( childLVL0 );
					stackTreeNodes.Push( childLVL2 );
				}
			}
			break;
		}

		if( m_root->GetColor() == ENodeColor_Red )
		{
			m_root->SetColor( ENodeColor_Black );
		}
	}

	void Add( const TypeValue& value, LinkedStack<TNode*>& stackTreeNodes, TNode** currentNode )
	{
		if( *currentNode == NULL )
		{
			*currentNode = new TNode();
			(*currentNode)->m_value = value;

			stackTreeNodes.Push( (*currentNode) );
			ResolveConflicts( stackTreeNodes );
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

private:
	TNode* m_root;
};


struct TreeRedBlackPrintHelpers
{
	template< class T >
	static void PrintTree( const T& tree )
	{
		typedef T::TNode TNode;

		HashTable<TNode*, int > highNodeMap;
		LinkedQueue<TNode*> queue;
		queue.Push( tree.m_root );

		highNodeMap[tree.m_root] = 0;
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
				previousHigh = currentHigh;
				cout << endl;
			}

			COutColor( value->GetColor()==T::ENodeColor_Red ? CoutColors::red : CoutColors::grey );

			cout << value->m_value;
			cout << ",";
		} 
		cout << endl;
	}
};