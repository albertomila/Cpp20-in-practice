#pragma once
#include "stdafx.h"

namespace nsAbstractFactory
{
	class IProduct
	{
	public:
		IProduct() : _value1(99) {}
	private:
		int _value1;
	};

	class CProductA : public IProduct
	{
	public:
		CProductA()
			: IProduct()
			, _value(98) {}
	private:
		int _value;
	};

	class CProductB : public IProduct
	{
	public:
		CProductB()
			: IProduct()
			, _value(97.9f) {}
	private:
		float _value;
	};

	class IFactory
	{
	public:
		virtual IProduct* CreateProduct() const = 0;
	};

	class CFactoryA : public IFactory
	{
	public:
		CProductA* CreateProduct() const override
		{
			CProductA* product = new CProductA();
			return product;
		}
	};

	class CFactoryB : public IFactory
	{
	public:
		CProductB* CreateProduct() const override
		{
			CProductB* product = new CProductB();
			return product;
		}
	};
}

BEGIN_TEST(AbstractFactory)
	using namespace nsAbstractFactory;

	std::vector<IFactory*> factories;
	factories.push_back(new CFactoryA());
	factories.push_back(new CFactoryB());

	for (int i = 0; i < 10; ++i)
	{
		IFactory* factory = factories[rand() % factories.size()];
		IProduct* product = factory->CreateProduct();
		delete product;
	}

END_TEST()



namespace nsAbstractFactory
{
	class IItem
	{
	};

	class CItemA : public IItem
	{
	};

	class CItemB : public IItem
	{
	};

	class CItemASuper : public IItem
	{
	};

	class CItemBSuper : public IItem
	{
	};

	class IFactoryItem
	{
	public:
		virtual IItem* CreateItemA() const = 0;
		virtual IItem* CreateItemB() const = 0;
	};

	class CFactoryItems : public IFactoryItem
	{
	public:
		CItemA* CreateItemA() const override
		{
			return new CItemA();
		}

		CItemB* CreateItemB() const override
		{
			return new CItemB();
		}
	};

	class CFactoryItemsSuper : public IFactoryItem
	{
	public:
		CItemASuper* CreateItemA() const override
		{
			return new CItemASuper();
		}

		CItemBSuper* CreateItemB() const override
		{
			return new CItemBSuper();
		}
	};
}

BEGIN_TEST(AbstractFactory2)
	using namespace nsAbstractFactory;

	std::vector<IFactoryItem*> factories;
	factories.push_back(new CFactoryItems());
	factories.push_back(new CFactoryItemsSuper());

	for (int i = 0; i < 10; ++i)
	{
		IFactoryItem* factory = factories[rand() % factories.size()];
		IItem* itemA = factory->CreateItemA();
		delete itemA;

		IItem* itemB = factory->CreateItemB();
		delete itemB;
	}

END_TEST()