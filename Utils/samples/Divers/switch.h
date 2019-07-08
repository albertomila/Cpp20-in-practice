#pragma once
#include "stdafx.h"

using namespace std;

/*
class Test
{
	void Foo1()
	{
		int x = x_;
		x = x_;
	}
	void Foo2()
	{
		int x = x_;
		x = x_;
		Foo1();
	}
	void Foo3()
	{
		int x = x_;
		x = x_;
	}
	void Foo4()
	{
		int x = x_;
		x = x_;
	}
	enum type_functions {TYPE_FOO1, TYPE_FOO2,TYPE_FOO3,TYPE_FOO4, MAX_FOO};
	typedef void (Test::*typefunction)(); 
	typefunction types[MAX_FOO];
	static const int x_ = 99;
public:
	Test()
	{
		types[TYPE_FOO1] = &Test::Foo1;
		types[TYPE_FOO2] = &Test::Foo2;
		types[TYPE_FOO3] = &Test::Foo3;
		types[TYPE_FOO4] = &Test::Foo4;
	}

	void Print()
	{
		type_functions type_ = TYPE_FOO2;
		(this->*types[type_])();
	}
};
int main () 
{
	Test* t = new Test();
	t->Print();
	delete t;

	return 0;
}
*/

namespace nsSwitch
{
	template <class T>
	struct GenericFunction
	{
		typedef void (T::*typefunction)();
		typefunction Tf_;
		GenericFunction(typefunction Tf) : Tf_(Tf)
		{
		}
		void operator()(T& t)
		{
			(t.*Tf_)();
		}
	};
	template <class T, class Arg1>
	struct GenericFunctionArg
	{
		typedef void (T::*typefunction)(Arg1);
		typefunction Tf_;
		Arg1 arg1_;
		GenericFunctionArg(typefunction Tf, Arg1 arg1) : Tf_(Tf), arg1_(arg1)
		{
		}
		void operator()(T& t)
		{
			(t.*Tf_)(arg1_);
		}
	};



	template <class T, class Arg1>
	struct GenericFunctionArgPtr
	{
		typedef void (T::*typefunction)(Arg1*);
		typefunction Tf_;
		Arg1* arg1_;
		GenericFunctionArgPtr(typefunction Tf, Arg1* arg1) : Tf_(Tf), arg1_(arg1)
		{
		}
		void operator()(T& t)
		{
			(t.*Tf_)(arg1_);
		}
	};
	
	struct Remove
	{
		Remove(){}
		template <class T>
		bool operator()(const T& t)
		{
			delete t;
			return true;
		}
	};
	struct Delete
	{
		Delete(){}
		template <class T>
		void operator()(const T& t)
		{
			delete t;
		}
	};
	struct Update
	{
		Update(){}
		template <class T>
		void operator()(const T& t)
		{
			t->Update();
		}
	};
};
struct TestBase
{
	virtual void SwitchFunction() = 0;
	virtual ~TestBase() = 0;
};
TestBase::~TestBase()
{ 

}
struct Test1 : public TestBase
{
	void SwitchFunction()
	{
	}
	~Test1()
	{
	}
};
struct Test2 : public TestBase
{
	void SwitchFunction()
	{
	}
	~Test2()
	{
	}
};
struct Test3 : public TestBase
{
	void SwitchFunction()
	{
	}
	~Test3()
	{
	}
};
class Info
{
public:
	enum type_functions {TYPE_FOO1, TYPE_FOO2,TYPE_FOO3, MAX_FOO};
private:
	TestBase* types[MAX_FOO];
	int pos_;
public:
	Info(int pos) : pos_(pos)
	{
		types[TYPE_FOO1] = new Test1();
		types[TYPE_FOO2] = new Test2();
		types[TYPE_FOO3] = new Test3();
	}
	~Info()
	{
		for_each(types, types + MAX_FOO, nsSwitch::Delete());
	}
	int GetPos() { return pos_; }
	void SwitchFunction(type_functions type_)
	{
		types[type_]->SwitchFunction();
	};
};

class TestInfo
{
	int pos_;
public:
	TestInfo() : pos_(99) {}
	void Update()
	{
	}
	void Move(int pos)
	{
		pos_ = pos;
	}
	void Update(TestInfo* test)
	{
		pos_ = test->pos_;
	}
	void SetTest(TestInfo test)
	{
		pos_ = test.pos_;
	}
};

BEGIN_TEST(Switch)
	vector<TestInfo> vinfo(10);
//	for_each(vinfo.begin(), vinfo.end(), nsSwitch::GenericFunction<TestInfo>(&TestInfo::Update));
	
	vector<TestInfo*> vinfo2;
	for(int i=0; i<10; i++)
	{
		vinfo2.push_back(new TestInfo);
	}
	
	for_each(vinfo.begin(), vinfo.end(), nsSwitch::GenericFunction<TestInfo>(&TestInfo::Update));

	int x = 98;
	for_each(vinfo.begin(), vinfo.end(), nsSwitch::GenericFunctionArg<TestInfo, int>(&TestInfo::Move, x));
	
	TestInfo t2;
	for_each(vinfo.begin(), vinfo.end(), nsSwitch::GenericFunctionArg<TestInfo, TestInfo>(&TestInfo::SetTest, t2) );

	TestInfo* t = new TestInfo();
	for_each(vinfo.begin(), vinfo.end(), nsSwitch::GenericFunctionArgPtr<TestInfo, TestInfo>(&TestInfo::Update, t));
	

	Info* info = new Info(99);
	info->SwitchFunction(Info::TYPE_FOO1);
	delete info;


	END_TEST()