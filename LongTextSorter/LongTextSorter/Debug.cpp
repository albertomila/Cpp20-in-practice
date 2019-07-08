#include "stdafx.h"
#include "Debug.h"
#include <iostream>

void OutputData::Init(int fileSize, int chunkSize, int pairSteps)
{
	outData.reserve(pairSteps);
	for (int i = 0; i < pairSteps; ++i)
	{
		int nextIndexBufferLeft = i*(chunkSize * 2);
		int nextIndexBufferRight = nextIndexBufferLeft + chunkSize;
		int boundaryLeft = nextIndexBufferLeft + chunkSize;
		int boundaryRight = nextIndexBufferRight + chunkSize;
		if (boundaryRight > fileSize)
		{
			boundaryRight = fileSize;
		}

		OutputDataStepPair outputDataStepPair;
		outputDataStepPair.left.current = nextIndexBufferLeft;
		outputDataStepPair.left.boundaryLow = nextIndexBufferLeft;
		outputDataStepPair.left.boundaryHigh = boundaryLeft;

		outputDataStepPair.right.current = nextIndexBufferRight;
		outputDataStepPair.right.boundaryLow = nextIndexBufferRight;
		outputDataStepPair.right.boundaryHigh = boundaryRight;

		outData.push_back(outputDataStepPair);
	}
}

void OutputData::UpdateData(int pairIndex, int currentIndexLeft, int currentIndexRight)
{
	outData[pairIndex].left.current = currentIndexLeft;
	outData[pairIndex].right.current = currentIndexRight;
}

void OutputData::PrintStatus()
{
	if (drawDelayCounter == DRAW_DELAY)
	{
		system("cls");
		for (unsigned int i = 0; i < outData.size(); ++i)
		{
			OutputDataStep& outDataStepLeft = outData[i].left;
			float currentPercentage = ((100.0f) / (float)(outDataStepLeft.boundaryHigh - outDataStepLeft.boundaryLow))*(outDataStepLeft.current - outDataStepLeft.boundaryLow);
			std::cout << "(" << ceil(currentPercentage) << ", ";

			OutputDataStep& outDataStepRight = outData[i].right;
			currentPercentage = ((100.0f) / (float)(outDataStepRight.boundaryHigh - outDataStepRight.boundaryLow))*(outDataStepRight.current - outDataStepRight.boundaryLow);
			std::cout << ceil(currentPercentage) << ") ";
		}

		drawDelayCounter = 0;
	}
	else
	{
		++drawDelayCounter;
	}
}