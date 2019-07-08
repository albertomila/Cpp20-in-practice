#include "stdafx.h"
#include <vector>

class Base 
{
public:
    virtual void doWork() = 0;         // base class virtual function
    virtual void doWorkLValue() & = 0;         // base class virtual function
    virtual void doWorkRValue() && = 0;         // base class virtual function
    virtual void doWorkDispatchLorR() & = 0;         // base class virtual function
    virtual void doWorkDispatchLorR() && = 0;         // base class virtual function
    virtual void mf4() const = 0;
};

class Derived : public Base 
{
public:
    virtual void doWork() override {}        // overrides Base::doWork ("virtual" is optional
    virtual void doWorkLValue() & override {}        // overrides Base::doWork ("virtual" is optional
    virtual void doWorkRValue() && {}       // overrides Base::doWork ("virtual" is optional
    virtual void doWorkDispatchLorR() & override {}        // overrides Base::doWork ("virtual" is optional
    virtual void doWorkDispatchLorR() && {}       // overrides Base::doWork ("virtual" is optional
    void mf4() const override
    {

    }
};                               

Derived makeDerived()
{
    Derived d;
    return d;
}


class WidgetOverriding 
{
public:
    using DataType = std::vector<double>;

public:
    DataType& data() &                // for lvalue Widgets, 
    {
        return values;
    }                // return lvalue

    DataType&& data() &&              // for rvalue Widgets,return rvalue
    { 
        return std::move(values); 
    }

private:
    DataType values;
};

WidgetOverriding makeWidget()
{
    WidgetOverriding w;
    return w;
}


BEGIN_TEST(TestOverriding)
    {
        Base* base = new Derived();
        base->doWork();
        base->doWorkLValue();
        base->doWorkDispatchLorR();
        base->mf4();
        //Derived makeDerived();
        makeDerived().doWorkRValue(); //rvalue
    }

    {
        WidgetOverriding w;

        WidgetOverriding::DataType vals1 = w.data();             // calls lvalue overload for
                                           // WidgetOverriding::data, copy-
                                           // constructs vals1

        WidgetOverriding::DataType vals2 = makeWidget().data();  // calls rvalue overload for
                                           // WidgetOverriding::data, move-
                                           // constructs vals2
    }
END_TEST()