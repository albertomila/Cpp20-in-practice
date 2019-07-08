#pragma once
#include <vector>

struct OutputDataStep
{
	int current;
	int boundaryLow;
	int boundaryHigh;

	OutputDataStep()
		: current(0)
		, boundaryLow(0)
		, boundaryHigh(0)
	{
	}
};

struct OutputDataStepPair
{
	OutputDataStep left;
	OutputDataStep right;
};

struct OutputData
{
	std::vector<OutputDataStepPair> outData;
	const int DRAW_DELAY = 50;
	int drawDelayCounter = DRAW_DELAY;

	void Init(int fileSize, int chunkSize, int pairSteps);
	void UpdateData(int pairIndex, int currentIndexLeft, int currentIndexRight);
	void PrintStatus();
};
