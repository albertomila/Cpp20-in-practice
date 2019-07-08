#pragma once
#include "stdafx.h"
#include <cstdio>

class CClient 
{
private:
	void A(int data) {}
    void B(float data) {}
    void C(double data) {}
    friend class Attorney;
};

class Attorney
{
private:
    static void CallA(CClient& client, int data)
    {
		client.A(data);
    } 
    static void CallB(CClient& client, float data)
    {
		client.B(data);
    }
    friend class CCaller;
};

class CCaller 
{
public:
	void DoProcess(CClient& c)
	{
		// Bar now has access to only Client::A and Client::B through the Attorney.
		Attorney::CallA(c, 99);
		Attorney::CallB(c, 99.9f);
	}
};

////////////////////////////////////////////////////////////////////////

class Base 
{
private:
    virtual void Func(int x) = 0;
    friend class Attorney2;
public:
    virtual ~Base() {}
};

class Derived : public Base 
{
private:
    virtual void Func(int x)  
    {
        printf("Derived::Func\n"); // This is called even though main is not a friend of Derived.
    }

public:
    ~Derived() {}
};

class Attorney2 
{
public:
    static void callFunc(Base & b, int x) 
    {
        return b.Func(x);
    }
};

BEGIN_TEST(AttorneyClient)
	CClient client;
	CCaller caller;
	caller.DoProcess(client);

	Derived d;
	Attorney2::callFunc(d, 10);
END_TEST()
