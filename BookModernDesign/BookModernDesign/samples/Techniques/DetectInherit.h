#include "stdafx.h"
template <class T, class U>
class Conversion
{
    typedef char Small;
    class Big { char dummy[2]; };
    static Small Test(U);
    static Big Test(...);
    static T MakeT();
public:
    enum 
    {
            exists = sizeof(Test(MakeT())) == sizeof(Small)
        ,   sameType = false 
    };
};

template <class T>
class Conversion<T, T>
{
public:
    enum 
    { 
            exists = 1
        ,   sameType = 1 
    };
};

#define SUPERSUBCLASS(T, U)                         \
    (Conversion<const U*, const T*>::exists &&      \
    !Conversion<const T*, const void*>::sameType)

#define SUPERSUBCLASS_STRICT(T, U)                  \
    (SUPERSUBCLASS(T, U) &&                         \
    !Conversion<const T, const U>::sameType)

template<class T, class U>
class IsDerivedClass
{
public:
    enum
    { 
        value =     Conversion<const U*, const T*>::exists
                && !Conversion<const T*, const void*>::sameType
                && !Conversion<const T, const U>::sameType
    };
};

class Widget
{
};

class ExtendedWidget : public Widget
{
};


BEGIN_TEST(DetectInherit)
    const bool isDerivedClass1 = SUPERSUBCLASS_STRICT( Widget, void );
    const bool isDerivedClass2 = SUPERSUBCLASS_STRICT( Widget, Widget );
    const bool isDerivedClass3 = SUPERSUBCLASS_STRICT( ExtendedWidget, Widget );
    const bool isDerivedClass4 = SUPERSUBCLASS_STRICT( Widget, ExtendedWidget );

    const bool isDerived1 = IsDerivedClass< Widget, void >::value;
    const bool isDerived2 = IsDerivedClass< Widget, Widget >::value;
    const bool isDerived3 = IsDerivedClass< ExtendedWidget, Widget >::value;
    const bool isDerived4 = IsDerivedClass< Widget, ExtendedWidget >::value;

	END_TEST()