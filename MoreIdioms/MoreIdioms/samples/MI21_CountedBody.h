
#pragma once
#include "stdafx.h"
///////////////////////////////////////////////////////////////
//namespace 
//{ // anonymous namespace
    class StringRep 
    {
        friend class CString;
    public:
        StringRep(const char *s)
            : count(1) 
        {
            SafeStrCopy(rep=new char[strlen(s)+1], s);
        }
        ~StringRep() 
        {
            delete [] rep; 
        }

        int count; 
        char *rep;
    };
//} // anonymous namespace

///////////////////////////////////////////////////////////////
class CString 
{
public:
    CString()
        :rep(new StringRep("")) 
    {

    }

    CString(const CString &s)
        : rep(s.rep) 
    { 
        rep->count++; 
    }

    CString &operator=(const CString &s)
    {
        CString temp(s); 
        temp.swap(*this); // copy-and-swap idiom
        return *this;
    }
    ~CString() 
    { // StringRep deleted only when the last handle goes out of scope.
        if(rep && --rep->count <= 0)
        {
            delete rep;
        }
    }

    CString(const char *s)
        : rep(new StringRep(s)) 
    {
    }

    void swap (CString & s) throw ()  
    {
        std::swap(this->rep, s.rep);
    }

private:
    StringRep *rep;
};

BEGIN_TEST(CountedBody)
	CString a = "hello";
	CString b = "world";
    a = b;

	END_TEST()