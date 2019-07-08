#pragma once
#include "stdafx.h"

//////////////////////////////////////////////////////////////
template <class Derived>
struct IBase
{
    void CallInterface()
    {
        implementation();
        static_cast<Derived*>(this)->implementation2();
        static_interface();
    }

    static void static_interface()
    {
        Derived::static_implementation();
    }

    // The default implementation may be (if exists) or should be (otherwise) 
    // overriden by inheriting in derived classes (see below)
    virtual void implementation() = 0;
    static void static_implementation();
};

///////////////////////////////////////////////////////////////
// The Curiously Recurring Template Pattern (CRTP)
struct CDerived1 : IBase<CDerived1>
{
    // This class uses base variant of implementation
    void implementation()
    {
        ;
    }

    void implementation2()
    {
        ;
    }

    // ... and overrides static_implementation
    static void static_implementation()
    {
        ;
    }
};

///////////////////////////////////////////////////////////////
struct CDerived2 : IBase<CDerived2>
{
    // This class overrides implementation
    void implementation()
    {
        ;
    }

    void implementation2()
    {
        ;
    }

    // ... and uses base variant of static_implementation
    static void static_implementation()
    {
        ;
    }
};

BEGIN_TEST(RecursiveInterface)
    CDerived1 d;
    d.CallInterface();
END_TEST()