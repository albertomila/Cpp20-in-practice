#include "stdafx.h"
#include <mutex>

class ItemData
{

};

class Item
{
private:
	ItemData _itemData;
	std::mutex _mutex;

public:
	Item()
	{
	}

	Item( const ItemData& itemData)
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
};


BEGIN_TEST(Ch3_Deadlock)
	Item item1;
	Item item2;

	Item::SwapData(item1, item2);

END_TEST()

//int main(){MainExample(); return 0;}
