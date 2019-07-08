#pragma once
#include "stdafx.h"
#include <typeinfo>
#include <vector>
#include <string>
#include <map>
#include <array>
#include <unordered_map>
#include <iostream>
using namespace std;

namespace nsAStar
{
	class CAStar
	{
		struct SNode
		{
			int x;
			int y;
			bool value;
		};

		struct SNodePair
		{
			const SNode* source;
			int cumulCost;
		};

		static const int SIZE = 20;

	public:
		CAStar()
		{
		}

		void ExecuteAStar()
		{
			Init_board();
			ComputeAlgorithm();
			DumpDataToUI();
			PrintBoard();
			PrintAStarPath();
		}

	private:
		void ComputeAlgorithm()
		{
			_targetNode = GetNode(SIZE - 1, SIZE - 1);
			SNode* originNode = GetNode(0, 0);
			_openNodes.push(originNode);
			_closedNodes.push_back(originNode);
			_costMap[originNode].source = nullptr;
			_costMap[originNode].cumulCost = 0;

			while (!_openNodes.empty())
			{
				SNode* currentNode = _openNodes.front();
				_openNodes.pop();

				std::vector<SNode*> adjacentNodes = GetAdjacentNodes(currentNode);
				EnqueAdjacentNodes(adjacentNodes);
				if (!adjacentNodes.empty())
				{
					UpdateAdjacentsCosts(currentNode, adjacentNodes);
					SNode* adjacentWithLessCost = GetNodeWithLessCost(currentNode, adjacentNodes);
					_closedNodes.push_back(adjacentWithLessCost);

				}
			}
		}

		int GetDistanceToTarget(SNode* currentNode) const
		{
			int distance = abs(currentNode->x - _targetNode->x) + abs(currentNode->y - _targetNode->y);

			return distance;
		}

		void UpdateAdjacentsCosts(SNode* currentNode, const std::vector<SNode*>& adjacentNodes)
		{
			int currentCost = GetNodeCost(currentNode);

			for (SNode* node : adjacentNodes)
			{
				int nodeCost = GetNodeCost(node);
				if (nodeCost == std::numeric_limits<int>::max())
				{
					nodeCost = 1 + GetDistanceToTarget(node);
				}

				SNodePair& nodeSource = _costMap[node];
				if (nodeCost < nodeSource.cumulCost)
				{
					nodeSource.cumulCost = nodeCost;
					nodeSource.source = currentNode;
				}
			}
		}

		void EnqueAdjacentNodes(const std::vector<SNode*>& adjacentNodes)
		{
			for (SNode* node : adjacentNodes)
			{
				_openNodes.push(node);
			}
		}

		int GetNodeCost(SNode* node)
		{
			std::unordered_map<const SNode*, SNodePair>::iterator it = _costMap.find(node);
			if (it == _costMap.end())
			{
				SNodePair nodeData;
				nodeData.source = nullptr;
				nodeData.cumulCost = std::numeric_limits<int>::max();

				_costMap.emplace(node, nodeData);

				return _costMap[node].cumulCost;
			}
			else
			{
				return it->second.cumulCost;
			}

			assert(false);
			return -1;
		}

		SNode* GetNodeWithLessCost(SNode* originNode, const std::vector<SNode*>& adjacentNodes)
		{
			int minCost = std::numeric_limits<int>::max();
			SNode* minCostAdjacent = nullptr;
			for (SNode* node : adjacentNodes)
			{
				int nodeCost = abs(originNode->x - node->x) + abs(originNode->y - node->y);
				if (nodeCost < minCost)
				{
					minCost = nodeCost;
					minCostAdjacent = node;
				}
			}

			if (minCostAdjacent == nullptr)
			{
				assert(minCostAdjacent != nullptr);
			}
			return minCostAdjacent;
		}

		std::vector<SNode*> GetAdjacentNodes(SNode* currentNode)
		{
			std::vector<SNode*> adjacentNodes;
			AddIfValidAdjacent(adjacentNodes, currentNode,  0, -1);
			AddIfValidAdjacent(adjacentNodes, currentNode, 1, -1);
			AddIfValidAdjacent(adjacentNodes, currentNode, 1, 0);
			AddIfValidAdjacent(adjacentNodes, currentNode, 1, 1);
			AddIfValidAdjacent(adjacentNodes, currentNode, 0, 1);
			AddIfValidAdjacent(adjacentNodes, currentNode, -1, 1);
			AddIfValidAdjacent(adjacentNodes, currentNode, -1, 0);
			AddIfValidAdjacent(adjacentNodes, currentNode, -1, -1);

			return adjacentNodes;
		}

		void AddIfValidAdjacent(std::vector<SNode*>& adjacentNodes_out, SNode* node, int x, int y)
		{
			int adjacentX = node->x + x;
			int adjacentY = node->y + y;

			if (   (adjacentX >= 0)
				&& (adjacentY >= 0)
				&& (adjacentX <= (SIZE - 1))
				&& (adjacentY <= (SIZE - 1)))
			{
				if (IsValidTarget(adjacentX, adjacentY))
				{
					SNode* adjacentNode = GetNode(adjacentX, adjacentY);
					if (!IsNodeClosed(adjacentNode))
					{
						adjacentNodes_out.push_back(adjacentNode);
					}
				}
			}
		}

		bool IsValidTarget(int x, int y) const
		{
			return _board[y][x].value == true;
		}

		bool IsNodeClosed(SNode* node)
		{
			return std::find(_closedNodes.begin(), _closedNodes.end(), node) != _closedNodes.end();
		}


		SNode* GetNode(int x, int y)
		{
			return  &_board[y][x];
		}

		const SNode* GetNode(int x, int y) const
		{
			return  &_board[y][x];
		}

		void Init_board()
		{
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 0; j < SIZE; ++j)
				{
					_board[i][j].x = j;
					_board[i][j].y = i;
					_board[i][j].value = true;
					_boardUI[i][j] = ' ';
				}
			}

			int x = 7;
			int y = 3;
			for (int i = y; i <= y + 10; ++i)
			{
				_board[i][x + 10].value = false;
				_boardUI[i][x +10] = '|';
			}
			
			for (int j = x; j <= x + 10; ++j)
			{
				_board[y][j].value = false;
				_boardUI[y][j] = '-';
			}

			for (int j = x; j <= x + 10; ++j)
			{
				_board[y + 10][j].value = false;
				_boardUI[y + 10][j] = '-';
			}
			
			_boardUI[0][0] = 'o';
			_boardUI[SIZE-1][SIZE-1] = 'e';
		}

		void DumpDataToUI()
		{
			const SNode* currentNode = GetNode(SIZE - 1, SIZE - 1);
			while (currentNode != nullptr)
			{
				_boardUI[currentNode->y][currentNode->x] = 'x';
				currentNode = _costMap[currentNode].source;
			}
		}

		void PrintBoard() const
		{
			std::cout << std::endl;
			for (int i = 0; i < SIZE; ++i)
			{
				for (int j = 0; j < SIZE; ++j)
				{
					std::cout << "[" << _boardUI[i][j] << "]";
				}
				std::cout << std::endl ;
			}
		}

		void PrintAStarPath() const
		{
			const SNode* currentNode = GetNode(SIZE - 1,SIZE - 1);
			while (currentNode != nullptr)
			{
				std::cout << "(" << currentNode->x << "," << currentNode->y << "), ";

				currentNode = _costMap.find(currentNode)->second.source;
			}
		}


		SNode _board[SIZE][SIZE];
		char _boardUI[SIZE][SIZE];
		std::vector<SNode*> _closedNodes;
		std::queue<SNode*> _openNodes;
		std::unordered_map<const SNode*, SNodePair> _costMap;
		SNode* _targetNode;
	};
}

BEGIN_TEST(AStar)
	using namespace nsAStar;

	CAStar astar;
	astar.ExecuteAStar();

END_TEST()