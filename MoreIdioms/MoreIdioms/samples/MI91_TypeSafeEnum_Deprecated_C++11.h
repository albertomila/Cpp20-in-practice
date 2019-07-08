#pragma once
#include "stdafx.h"
template<typename def, typename inner = typename def::type>
class safe_enum : public def
{
    typedef typename def::type type;
    inner val;

public:

    safe_enum(type v) : val(v) 
    {
    }

    inner underlying() const 
    { 
        return val; 
    }

    friend bool operator == (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val == rhs.val; }
    friend bool operator != (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val != rhs.val; }
    friend bool operator <  (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val <  rhs.val; }
    friend bool operator <= (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val <= rhs.val; }
    friend bool operator >  (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val >  rhs.val; }
    friend bool operator >= (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val >= rhs.val; }
};

struct color_def 
{
    enum type { red, green, blue };
};
typedef safe_enum<color_def> color;

struct shape_def 
{
    enum type { circle, square, triangle };
};
typedef safe_enum<shape_def, unsigned char> shape; // unsigned char representation

BEGIN_TEST(TypeSafeEnum)
    color c = color::red;
    //bool flag1 = (c >= shape::triangle); // Compiler error.
    bool flag2 = (c >= color::red); // ok

    shape s( shape::triangle );
    unsigned char cha = s.underlying();


	enum class EType1 : unsigned int
	{
		EType1_Value1,
		EType1_Value2,
		EType1_Value3
	};

	enum class EType2 : unsigned int
	{
		EType2_Value1,
		EType2_Value2,
		EType2_Value3
	};

	EType1 type1 = EType1::EType1_Value1;
	//EType2 type2 = EType1::EType1_Value1; //type safe already in C++11


	END_TEST()

/*
Minimized version

template<typename def>
class safe_enum
{
    def val;

public:

    safe_enum(def v) : val(v) 
    {
    }

    def underlying() const 
    { 
        return val; 
    }

    friend bool operator == (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val == rhs.val; }
    friend bool operator != (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val != rhs.val; }
    friend bool operator <  (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val <  rhs.val; }
    friend bool operator <= (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val <= rhs.val; }
    friend bool operator >  (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val >  rhs.val; }
    friend bool operator >= (const safe_enum & lhs, const safe_enum & rhs) { return lhs.val >= rhs.val; }
};

enum color_def { red, green, blue };
typedef safe_enum<color_def> color;

enum shape_def { circle, square, triangle };
typedef safe_enum<shape_def> shape; // unsigned char representation

int main(void)
{
    color c = red;
    bool flag1 = (c >= triangle); // Compiler error.
    bool flag2 = (c >= red); // ok
}
*/