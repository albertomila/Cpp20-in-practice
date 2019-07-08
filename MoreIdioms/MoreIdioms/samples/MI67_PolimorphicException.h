#pragma once
#include "stdafx.h"
//////////////////////////////////////////////////////////
struct ExceptionBase 
{ 
    virtual void raise() { throw *this; }
    virtual ~ExceptionBase() {} 
};

//////////////////////////////////////////////////////////
struct ExceptionDerived : ExceptionBase 
{ 
   // virtual void raise() { throw *this; }
};

//////////////////////////////////////////////////////////
void PE_Foo(ExceptionBase& e)
{
    e.raise(); // Uses dynamic type of e while raising an exception.
}

//////////////////////////////////////////////////////////

BEGIN_TEST(PolimoriphicException)
    ExceptionDerived e;
    try 
    {
		PE_Foo(e);
    }
    catch (ExceptionDerived& e) 
    {
        // Exception raised in foo now matches this catch.
    }
    catch (...) 
    {
        // not here anymore!
    }

	END_TEST()