#pragma once
#include "stdafx.h"
#include <iosfwd>

class VFF_Base 
{
public:
    friend std::ostream& operator << (std::ostream& o, const VFF_Base& b);
    // ...
protected:
    virtual void print(std::ostream& o) const
    {
        std::cout << "Base";
        ;
    }
};
/* make sure to put this function into the header file */
inline std::ostream& operator << (std::ostream& o, const VFF_Base& b)
{
    b.print(o); // delegate the work to a polymorphic member function.
    return o;
}

class VFF_Derived : public VFF_Base
{
protected:
    virtual void print(std::ostream& o) const override
    {
        std::cout << "Derived";
        ;
    }
};

BEGIN_TEST(VirtualFriendFunction)
	VFF_Derived d;

    std::cout << "test" << d << std::endl;
END_TEST()