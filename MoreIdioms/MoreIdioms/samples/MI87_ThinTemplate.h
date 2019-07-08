#pragma once
#include "stdafx.h"

// Not a template
class VectorBase 
{
    void insert (void *); 
    void *at (int index);
};

template <class T>
class Vector // Thin template 
    : VectorBase 
{
    inline void insert (T *t) 
    {
        VectorBase::insert (t);
    }
    inline T *at (int index) 
    {
        return static_cast<T*>(VectorBase::at(index));
    }
};

/* another example: 

template <class T> 
class CArrayFix : public CArrayFixBase //where CArrayFixBase does all the work
{
}

*/