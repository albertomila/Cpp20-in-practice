#include "stdafx.h"
#include "Samples/arrayVector.h"
#include "Samples/HashSet.h"
#include "Samples/HashTable.h"
#include "Samples/LinkedList.h"
#include "Samples/LinkedQueue.h"

struct GraphAdjacentPrintHelpers;

template<class T>
class GraphAdjacentList
{
private:
	friend struct GraphAdjacentPrintHelpers; //For developer debug purposes

public:
	template<class T>
	struct Node
	{
		Node()
		{
		}

		T m_value;
	};

public:
	typedef T TypeValue;
	typedef Node<TypeValue> TNode;
	typedef LinkedList<TNode*> TLinkedList;

	GraphAdjacentList()
		:m_root(NULL)
	{
	}

	typename TNode* CreateNode( const TypeValue& value )
	{
		TNode* newNode = new TNode();
		newNode->m_value = value;

		if( m_root == NULL )
		{
			m_root = newNode;
		}

		assert( !m_shortestRouteMap.Exist( newNode ) );
		m_shortestRouteMap.Push( newNode, TLinkedList() );

		return newNode;
	}

	void AddChild( TNode* nodeTarget, TNode* node )
	{
		assert( m_shortestRouteMap.Exist( nodeTarget ) );
		TLinkedList& adjacentList = m_shortestRouteMap.Get( nodeTarget );
		adjacentList.PushBack( node );
	}


	bool IsEmpty() const
	{
		return m_shortestRouteMap.IsEmpty();
	}

	bool Exist(const TypeValue& value)
	{
		if( m_root == NULL )
		{
			return false;
		}

		HashSet<TNode*> visitedNodes;

		LinkedQueue<TNode*> queue;
		queue.Push( m_root );

		while( !queue.IsEmpty() )
		{
			TNode* currentNode = queue.GetHead();
			queue.Pop();

			visitedNodes.Set( currentNode );

			if( currentNode->m_value == value )
			{
				return true;
			}

			TLinkedList& adjacentList = m_shortestRouteMap.Get( currentNode );

			TLinkedList::TNode* node = adjacentList.GetFirst();
			while( node != NULL )
			{
				TNode* currentChildNode = node->m_value;

				if( !visitedNodes.Exist( currentChildNode ) )
				{
					visitedNodes.Set( currentChildNode );
					queue.Push( currentChildNode  );
				}
				node = node->m_next;
			}
		}

		return false;
	}

	void GetRoute( TNode* targetNode, ArrayVector<TNode*>& route_out )
	{
		HashSet<TNode*> visitedNodes;
		HashTable<TNode*,std::pair<TNode*, int> > shortestRouteMap;

		visitedNodes.Set( m_root );

		shortestRouteMap.Push( m_root, std::pair<TNode*,int>((TNode*)NULL,0));

		GetRouteBFS( m_root, visitedNodes, shortestRouteMap, 1 );

		route_out.PushBack( targetNode );

		std::pair<TNode*,int> currentNodeRoute = shortestRouteMap.Get( targetNode );
		while( currentNodeRoute.first != NULL )
		{
			//std method.
			//route_out.insert( route_out.begin(), currentNodeRoute.first );
			route_out.Insert( currentNodeRoute.first, 0 );
			currentNodeRoute = shortestRouteMap.Get( currentNodeRoute.first );
		}
	}

	void GetRouteBFS( TNode* currentNode
					, HashSet<TNode*>& visitedNodes
					, HashTable<TNode*,std::pair<TNode*, int> >& shortestRouteMap
					, int hops )
	{
		TLinkedList& adjacentList = m_shortestRouteMap.Get( currentNode );
		TLinkedList::TNode* node = adjacentList.GetFirst();
		while( node != NULL )
		{
			TNode* currentChildNode = node->m_value;
			node = node->m_next;

			if( !shortestRouteMap.Exist( currentChildNode ) )
			{
				shortestRouteMap.Push( currentChildNode, std::pair<TNode*,int>(currentNode,hops) );
			}
			else
			{
				std::pair<TNode*,int>& routeNode = shortestRouteMap.Get( currentChildNode );
				if( routeNode.second > hops )
				{
					routeNode.first = currentNode;
					routeNode.second = hops;
				}
			}

			if( visitedNodes.Exist( currentChildNode ) )
			{
				continue;
			}
			visitedNodes.Set( currentChildNode );
			GetRouteBFS( currentChildNode, visitedNodes, shortestRouteMap, hops + 1 );
		}
	}
	
private:
	HashTable<TNode*, TLinkedList > m_shortestRouteMap;
	TNode* m_root;
};

struct GraphAdjacentPrintHelpers
{
	template< class T >
	static void Print( T& graphAdjacent)
	{
		typedef T::TNode TNode;
		typedef T::TLinkedList TLinkedList;
		if( graphAdjacent.m_root == NULL )
		{
			return;
		}

		HashSet<TNode*> visitedNodes;

		LinkedQueue<TNode*> queue;
		queue.Push( graphAdjacent.m_root );

		while( !queue.IsEmpty() )
		{
			TNode* currentNode = queue.GetHead();
			queue.Pop();

			visitedNodes.Set( currentNode );

			COutColor( CoutColors::yellow );
			cout << currentNode->m_value << ":";
			cout << endl;

			TLinkedList& adjacentList = graphAdjacent.m_shortestRouteMap.Get( currentNode );

			TLinkedList::TNode* node = adjacentList.GetFirst();
			while( node != NULL )
			{
				TNode* currentChildNode = node->m_value;

				COutColor( CoutColors::cyan );
				cout << " ->" << currentChildNode->m_value;
				cout << endl;

				if( !visitedNodes.Exist( currentChildNode ) )
				{
					visitedNodes.Set( currentChildNode );
					queue.Push( currentChildNode  );
				}
				node = node->m_next;
			}
		}
	}
};
