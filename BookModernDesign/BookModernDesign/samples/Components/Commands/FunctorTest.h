#pragma once
#include "stdafx.h"
#include "Functors.h"
#include <iostream>
// The using directive is acceptable for a small C++ program
using namespace std;

// Define a test functor
struct FunctorTest_Predicate
{
    void operator()(int i, double d)
    {
        cout << "TestFunctor::operator()(" << i
            << ", " << d << ") called.\n";
    }
};


inline void FunctorTest_TestFunction(int i)
{
	cout << "TestFunction(" << i << ") called." << endl;
}

inline void FunctorTest_TestFunction(int i, double d)
{
	cout << "TestFunction(" << i
		<< ", " << d << ") called." << endl;
}

BEGIN_TEST(FunctorTest)
    Functor<double, TYPELIST_2(int, double)> myFunctor;
    double result = myFunctor(4, 5.6);
    
	FunctorTest_Predicate f;
    Functor<void, TYPELIST_2(int, double)> cmd(f);
    cmd(4, 4.5);
    /*
    //doesn´t work with function overload
    Functor<void, TYPELIST_2(int, double)> cmd2(&TestFunction);
    cmd2(4, 4.5);
    */
    typedef void (*TpFun)(int, double);
    TpFun pF = &FunctorTest_TestFunction;

    Functor<void, TYPELIST_2(int, double)> cmd3(pF);
    cmd3(4, 4.5);
    
    Functor<void, TYPELIST_2(int, double)> cmd4(static_cast<TpFun>(&FunctorTest_TestFunction)); // Ok
    cmd4(4, 4.5);
  
    typedef void (*TpFun1)(int);
    TpFun1 pF1 = &FunctorTest_TestFunction;
    
    Functor<void, TYPELIST_1(int)> cmd5(pF1);
	cmd5(4);
	END_TEST()