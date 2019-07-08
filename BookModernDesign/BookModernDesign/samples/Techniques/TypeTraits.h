#include "stdafx.h"

class MyType
{
};

template <int v>
struct TypeTraits_Int2Type
{
    enum { value = v };
};

template <typename T> 
struct SupportsBitwiseCopy
{
    enum { result = TypeTraits<T>::isStdFundamental };
};

template<> 
struct SupportsBitwiseCopy<MyType>
{
    enum { result = true };
};

enum CopyAlgoSelector { Conservative, Fast };

// Conservative routine-works for any type
template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result,
    TypeTraits_Int2Type<Conservative>)
{
    for (; first != last; ++first, ++result)
        *result = *first;
    return result;
}

// Fast routine-works only for pointers to raw data
template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result,
    TypeTraits_Int2Type<Fast>)
{
    const size_t n = last-first;
    BitBlast(first, result, n * sizeof(*first));
    return result + n;
}


template <typename InIt, typename OutIt>
OutIt Copy(InIt first, InIt last, OutIt result,
    TypeTraits_Int2Type<true>)
{
    typedef TypeTraits<InIt>::PointeeType SrcPointee;
    typedef TypeTraits<OutIt>::PointeeType DestPointee;
    
    enum { useBitBlast =        TypeTraits<InIt>::isPointer 
                            &&  TypeTraits<OutIt>::isPointer
                            &&  SupportsBitwiseCopy<SrcPointee>::result
                            &&  SupportsBitwiseCopy<DestPointee>::result
                            &&  sizeof(SrcPointee) == sizeof(DestPointee) 
        };

    return CopyImpl(first, last, TypeTraits_Int2Type<useBitBlast>);
}

BEGIN_TEST(TypeTraits)
END_TEST()