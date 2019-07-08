#pragma once

#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

enum Direction
{
	North,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};

struct Pos2 {
	double x = 0.0;
	double y = 0.0;
};

class StepDistance
{
public:

	StepDistance(vector<int> distances, vector<Direction> directions)
	{
		assert(distances.size() == directions.size(), "Invalid input data");

		for(int i = 0; i< directions.size(); ++i)
		{
			Direction direction = directions[i];
			int distance = distances[i];

			switch (direction)
			{
			case North:
				_finalPos.y += distance;
				break;
			case NorthEast:
				Compute2DComponents(135, distance);
				break;
			case East:
				_finalPos.x -= distance;
				break;
			case SouthEast:
				Compute2DComponents(225, distance);
				break;
			case South:
				_finalPos.y -= distance;
				break;
			case SouthWest:
				Compute2DComponents(-45, distance);
				break;
			case West:
				_finalPos.x += distance;
				break;
			case NorthWest:
				Compute2DComponents(45, distance);
				break;
			default:
				break;
			}
		}
	}

	double DistanceFromStart()
	{
		double distance = sqrt( pow(_finalPos.x,2) + pow(_finalPos.y, 2));
		return distance;
	}
private:
	void Compute2DComponents(int angle, int distance) {
		static const float PI = 3.141592653f;

		float angleToRadiants = angle * PI / 180.0f;
		Pos2 components;
		components.x = distance * sin(angleToRadiants);
		components.y = distance * cos(angleToRadiants);

		_finalPos.x += components.x;
		_finalPos.y += components.y;
	}


	Pos2 _finalPos;
};
/*
#ifndef OMNIDRONE_TEST // Please don't remove
int main()
{
	StepDistance sd(vector<int>{1}, vector<Direction>{Direction::North});
	cout << sd.DistanceFromStart(); // 1.0

	sd = StepDistance(vector<int>{2, 1}, vector<Direction>{Direction::North, Direction::East});
	cout << sd.DistanceFromStart(); // 2.2360679774997898

	sd = StepDistance(vector<int>{2}, vector<Direction>{Direction::NorthWest});
	cout << sd.DistanceFromStart(); // 2.0
}
#endif*/