#pragma once
#include "stdafx.h"

#define CREATE_MEMBER_DETECTOR(X)                                                   \
template<typename T> class Detect_##X {                                             \
    struct Fallback { int X; };                                                     \
    struct Derived : T, Fallback { };                                               \
                                                                                    \
    template<typename U, U> struct Check;                                           \
                                                                                    \
    typedef char ArrayOfOne[1];                                                     \
    typedef char ArrayOfTwo[2];                                                     \
                                                                                    \
    template<typename U> static ArrayOfOne & func(Check<int Fallback::*, &U::X> *); \
    template<typename U> static ArrayOfTwo & func(...);                             \
  public:                                                                           \
    typedef Detect_##X type;                                                        \
    enum { value = sizeof(func<Derived>(0)) == 2 };                                 \
};
 
CREATE_MEMBER_DETECTOR(first);
CREATE_MEMBER_DETECTOR(second);
/*
int main(void)
{
  typedef std::pair<int, double> Pair;
  std::cout << ((Detect_first<Pair>::value && Detect_second<Pair>::value)? "Pair" : "Not Pair");
}
*/

#define CREATE_METHOD_DETECTOR(X) \
template<typename T, typename RESULT, typename ARG1, typename ARG2>         \
class HasMember_##X                                                         \
{                                                                           \
    template <typename U, RESULT (U::*)(ARG1, ARG2)> struct Check;          \
    template <typename U> static char func(Check<U, &U::X> *);              \
    template <typename U> static int func(...);                             \
public:                                                                     \
    enum { value = sizeof(func<T>(0)) == sizeof(char) };                    \
};

#define HAS_METHOD(X, T, RESULT, ARG1, ARG2)                                \
    HasMember_##X<T, RESULT, ARG1, ARG2>::value

class MemberDetector_CTest
{
public:
    float Create( int x, int y )
    {
        return 0.f;
    }
};

CREATE_METHOD_DETECTOR(Create);


BEGIN_TEST(MemberDetector)
    std::cout << ((HasMember_Create<MemberDetector_CTest, float, int, int>::value)? "Has member" : "Doesn't have");

END_TEST()