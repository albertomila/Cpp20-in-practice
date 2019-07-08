#pragma once
#include "stdafx.h"
using namespace std;

void RefPointers_Foo(int x){	cout << "1" << endl;	}
void RefPointers_Foo(int* x){	cout << "2" << endl;	}
void RefPointers_Foo(int** x){	cout << "3" << endl;	}
//void RefPointers_Foo(int &x){	cout << "5" << endl;	}

void Print(int *x)
{
	RefPointers_Foo(x);
	RefPointers_Foo(&x);

	int* y = (int*)&x;
	RefPointers_Foo(*y);
	RefPointers_Foo(y);
	RefPointers_Foo(&y);
}

int RefPointers_Inc(int& x)
{
	x++;
	return x;
}
int RefPointers_Inc2(int& x)
{
	++x;
	return x;
}

template<class T>
T minimum(const T& value1, const T& value2)
{
	return value1 < value2 ? value1 : value2;
}
enum TYPE_ERROR { UNKNOWN, DIV_BY_ZERO, ERROR2,ERROR3,ERROR4,MAX_ERRORS };

class ERRORS_UNKNOWN;
class ERRORS_DIV_BY_ZERO;
class ERRORS_ERROR2;
class ERRORS_ERROR3;
class ERRORS_ERROR4;


class Except
{
	
protected:
	std::string error_;
	Except() : error_(GetError()){}
	Except(std::string error) : error_(error){}
public:
	virtual const std::string GetError() throw() {return error_; }
};

template<TYPE_ERROR T>
struct Exception;

template<>
struct Exception<DIV_BY_ZERO> : Except
{
	Exception() : Except(GetError()){}
	static const std::string GetError() throw() {return "Error: divided by zero"; }
};

class ErrorMat
{
	TYPE_ERROR type_error_;
public:
    ErrorMat() : type_error_(UNKNOWN) {};
    ErrorMat(const TYPE_ERROR& type_error)
	{
		if(type_error_ < UNKNOWN && type_error_ >= MAX_ERRORS)
			type_error_ = UNKNOWN;
		else
			type_error_ = type_error;
	}
	typedef char char_string[100];
	static char_string type_errors[MAX_ERRORS];
	const char* reason() throw(){ return type_errors[type_error_];}
};

ErrorMat::char_string ErrorMat::type_errors[MAX_ERRORS] = 
{
	"Error: unknown error",
	"Error: divided by zero error",
	"Error: error2",
	"Error: error3",
	"Error: error4"
};


class RefPointers_Test
{
public:
	RefPointers_Test(){}
	void print(){}
	void const_print() const {}

	void ThrowTest()
	{
		int z = 0;
		if(z == 0)
		{
			throw Exception<DIV_BY_ZERO>();
		}
		int x = 1/z;
	}
	void ThrowException()
	{
		int z = 0;
		if(z == 0)
		{
			throw ErrorMat(DIV_BY_ZERO);
		}
		int x = 1/z;
	}
};

BEGIN_TEST(RefPointers)
	RefPointers_Test* test = new RefPointers_Test();

	try
	{
		test->ThrowTest();
		//test->ThrowException();
	}
	catch(ErrorMat e)
	{
		string error = e.reason();
	}/*
	catch(Exception<DIV_BY_ZERO> e)
	{
		string error = e.GetError();
	}*/
	catch(Except e)
	{
		string error = e.GetError();
		int x = 0;
		x = 0;
	}

	int m1 = 3;
	int m2 = 2;
	int m = minimum<int>(m1,m2);
	float m3 = minimum<float>(2.1f,2.2f);
	char m4 = minimum<char>('A','C'); 

	string m5 = "hola";
	string m6 = "holb";
	string m7 = minimum<string>(m5,m6);

	int h = 0;
	//3 2 1
	cout << RefPointers_Inc(h) << RefPointers_Inc(h) << RefPointers_Inc(h) << endl;
	
	h = 0;
	//3 2 1
	cout << RefPointers_Inc2(h) << RefPointers_Inc2(h) << RefPointers_Inc2(h) << endl;

	h = 0;
	//2 1 0
	cout << h++ << h++ << h++ << endl;

	h = 0;
	//3 3 3
	cout << ++h << ++h << ++h << endl;

	h = 0;
	//1 1 1
	cout << ++h << --h << ++h << endl;

	h = 0;
	//1 1 0
	cout << ++h << ++h << h-- << endl;

	int n1 = 0;
	int n2 = n1++;
	n1 = 0;
	int n3 = ++n1;
	n1 = 0;
	int n4 = (++n1)++;
	n1 = 0;
	int n5 = ++(++n1);



	int z1 = 1;
	const int z2 = 2;
	int *const z3 = new int(3);
	int *const z4 = &z1;
	const int * z5 = &z1;
	const int *const z6 = &z1;
	z1 = 1;
	//z2 = 2;			//error
	//z3 = new int(3);	//error
	//z4 = &z1;			//error
	z5 = &z1;
	//*z5 = 4;			//error
	//z6 = &z1;			//error


	int s1 = 1;
	int s2 = 2;
	int* s3 = &s2;
	s2 = s1;
	s1 = 3;
	int &s4 = s1;
	s4 = s2;

	
	int				 variable1 = 1;
	const int        constante1 = 2;
	const int&      referencia_a_constante = constante1;
 
	// &const es permitido pero innecesario. Por eso nunca se usa.
	//warning C4227: anachronism used: qualifiers on reference are ignored
	//	  int &const referencia_constante_a_variable = variable1;
	//const int &const referencia_constante_a_constante = constante1;

	


	int g1 = 1;
	int g2 = 2;
	int &g3 = g2;
	int *g4 = new int(7);
	g3 = g1;	//g3 = 2
	g3 = 2;		//g1 = 1
	g1 = 5;		//g3 = 5

	g3 = g2;	//g3 = 2
	g2 = 10;	//g3 = g2

	g3 = g2;	//g3 = 10
	g2 = 2;		//g3 = g2

	g3 = *g4;	//g3 = 7
	*g4 = 20;	//g3 = 7

	//const int &g3 = g1;
//	g3 = g1;
//	const int &const g4 = g4;
	//g4 = g1;

	int x = 10;
	RefPointers_Foo(x);
	RefPointers_Foo(&x);

	int* y = new int(20);
	RefPointers_Foo(*y);
	RefPointers_Foo(y);
	RefPointers_Foo(&y);

	int* z = &x;
	RefPointers_Foo(*z);
	RefPointers_Foo(z);
	RefPointers_Foo(&z);
	
	Print(&x);

			RefPointers_Test		t1;					//variable
	const	RefPointers_Test		t2;					//t1 constant
			RefPointers_Test*		t3 = new RefPointers_Test();	//pointer
	const	RefPointers_Test*		t4 = new RefPointers_Test();	//pointer to constant var
			RefPointers_Test* const t5 = new RefPointers_Test();	//constant pointer to var
	const	RefPointers_Test* const t6 = new RefPointers_Test();	//contant pointer to constant var

	t1.print();
	t1.const_print();

	//t2.print(); error
	t2.const_print();

	t3->print();
	t3->const_print();

	//t4->print(); error
	t4->const_print();
	
	t5->print();
	t5->const_print();
	//t5 = new RefPointers_Test(); error
	

			RefPointers_Test a1;					//variable
			RefPointers_Test const a2;					//t1 constant
			RefPointers_Test *a3 = new RefPointers_Test();	//pointer
			RefPointers_Test  const *a4 = new RefPointers_Test();	//pointer to constant var
			RefPointers_Test *const a5 = new RefPointers_Test();	//constant pointer to var
			RefPointers_Test  const	*const a6 = new RefPointers_Test();	//contant pointer to constant var

			/*
			a1.print();
			a2.print();
			a2 = a1;
			a3->print();
			a3 = a3;
			a4->print();
			a4 = a3;
			a5->print();
			a5 = a3;
			a6->print();
			*/

		  int			variable = 1;
	const int			constante = 2;
		  int*			puntero = &variable;
	const int*			puntero_a_constante = &constante;
		  int*	const	puntero_constante_a_variable = &variable;
	const int*	const	puntero_constante_a_constante = &constante;

	variable = 1;
	///////////////////////////////////////////////////////////

	//constante = 3; error
	///////////////////////////////////////////////////////////

	*puntero = variable;
	puntero = &variable;
	///////////////////////////////////////////////////////////

	//*puntero_a_constante = 3; error
	puntero_a_constante = &constante;
	puntero_a_constante = &variable;

	///////////////////////////////////////////////////////////
	//puntero_constante_a_variable = &variable; error
	*puntero_constante_a_variable = variable;

	///////////////////////////////////////////////////////////
	//puntero_constante_a_constante = &variable; error
	//*puntero_constante_a_constante = variable; error

	END_TEST()