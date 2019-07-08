#include "stdafx.h"
#include "Samples/arrayVector.h"
#include "Samples/LinkedList.h"
#include "Samples/LinkedQueue.h"
#include "Samples/HashSet.h"
#include "Samples/HashTable.h"

struct GraphMatrixPrintHelpers;

template<class T, unsigned int CAPACITY>
class GraphMatrix
{
private:
	friend struct GraphMatrixPrintHelpers;

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
	typedef HashTable<TNode*, unsigned int> TIndexMap;
	typedef HashTable<unsigned int, TNode*> TNodeMap;

	GraphMatrix()
		: m_root(NULL)
		, m_nextIndex( 0 )
	{
		for( unsigned int i = 0; i<CAPACITY; ++i)
		{
			for( unsigned int j = 0; j<CAPACITY; ++j)
			{
				m_childrenMatrix[i][j] = false;
			}
		}
	}

	unsigned int GetCapacity() const
	{
		return CAPACITY;
	}

	typename TNode* CreateNode( const TypeValue& value )
	{
		TNode* newNode = new TNode();
		newNode->m_value = value;

		if( m_root == NULL )
		{
			m_root = newNode;
		}
		m_indexMap.Push( newNode, m_nextIndex );
		m_nodeMap.Push( m_nextIndex, newNode );

		++m_nextIndex;
		return newNode;
	}

	void AddChild( TNode* sourceNode, TNode* targetNode )
	{
		assert( m_indexMap.Exist( sourceNode ) );
		assert( m_indexMap.Exist( targetNode ) );
		unsigned int sourceNodeIndex = m_indexMap.Get( sourceNode );
		unsigned int targetNodeIndex = m_indexMap.Get( targetNode );
		m_childrenMatrix[sourceNodeIndex][targetNodeIndex] = true;
	}

	bool IsEmpty() const
	{
		return m_indexMap.IsEmpty();
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

			unsigned int nodeIndex = m_indexMap.Get( currentNode );
			for( unsigned int j = 0; j<CAPACITY; ++j)
			{
				if( m_childrenMatrix[nodeIndex][j] )
				{
					TNode* currentChildNode = m_nodeMap.Get( j );

					if( !visitedNodes.Exist( currentChildNode ) )
					{
						visitedNodes.Set( currentChildNode );
						queue.Push( currentChildNode  );
					}
				}
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
		unsigned int nodeIndex = m_indexMap.Get( currentNode );
		for( unsigned int j = 0; j<CAPACITY; ++j)
		{
			if( m_childrenMatrix[nodeIndex][j] )
			{
				TNode* currentChildNode = m_nodeMap.Get( j );

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
	}

private:
	TIndexMap m_indexMap;
	TNodeMap m_nodeMap;
	bool m_childrenMatrix[CAPACITY][CAPACITY];
	TNode* m_root;
	unsigned int m_nextIndex;
};



struct GraphMatrixPrintHelpers
{
	template< class T >
	static void Print( T& graph)
	{
		typedef T::TNode TNode;

		if( graph.m_root == NULL )
		{
			return;
		}

		HashSet<TNode*> visitedNodes;

		LinkedQueue<TNode*> queue;
		queue.Push( graph.m_root );

		while( !queue.IsEmpty() )
		{
			TNode* currentNode = queue.GetHead();
			queue.Pop();

			visitedNodes.Set( currentNode );

			COutColor( CoutColors::yellow );
			cout << currentNode->m_value << ":";
			cout << endl;

			unsigned int nodeIndex = graph.m_indexMap.Get( currentNode );
			for( unsigned int j = 0; j<graph.GetCapacity(); ++j)
			{
				if( graph.m_childrenMatrix[nodeIndex][j] )
				{
					TNode* currentChildNode = graph.m_nodeMap.Get( j );

					COutColor( CoutColors::cyan );
					cout << " ->" << currentChildNode->m_value;
					cout << endl;

					if( !visitedNodes.Exist( currentChildNode ) )
					{
						visitedNodes.Set( currentChildNode );
						queue.Push( currentChildNode  );
					}
				}
			}
		}
	}

	template< class T >
	static void PrintMatrix( const T& graph)
	{
		COutColor( CoutColors::red );
		cout << "	";
		for( unsigned int i = 0; i<graph.GetCapacity(); ++i)
		{
			cout << i << " ";
		}
		cout << endl;

		for( unsigned int j = 0; j<graph.GetCapacity(); ++j)
		{
			COutColor( CoutColors::red );
			cout << j << "	";
			for( unsigned int i = 0; i<graph.GetCapacity(); ++i)
			{
				if( graph.m_childrenMatrix[i][j] )
				{
					COutColor( CoutColors::yellow );
				}
				else
				{
					COutColor( CoutColors::cyan );
				}
				cout << graph.m_childrenMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};
