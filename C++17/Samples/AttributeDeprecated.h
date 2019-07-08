#pragma once
#include "stdafx.h"

namespace nsAttributeDeprecated
{
	namespace[[deprecated]] nsDeprecatedNamespace{
		void DoSomething()
		{

		}
	}

	struct[[deprecated]] SDeprecatedStruct
	{
		int _value;
	};

	enum EnumWithDeprecatedValue {
		value1 = 0,
		value2[[deprecated]] = 1
	};
}

BEGIN_TEST(AttributeDeprecated)
	using namespace nsAttributeDeprecated;

	nsDeprecatedNamespace::DoSomething(); // Emits warning
	
	SDeprecatedStruct deprecatedStruct;
	deprecatedStruct._value = 0;

	EnumWithDeprecatedValue e = EnumWithDeprecatedValue::value2; // Emits warning

END_TEST()


