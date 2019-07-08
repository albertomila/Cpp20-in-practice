#pragma once
#include "stdafx.h"
/////////////////////////////////////////////////////////static cast
/*
Base*		<—	(Dérivée*)e
Dérivée*	<—	(Base*)e

struct B { 
	int pos_;
	B(int pos) : pos_(pos)
	{}
};
struct D0 : public B { 
	int vel_;
	D0() : B(0), vel_(3){}
};
struct D1 : public B { 
	D1() : B(1){}
};
struct D : public D0, public D1 {
};

void f (D *pD)
{
//   B *pB = pD; // illégal car ambigü: il y a deux B dans un D!
   B* pB = static_cast<D1*>(pD); // Ok, ambiguité levée (aussi Ok
                                 // si on passe par un D0*
}
void f2 (B* pB, D0* pD)
{
   D0* pD2 = static_cast<D0*>(pB); // peut être risqué, selon le
                                 // contexte. Était «(D*)pB»
   B* pB2 = static_cast<B*>(pD); // sécuritaire, implicite
   D0* pD3 = static_cast<D0*>(pB2); // peut être risqué, selon le
}
void f3 (B* pb)
{
   D0* pd1 = static_cast<D0*>(pb); // OK si pb est un D*, mais
                                 // fort dangereux sinon
}
int main()
{
	 D* d = new D();
	 f(d);
	 delete d;

	 D0* d0 = new D0();
	 D1* d1 = new D1();
	 B* b = new B(2);
	 f2(d1,d0);
	 f2(b,d0);

	 f3(d0);
	return 0;
}
*/


/////////////////////////////////////////////////////////dynamic cast
/*
Dérivée* <— (Base*)e
*/

/*
#include <typeinfo.h>
#include <iostream>

class Shape {
public:
   virtual void virtualfunc() const {}
};

class Circle: public Shape {
public:
   virtual void virtualfunc() const {}
};

using namespace std;
int main() {
   Shape shape_instance;
   Shape& ref_shape = shape_instance;
   try 
   {
      Circle& ref_circle = dynamic_cast<Circle&>(ref_shape); //ko
   }
   catch (bad_cast b) 
   {
      cout << "Caught: " << b.what();
   }


   Circle circle_instance;
   Circle& ref_circle = circle_instance;
   try 
   {
		Shape& ref_shape = dynamic_cast<Shape&>(ref_circle);	//ok
   }
   catch (bad_cast b) 
   {
      cout << "Caught: " << b.what();
   }
}
*/

/////////////////////////////////////////////////////////reinterpret cast -> seulement conversions de pointeurs
/*
unsigned long __stdcall AffichageCyclique(void *p)
{
   bool *pArret = reinterpret_cast<bool *>(p);
   return 0;
}

int main() 
{
}
*/


/////////////////////////////////////////////////////////const cast - const ou volatile to const ou volatile

// on se tape la job de l'enrober proprement
inline void Internal_strcpy(char* dest, const char* source)
{
   // appel à la fonction rapide, en cachette. Aussi vite
   // que possible, sans blagues.
   SafeStrCopy(dest, const_cast<char*>(source));
}

BEGIN_TEST(Casting)
	const char cc = 'a'; // constante de type char
	const char* pcc = &cc; // légal
	const char **ppcc = &pcc;  // légal
	void* pv = ppcc; // légal; eh oui, on peut «caster» implicitement
					 // n'importe quoi en «void*». C'est la vie. Mais
					 // on vient de perdre notre «const»!
	char **ppc = (char**)pv; // ouch!
							 //char **ppc =  static_cast<char**>(pv);
							 //char **ppc =  reinterpret_cast<char**>(pv);


	char a1 = cc;
	char a2 = *pcc;
	char a3 = **ppcc;
	char a4 = **ppc;
	char **a5 =  reinterpret_cast<char**>(pv);
	char a6 = **a5;
	char **a7 =  static_cast<char**>(pv);

	const char* s1 = "123456789 123456789 123456789 123456789 123456789 ";
	char* s2 = new char();
	Internal_strcpy(s2, s1);
	/*
	char* str1 = "hello";
	const char* str2 = "mila";
	//const char* str3 = strcpy("hello","mila");
	char *maxPtr1 = const_cast<char*>(str2);

	char* x1="Sample string";
	char x2[40];
	strcpy (x2,x1);

	char s1[] = "h";
	char s2[] = "g";
	char *maxPtr = const_cast< char * >(s1);
	*/

	END_TEST()
