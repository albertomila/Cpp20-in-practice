#pragma once
#include "stdafx.h"
#include <future>
#include <string> 
#include <queue>
#include <sstream>
#include "samples/2.SharingData/9.Semaphore.h"

namespace Ex30
{
	const int MAX_TASKS_TO_EXECUTE = 70;
	Ex15::Semaphore* g_semaphore = nullptr;
	std::queue<int> g_waitForDeadFutureTaks;
	std::mutex g_waitForDeadTaksMutex;
	std::mutex g_endTaskMutex;
	std::mutex g_printMutex;

	template<typename T>
	bool future_is_ready(std::future<T>& t)
	{
		return t.wait_for(std::chrono::nanoseconds(0)) == std::future_status::ready;
	}

	void PrintExclusive(std::string& value)
	{
		std::lock_guard<std::mutex> printMutex(g_printMutex);
		std::cout << value.c_str() << std::endl;
	}
	int GetFreeSlot(std::vector<std::future<int>*>& tasksPool)
	{
		int count = 0;
		for (std::future<int>*& future : tasksPool)
		{
			if (!future)
			{
				return count;
			}
			++count;
		}

		return -1;
	}


	int AreAllEmptySlots(std::vector<std::future<int>*>& tasksPool)
	{
		for (std::future<int>*& future : tasksPool)
		{
			if (future)
			{
				return false;
			}
		}

		return true;
	}

	void PrintFutureStatus(std::vector<std::future<int>*>& tasksPool)
	{
		std::string printValue;
		for (std::future<int>*& future : tasksPool)
		{
			printValue += "[";

			if (future == nullptr)
			{
				printValue += "0";
			}
			else if (!future->valid())
			{
				printValue += "1";
			} 
			else if (!future_is_ready(*future))
			{
				printValue += "2";
			}
			else
			{
				printValue += "3";
			}

			printValue += "],";
		}

		printValue += "\n";
		PrintExclusive(printValue);
	}

	void ThreadPrintStatus(std::vector<std::future<int>*>& tasksPool, int& currentFinishedTasks, int MAX_TASKS_TO_EXECUTE)
	{
		while (currentFinishedTasks < MAX_TASKS_TO_EXECUTE)
		{
			sleep(1000);
			PrintFutureStatus(tasksPool);
		}
	}


	std::string GetCurrentThreadID()
	{
		std::stringstream ss;
		ss << std::this_thread::get_id();
		std::string mystring = ss.str();
		return mystring;
	}

	int TaskGeneric(int indexIntasksPool, int randValue)
	{
		sleep(randValue);

		std::lock_guard<std::mutex> waitForDeadTaksMutex(g_waitForDeadTaksMutex);
		g_waitForDeadFutureTaks.push(indexIntasksPool);

		PrintExclusive(std::string("Task end, value:" + std::to_string(randValue)));
		return randValue;
	}

	int TaskA(int indexIntasksPool)
	{
		PrintExclusive(std::string("Init tak A, id: ") + GetCurrentThreadID());
		int randValue = 1000 + rand() % 1000;
		return TaskGeneric(indexIntasksPool, randValue);
	}

	int TaskB(int indexIntasksPool)
	{
		PrintExclusive(std::string("Init tak B, id: ") + GetCurrentThreadID());
		int randValue = 2000 + rand() % 1000;
		return TaskGeneric(indexIntasksPool, randValue);
	}

	int TaskC(int indexIntasksPool)
	{
		PrintExclusive(std::string("Init tak C, id: ") + GetCurrentThreadID());
		int randValue = 3000 + rand() % 3000;
		return TaskGeneric(indexIntasksPool, randValue);
	}

	int TaskD(int indexIntasksPool)
	{
		PrintExclusive(std::string("Init tak D, id: ") + GetCurrentThreadID());
		int randValue = 1000 + rand() % 3000;
		return TaskGeneric(indexIntasksPool, randValue);
	}


	void HandleFinishedTasks(std::vector<std::future<int>*>& tasksPool, int& cumul, int& currentFinishedTasks, int currentTask)
	{
		std::lock_guard<std::mutex> waitForDeadTaksMutex(g_waitForDeadTaksMutex);
		while (!g_waitForDeadFutureTaks.empty())
		{
			int indexIntasksPool = g_waitForDeadFutureTaks.front();
			g_waitForDeadFutureTaks.pop();

			std::future<int>*& futureTask = tasksPool[indexIntasksPool];
			cumul += futureTask->get();
			++currentFinishedTasks;

			std::string printValue = "cumul: " + std::to_string(cumul);
			PrintExclusive(printValue);

			printValue = "tasks: " + std::to_string(currentTask) + "/" + std::to_string(currentFinishedTasks) + "/" + std::to_string(MAX_TASKS_TO_EXECUTE);
			PrintExclusive(printValue);

			delete futureTask;
			futureTask = nullptr;
		}
	}

	BEGIN_TEST(Ex30_CumulValueThreads)

		//Tasks prototypes
		typedef int(*TTask)(int);
		const int MAX_TASKS_PROTOTYPES = 4;
		TTask tasksPrototypes[MAX_TASKS_PROTOTYPES]
		{
			 TaskA
			,TaskB
			,TaskC
			,TaskD
		};
		int taskToTriggerIndex = 0;

		//pool of current running tasks
		int cumul = 0;
		int maxAvailableTasks = std::thread::hardware_concurrency() -1;
		std::vector<std::future<int>*> tasksPool;
		tasksPool.resize(maxAvailableTasks, nullptr);

		//semaphore to lock trigger new tasks
		g_semaphore = new Ex15::Semaphore(maxAvailableTasks);
		int currentFinishedTasks = 0;
		int currentTask = 0;

		std::thread threadPrint(ThreadPrintStatus, std::ref(tasksPool), std::ref(currentFinishedTasks), MAX_TASKS_TO_EXECUTE);

		while (currentTask < MAX_TASKS_TO_EXECUTE)
		{
			//lock the execution when max threads running is reached
			g_semaphore->wait();
			{
				//listen those that are finished and retrieve the cumul value
				HandleFinishedTasks(tasksPool, cumul, currentFinishedTasks, currentTask);
			}
			
			//select next task to trigger
			TTask& nextTaskToTrigger = tasksPrototypes[taskToTriggerIndex];
			++taskToTriggerIndex;
			taskToTriggerIndex %= MAX_TASKS_PROTOTYPES;

			//assign a slot on the pool
			int index = GetFreeSlot(tasksPool);
			tasksPool[index] = new std::future<int>(std::async(nextTaskToTrigger, index));
			++currentTask;
		}
		
		//wait until all tasks are finished
		while (!AreAllEmptySlots(tasksPool))
		{
			//listen those that are finished and retrieve the cumul value
			HandleFinishedTasks(tasksPool, cumul, currentFinishedTasks, currentTask);
		}

		//properly close the thread print
		threadPrint.join();
	END_TEST()
}