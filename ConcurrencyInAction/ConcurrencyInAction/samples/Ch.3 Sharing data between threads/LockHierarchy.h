#include "stdafx.h"

class hierarchical_mutex
{
private:

	std::mutex _mutex;
	const unsigned long _hierarchyValue;
	static thread_local unsigned long _thisThreadHierarchyValue;
	unsigned long _previousHierarchyValue;

	void CheckForViolation()
	{
		if (_thisThreadHierarchyValue <= _hierarchyValue)
		{
			throw std::logic_error("mutex hierarchy violated!");
		}
	}

	void UpdateHierarchyValue()
	{
		_previousHierarchyValue = _thisThreadHierarchyValue;
		_thisThreadHierarchyValue = _hierarchyValue;
	}

public:

	explicit hierarchical_mutex(unsigned long hierarchyValue)
		:_hierarchyValue(hierarchyValue)
		, _previousHierarchyValue(0)
	{
	}

	void lock()
	{
		CheckForViolation();
		_mutex.lock();
		UpdateHierarchyValue();
	}

	void unlock()
	{
		_thisThreadHierarchyValue = _previousHierarchyValue;
		_mutex.unlock();
	}

	bool TryLock()
	{
		CheckForViolation();
		if (!_mutex.try_lock())
		{
			return false;
		}

		UpdateHierarchyValue();
		return true;
	}
};

//static var initialization
thread_local unsigned long hierarchical_mutex::_thisThreadHierarchyValue(ULONG_MAX);


////////////////////////////////////////////////
hierarchical_mutex g_highLevelMutex(10000ul);
hierarchical_mutex g_lowLevelMutex(5000ul);

int LowLevelFunc()
{
	std::lock_guard<hierarchical_mutex> mutexLowLevel(g_lowLevelMutex);

	for (int i = 0; i < 1000; ++i)
	{
		std::cout << "LowLevelFunc waiting"  << i << "\n" << std::endl;
	}

	return 0;
}

int HighLevelFunc()
{
	for (int i = 0; i < 100; ++i)
	{
		std::cout << "HighLevelFunc waiting" << "\n" << std::endl;
	}
	std::lock_guard<hierarchical_mutex> highLevel(g_lowLevelMutex);
	
	//that code below  is forbidden, that will cause exception
	//std::lock_guard<hierarchical_mutex> lowLevel(g_highLevelMutex);

	return LowLevelFunc();
}

void ThreadA_()
{
	std::cout << "ThreadA" << "\n" << std::endl;
	HighLevelFunc();
}

void ThreadB_()
{
	std::cout << "ThreadB" << "\n" << std::endl;
	LowLevelFunc();
}


BEGIN_TEST(Ch3_LockHierarchy)
	std::thread threadA(ThreadA_);
	std::thread threadB(ThreadB_);
	
	threadA.join();
	threadB.join();
	
END_TEST()

//int main(){MainExample(); return 0;}
