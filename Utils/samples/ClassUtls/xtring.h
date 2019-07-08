#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "../MetaProg/LexicalCast.h"
using namespace std;
using std::find;

class xtring : public string
{
public:
	xtring(void);
	xtring(char *value);
	xtring(const char *value);

	template <class T> 
	xtring(T value) : string(xtring::ToString<T>(value)){}

	template <class T> 
	xtring(T *value) : string(xtring::ToString<T>(*value)){}
	
	template <class T> 
	xtring(T *value, const int& length, const string &sep = "") : string("")
	{
		for(T* itt = value; itt != value+length; ++itt)
		{
			*this += xtring::ToString<T>(*itt);
			if(itt != value+length - 1)
				*this += sep;
		}
	}

	~xtring(void);
	
	string GetString() const;
	xtring ToUpperCase();
	xtring ToLowerCase();
	xtring Trim();
	xtring Replace(char inReplace, char outReplace);

	bool	ToBool();
	float	ToFloat();
	double	ToDouble();
	short	ToShort();
	int		ToInt();
	long	ToLong();
	
	template <class T>
	static string ToString(const T &value)
	{		
		return lexical_casts<string>(value);	
	}
	
	vector<string> split(const char &delim);
	vector<string> split();
};



	/*
	char v3[100] = "alo alo yeah yeah men men\0";
	xtring x3 = v3;
	
	char* v1 = "alo alo yeah yeah men men\0";
	xtring x1 = v1;
	
	string v2 ="alo alo yeah yeah men men\0";
	xtring x2 = v2;
	
	int v4 = 4;
	xtring x4 = v4;
	xtring x5(5);
	xtring x6(5.7f);
	xtring x7('A');
	xtring x8("AAAA");
	xtring x9(string("BBBB"));

	xtring x15 = 5;
	xtring x16 = 5.7f;
	xtring x17 = 'A';
	xtring x18 = "AAAA";
	xtring x19 = string("BBBB");

	x15 = 5;
	x16 = 5.7f;
	x17 = 'A';
	x18 = "AAAA";
	x19 = string("BBBB");
	xtring x20 = x18;
	
	int v30 = 4;
	xtring x30;
	x30 = x30.ToString(v30);
	int *v31 = new int[5];
	v31[0] = 0;
	v31[1] = 1;
	v31[2] = 2;
	v31[3] = 3;
	v31[4] = 4;
	xtring x31(v31,5,"-");
	
	int v32[5] = {0,1,2,3,4};
	xtring x32(v32,5,"-");
	*/