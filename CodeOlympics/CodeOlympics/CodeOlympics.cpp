// CodeOlympics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>

void split(const std::string& text, const std::string& delims, std::vector<std::string>& tokens)
{
	std::size_t start = text.find_first_not_of(delims);
	std::size_t end = 0;

	while ((end = text.find_first_of(delims, start)) != std::string::npos)
	{
		tokens.push_back(text.substr(start, end - start));
		start = text.find_first_not_of(delims, end);
	}
	if (start != std::string::npos)
	{
		tokens.push_back(text.substr(start));
	}
}

void split(const std::string &text, char sep, std::vector<std::string>& tokens)
{
	std::size_t start = 0;
	std::size_t end = 0;

	while ((end = text.find(sep, start)) != std::string::npos)
	{
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
}

void SplitToInt(const std::string &text, char sep, std::vector<int>& tokens)
{
	std::size_t start = 0;
	std::size_t end = 0;

	while ((end = text.find(sep, start)) != std::string::npos)
	{
		tokens.push_back(atoi(text.substr(start, end - start).c_str()));
		start = end + 1;
	}
	tokens.push_back(atoi(text.substr(start).c_str()));
}


void NumberToBits(int inputNumber, std::vector<int>& bits_out)
{
	int divTestNumber = inputNumber;
	while (divTestNumber >= 1)
	{
		int mod = divTestNumber % 2;
		bits_out.push_back(mod);
		divTestNumber /= 2;
	}
	assert(divTestNumber == 0 || divTestNumber == 1);
	bits_out.push_back(divTestNumber);
}



struct InputValues
{
	int iterations;
	std::vector<std::vector<int>> values;
};
void FillInputValues(InputValues& testCases)
{
	int numberIterations = 1;
	std::cin >> numberIterations;
	std::cin.get();

	for (int i = 0; i < numberIterations; ++i)
	{
		int numElements = 1;
		std::cin >> numElements;
		std::cin.get();

		std::string inputString;
		std::getline(std::cin, inputString);
		std::vector<int> values;
		SplitToInt(inputString, ' ', values);

		testCases.values.push_back(values);
	}
}

void FillDebugValues(InputValues& testCases)
{
	testCases.iterations = 1;
	std::vector<int> values;
	values.push_back(1);
	values.push_back(2);
	values.push_back(3);
	testCases.values.push_back(values);

	/*
	testCases.nodes.push_back(100);
	testCases.nodes.push_back(200);
	testCases.nodes.push_back(100);
	testCases.nodes.push_back(500);
	testCases.nodes.push_back(100);
	testCases.nodes.push_back(600);
	*/

}

void FillValues(InputValues& testCases, bool isDebug)
{
	if (isDebug)
	{
		FillDebugValues(testCases);
	}
	else
	{
		FillInputValues(testCases);
	}
}

int GCD(int a, int b)
{
	return  b == 0 
			? a 
			: GCD(b, a % b);
}

int LCM(int a, int b)
{
	int temp = GCD(a, b);

	return temp ? (a / temp * b) : 0;
}
/*
int main()
{
	bool isDebug = false;

	InputValues testCases;
	FillValues(testCases, isDebug);

	return 0;
}
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int NumScores(int A, int B)
{
	if (A == 0 && B == 0)
	{
		return 1;
	}

	if (A < 0 || B < 0)
	{
		return 0;
	}


	if (A < 25 || B < 25)
	{
		return NumScores(A - 1, B) + NumScores(A, B - 1);
	}

	if (abs(A - B) > 1)
	{
		return 0;
	}

	return NumScores(A - 1, B) + NumScores(A, B - 1);
}

unsigned long long factorial(unsigned long long value)
{
	if(value == 1)
	{
		return 1;
	}
	return value * factorial(value - 1);
}

int main()
{
	int A = 3;
	//std::cin >> A;
	//std::cin.get();
	int B = 25;
	//std::cin >> B;
	//std::cin.get();
	int minValue = A < B ? A : B;
	int maxValue = A < B ? B : A;

	int currentMin = minValue;
	int currentMax = maxValue + 1;

	int permutationsMin = pow(2, minValue);
	int count = 0;
	for (int i = 0; i < permutationsMin; ++i)
	{
		for (int k = currentMax - i; k > 0; --k)
		{
			++count;
		}
	}


	std::cout << count;


	if (minValue == maxValue)
	{
		std::cout << 0;
		return 0;
	}

	if (maxValue < 25 || maxValue > 1000000000)
	{
		std::cout << 0;
		return 0;
	}

	if (maxValue > 25 && (maxValue - minValue) > 2)
	{
		std::cout << 0;
		return 0;
	}
	/*
	if (maxValue > 25) //means min is max-2
	{
		int restMax = maxValue - 26;
		int restMin = minValue - 24;

		int additionalCombinations = restMin * 2;
		additionalCombinations += 1; //combinations for max to win.

		maxValue = maxValue - 26;
		maxValue = maxValue - 26;
	}
	*/
	

	unsigned long long fact = factorial((unsigned long long)minValue);

	unsigned long long upValue = maxValue;
	for (int i = 1; i < minValue; ++i)
	{
		upValue *= (maxValue + i);
	}


	double value = (double)upValue / (double)fact;

	maxValue--;
	int scores = NumScores(minValue, maxValue);
	std::cout << scores;

	return 0;
}