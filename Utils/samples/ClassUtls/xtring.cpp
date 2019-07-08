#include "stdafx.h"
#include "xtring.h"


xtring::xtring(void) : string(string())
{
}

xtring::xtring(char *value) : string(value)
{
}

xtring::xtring(const char *value) : string(value)
{
}

xtring::~xtring(void)
{
}

string xtring::GetString() const
{
	return *this;
}

xtring xtring::ToUpperCase()
{
	xtring temp;
	for (unsigned int i = 0; i < this->length(); i++) 
		temp += toupper((*this)[i]);
	return temp;
}
	
xtring xtring::ToLowerCase()
{
	xtring temp;
	for (unsigned int i = 0; i < this->length(); i++)
		temp += tolower((*this)[i]);
	return temp;
}

xtring xtring::Trim()
{
	xtring temp;
	for (unsigned int i = 0; i < this->length(); i++)
		if ((*this)[i] != ' ') temp += (*this)[i];
	return temp;
}

xtring xtring::Replace(char inReplace, char outReplace)
{
	xtring temp;
	for (unsigned int i = 0; i < this->length(); i++)
		if ((*this)[i] == inReplace) temp += outReplace;
		else temp += (*this)[i];
	return temp;
}

bool	xtring::ToBool(){	return lexical_cast<bool>(*this);	}
float	xtring::ToFloat(){	return lexical_cast<float>(*this);	}
double	xtring::ToDouble(){	return lexical_cast<double>(*this);	}
short	xtring::ToShort(){	return lexical_cast<short>(*this);	}
int		xtring::ToInt(){	return lexical_cast<int>(*this);	}
long	xtring::ToLong(){	return lexical_cast<long>(*this);	}
	
vector<string> xtring::split(const char &delim) 
{
	vector<string> v;
	string::iterator p = this->begin();
	string::iterator q = std::find(p,  this->end(), delim);

	while(q !=  this->end()) 
	{
		v.push_back(string(p, q));
		p = q;
		q = std::find(++p,  this->end(), delim);
	}
			
	if(p !=  this->end ()) {
		v.push_back(string(p,  this->end()));
	}
			
	return v;
}
		
vector<string> xtring::split() 
{
	return split(' ');
}