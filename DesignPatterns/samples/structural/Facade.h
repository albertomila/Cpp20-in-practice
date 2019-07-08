#pragma once
#include "stdafx.h"
#include <vector>

namespace nsFacade
{
	class UISystem
	{
	};

	class GamplayeSystem
	{
	};

	class AISystem
	{
	};

	class ServerSystem
	{
	};

	class FileSystem
	{
	};

	class EventSystem
	{
	};

	class MainManagerFacade
	{
	public:
		void Init()
		{
			//create all systems
			//initialize systems
		}

		bool AreSystemsReady() const
		{
			//tells if the system is ready
			return true;
		}

		bool IsFinished() const
		{
			//tells if the system is finished
			return true;
		}

		void Update()
		{
			//Updates all systems
		}

		void Shutdown()
		{
			//removes all systems, unregister, destroy memory, clean up.
		}
	};
}

BEGIN_TEST(Facade)
	using namespace nsFacade;

	MainManagerFacade mainManager;
	mainManager.Init();

	while (!mainManager.AreSystemsReady())
	{
	}

	while (mainManager.IsFinished())
	{
		mainManager.Update();
	}

END_TEST()