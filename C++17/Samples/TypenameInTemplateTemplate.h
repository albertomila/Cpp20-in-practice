#pragma once
#include "stdafx.h"
#include <queue>
#include <stack>

namespace nsTypenameInTemplateTemplate
{
	template
	<
		template <typename...>
		typename Container
	>
	struct STest
	{
		Container<int> _container;
	};
}

BEGIN_TEST(TypenameInTemplateTemplate)
	using namespace nsTypenameInTemplateTemplate;

	//typename in a template template parameter
	STest<std::vector> dataVector;
	STest<std::queue> dataQueue;
	STest<std::stack> dataStack;

END_TEST()


