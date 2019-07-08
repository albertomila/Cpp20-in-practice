#include "stdafx.h"
#include <mutex>
#include <queue>

template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex _mutex;
	std::queue<T> _dataQueue;
	std::condition_variable _conditionVar;

public:
	threadsafe_queue()
	{
	}

	threadsafe_queue(const threadsafe_queue& other)
	{
		std::lock_guard<std::mutex> lockGuard(other._mutex);
		_dataQueue = other._dataQueue;
	}

	bool Empty() const
	{
		std::lock_guard<std::mutex> lockGuard(_mutex);
		return _dataQueue.empty();
	}

	void Push(T newValue)
	{
		std::shared_ptr<T> data( std::make_shared<T>(std::move(newValue)) );
		
		std::lock_guard<std::mutex> lockGuard(_mutex);
		_dataQueue.push(data);
		_conditionVar.notify_one();
	}

	shared_ptr<T> WaitAndPop()
	{
		std::unique_lock<std::mutex> uniqueLock(_mutex);

		_conditionVar.wait(uniqueLock,
										[this]
										{
											return !_dataQueue.empty(); //wait condition
										});

		std::shared_ptr<T> res = _dataQueue.front();
		_dataQueue.pop();

		return res;
	}

	void WaitAndPop(T& value)
	{
		std::unique_lock<std::mutex> uniqueLock(_mutex);

		_conditionVar.wait(uniqueLock,
										[this]
										{
											return !_dataQueue.empty(); //wait condition
										});

		value = std::move(*_dataQueue.front());
		_dataQueue.pop();
	}

	shared_ptr<T> try_pop()
	{
		std::unique_lock<std::mutex> uniqueLock(_mutex);
		if (_dataQueue.empty())
		{
			return std::shared_ptr<T>();
		}

		std::shared_ptr<T> res = _dataQueue.front();
		_dataQueue.pop();

		return res;
	}

	bool try_pop(T& value)
	{
		std::unique_lock<std::mutex> uniqueLock(_mutex);
		if (_dataQueue.empty())
		{
			return std::shared_ptr<T>();
		}

		value = std::move(*_dataQueue.front());
		_dataQueue.pop();

		return res;
	}

	bool empty()
	{
		std::unique_lock<std::mutex> uniqueLock(_mutex);
		return _dataQueue.empty();
	}
};

BEGIN_TEST(Ch6_ThreadSafeQueue)
END_TEST()
