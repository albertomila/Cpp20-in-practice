#pragma once
#include "stdafx.h"

namespace Ex11
{
	class hierarchical_mutex
	{
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
			s_thisThreadHierarchyValue = _previousHierarchyValue;
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

	private:
		void CheckForViolation()
		{
			if (s_thisThreadHierarchyValue <= _hierarchyValue)
			{
				throw std::logic_error("mutex hierarchy violated!");
			}
		}

		void UpdateHierarchyValue()
		{
			_previousHierarchyValue = s_thisThreadHierarchyValue;
			s_thisThreadHierarchyValue = _hierarchyValue;
		}

		std::mutex _mutex;
		const unsigned long _hierarchyValue;
		static thread_local unsigned long s_thisThreadHierarchyValue;
		unsigned long _previousHierarchyValue;
	};

	//static var initialization
	thread_local unsigned long hierarchical_mutex::s_thisThreadHierarchyValue(ULONG_MAX);


	////////////////////////////////////////////////
	hierarchical_mutex g_highLevelMutex(10000ul);
	hierarchical_mutex g_lowLevelMutex(5000ul);

	int LowLevelFunc()
	{
		std::lock_guard<hierarchical_mutex> mutexLowLevel(g_lowLevelMutex);
		sleep(10000);

		return 0;
	}

	int HighLevelFunc()
	{
		std::lock_guard<hierarchical_mutex> highLevel(g_highLevelMutex);
		sleep(1000);

		//that code below  is forbidden, that will cause exception
		//std::lock_guard<hierarchical_mutex> lowLevel(g_highLevelMutex);

		return LowLevelFunc();
	}

	void ThreadA()
	{
		std::cout << "ThreadA" << "\n" << std::endl;
		HighLevelFunc();
	}

	void ThreadB()
	{
		std::cout << "ThreadB" << "\n" << std::endl;
		LowLevelFunc();
	}


	BEGIN_TEST(Ex11_LockHierarchy)
		std::thread threadA(ThreadA);
		std::thread threadB(ThreadA);

		threadA.join();
		threadB.join();
	END_TEST()
}