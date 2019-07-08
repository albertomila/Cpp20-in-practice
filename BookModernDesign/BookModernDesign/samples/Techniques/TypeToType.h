#include "stdafx.h"
#include <string>


class TypeToType_Widget
{
public:
    template<class T>
    TypeToType_Widget( const T& arg)
    {
    }
};


template <typename T>
struct Type2Type
{
    typedef T OriginalType;
};
// An implementation of Create relying on overloading
//      and Type2Type
template <class T, class U>
T* Create(const U& arg, Type2Type<T>)
{
    return new T(arg);
}
template <class U>
TypeToType_Widget* Create(const U& arg, Type2Type<TypeToType_Widget>)
{
    return new TypeToType_Widget(arg);
}


BEGIN_TEST(TypeToType)
    std::string* pStr = Create("Hello", Type2Type<std::string>());
    delete pStr;

    TypeToType_Widget* pW = Create(100, Type2Type<TypeToType_Widget>());
	delete pW;
END_TEST()