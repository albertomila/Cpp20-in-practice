#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Event
{
	public:
		virtual ~Event() {};
};

class IntEventArgs : public Event
{
	private:
		int mValue;
	public:
		IntEventArgs(int value) : mValue(value){};
		int getValue() const	{return mValue;}
};
class BoolEventArgs : public Event
{
	private:
		bool mValue;
	public:
		BoolEventArgs(bool value) : mValue(value){};
		bool getValue() const	{return mValue;}
};

class FloatEventArgs : public Event
{
	private:
		float mValue;
	public:
		FloatEventArgs(float value) : mValue(value){};
		float getValue() const	{return mValue;}
};

class StringEventArgs : public Event
{
	private:
		string mValue;
	public:
		StringEventArgs(string value) : mValue(value){};
		string getValue() const	{return mValue;}
};

template <class T>
class VectorEventArgs : public Event
{
	private:
		vector<T> mValue;
	public:
		VectorEventArgs(vector<T> value) : mValue(value){};
		vector<T>  getValue() const	{return mValue;}
};

template <class T>
class ObjectEventArgs : public Event
{
	private:
		T mValue;
	public:
		ObjectEventArgs(T value) : mValue(value){};
		T  getValue() const	{return mValue;}
};