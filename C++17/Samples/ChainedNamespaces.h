#pragma once
#include "stdafx.h"

namespace nsChainedNamespaces
{
	namespace nsFrontEnd::nsUI::nsSomeUISystem::nsData 
	{
		struct SData
		{
		};
	}
}

BEGIN_TEST(ChainedNamespaces)
	using namespace nsChainedNamespaces;

	nsFrontEnd::nsUI::nsSomeUISystem::nsData::SData data;

	UNUSED(data);

END_TEST()


