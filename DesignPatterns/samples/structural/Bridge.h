#pragma once
#include "stdafx.h"

namespace nsBridge
{
	class IAssetsLoader
	{
	public:
		virtual void Load() = 0;
	};

	class CImageLoader : public IAssetsLoader
	{
	public:
		void Load() override {}
	};

	class CSoundLoader : public IAssetsLoader
	{
	public:
		void Load() override {}
	};

	class CObject
	{
	public:
		CObject()
			:_assetLoaderPtr(nullptr)
		{
		}

		void SetLoader(IAssetsLoader* assetLoader)
		{
			_assetLoaderPtr = assetLoader;
		}

		void LoadAssets()
		{
			_assetLoaderPtr->Load();
		}

	private:
		IAssetsLoader* _assetLoaderPtr;
	};
}


BEGIN_TEST(Bridge)
	using namespace nsBridge;

	CObject obj;
	IAssetsLoader* loader = new CImageLoader();
	obj.SetLoader(loader);
	obj.LoadAssets();
	delete loader;
END_TEST()