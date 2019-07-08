#pragma once
#include "stdafx.h"
#include <map>

namespace nsMultiton
{
	class CManager
	{
		int _data = 99;
	};

	class Incopiable
	{
		Incopiable(const Incopiable &value) {}
		Incopiable& operator = (const Incopiable &value) {}
	protected:
		Incopiable() throw() {}
		virtual ~Incopiable() throw() {}
	};

	template<typename T>
	class CSingleton : public Incopiable
	{
	public:
		static void CreateInstance()
		{
			if (ms_instance == NULL)
			{
				ms_instance = new T();
			}
			else
			{
				assert(false && "entity already created");
			}
		}

		static void DestroyInstance()
		{
			delete ms_instance;
		}

		static inline T* Get()
		{
			return ms_instance;
		}

	private:
		static T* ms_instance;
	};

	template< typename T >
	T* CSingleton<T>::ms_instance = NULL;

	template<class T>
	class CMultiton : public CSingleton<CMultiton<T>>
	{
		using TPairMap = std::pair<const char*, T*>;
		using TMapType = std::map<const char*, T*>;

	public:
		~CMultiton()
		{
			for (const TPairMap& element : _uniqueInstances)
			{
				delete element.second;
			}
		}

		void CreateSingleton(const char* key)
		{
			TMapType::iterator it = _uniqueInstances.find(key);
			if (it == _uniqueInstances.end())
			{
				T* newInstance = new T();
				_uniqueInstances[key] = newInstance;
			}
			else
			{
				assert(false && "entity already created");
			}
		}

		void DestroySingleton(const char* key)
		{
			TMapType::iterator it = _uniqueInstances.find(key);
			if (it == _uniqueInstances.end())
			{
				assert(false && "entity not created");
			}
			else
			{
				T* instance = it->second;
				delete instance;
				_uniqueInstances.erase(it);
			}
		}

		T* GetSingleton(const char* key)
		{
			TMapType::iterator it = _uniqueInstances.find(key);
			if (it != _uniqueInstances.end())
			{
				T* instance = it->second;
				return instance;
			}

			assert(false && "entity not created");
			return nullptr;
		}

		static T* GetInstance(const char* key)
		{
			return CMultiton<T>::Get()->GetSingleton(key);
		}
	private:
		TMapType _uniqueInstances;
	};
}

BEGIN_TEST(Multiton)
	using namespace nsMultiton;
	
	using TMultitonManager = CMultiton<CManager>;

	TMultitonManager::CreateInstance();
	TMultitonManager* multitonInstance = TMultitonManager::Get();
	multitonInstance->CreateSingleton("Manager1");
	multitonInstance->CreateSingleton("Manager2");

	CManager* manager1 = multitonInstance->GetSingleton("Manager1");
	CManager* manager2 = multitonInstance->GetSingleton("Manager2");

	multitonInstance->DestroySingleton("Manager1");
	multitonInstance->DestroySingleton("Manager2");

	CManager* manager = TMultitonManager::GetInstance("Manager1");


	CMultiton<CManager>::DestroyInstance();
END_TEST()