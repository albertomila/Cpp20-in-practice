#include "stdafx.h"

//trick 1

template<typename T>       // declaration only for TD;
class TD;                  // TD == "Type Displayer"

BEGIN_TEST(TestDeducedTypes)
    int x;
    const int* y = nullptr;

    //using error output to get the type name
    //TD<decltype(x)> xType;     // elicit errors containing
    //TD<decltype(y)> yType;     // x's and y's types
END_TEST()

//using C++ to get the type name
//typeid(x).name()

//Using boost to get the type name.
//#include <boost/type_index.hpp>
//boost::typeindex::type_id_with_cvr<T>().pretty_name()
//boost::typeindex::type_id_with_cvr<decltype(param)>().pretty_name()