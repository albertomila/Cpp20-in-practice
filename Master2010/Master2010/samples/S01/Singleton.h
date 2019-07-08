#pragma once
#include "stdafx.h"
#include "samples/S02/Incopiable.h"

template <class S>
class Singleton : public Incopiable
{
public:
    static S & get()
    {
        static S singleton;
        return singleton;
    }
};
   
/*
class X
{
   static X *singleton;
   X () {}
   X (const X &);
   void operator=(const X &);
public:
   static X *get()
   {
      return singleton;
   }
};
X *X::singleton = new X;

static X *singleton;
static X *get()
{
    return singleton;
}

static X singleton;
static X *get() throw() 
{ 
	return &singleton; 
}


static X singleton;
static X &Getsingleton () throw()
{ 
	 return singleton; 
}
*/