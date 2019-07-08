#pragma once
#include "stdafx.h"
using namespace std;


bool foo(const string& s, const bool b)
{
	cout << s << endl;
	return b;
}

union unCoor3D { 
   struct { 
      int X, Y, Z; 
   }; 
   int Coor[3]; 
};
union UnionExample { 
   int A; 
   char B; 
   double C; 
};

BEGIN_TEST(UnionReinterpretCast)
	unCoor3D p;
	p.X =3;

	UnionExample union1 = {10}; // int
	UnionExample union2 = {'a'}; // char
	UnionExample union3 = {10.02}; // double

	//////low float precisition
	float a = 12335545621232154;
	a = a + 1; 
	a = a - 12335545621232154;

	int b = 12335545621232154;
	b = b + 1; 
	b = b - 12335545621232154;

	//consecutive numbers
	enum tipohoras { una=1, dos, tres, cuatro, cinco, 
  seis, siete, ocho, nueve, diez, once, 
  doce, trece=1, catorce, quince, 
  dieciseis, diecisiete, dieciocho,
  diecinueve, veinte, ventiuna, 
  ventidos, ventitres, venticuatro = 0};

	//analyser order
	if((foo("1",true) || foo("2",true)) && foo("3",true))
	{
		int x = 0;
		x = 0;
	}
	//out = 1,3
	
	//analyser order
	if((foo("1",true) | foo("2",true)) & foo("3",true))
	{
		int x = 0;
		x = 0;
	}
	//out = 1,2,3




	
	int *x = new int(5);
	char *y = "hola";
	float *f = new float(1.2f);

	void *n = (void*)x;
	n = (void*)y;
	n = (void*)f;

	void *m = reinterpret_cast<void*>(x);
	int *x1 = reinterpret_cast<int*>(m);
	
	m = reinterpret_cast<void*>(y);
	char *x2 = reinterpret_cast<char*>(m);

	m = reinterpret_cast<void*>(f);
	float *x3 = reinterpret_cast<float*>(m);

	float **z; 
	z = new float*[10];
	for(int i=0; i<10; ++i)
	{
		z[i] = new float[10];
	}

	float result = 25.0f / 5.0f * 3.0f;
	int res = 25 / 5 * 3;
	cout << 25 / 5 * 3 << endl;

	END_TEST()