#include "stdafx.h"
#include <vector>

class WidgetBraces {
public:
    WidgetBraces()
        : m_x(0)
        , m_y(0)
    {}
    WidgetBraces(int i, bool b) 
        : m_x(i)
        , m_y(b)
    {}                          
    WidgetBraces(int i, double d)
        : m_x(i)
        , m_y(d)
    {}                                    

    WidgetBraces(std::initializer_list<long double> il)   // added
    {
        if (il.size() > 0)
        {
            m_x = *(il.begin());
            m_y = *(il.begin() + 1);
        }
    }


    operator float() const                          // convert to float
    {
        return 99.9f;
    }

    int m_x;
    int m_y;
};

BEGIN_TEST(TestBraces)
    {
        int x1 = 1;
        int x2 = 2;
        int x3 = 3;

        std::vector<int> v{ x1, x2, x3 }; // v's initial content is 1, 3, 5
    }

    {
        std::vector<int> v1(10, 20);  // use non-std::initializer_list
                                      // ctor: create 10-element
                                      // std::vector, all elements have
                                      // value of 20

        std::vector<int> v2{ 10, 20 };  // use std::initializer_list ctor:
                                        // create 2-element std::vector,
                                        // element values are 10 and 20
    }

    {
        WidgetBraces w01;            // calls default ctor

        WidgetBraces w02{};          // also calls default ctor

        WidgetBraces w03();          // most vexing parse! declares a function!

        WidgetBraces w04( {} );        // calls std::initializer_list ctor
                              // with empty list

        WidgetBraces w05{ {} };        // ditto

        WidgetBraces w1(10, true);     // uses parens and, as before,
                                 // calls first ctor

        WidgetBraces w2{ 10, true };     // uses braces, but now calls
                                   // std::initializer_list ctor
                                   // (10 and true convert to long double)

        WidgetBraces w3(10, 5.0);      // uses parens and, as before,
                                 // calls second ctor

        WidgetBraces w4{ 10, 5.0 };      // uses braces, but now calls
                                   // std::initializer_list ctor
                                   // (10 and 5.0 convert to long double)

        WidgetBraces w5(w4);               // uses parens, calls copy ctor

        WidgetBraces w6{ w4 };               // uses braces, calls
                                       // std::initializer_list ctor
                                       // (w4 converts to float, and float
                                       // converts to long double)

        WidgetBraces w7(std::move(w4));    // uses parens, calls move ctor

        WidgetBraces w8{ std::move(w4) };    // uses braces, calls
                                       // std::initializer_list ctor
                                       // (for same reason as w6)
    }
END_TEST()
