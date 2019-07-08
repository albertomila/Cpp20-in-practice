#pragma once
#include "stdafx.h"
#include <assert.h> 

namespace nsVirtualFunctionsConstructor
{
	class IObject
	{
	};

	template<class DerivedClass>
	class CBaseObject : public IObject
	{
	public:
		CBaseObject()
		{
			DerivedClass::OnBaseObjectInit();
			DerivedClass::StaticLoad(static_cast<DerivedClass*>(this));
			DerivedClass::OnBaseObjecEnd();
		}

		virtual void Load() = 0;
	};

	class CDerivedObject : public CBaseObject<CDerivedObject>
	{
	public:
		CDerivedObject()
		{
		}

		static void OnBaseObjectInit()
		{
			std::cout << "OnBaseObjectInit";
		}
		static void OnBaseObjecEnd()
		{
			std::cout << "OnBaseObjecEnd";
		}

		static void StaticLoad(CDerivedObject* derivedObj)
		{
			assert(derivedObj); //ok because we used static_cast
			derivedObj->m_value = 0; //ok, but risky and really bad
			//derivedObj->Load(); //crash, it doesn't find Load() method
		}

		void Load() override
		{
			//derived load operations
		}

	private:
		int m_value;
	};
}


BEGIN_TEST(VirtualFunctionsConstructor)
	using namespace nsVirtualFunctionsConstructor;
	CDerivedObject ojb;
END_TEST()