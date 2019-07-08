#pragma once
#include "stdafx.h"
#include <map>

namespace nsLazyInitialization
{
	class CItem
	{
	public:
		CItem(int type)
			:_type(type)
		{

		}

		int GetType() { return _type; }

	private:
		int _type;
	};

	class CLazyFactory
	{
		using TMapType = std::map<int, CItem*>;
	public:
		CItem* GetUniqueItem(int key)
		{
			TMapType::iterator it = _uniqueItems.find(key);
			if (it != _uniqueItems.end())
			{
				return it->second;
			}
			else
			{
				CItem* newItem = new CItem(key);
				_uniqueItems[key] = newItem;

				return newItem;
			}
		}

	private:
		TMapType _uniqueItems;
	};

}

BEGIN_TEST(LazyInitialization)
	using namespace nsLazyInitialization;

	CLazyFactory lazyFactory;

	CItem* item1 = lazyFactory.GetUniqueItem(0);
	CItem* item2 = lazyFactory.GetUniqueItem(1);
	CItem* item3 = lazyFactory.GetUniqueItem(0);
	CItem* item4 = lazyFactory.GetUniqueItem(2);
	CItem* item5 = lazyFactory.GetUniqueItem(1);

END_TEST()