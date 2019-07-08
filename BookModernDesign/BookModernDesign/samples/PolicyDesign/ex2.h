#pragma once
#include "stdafx.h"
#include <type_traits>
#include <map>
using namespace std;

namespace nsPolicyDesign2
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

	protected:
		~OpNewCreator() {}
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

	protected:
		~MallocCreator() {}
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
	protected:
		~PrototypeCreator() {}

	private:
		T* pPrototype_;
	};

	class Widget
	{
	public:
		Widget* Clone()
		{
			return NULL;
		}
	};

	class Gadget
	{
	};

	//////////////////////////////////////
	template <template <class> class CreationPolicy = OpNewCreator >
	class WidgetManager : public CreationPolicy<Widget>
	{
		void DoSomething()
		{
			Gadget* pW = CreationPolicy<Gadget>().Create();
		}

		void SwitchPrototype(Widget* pNewPrototype)
		{
			CreationPolicy<Widget>& myPolicy = *this;
			delete myPolicy.GetPrototype();
			myPolicy.SetPrototype(pNewPrototype);
		}

	};

	typedef WidgetManager<>                     MyWidgetMgrDefault;
	typedef WidgetManager< OpNewCreator >       MyWidgetMgr1;
	typedef WidgetManager< MallocCreator >      MyWidgetMgr2;
	typedef WidgetManager< PrototypeCreator >   MyWidgetMgr3;
}

BEGIN_TEST(PolicyDesign2)
	using namespace nsPolicyDesign2;

	MyWidgetMgrDefault myWidgetMgr;

    MyWidgetMgr1 myWidgetMgr1;
    Widget* widget1 = myWidgetMgr1.Create();
    delete widget1;

    MyWidgetMgr2 myWidgetMgr2;
    Widget* widget2 = myWidgetMgr2.Create();
    delete widget2;

    MyWidgetMgr3 myWidgetMgr3;
    Widget* widget3 = myWidgetMgr3.Create();
    myWidgetMgr3.SetPrototype( widget2 );
    delete widget3;
    //PrototypeCreator<Widget>* pCreator = &myWidgetMgr3; 
    //delete pCreator;  // compiles fine, but has undefined behavior
END_TEST()