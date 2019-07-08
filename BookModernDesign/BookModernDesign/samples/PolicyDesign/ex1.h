#pragma once
#include "stdafx.h"
#include <type_traits>
#include <map>
using namespace std;

namespace nsPolicyDesign1
{
	///////////////////////////////////////
	//Policy clases
	//////////////////////////////////////
	template <class T>
	struct OpNewCreator
	{
		static T* Create()
		{
			return new T;
		}
	};

	//////////////////////////////////////
	template <class T>
	struct MallocCreator
	{
		static T* Create()
		{
			void* buf = std::malloc(sizeof(T));
			if (!buf)
			{
				return 0;
			}

			return new(buf) T;
		}
	};

	//////////////////////////////////////
	template <class T>
	struct PrototypeCreator
	{
		PrototypeCreator(T* pObj = 0)
			:pPrototype_(pObj)
		{
		}

		T* Create()
		{
			return pPrototype_ ? pPrototype_->Clone() : 0;
		}

		T* GetPrototype() { return pPrototype_; }
		void SetPrototype(T* pObj) { pPrototype_ = pObj; }
	private:
		T* pPrototype_;
	};

	//////////////////////////////////////
	template <class CreationPolicy>
	class WidgetManager : public CreationPolicy
	{
	};

	class Widget
	{
	public:
		Widget* Clone()
		{
			return NULL;
		}
	};

	typedef WidgetManager< OpNewCreator<Widget> >       MyWidgetMgr1;
	typedef WidgetManager< MallocCreator<Widget> >      MyWidgetMgr2;
	typedef WidgetManager< PrototypeCreator<Widget> >   MyWidgetMgr3;
}

template<class T>
inline void UNUSED(const T&){}

BEGIN_TEST(PolicyDesign1)
	using namespace nsPolicyDesign1;
	
    MyWidgetMgr1 myWidgetMgr1;
	UNUSED(myWidgetMgr1);
    Widget* widget1 = myWidgetMgr1.Create();
    delete widget1;

	MyWidgetMgr2 myWidgetMgr2;
	UNUSED(myWidgetMgr2);
    Widget* widget2 = myWidgetMgr2.Create();
    delete widget2;
    
	MyWidgetMgr3 myWidgetMgr3;
	UNUSED(myWidgetMgr3);
    Widget* widget3 = myWidgetMgr3.Create();
	delete widget3;
END_TEST()