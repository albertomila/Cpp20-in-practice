#pragma once
#include "stdafx.h"
#include <typeinfo>
using namespace std;

template<class T, class V>
T DoDisableDynamicCast(V& /*obj*/)
{
	static_assert(false, "dynamic_cast is disabled");

	return nullptr;
};

//#define dynamic_cast DoDisableDynamicCast
	

namespace nsDisableDynamicCast
{
	class IObject
	{
		virtual void Init() = 0;
	};

	class CObject : public IObject
	{
		void Init() override{}
	};
}

using namespace nsDisableDynamicCast;

BEGIN_TEST(DisableDynamicCast)

	IObject* interfaceObj = new CObject();
	CObject* obj = dynamic_cast<CObject*>(interfaceObj);
END_TEST()