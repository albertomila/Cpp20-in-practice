#pragma once
#include "stdafx.h"
using namespace std;

inline void PointerToFunction_Foo() {}
inline void PointerToFunction_Bar() {}

class PointerToFunction_Parrot
{
public:
    void Eat()
    {
        cout << "Tsk, knick, tsk...\n";
    }
    void Speak()
    {
        cout << "Oh Captain, my Captain!\n";
    }
};

BEGIN_TEST(PointerToFunction)
    // Define a pointer to a function that takes no
    // parameters and returns void.
    // Initialize that pointer with the address of Foo
    void (*pF)() = &PointerToFunction_Foo;
	PointerToFunction_Foo();                // Call Foo directly
	PointerToFunction_Bar();                // Call Bar directly
    (*pF)();              // Call Foo via pF

    void (*pF2)() = pF;   // Create a copy of pF
    pF = &PointerToFunction_Bar;            // Change pF to point to Bar
    (*pF)();              // Now call Bar via pF
    (*pF2)();             // Call Foo via pF2


    typedef void (PointerToFunction_Parrot::* TpMemFun)();

    // Create an object of that type
    // and initialize it with the address of
    // Parrot::Eat.
    TpMemFun pActivity = &PointerToFunction_Parrot::Eat;
    // Create a Parrot...
	PointerToFunction_Parrot geronimo;
    // ...and a pointer to it
	PointerToFunction_Parrot* pGeronimo = &geronimo;

    // Invoke the member function stored in Activity
    // via an object. Notice the use of operator.*
    (geronimo.*pActivity)();

    // Same, via pointer. Now we use operator->*
    (pGeronimo->*pActivity)();
    // Change the activity
    pActivity = &PointerToFunction_Parrot::Speak;

    // Wake up, Geronimo!
	(geronimo.*pActivity)();

	END_TEST()