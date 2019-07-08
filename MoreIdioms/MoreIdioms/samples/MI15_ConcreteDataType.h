#pragma once
#include "stdafx.h"
//////////////////////////////////////////////////////
class EventHandler 
{
public:
    virtual ~EventHandler () {}
};

//////////////////////////////////////////////////////
class MouseEventHandler : public EventHandler // Note inheritance
{
protected:
    ~MouseEventHandler () {} // A protected virtual destructor.
public:
    MouseEventHandler () {} // Public Constructor.
};

//////////////////////////////////////////////////////
class MouseEventHandler2 // Note no inheritance
{
protected:
    MouseEventHandler2 () {} // Protected Constructor.
    ~MouseEventHandler2 () {} // A protected, non-virtual destructor.
public:
    static MouseEventHandler2 * Create() { return new MouseEventHandler2(); }
    void Destroy() { delete this; }  // Reclaim memory.
};

//////////////////////////////////////////////////////
class ScopedLock
{
private:
    static void * operator new (size_t size); // Disallow dynamic allocation
    static void * operator new (size_t, void * mem);  // Disallow placement new as well.
};

BEGIN_TEST(ConcreteDataType)
    //example 1: scoped not allowed
    //MouseEventHandler m; // A scoped variable is not allowed as destructor is protected.
    EventHandler *e = new MouseEventHandler (); // Dynamic allocation is allowed
    delete e;  // Polymorphic delete. Does not leak memory.

    //example 2: pointer not allowed
    ScopedLock s; // Allowed
    //ScopedLock * sl = new ScopedLock (); // Standard new and nothrow new are not allowed.
    //void * buf = ::operator new (sizeof (ScopedLock));
    //ScopedLock * s2 = new(buf) ScopedLock;  // Placement new is also not allowed

	END_TEST()