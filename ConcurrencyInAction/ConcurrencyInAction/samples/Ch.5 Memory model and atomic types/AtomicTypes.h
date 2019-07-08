#include "stdafx.h"
#include <atomic> 


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

			//b = flag.test_and_set(std::memory_order_acquire);
		}

		void unlock()
		{
			flag.clear(std::memory_order_release);
		}
	};

	struct Buildings
	{
		void TestMethod()
		{

		}
	};

	BEGIN_TEST(Ch5_AtomicTypes)
		spinlock_mutex s;
		s.lock();
		s.unlock();

		std::atomic<bool> b;
		bool x = b.load(std::memory_order_acquire);
		b.store(true);
		x = b.exchange(false, std::memory_order_acq_rel);

		std::atomic<Buildings> atomicBuilding;
		atomicBuilding.load().TestMethod();
	END_TEST()