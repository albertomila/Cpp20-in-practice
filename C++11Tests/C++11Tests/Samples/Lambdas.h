#include "stdafx.h"
#include <algorithm>
#include <vector>
#include <functional>

using FilterContainer = std::vector<std::function<bool(int)>>;
using IntFunction = std::function<int(int)>;

bool FiltersFunction(int i)
{
    return false;
}
void AddOperationReference(FilterContainer& filters)
{
    auto divisor = 4 / 2;

    filters.push_back
    (                              // danger!
            [&](int value) { return divisor == 2; }  // ref to
    );
    filters.push_back
    (                              // danger!
            [&divisor](int value) { return divisor == 2; }  // ref to
    );
}
void AddOperationCopyValue(FilterContainer& filters)
{
    auto divisor = 4 / 2;

    filters.push_back
    (                              // danger!
        [=](int value) { return divisor == 2; }  // ref to
    );
}


//[] don't capture anything
//[&] capture a reference
//[=] capture an object
//[myObject] capture an object
//[myVarMemberCopied] capture a variable

class WidgetLambdas {
public:
    bool isValidated() const { return true; }
    bool isProcessed() const { return true; }
    bool isArchived() const { return true; }
    void addFilter(FilterContainer& filters) const
    {
        /*
        filters.push_back
        (
        //it doesn't compile
        //error C4573: the usage of 'Widget::divisor' requires the compiler to capture 'this' but the current default capture mode does not allow it
        [](int value) { return value % divisor == 0; }
        );
        */

        /*
        filters.push_back
        (
        //it doesn't compile
        //error C3480: 'Widget::divisor': a lambda capture variable must be from an enclosing function scope
        [divisor](int value) { return value % divisor == 0; }
        );
        */

        //ok, copy member
        filters.push_back
            (
                [=](int value) { return value % divisor == 0; }
        );

        //ok, capture member
        filters.push_back
            (
                [this](int value) { return value % this->divisor == 0; }
        );

        //ok, capture member
        const WidgetLambdas* widget = this;
        filters.push_back
            (
                [widget](int value) { return value % widget->divisor == 0; }
        );

        //ok, capture variable
        int divisorWidget = divisor;
        filters.push_back
            (
                [divisorWidget](int value) { return value % divisorWidget == 0; }
        );

        //ok, capture variable
        filters.push_back
            (
                [=](int value) { return value % divisorWidget == 0; }
        );

        //C++14 capture copy member
        filters.push_back
            (
                [divisor2 = divisor](int value) { return value % divisor2 == 0; }
        );

    }

private:
    int divisor;                       // used in Widget's filter
};
class WidgetInt
{
public:

    //ok
    void Test1(IntFunction& intFunction)
    {
        intFunction = { [=](int value) { return value; } };
    }

    //ok
    void Test2(IntFunction& intFunction)
    {
        intFunction = { [this](int value) { return this->divisor; } };
    }

    //ok
    void Test3(IntFunction& intFunction)
    {
        int divisorWidget = divisor;
        intFunction = { [divisorWidget](int value) { return divisorWidget; } };
    }

    //ok
    void Test4(IntFunction& intFunction)
    {
        int divisorWidget = divisor;
        intFunction = { [=](int value) { return divisorWidget; } };
    }

    //ok
    void Test5(IntFunction& intFunction)
    {
        intFunction = { [divisor2 = divisor](int value) { return divisor2; } };
    }

    //KO!!! dangle variable
    void Test6(IntFunction& intFunction)
    {
        int divisorWidget = divisor;
        intFunction = { [&](int value) { return divisorWidget; } };
    }
    void WidgetInt::Init()
    {
        IntFunction intFunction;
        int resultValue = 0;

        //ok
        Test1(intFunction);
        resultValue = intFunction(1);

        //ok
        Test2(intFunction);
        resultValue = intFunction(2);

        //ok
        Test3(intFunction);
        resultValue = intFunction(3);

        //ok
        Test4(intFunction);
        resultValue = intFunction(4);

        //ok
        Test5(intFunction);
        resultValue = intFunction(5);

        //KO!!! dangle variable
        Test6(intFunction);
        resultValue = intFunction(5);
    }

private:
    int divisor = 99;
};

BEGIN_TEST(TestLambdas)
    {
        std::vector<int> container;
        container.push_back(0);
        container.push_back(1);
        container.push_back(2);
        container.push_back(3);
        container.push_back(4);
        container.push_back(5);
        container.push_back(6);

        int minValue = 4;
        int maxValue = 10;

        std::vector<int>::iterator it = std::find_if( container.begin()
                                                    , container.end()
                                                    , [minValue, maxValue](int val)
                                                        {
                                                            return minValue < val && val < maxValue;
                                                        }
                                                    );
    }

    {
        FilterContainer filters;                    // filtering funcs

        filters.push_back
        (                       // see Item 42 for
            [](int value) { return value % 5 == 0; }  // info on
        );

        filters.push_back(&FiltersFunction);
        filters.push_back(::FiltersFunction);
        filters.push_back(FiltersFunction);
        filters[0](1);
        filters[1](1);
        filters[2](1);
        filters[3](1);

        AddOperationReference(filters);
        AddOperationCopyValue(filters);
    }

    {
        WidgetInt w;
        w.Init();
    }

    {
		WidgetLambdas pw;
        std::function<bool()> func = [pw = std::move(pw)]
        {
            return pw.isValidated() && pw.isArchived();
        };
        bool b1 = func();
    }
END_TEST()