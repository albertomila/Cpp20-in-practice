#pragma once
#include "stdafx.h"
#include <functional>
#include <assert.h> 

//problem
/*
class VFC_Base 
{
public:
    VFC_Base();
    ...
    virtual void foo(int n) const; // often pure virtual
    virtual double bar() const;    // often pure virtual
};

VFC_Base::VFC_Base()
{
    ... foo(42) ... bar() ...
        // these will not use dynamic binding
        // goal: simulate dynamic binding in those calls
}

class VFC_Derived : public VFC_Base 
{
public:
    ...
        virtual void foo(int n) const;
    virtual double bar() const;
};
*/

//solution 1 : Using Init()
/*
class VFC_Base 
{
public:
    void init();  // may or may not be virtual
    ...
        virtual void foo(int n) const; // often pure virtual
    virtual double bar() const;    // often pure virtual
};

void VFC_Base::init()
{
    ... foo(42) ... bar() ...
        // most of this is copied from the original VFC_Base::VFC_Base()
}

class VFC_Derived : public VFC_Base 
{
public:
    VFC_Derived (const char *);
    virtual void foo(int n) const;
    virtual double bar() const;
};

template <class VFC_Derived, class Parameter>
std::auto_ptr <VFC_Base> factory (Parameter p)
{
    std::auto_ptr <VFC_Base> ptr (new VFC_Derived (p));
    ptr->init (); 
    return ptr;
}

class VFC_Base {
public:
    template <class D, class Parameter>
    static std::auto_ptr <VFC_Base> Create (Parameter p)
    {
        std::auto_ptr <VFC_Base> ptr (new D (p));       
        ptr->init (); 
        return ptr;
    }
};

int main ()
{
    std::auto_ptr <VFC_Base> b = VFC_Base::Create <VFC_Derived> ("para");
}
*/

//using static methods
////////////////////////////////////////////////////////
class VFC_Base 
{
};

////////////////////////////////////////////////////////
template <class D>
class InitTimeCaller : public VFC_Base 
{
protected:
    InitTimeCaller () 
    {
        D::foo ();
        D::bar ();

        D::test( this );
    }

	virtual void Load() = 0;
};

////////////////////////////////////////////////////////
class VFC_Derived : public InitTimeCaller <VFC_Derived> 
{
	using base = InitTimeCaller <VFC_Derived>;
public:
	VFC_Derived() 
		: InitTimeCaller <VFC_Derived>()
       //, m_x( 99 )
    {
        std::cout << "VFC_Derived::VFC_Derived()\n";
    }
    static void foo () 
    {
        std::cout << "VFC_Derived::foo()\n";
    }
    static void bar () 
    {
        std::cout << "VFC_Derived::bar()\n";
    }
    static void test (base* baseObj )
    {
        VFC_Derived* derived = static_cast<VFC_Derived*>(baseObj);

        derived->m_x = 10;

        std::cout << "VFC_Derived::base()\n";
    }
	void Load() override
	{
		std::cout << "VFC_Derived::Load()\n";
	}


    int m_x;
};


////////////////////////////////////////////////////////
template <class TParent, void (TParent::*TMethod)()>
class ConstructorFinishedCaller
{
	typedef void (TParent::*TMethod)();
	TParent* _parent;
	TMethod _method;
public:
	ConstructorFinishedCaller(TParent* parent, TMethod method)
		:_parent(parent)
		, _method(method)
	{
	}

	~ConstructorFinishedCaller()
	{
		((*_parent).*_method)();
	}
};


////////////////////////////////////////////////////////
class ConstructorFinishedCaller11
{
	std::function<void()> _method;
public:
	ConstructorFinishedCaller11(std::function<void()> method)
		: _method(method)
	{
	}

	~ConstructorFinishedCaller11()
	{
		_method();
	}
};

////////////////////////////////////////////////////////
class Parent
{
public:
	Parent()
	{
		ConstructorFinishedCaller<Parent, &Parent::A> constructorFinishedCaller(this, &Parent::A);
		ConstructorFinishedCaller11 constructorFinishedCaller11(std::bind(&Parent::A, this));
		int x = 0;
		++x;
	}
	
public:
	void A()
	{

	}
};


BEGIN_TEST(VirtualFunctionsConstructor)
    VFC_Derived d;

	Parent p;
END_TEST()