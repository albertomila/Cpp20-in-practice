#pragma once
#include "stdafx.h"
#include <vector>
#include <samples/creational/Singleton.h>
#include <map>

namespace nsFlyWeight
{
	class CSoundResource
	{
	public:
		using ID = std::string;
		ID _soundID;
	};

	class CSoundSystem : public Singleton<CSoundSystem>
	{
	public:
		CSoundSystem()
		{
			_soundMap["AISound"] = new CSoundResource();
		}

		void PlaySound(CSoundResource::ID soundID)
		{
			const CSoundResource* sound = GetSound(soundID);
			//play sound;
		}

		CSoundResource* GetSound(CSoundResource::ID soundID)
		{
			return _soundMap[soundID];
		}

		std::map<CSoundResource::ID, CSoundResource*> _soundMap;
	};

	class IComponent
	{
	public:
		virtual void Init() {}
		virtual void Update() {}
	};

	class CAIComponent : public IComponent
	{
	public:
		void Init() override 
		{
			_sound = CSoundSystem::Get()->GetSound("AISound");
		}
		void Update() override {}

		const CSoundResource* _sound;
	};

}

BEGIN_TEST(FlyWeight)
	using namespace nsFlyWeight;

	CSoundSystem::CreateInstance();

	CAIComponent aiComponent;
	aiComponent.Init();

	CSoundSystem::DestroyInstance();

END_TEST()