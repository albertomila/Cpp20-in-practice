#include "stdafx.h"
#include <queue>

class DataChunk
{

};

std::mutex _mutex1;
std::queue<DataChunk> _dataQueue;
std::condition_variable _dataCondition;

bool MoreDataToPrepare()
{
	return true;
}

DataChunk PrepareData()
{
	return DataChunk();
}

void ProcessData(const DataChunk& data)
{
}


bool DataConditionWait()
{
	return !_dataQueue.empty();
}


bool IsLastChunk(const DataChunk& data)
{
	return false;
}

void ThreadDataPreparation()
{
	while (MoreDataToPrepare())
	{
		sleep(1000);
		
		const DataChunk data = PrepareData();
		std::lock_guard < std::mutex> lockGuard(_mutex1);
		_dataQueue.push(data);

		_dataCondition.notify_one();
	}
}

void ThreadDataProcessing()
{
	while (true)
	{
		std::unique_lock < std::mutex> uniqueLock(_mutex1);

		_dataCondition.wait(uniqueLock, DataConditionWait);

		DataChunk data = _dataQueue.front();
		uniqueLock.unlock();
		ProcessData(data);

		if (IsLastChunk(data))
		{
			break;
		}
	}
}


BEGIN_TEST(Ch4_ThreadsafeQueue)
	std::thread threadPreparation(ThreadDataPreparation);
	std::thread threadProcessing(ThreadDataProcessing);

	threadPreparation.join();
	threadProcessing.join();

END_TEST()
