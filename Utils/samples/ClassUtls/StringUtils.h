#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "windows.h"

using namespace std;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::vector;
using std::copy;
using std::find;
using std::basic_string;
using std::wstring;

class StringUtils {
public:
	static void ToUpperCase(std::string &str)
	{
		std::string temp;
		for (unsigned int i = 0; i < str.length(); i++)
		{
			temp += toupper(str[i]);
		}
		str = temp;
	}
	static void ToLowerCase(std::string &str)
	{
		std::string temp;
		for (unsigned int i = 0; i < str.length(); i++)
		{
			temp += tolower(str[i]);
		}
		str = temp;
	}
	static void Trim(std::string &str)
	{
		std::string temp;
		for (unsigned int i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ') temp += str[i];
		}
		str = temp;
	}
	static void Replace(std::string &str, char inReplace, char outReplace)
	{
		std::string temp;
		for (unsigned int i = 0; i < str.length(); i++)
		{
			if (str[i] == inReplace) temp += outReplace;
			else temp += str[i];
		}
		str = temp;
	}
	static LPCWSTR StringToLPCWSTR(const string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		LPCWSTR result = r.c_str();
		return result;
	}
		
	static bool cvtLPW2stdstring(string& s, LPCWSTR pw, UINT codepage = CP_ACP) {
		bool res = false;
		char* p = 0;
		int bsz;
		bsz = WideCharToMultiByte(codepage, 0, pw, -1, 0, 0, 0, 0);
			
		if(bsz > 0) {
			p = new char[bsz];
				
			int rc = WideCharToMultiByte(codepage, 0, pw, -1, p, bsz, 0, 0);
				
			if(rc != 0) {
				p[bsz-1] = 0;
				s = p;
				res = true;
			}
		}
			
		delete[] p;
			
		return res;
	}
		
	static bool stringToBool(const string str, bool& dest) {
		dest = (str == "true" ? true : false);
			
		return true;
	}
		
	template<typename T>
	static bool fromString(const string str, T& dest) {
		istringstream iss(str);
			
		return (iss >> dest != 0);
		//if(!iss.good()) {
		//}
	}
		
	static bool boolToString(const bool input, string& dest) {
		dest = (input ? "true" : "false");
			
		return true;
	}
		
	template<typename T>
	static bool toString(const T input, string& dest) {
		ostringstream oss;
		oss << input;
			
		dest = oss.str();
			
		return (input != 0);
	}
		
	template <class CType>
	static vector<basic_string<CType>> split(const basic_string<CType>& src, const CType delim) {
		vector<basic_string<CType>> v;
		basic_string<CType>::const_iterator p = src.begin();
		basic_string<CType>::const_iterator q = find(p, src.end(), delim);
			
		while(q != src.end()) {
			v.push_back(basic_string<CType>(p, q));
			p = q;
			q = find(++p, src.end(), delim);
		}
			
		if(p != src.end ()) {
			v.push_back(basic_string<CType>(p, src.end()));
		}
			
		return v;
	}
		
	template <class CType>
	static vector<basic_string<CType>> split(const basic_string<CType>& src) {
		return StringUtils::split(src, ' ');
	}
		
	static wstring stringToWString(const string s) {
		int len;
		int slength = (int) s.length() + 1;
			
		len = ::MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
			
		::MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		wstring r(buf);
			
		delete[] buf;
			
		return r;
	}
};