#include "stdafx.h"

class ItemDataUniqueLock
{

};

class ItemUniqueLock
{
private:
	ItemDataUniqueLock _itemData;
	std::mutex _mutex;

public:
	ItemUniqueLock()
	{
	}

	ItemUniqueLock(const ItemDataUniqueLock& itemData)
		: _itemData(itemData)
	{
	}


	static void SwapData(ItemUniqueLock& item1, ItemUniqueLock& item2)
	{
		if (&item1 == &item2)
		{
			return;
		}

		//std::defer_lock leaves mutexes unlocked
		//unique_lock  more flexibility than std::lock_guard
		std::unique_lock<std::mutex> lockA(item1._mutex, std::defer_lock);
		std::unique_lock<std::mutex> lockB(item2._mutex, std::defer_lock);

		//Mutexes are locked here
		std::lock(item1._mutex, item2._mutex);

		std::swap(item1._itemData, item2._itemData);
	}
};


void UniqueLock_ThreadA()
{
	std::cout << "ThreadA" << "\n" << std::endl;
}

void UniqueLock_ThreadB()
{
	std::cout << "ThreadB" << "\n" << std::endl;
}

BEGIN_TEST(Ch3_UniqueLock)
	std::thread threadA(UniqueLock_ThreadA);
	std::thread threadB(UniqueLock_ThreadB);

	threadA.join();
	threadB.join();

	ItemUniqueLock item1;
	ItemUniqueLock item2;

	ItemUniqueLock::SwapData(item1, item2);

END_TEST()
