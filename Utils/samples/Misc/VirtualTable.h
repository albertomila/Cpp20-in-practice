#pragma once
#include "stdafx.h"
#include <typeinfo>

namespace nsVirtualTable
{
	struct SDataBase
	{
	};

	struct SDataDerived : public SDataBase
	{
	};

	struct SVirtualDataBase
	{
		virtual void Init() {}
	};

	struct SVirtualDataDerived : public SVirtualDataBase
	{
		void Init() override {}
	};
}

BEGIN_TEST(VirtualTable)
	using namespace nsVirtualTable;
	constexpr int s11 = sizeof(SDataBase);
	constexpr int s12 = sizeof(SDataBase*);
	constexpr int s13 = sizeof(SDataBase&);
	constexpr int s2 = sizeof(SDataDerived);
	constexpr int s3 = sizeof(SVirtualDataBase);
	constexpr int s4 = sizeof(SVirtualDataDerived);

	SDataDerived derived;
	SDataBase& base = derived;
	int s6 = sizeof(base);
	int s7 = sizeof(derived);

	int x = 0;
	++x;

END_TEST()