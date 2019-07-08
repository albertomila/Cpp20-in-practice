#pragma once
#include "stdafx.h"

template <int v>
struct NiftyContainer_Int2Type
{
    enum { value = v };
};

template <typename T, bool isPolymorphic>
class NiftyContainer
{
private:
    void DoSomething(T* pObj, NiftyContainer_Int2Type<true>)
    {
        T* pNewObj = pObj->Clone();
    }
    void DoSomething(T* pObj, NiftyContainer_Int2Type<false>)
    {
        T* pNewObj = new T(*pObj);
    }
public:
    void DoSomething(T* pObj)
    {
        DoSomething(pObj, NiftyContainer_Int2Type<isPolymorphic>());
    }
};

BEGIN_TEST(IntegralConstantType)
END_TEST()