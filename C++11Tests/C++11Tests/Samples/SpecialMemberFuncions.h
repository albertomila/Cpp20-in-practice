#include "stdafx.h"
#include <xutility>

class WidgetSpecial1
{
public:
    WidgetSpecial1(){}

    virtual ~WidgetSpecial1() {}

    //The copy constructor is generated only for classes lacking an explicitly declared copy constructor,
    WidgetSpecial1(const WidgetSpecial1&) {}

    //The copy assignment operator is generated only for classes lacking an explicitly declared copy assignment operator
    //The copy assignment operator is deleted if a move operation is declared
    WidgetSpecial1& operator = (const WidgetSpecial1& w){ return *this;}

    //Move operations are generated only for classes lacking explicitly declared move operations, copy operations, or a destructor.
    WidgetSpecial1(WidgetSpecial1&& w) {}

    WidgetSpecial1& operator = (WidgetSpecial1&& w){ return *this; }
};

class WidgetSpecial2
{
public:
    WidgetSpecial2() = default;

    virtual ~WidgetSpecial2() = default;

    //The copy constructor is generated only for classes lacking an explicitly declared copy constructor,
    WidgetSpecial2(const WidgetSpecial2&) = default;

    //The copy assignment operator is generated only for classes lacking an explicitly declared copy assignment operator
    //The copy assignment operator is deleted if a move operation is declared
    WidgetSpecial2& operator = (const WidgetSpecial2&) = default;

    //Move operations are generated only for classes lacking explicitly declared move operations, copy operations, or a destructor.
    WidgetSpecial2(WidgetSpecial2&&) = default;
    WidgetSpecial2& operator = (WidgetSpecial2&&) = default;
};

BEGIN_TEST(TestSpecialMemberFunctions)
    {
        WidgetSpecial1 w11;
        WidgetSpecial1 w12(w11);

        WidgetSpecial1 w21;
        WidgetSpecial1 w22;
        w22 = w21;

        WidgetSpecial1 w31;
        WidgetSpecial1 w32(std::move(w31));

        WidgetSpecial1 w41;
        WidgetSpecial1 w42;
        w42 = std::move(w41);
    }

    {
        WidgetSpecial2 w11;
        WidgetSpecial2 w12(w11);

        WidgetSpecial2 w21;
        WidgetSpecial2 w22;
        w22 = w21;

        WidgetSpecial2 w31;
        WidgetSpecial2 w32(std::move(w31));

        WidgetSpecial2 w41;
        WidgetSpecial2 w42;
        w42 = std::move(w41);
    }
END_TEST()