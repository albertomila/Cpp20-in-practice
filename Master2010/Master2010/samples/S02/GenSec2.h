#pragma once
#include "stdafx.h"
#include "Incopiable.h" // je suppose que c'est évident

class GenSeq2
    : Incopiable
{
public:
    typedef int value_type;

private:
    class Impl; // on introduit le nom sans rien dire d'autre
    Impl *p_;
    static Impl *Creer();
    static void Liberer(const Impl *) throw();
public:
    GenSeq2()
       : p_(Creer())
    {
    }
    ~GenSeq2() throw()
    { 
		Liberer(p_); 
	}
	value_type prochain();
};

BEGIN_TEST(GenSeq2Test)
	GenSeq2* genSeq2 = new GenSeq2();
	int x = genSeq2->prochain();
END_TEST()