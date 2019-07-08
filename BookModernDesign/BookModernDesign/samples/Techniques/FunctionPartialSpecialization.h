#pragma once
#include "stdafx.h"

class Door
{
};

class Window
{
};

// primary template
template <class T, class U> 
U& Fun(U& obj)
{
    return obj;
}

/*
// illegal partial
template <class U> 
void Fun<void, U>(U obj)
{
}
*/

// legal (overloading)
template <class T> 
Window& Fun (Window& obj)
{
    return obj;
}

BEGIN_TEST(PartialSpecialization)
    Fun<Door,Door>( Door() );
	Fun<Door>(Window());
END_TEST()