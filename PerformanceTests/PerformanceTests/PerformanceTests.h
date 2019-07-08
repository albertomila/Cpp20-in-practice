#pragma once
#include <vector>
#include <cmath>

class CPerformanceTests
{
	typedef void(*TFoo)();
	struct SResultEntry
	{
		std::string _entryName;
		TFoo _foo;
		std::vector<std::pair<std::vector<double>, double>> _timeSpendSteps;
	};

public:
	CPerformanceTests(int timesPerSteps)
		:_timesPerSteps(timesPerSteps)
	{
		/*
		_steps.push_back(10000);
		_steps.push_back(25000);
		_steps.push_back(50000);
		_steps.push_back(100000);
		_steps.push_back(250000);
		_steps.push_back(500000);
		_steps.push_back(1000000);
		_steps.push_back(5000000);
		_steps.push_back(10000000);
		*/
		_steps.push_back(500000000);
	}

	void SetEntryTest(const std::string& name, TFoo foo)
	{
		_entriesTests.emplace_back();
		SResultEntry& newEntry = _entriesTests.back();
		newEntry._entryName = name;
		newEntry._foo = foo;
	}

	void ComputeMediaTimes(std::pair<std::vector<double>, double>& results)
	{
		double count = 0;
		for (double result : results.first)
		{
			count += result;
		}
		results.second = count / static_cast<double>(results.first.size());
	}

	void StartTest()
	{
		for (int step = 0; step < static_cast<int>(_steps.size()); ++step)
		{
			int loops = GetLoops(step);
			std::cout << "Cycles: " << loops << std::endl;
			for(SResultEntry& resultEntry : _entriesTests)
			{
				resultEntry._timeSpendSteps.emplace_back();
				std::pair<std::vector<double>, double>& results = resultEntry._timeSpendSteps.back();
				for (int repetition = 0; repetition < _timesPerSteps; ++repetition)
				{
					clock_t begin_time = clock();
					for (int i = 0; i < loops; ++i)
					{
						resultEntry._foo();
					}
					clock_t end_time = clock();
					double difTime = (end_time - begin_time) / static_cast<double>(CLOCKS_PER_SEC);

					results.first.push_back(difTime);
				}

				ComputeMediaTimes(results);

				PrintResultEntry(step, resultEntry);
			}
			std::cout << std::endl;
		}
	}

private:
	void PrintResultEntry(int step, SResultEntry& resultEntry)
	{
		int loops = GetLoops(step);

		std::cout << resultEntry._entryName.c_str();
		std::pair<std::vector<double>, double>& results = resultEntry._timeSpendSteps.back();

		std::cout << "\ttime:" << results.second << "\tsamples(";
		for(int i = 0; i<static_cast<int>(results.first.size()); ++i)
		{
			std::cout << results.first[i];
			if (i < static_cast<int>(results.first.size()) - 1)
			{
				std::cout << ",";
			}
		}
		std::cout << ")" << std::endl;
	}

	int GetLoops(int step) const
	{
		return _steps[step];
	}


private:
	int _timesPerSteps;
	std::vector<int> _steps;
	std::vector<SResultEntry> _entriesTests;
};