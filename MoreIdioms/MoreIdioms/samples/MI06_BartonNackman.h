#pragma once
#include "stdafx.h"

///////////////////////////////////////////////////////////////////////
template<typename T>
class List 
{
public:
    List( T& value ) 
        : m_value( value ) 
    {
    }

    const T& GetValue() const{ return m_value; }

    friend bool operator==( const List<T> & lft,
                            const List<T> & rgt) 
    {
        return lft.GetValue() == rgt.GetValue();
    }

private:
    T m_value;
};

///////////////////////////////////////////////////////////////////////
template<typename T>
class EqualityComparable 
{
public:
    friend bool operator==(const T & lft, const T & rgt) 
    { 
        return lft.equalTo(rgt); 
    }
    friend bool operator!=(const T & lft, const T & rgt) 
    { 
        return !lft.equalTo(rgt); 
    }
};

class ValueType : private EqualityComparable<ValueType> 
{
public:
    ValueType( int x )
        : m_x( x )
    {
    }
    bool equalTo(const ValueType & other) const
    {
        return m_x == other.m_x;
    }

private:
    int m_x;
};


BEGIN_TEST(BartonNackMark)
    ValueType value1( 5 );
    List<ValueType> list1( value1 );

    ValueType value2( 97 );
    List<ValueType> list2( value2 );

    bool isEqual =( list1 == list2 );

END_TEST()