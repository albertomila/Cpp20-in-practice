#include "stdafx.h"
#include <samples/structural/PrivateImplementation.h>

namespace nsPrivateImplementation
{
	class CGameplaySystem::CGameplaySystemPimpl
	{
	public:

		void Init()
		{
		}

		void Shutdown()
		{
		}
	};

	void CGameplaySystem::Init()
	{
		_pImpl = new CGameplaySystemPimpl();
		_pImpl->Init();
	}

	void CGameplaySystem::Shutdown()
	{
		_pImpl->Shutdown();
		delete _pImpl;
	}
}