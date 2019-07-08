#pragma once
#include "stdafx.h"
#include <stdexcept>
#include <cassert>

//////////////////////////////////////////////////////////////////
struct CT_B 
{
    CT_B (const char* value) 
    { 
        throw std::runtime_error("CT_B Error"); 
    }
};

//////////////////////////////////////////////////////////////////
struct CT_C 
{
    CT_C (const char* value) 
    { 
        throw std::runtime_error("CT_C Error"); 
    }
};

//////////////////////////////////////////////////////////////////
class CT_A 
{
    CT_B b_;
    CT_C c_;
    enum TrackerType 
    { 
          NONE
        , ONE
        , TWO 
    };

public:
    CT_A( TrackerType tracker = NONE)
    try    // CT_A constructor try block.
        : b_((tracker = ONE, "hello")) // Can throw std::exception
        , c_((tracker = TWO, "world")) // Can throw std::exception
    {
        assert(tracker == TWO);
        // ... constructor body ...
    }

    catch (std::exception const & e)
    {
        if (tracker == ONE) 
        {
            std::cout << "CT_B threw: " << e.what() << std::endl;
        }
        else if (tracker == TWO) 
        {
            std::cout << "CT_C threw: " << e.what() << std::endl;
        }
        throw;
    }
};


BEGIN_TEST(ConstructionTracker)
    try 
    {
        CT_A a;
    }
    catch (std::exception const & e) 
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }
END_TEST()