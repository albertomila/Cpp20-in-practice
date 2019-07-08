#pragma once
#include "stdafx.h"
#include <string>

namespace nsAvoidNamespaceDependencies
{
	class CStringID
	{
	public:
		CStringID(const char* id)
			:m_id(id)
		{
		}

	private:
		std::string m_id;
	};

	class CAnyClass
	{
	public:
		static const char* ANY_ID;
	};

	namespace nsOtherNamespace
	{
		const CStringID ANY_STRING_ID(CAnyClass::ANY_ID);
	}

}

BEGIN_TEST(AvoidNamespaceDependencies)
using namespace nsAvoidNamespaceDependencies;

END_TEST()
