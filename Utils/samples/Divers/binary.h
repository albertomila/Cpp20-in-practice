#pragma once
#include "stdafx.h"
#include <iostream>
#include <limits>
using namespace std;

BEGIN_TEST(Binary)
	char n1 = 0x00;
	char n2 = 0xFF;
	char n3 = ~n1;
	char n4 = ~n2;
	n1 = 0x01;

	unsigned int n5 = 1;
	n5 = n5 << 0x01;
	n5 = n5 >> 0x01;

	int n6 = 1;
	n6 <<= 0x01;
	n6 >>= 0x01;
	
	char n7 = 0x00;
	n7 = n7 + 0x01;
	for(int i = 0; i< 256; ++i)
	{
		cout << n7;
		n7 += 0x01;
	}

	
	int s1 = sizeof(__int8);

	int s21 = sizeof(short);
	int s2 = sizeof(__int16);

	int s3 = sizeof(int);
	int s41 = sizeof(long);
	int s6 = sizeof(int long);
	int s4 = sizeof(__int32);

	int s51 = sizeof(long long);
	int s5 = sizeof(__int64);

	__int64 m1 = numeric_limits<unsigned __int8>::min();
	__int64 m2 = numeric_limits<unsigned short>::min();
	__int64 m3 = numeric_limits<unsigned __int16>::min();
	__int64 m4 = numeric_limits<unsigned int>::min();
	__int64 m5 = numeric_limits<unsigned long>::min();
	__int64 m6 = numeric_limits<unsigned __int32>::min();
	__int64 m7 = numeric_limits<unsigned int long>::min();
	__int64 m8 = numeric_limits<unsigned __int64>::min();
	__int64 m9 = numeric_limits<unsigned long long>::min();

	__int64 m11 = numeric_limits<unsigned __int8>::max();
	__int64 m12 = numeric_limits<unsigned short>::max();
	__int64 m13 = numeric_limits<unsigned __int16>::max();
	__int64 m14 = numeric_limits<unsigned int>::max();
	__int64 m15 = numeric_limits<unsigned long>::max();
	__int64 m16 = numeric_limits<unsigned __int32>::max();
	__int64 m17 = numeric_limits<unsigned int long>::max();
	unsigned __int64 m18 = numeric_limits<unsigned __int64>::max();
	unsigned __int64 m19 = numeric_limits<unsigned long long>::max();

	
	unsigned __int8 d1 = 0xFF; 
	d1 >>= 4;
	d1 <<= 4;
	
	d1 = 0xFF; 
	d1 = (d1 >> 4) << 4;
	
	d1 = 0xFF; 
	d1 &= 0xF0;
	
	/*
	__int8	=>	1 byte = 8 bits
	4 bits	=>	16 values
	0xFF	=>	4 bits + 4 bits
	*/

	unsigned __int32 rgba = 0xBD7520FF, arbg = 0x0000000;
	unsigned __int32 r = 0x00000000, g= 0x00000000, b= 0x00000000, a=0x00000000;
	r = (rgba >> 24) & 0xFF;
	g = (rgba >> 16) & 0xFF;
	b = (rgba >> 8)  & 0xFF;
	a = rgba & 0xFF;

	arbg |= a << 24;
	arbg |= r << 16;
	arbg |= b << 8;
	arbg |= g;

	END_TEST()