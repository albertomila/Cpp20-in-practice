#pragma once
#include "stdafx.h"
#include "Samples/Graph.h"

BEGIN_TEST(TestGraph)
		typedef Graph<int> TGraph;
		TGraph graph;

		TGraph::TNode* node0 = graph.CreateNode( 0 );
		TGraph::TNode* node1 = graph.CreateNode( 1 );
		TGraph::TNode* node2 = graph.CreateNode( 2 );
		TGraph::TNode* node3 = graph.CreateNode( 3 );
		TGraph::TNode* node4 = graph.CreateNode( 4 );
		TGraph::TNode* node5 = graph.CreateNode( 5 );
		TGraph::TNode* node6 = graph.CreateNode( 6 );
		TGraph::TNode* node7 = graph.CreateNode( 7 );
		TGraph::TNode* node8 = graph.CreateNode( 8 );
		TGraph::TNode* node9 = graph.CreateNode( 9 );
		TGraph::TNode* node10 = graph.CreateNode( 10 );

		graph.AddChild( node0, node1 );
		graph.AddChild( node0, node2 );
		graph.AddChild( node0, node3 );
		graph.AddChild( node0, node4 );

		graph.AddChild( node1, node5 );
		graph.AddChild( node2, node5 );

		graph.AddChild( node3, node6 );
		graph.AddChild( node4, node6 );

		graph.AddChild( node4, node7 );

		graph.AddChild( node5, node10 );
		graph.AddChild( node3, node10 );
		graph.AddChild( node9, node10 );

		graph.AddChild( node6, node8 );
		graph.AddChild( node6, node9 );
		graph.AddChild( node8, node9 );

		ArrayVector<TGraph::TNode*> route;
		graph.GetRoute( node10, route );

		//print route
		COutColor( CoutColors::yellow );
		for(  ArrayVector<TGraph::TNode*>::iterator it = route.begin()
			; it != route.end()
			; ++it)
		{
			cout << (*it)->m_value;
			if( it != (route.end() - 1) )
			{
				cout << " -> ";
			}
		}
		cout << endl;

		bool existValue = graph.Exist( 5 );
		existValue = graph.Exist( 10 );
		existValue = graph.Exist( 11 );

		existValue = graph.ExistUsingAlgorithm<TGraph::BFS>( 5 );
		existValue = graph.ExistUsingAlgorithm<TGraph::BFS>( 10 );
		existValue = graph.ExistUsingAlgorithm<TGraph::BFS>( 11 );

		GraphPrintHelpers::Print( graph );
		GraphPrintHelpers::PrintBFS( graph );
END_TEST()