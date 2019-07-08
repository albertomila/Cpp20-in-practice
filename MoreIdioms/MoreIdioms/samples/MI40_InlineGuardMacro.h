#pragma once
#include "stdafx.h"

#ifdef _INLINE_
#define INLINE inline // Define INLINE as inline (the keyword)
#else 
#define INLINE // INLINE is defined as empty string
#endif

class Test
{
public:
	INLINE void func();
};


BEGIN_TEST(InlineMacro)
	Test t;
	t.func();
END_TEST()