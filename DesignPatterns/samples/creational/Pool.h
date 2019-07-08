#pragma once
#include "stdafx.h"
#include <map>

namespace nsPool
{
	class CObject
	{
	public:
		CObject()
			:_isFree(true)
			, _isFinished(false)
			, _data(0)
		{
		}

		void Create()
		{
			_isFree = false;
			_isFinished = false;
			_data = 99;
		}

		void SetFinished()
		{
			_isFinished = true;
		}

		bool IsFinished()
		{
			return _isFinished;
		}

		void Destroy()
		{
			_data = 0;
			_isFree = true;
			_isFinished = false;
		}

		bool IsFree()
		{
			return _isFree;
		}
		
	private:
		bool _isFinished;
		bool _isFree;
		int _data;
	};

	template<class T, int SIZE>
	class CPool
	{
	public:
		CPool()
			:_pool(SIZE)
		{
			for (T*& poolObject : _pool)
			{
				poolObject = new T();
			}
		}

		~CPool()
		{
			for (T*& poolObject : _pool)
			{
				delete poolObject;
			}
		}

		T* CreateNewObject()
		{
			T* freeObject = GetFirstFreeObject();
			if (freeObject == nullptr)
			{
				return nullptr;
			}

			freeObject->Create();
			return freeObject;
		}

		void Update()
		{
			for (T*& poolObject : _pool)
			{
				if (poolObject->IsFinished())
				{
					poolObject->Destroy();
				}
			}
		}

	private:
		T* GetFirstFreeObject()
		{
			for (T*& poolObject : _pool)
			{
				if (poolObject->IsFree())
				{
					return poolObject;
				}
			}

			return nullptr;
		}


		std::vector<T*> _pool;
	};

}

BEGIN_TEST(Pool)
	using namespace nsPool;

	CPool<CObject, 10> poolObjects;
	CObject* obj1 = poolObjects.CreateNewObject();
	CObject* obj2 = poolObjects.CreateNewObject();
	CObject* obj3 = poolObjects.CreateNewObject();

	obj1->SetFinished();
	obj2->SetFinished();
	poolObjects.Update();

	obj3->SetFinished();
	poolObjects.Update();

END_TEST()