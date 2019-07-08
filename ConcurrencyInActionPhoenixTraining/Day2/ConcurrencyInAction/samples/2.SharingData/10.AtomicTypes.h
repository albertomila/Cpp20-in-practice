#pragma once
#include "stdafx.h"
#include <atomic> 


namespace Ex22
{
	class spinlock_mutex
	{
		std::atomic_flag flag = ATOMIC_FLAG_INIT;
	public:
		spinlock_mutex()
		{
		}

		void lock()
		{
			bool b = true;
			while (b)
			{
				//flag was false, so b = false
				//flag is set to true
				//test_and_set returns the old value, when the old value is false the mutex is locked
				b = flag.test_and_set(std::memory_order_acquire);
			}
		}

		void unlock()
		{
			flag.clear(std::memory_order_release);
		}
	};


	std::vector<int> g_list;
	spinlock_mutex g_mutex;
	static const int SLEEP_TIME = 30;

	void ThreadAdd()
	{
		while (true)
		{
			sleep(SLEEP_TIME);
			int value = rand() % 10;

			std::lock_guard<spinlock_mutex> guard(g_mutex);
			g_list.push_back(value);
		}
	}

	void ThreadRemove()
	{
		while (true)
		{
			sleep(SLEEP_TIME);
			int value = rand() % 10;

			std::lock_guard<spinlock_mutex> guard(g_mutex);

			std::vector<int>::iterator it = std::find(g_list.begin(), g_list.end(), value);
			if (it != g_list.end())
			{
				g_list.erase(it);
			}
		}
	}

	void ThreadPrint()
	{
		while (true)
		{
			sleep(SLEEP_TIME);
			std::lock_guard<spinlock_mutex> guard(g_mutex);
			if (!g_list.empty())
			{
				for (int value : g_list)
				{
					std::cout << value << ",";
				}
				std::cout << endl;
			}
		}
	}

	BEGIN_TEST(Ex22_AtomicTypes_Flag)

		std::atomic_flag f = ATOMIC_FLAG_INIT;
		f.clear(std::memory_order_release);
		bool flagValue = f.test_and_set();

		std::thread thread1(ThreadAdd);
		std::thread thread2(ThreadRemove);
		std::thread thread3(ThreadPrint);
		thread1.join();
		thread2.join();
		thread3.join();
	END_TEST()


	BEGIN_TEST(Ex22_AtomicTypes_Bool)
		std::atomic<bool> b(false);
		bool x = b.load(std::memory_order_acquire);
		b = true;
		b.store(true);
		x = b.exchange(false, std::memory_order_acq_rel); //equal to test_and_set

		bool expected = (x == true);
		bool successOperation = b.compare_exchange_weak(expected, true); //it may fail depending on the compiler.
		bool valueHasChanged = b.compare_exchange_strong(expected, true); //returns false if the actual value is not equal to the expected value.
	END_TEST()


	std::queue<std::string> output;
	class AtomicClassTest
	{
	public:
		void SetData(int value)
		{
			_data = value;
		}

	private:
		int _data = 10;
	};

	void ThreadA(std::atomic<AtomicClassTest>& atomicClassTest)
	{
		while (true)
		{
			sleep(500);
			int value = rand() % 10;
			AtomicClassTest classTestLoaded = atomicClassTest.load();
			classTestLoaded.SetData(value);
			atomicClassTest.store(classTestLoaded);
		}
	}

	void ThreadB(std::atomic<AtomicClassTest>& atomicClassTest)
	{
		while (true)
		{
			sleep(500);
			int value = rand() % 10;
			AtomicClassTest classTestLoaded = atomicClassTest.load();
			classTestLoaded.SetData(value);
			atomicClassTest.store(classTestLoaded);
		}
	}

	void ThreadP()
	{
		while (true)
		{
			if (!output.empty())
			{
				std::cout << output.front().c_str() << std::endl;
				output.pop();
			}
		}
	}

	BEGIN_TEST(Ex22_AtomicTypes_Class)
		std::atomic<AtomicClassTest> atomicClassTest;

		std::thread threadA(ThreadA, std::ref(atomicClassTest));
		std::thread threadB(ThreadB, std::ref(atomicClassTest));
		std::thread threadPrint(ThreadP);
		threadA.join();
		threadB.join();
		threadPrint.join();

		//std::atomic<int> aint;
		//atomic_int aint2;

	END_TEST()
}