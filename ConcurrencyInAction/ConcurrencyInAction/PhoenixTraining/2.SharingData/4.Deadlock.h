#include "stdafx.h"
#include <mutex>

namespace Ex10
{
	struct ItemData
	{
		int _value;
	};

	class Item
	{
	private:
		ItemData _itemData;
		std::mutex _mutex;

	public:
		Item(int value)
			:_itemData{ value }
		{
		}

		Item(const ItemData& itemData)
			: _itemData(itemData)
		{
		}


		static void SwapData(Item& item1, Item& item2)
		{
			if (&item1 == &item2)
			{
				return;
			}

			//lock mutex A and mutex B always in this order
			//or lock mutex A and mutex B at the same time
			std::lock(item1._mutex, item2._mutex);
			std::lock_guard<std::mutex> lockA(item1._mutex, std::adopt_lock);//adopt_lock takes a mutex already locked
			std::lock_guard<std::mutex> lockB(item2._mutex, std::adopt_lock);

			std::swap(item1._itemData, item2._itemData);
		}

		static void Print(Item& item1, Item& item2)
		{
			std::lock(item1._mutex, item2._mutex);
			std::lock_guard<std::mutex> lockA(item1._mutex, std::adopt_lock);//adopt_lock takes a mutex already locked
			std::lock_guard<std::mutex> lockB(item2._mutex, std::adopt_lock);

			std::cout << item1._itemData._value << "," << item2._itemData._value << std::endl;
		}
	};

	Item item1(1);
	Item item2(2);

	void ThreadA()
	{
		for (int i = 0; i < 100; ++i)
		{
			sleep(20);
			Item::SwapData(item1, item2);
		}
	}

	void ThreadB()
	{
		for (int i = 0; i < 100; ++i)
		{
			sleep(20);
			Item::SwapData(item1, item2);
		}
	}


	void ThreadPrint()
	{
		for (int i = 0; i < 100; ++i)
		{
			sleep(20);
			Item::Print(item1, item2);
		}
	}

	BEGIN_TEST(Ex10_Deadlock)
		std::thread threadA(ThreadA);
		std::thread threadB(ThreadB);
		std::thread threadPrint(ThreadPrint);
		threadA.join();
		threadB.join();
		threadPrint.join();
	END_TEST()

}