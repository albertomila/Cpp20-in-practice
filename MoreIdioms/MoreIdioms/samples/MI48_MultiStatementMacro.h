#pragma once
#include "stdafx.h"

#define MACRO(arg1, arg2)   \
    do {                    \
        int x = arg1;       \
        x+=arg2;            \
    } while(0)    /* (addind do while(0) foces to put trailing ';' on the client side ) */



BEGIN_TEST(MultiStatementMacro)
    if( true )
        MACRO( 10, 20 );
    else
        int x = 0;
END_TEST()