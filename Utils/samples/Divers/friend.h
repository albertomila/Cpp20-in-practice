#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;
 
class Friend_B
{
	friend class Friend_A;
	int pos_;
public:
	Friend_B(const int& pos) : pos_(pos)
	{}
	int GetPos() const
	{
		return pos_;
	}
};

class Friend_A 
{
  private:
    friend void Ver(Friend_A); // "Ver" es amiga de la clase Friend_A	
    int a;
  public:
    Friend_A(int i=0) : a(i) {}
    void Ver() { cout << a << endl; }
	
	void foo(Friend_B b)
	{
		int pos = b.GetPos();
		int pos2 = b.pos_;
	}
};
 
inline void Ver(Friend_A Xa) 
{
   // La función Ver puede acceder a miembros privados
   // de la clase Friend_A, ya que ha sido declarada "amiga" de Friend_A
   cout << Xa.a << endl;
}

BEGIN_TEST(Friend)
   Friend_A Na(10);
 
   Ver(Na);  // Ver el valor de Na.a
   Na.Ver(); // Equivalente a la anterior

   END_TEST()