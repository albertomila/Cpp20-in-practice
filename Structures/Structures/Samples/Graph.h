#include "stdafx.h"
#include "Samples/arrayVector.h"
#include "Samples/LinkedQueue.h"
#include "Samples/LinkedStack.h"
#include "Samples/HashSet.h"
#include "Samples/HashTable.h"

struct GraphPrintHelpers;

template<class T>
class Graph
{
private:
	friend struct GraphPrintHelpers;

public:
	template<class T>
	struct Node
	{
		Node()
		{
		}

		T m_value;
		ArrayVector<Node*> m_children;
	};

	enum ESearchAlgorithm
	{
		  DFS
		, BFS
	};

public:
	typedef T TypeValue;
	typedef Node<TypeValue> TNode;

public:
	Graph()
		: m_root( NULL )
	{
	}

	void SetRoot(TNode* node)
	{
		m_root = node;
	}

	typename Graph::TNode* CreateNode( const TypeValue& value )
	{
		TNode* newNode = new TNode();
		newNode->m_value = value;
		
		if( !m_root )
		{
			m_root = newNode;
		}
		
		return newNode;
	}
	void AddChild( TNode* nodeTarget, TNode* node )
	{
		nodeTarget->m_children.PushBack( node );
	}

	bool IsEmpty() const
	{
		return m_root == NULL;
	}

	bool Exist( const TypeValue& value )
	{
		return ExistUsingAlgorithm<DFS>(value);
	}

	template<ESearchAlgorithm>
	bool ExistUsingAlgorithm( const TypeValue& value )
	{
		HashSet<int> visitedNodes;
		LinkedQueue<TNode*> queue;
		queue.Push( m_root );

		while( !queue.IsEmpty() )
		{
			TNode* currentNode = queue.GetHead();
			queue.Pop();

			if( currentNode->m_value == value )
			{
				return true;
			}

			unsigned int address = reinterpret_cast<unsigned int>( currentNode );
			visitedNodes.Set( address );

			for(  ArrayVector<TNode*>::iterator it = currentNode->m_children.begin()
				; it != currentNode->m_children.end()
				; ++it)
			{
				TNode* currentChildNode = *it;
				unsigned int currentChildAddress = reinterpret_cast<unsigned int>( currentChildNode );
				if( !visitedNodes.Exist( currentChildAddress ) )
				{
					queue.Push( currentChildNode );
				}
			}
		}

		return false;
	}

	template<>
	bool ExistUsingAlgorithm<BFS>( const TypeValue& value )
	{
		HashSet<int> visitedNodes;
		return ExistBFSInternal( visitedNodes, m_root, value );
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
			//with std, TODO: support iterator insertion on ArrayVector
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
		for(  ArrayVector<TNode*>::iterator it = currentNode->m_children.begin()
			; it != currentNode->m_children.end()
			; ++it)
		{
			TNode* currentChildNode = *it;
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
	bool ExistBFSInternal( HashSet<int>& visitedNodes, TNode* currentNode, const TypeValue& value )
	{
		if( currentNode->m_value == value )
		{
			return true;
		}

		unsigned int address = reinterpret_cast<unsigned int>( currentNode );
		visitedNodes.Set( address );

		for(  ArrayVector<TNode*>::iterator it = currentNode->m_children.begin()
			; it != currentNode->m_children.end()
			; ++it)
		{
			TNode* currentChildNode = *it;
			unsigned int currentChildAddress = reinterpret_cast<unsigned int>( currentChildNode );
			if( !visitedNodes.Exist( currentChildAddress ) )
			{
				if( ExistBFSInternal( visitedNodes, currentChildNode, value ) )
				{
					return true;
				}
			}
		}

		return false;
	}

private:
	TNode* m_root;
};

struct GraphPrintHelpers
{
	template< class T >
	static void Print( const T& graph )
	{
		DoPrintDFS<T>( graph );
	}

	template< class T >
	static void PrintBFS( const T& graph )
	{
		HashSet<int> visitedNodes;
		DoPrintBFS<T>( visitedNodes, graph.m_root );
	}

private:
	template< class T >
	static void DoPrintDFS( const T& graph )
	{
		HashSet<int> visitedNodes;
		LinkedQueue<T::TNode*> queue;
		queue.Push( graph.m_root );

		while( !queue.IsEmpty() )
		{
			T::TNode* currentNode = queue.GetHead();
			queue.Pop();

			unsigned int address = reinterpret_cast<unsigned int>( currentNode );

			if( visitedNodes.Exist( address ) )
			{
				continue;
			}

			COutColor( CoutColors::yellow );
			cout << currentNode->m_value << ":";
			cout << endl;

			visitedNodes.Set( address );

			for(  ArrayVector<T::TNode*>::iterator it = currentNode->m_children.begin()
				; it != currentNode->m_children.end()
				; ++it)
			{
				T::TNode* currentChildNode = *it;

				COutColor( CoutColors::cyan );
				cout << " ->" << currentChildNode->m_value;
				cout << endl;

				unsigned int currentChildAddress = reinterpret_cast<unsigned int>( currentChildNode );
				if( !visitedNodes.Exist( currentChildAddress ) )
				{
					queue.Push( currentChildNode );
				}
			}
			cout << endl;
		}
	}

	template< class T >
	static void DoPrintBFS( HashSet<int>& visitedNodes, typename T::TNode* currentNode )
	{
		unsigned int address = reinterpret_cast<unsigned int>( currentNode );
		if( visitedNodes.Exist( address ) )
		{
			return;
		}

		COutColor( CoutColors::yellow );
		cout << currentNode->m_value << ":";
		cout << endl;

		visitedNodes.Set( address );

		for(  ArrayVector<T::TNode*>::iterator it = currentNode->m_children.begin()
			; it != currentNode->m_children.end()
			; ++it)
		{
			T::TNode* currentChildNode = *it;

			COutColor( CoutColors::cyan );
			cout << " ->" << currentChildNode->m_value;
			cout << endl;

			unsigned int currentChildAddress = reinterpret_cast<unsigned int>( currentChildNode );
			if( !visitedNodes.Exist( currentChildAddress ) )
			{
				DoPrintBFS<T>( visitedNodes, currentChildNode );
			}
		}
		cout << endl;
	}
};
