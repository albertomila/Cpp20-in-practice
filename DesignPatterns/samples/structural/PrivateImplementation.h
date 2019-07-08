#pragma once
#include "stdafx.h"
#include <vector>

namespace nsPrivateImplementation
{
	class CGameplaySystem
	{
	private:
		class CGameplaySystemPimpl;

	public:
		CGameplaySystem()
			: _pImpl(nullptr)
		{
		}

		void Init();
		void Shutdown();

	private:
		CGameplaySystemPimpl* _pImpl;
	};
}



BEGIN_TEST(PrivateImplementation)
	using namespace nsPrivateImplementation;

	CGameplaySystem gameplaySystem;
	gameplaySystem.Init();
	gameplaySystem.Shutdown();

END_TEST()