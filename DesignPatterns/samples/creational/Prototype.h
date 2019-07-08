#pragma once
#include "stdafx.h"

namespace nsPrototype
{
	class IItem
	{
		virtual IItem* Clone() = 0;
	};

	class CItemA : public IItem
	{
	public:
		CItemA()
			: _data(99)
		{
		}

		CItemA(CItemA& other)
			: _data(other._data)
		{
		}

		CItemA* Clone() override
		{
			return new CItemA(*this);
		}

	private:
		int _data;
	};

	class CItemB : public IItem
	{
	public:
		CItemB()
			: _data("test")
		{
		}

		CItemB(CItemB& other)
			: _data(other._data)
		{
		}

		CItemB* Clone() override
		{
			return new CItemB(*this);
		}

	private:
		std::string _data;
	};
}

BEGIN_TEST(Prototype)
	using namespace nsPrototype;

	CItemA prototypeA;
	CItemB prototypeB;

	IItem* itemACopy = prototypeA.Clone();
	IItem* itemBCopy = prototypeB.Clone();

END_TEST()