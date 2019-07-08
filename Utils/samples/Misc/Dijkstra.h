#pragma once
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <queue>
#include <set>

using namespace std;

namespace nsDijkstra
{
	struct SNode;

	struct SNodePtr
	{
		int _cost = 0;
		SNode* _node = nullptr;
	};

	struct SNode
	{
		SNode() : _id('\0') {}
		SNode(char id) : _id(id) {}

		char _id;
		std::vector<SNodePtr> _nodes;
	};

	struct SData
	{
		char _sourceId;
		int cost = 0;
	};

	class CHelpers
	{
	public:
		static std::vector<SNode> CreateAllNodes(int amount)
		{
			char initId = 'A';
			std::vector<SNode> nodes;
			nodes.resize(amount);
			for (int i = 0; i < amount; ++i)
			{
				nodes[i]._id = initId;
				++initId;
			}

			return nodes;
		}

		static SNode& GetNodeById(std::vector<SNode>& nodes, char id)
		{
			std::vector<SNode>::iterator it = std::find_if(nodes.begin(), nodes.end(),
				[id](SNode& node)
			{
				return node._id == id;
			});

			return *it;
		}

		static void LinkNodes(std::vector<SNode>& nodes, char id1, char id2, int cost)
		{
			SNode& node1 = GetNodeById(nodes, id1);
			SNode& node2 = GetNodeById(nodes, id2);

			node1._nodes.emplace_back();
			SNodePtr& lastNodePtr = node1._nodes.back();
			lastNodePtr._cost = cost;
			lastNodePtr._node = &node2;
			
			node2._nodes.emplace_back();
			SNodePtr& lastNodePtr2 = node2._nodes.back();
			lastNodePtr2._cost = cost;
			lastNodePtr2._node = &node1;
		}

		static std::vector<char> MinPath(SNode*rootNode, char id2)
		{
			std::set<char> visitedNodes;
			std::unordered_map<char, SData> minCost;

			SData data;
			data.cost = 0;
			data._sourceId = '\0';
			minCost.insert({ rootNode->_id, data });

			SNode* pendingVisitNode = rootNode;
			visitedNodes.insert(rootNode->_id);

			while (pendingVisitNode != nullptr)
			{
				SNode* currentVisitNode = pendingVisitNode;
				pendingVisitNode = nullptr;

				char sourceId = currentVisitNode->_id;
				int childrenMinCost = 9999;
				SNode* minCostNode = nullptr;
				for (SNodePtr& currentNodePtr : currentVisitNode->_nodes)
				{
					char currentNodeId = currentNodePtr._node->_id;
					if (visitedNodes.find(currentNodeId) != visitedNodes.end())
					{
						continue;
					}

					int currentCost = minCost[sourceId].cost;
					int branchCost = currentCost + currentNodePtr._cost;

					if (minCost.find(currentNodeId) == minCost.end())
					{
						SData data;
						data.cost = branchCost;
						data._sourceId = sourceId;
						minCost[currentNodeId] = data;
					}
					else if(minCost[currentNodeId].cost > branchCost)
					{
						SData& data = minCost[currentNodeId];
						data.cost = branchCost;
						data._sourceId = sourceId;
					}

					if (childrenMinCost > currentNodePtr._cost)
					{
						childrenMinCost = currentNodePtr._cost;
						minCostNode = currentNodePtr._node;
					}
				}

				if (minCostNode != nullptr)
				{
					pendingVisitNode = minCostNode;
				}

				visitedNodes.insert(sourceId);
			}

			std::vector<char> minPath;
			char currentId = id2;
			minPath.push_back(currentId);

			char minNode = minCost[currentId]._sourceId;
			while (minNode != '\0')
			{
				currentId = minNode;
				minPath.push_back(currentId);
				minNode = minCost[currentId]._sourceId;
			}
			
			return minPath;
		}
	};

}

BEGIN_TEST(Dijkstra)
using namespace nsDijkstra;
	std::vector<SNode> nodes = CHelpers::CreateAllNodes(6);
	CHelpers::LinkNodes(nodes, 'A', 'B', 4);
	CHelpers::LinkNodes(nodes, 'A', 'C', 2);

	CHelpers::LinkNodes(nodes, 'B', 'D', 5);
	CHelpers::LinkNodes(nodes, 'B', 'C', 1);

	CHelpers::LinkNodes(nodes, 'C', 'D', 8);
	CHelpers::LinkNodes(nodes, 'C', 'E', 10);

	CHelpers::LinkNodes(nodes, 'D', 'E', 2);
	CHelpers::LinkNodes(nodes, 'D', 'F', 6);

	CHelpers::LinkNodes(nodes, 'E', 'F', 2);

	SNode* rootNode = &(nodes[0]);
	std::vector<char> minPath = CHelpers::MinPath(rootNode, 'F');

	for (std::vector<char>::reverse_iterator it =minPath.rbegin(); it != minPath.rend(); ++it)
	{
		std::cout << *it << ",";
	}

	//Dikjstra pseudocode
	//----------------------------------------
	//start from Node source
	//for each children
	//	if cost is less than the one registered
	//		register cost of each node add the source
	//take node with less cost to be the next to analyze
	//register current node as visited
	//repeat
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//
	//


END_TEST()