#pragma once
#include "stdafx.h"

namespace nsHiddenImpl
{
	class IHiddenImplObjectBase
	{
	public:
		virtual ~IHiddenImplObjectBase() {}
		virtual int GetData() const = 0;
	};

	class CCreator
	{
	public:
		IHiddenImplObjectBase* CreateHiddenImplObject()
		{
			class CHiddenImplObject : public IHiddenImplObjectBase
			{
			public:
				~CHiddenImplObject() override 
				{
					_data = 0;
				}
				int GetData() const override { return _data; }
				void SetData(int data) { _data = data; }

			private:
				int _data = 0;
			};

			CHiddenImplObject* hiddenObject = new CHiddenImplObject();
			int data = hiddenObject->GetData();
			return hiddenObject;
		}
	};

	class CDeleter
	{
	public:
		void ProcessPrivateObject(IHiddenImplObjectBase* privateObjecte)
		{
			//doesn't find type
			//CHiddenImplObject* obj = dynamic_cast<CHiddenImplObject>(privateObjecte);

			//doesn't find type
			//CTest1::CHiddenImplObject* obj = dynamic_cast<CTest1::CHiddenImplObject>(privateObjecte);


			//if you want to reuse this code in CreateHiddenImplObject or DeletePrivateObject while keeping the private impl,
			//then create a MACRO #define, or an include file with all the content of this class below.
			//Like #include <samples/HiddenClass.h>
			//or use the macro DEFINE_CHIDDEN_IMPL_OBJECT macro that should be declared somewhere on this file.
			class CHiddenImplObject : public IHiddenImplObjectBase
			{
			public:
				~CHiddenImplObject() override
				{
					//It doesn't hit this breackpoint, it hits the original class definition
					_data = 99;
				}
				int GetData() const override 
				{
					//It doesn't hit this breackpoint, it hits the original class definition
					return _data; 
				}
				int GetMoreData() const
				{
					//It hits this breakpoint
					return _data * 2;
				}

			private:
				int _data = 0;
			};

			//finds the type defined just above.

			//works fine
			CHiddenImplObject* hiddenImplObject1 = static_cast<CHiddenImplObject*>(privateObjecte);

			//doesn't work
			CHiddenImplObject* hiddenImplObject2 = dynamic_cast<CHiddenImplObject*>(privateObjecte); 

			//works fine
			CHiddenImplObject* hiddenImplObject3 = reinterpret_cast<CHiddenImplObject*>(privateObjecte); 
			int data = hiddenImplObject1->GetData();
			int moreData = hiddenImplObject1->GetMoreData();

			delete privateObjecte;
		}

		void DeletePrivateObject(IHiddenImplObjectBase* privateObjecte)
		{
			delete privateObjecte;
		}
	};

}

BEGIN_TEST(HiddenImplementation)
	using namespace nsHiddenImpl;
	CCreator creator;
	CDeleter deleter;

	IHiddenImplObjectBase* obj = creator.CreateHiddenImplObject();
	deleter.ProcessPrivateObject(obj);
	deleter.DeletePrivateObject(obj);

END_TEST()