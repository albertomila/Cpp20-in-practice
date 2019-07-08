#include "stdafx.h"
#include <queue>

namespace Ex16
{
	struct DataChunk
	{
		DataChunk(int data)
			:_data(data)
		{
		}
		int _data;
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
		int randValue = rand() % 100;
		return DataChunk(randValue);
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

			std::cout << "notify_one: " << data._data << "\n" << std::endl;
			_dataCondition.notify_one();
		}
	}

	void ThreadDataProcessing()
	{
		while (true)
		{
			std::unique_lock < std::mutex> uniqueLock(_mutex1);

			std::cout << "wait" << "\n" << std::endl;
			_dataCondition.wait(uniqueLock, DataConditionWait);

			DataChunk data = _dataQueue.back();
			_dataQueue.pop();
			std::cout << "contine: " << data._data << "\n" << std::endl;
			std::cout << "------------------\n" << std::endl;
			uniqueLock.unlock();
			ProcessData(data);

			if (IsLastChunk(data))
			{
				break;
			}
		}
	}


	BEGIN_TEST(Ex16_ConditionVariable)
		std::thread threadPreparation(ThreadDataPreparation);
		std::thread threadProcessing(ThreadDataProcessing);

		threadPreparation.join();
		threadProcessing.join();

	END_TEST()
}