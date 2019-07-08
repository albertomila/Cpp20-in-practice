#pragma once
#include "stdafx.h"

class ScopeGuard
{
public:
    ScopeGuard () 
        : engaged_ (true) 
    { /* Acquire resources here. */ }

    ~ScopeGuard ()  
    { 
        if (engaged_) 
        { 
			release();
		}
    }
    void release () 
    { 
        engaged_ = false; 
        /* Resources no longer be released */ 
    }
private:
    bool engaged_;
};

void some_init_function ()
{
    ScopeGuard guard;
    // ...... Something may throw here. If it does we release resources.
    //guard.release(); // Resources will not be released in normal execution.
}

BEGIN_TEST(ScopeGuardTest)
    some_init_function();

END_TEST()