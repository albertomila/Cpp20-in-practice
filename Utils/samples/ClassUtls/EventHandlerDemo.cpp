#include "stdafx.h"
#include "EventHandler.h"

class Dummy : public EventHandler///////////////////////////STEP 0 you have to extend class to EventHandler
{
public:
	Dummy() 
	{
	}
	void walk()
	{
		this->callEvent();///////////////////////////STEP 3 FINAL, execute the event
		this->callEvent(new IntEventArgs(40));
		this->callEvent(new StringEventArgs("hello"));

		vector<float> v;
		v.push_back(0.0f);
		v.push_back(1.0f);
		v.push_back(2.0f);
		v.push_back(3.0f);
		this->callEvent(new VectorEventArgs<float>(v));
		this->callEvent(new ObjectEventArgs<Dummy*>(this));
	}
};


class Test
{
	Dummy obj;
public:
	Test()
	{
	}
	void Init()
	{
		obj.AddEventListener(this,&Test::onEventListener);///////////////////////////STEP 1 add listener to class
		obj.AddEventListener(this,&Test::onEventListenerInt);
		obj.AddEventListener(this,&Test::onEventListenerString);
		obj.AddEventListener(this,&Test::onEventListenerVector);
		obj.AddEventListener(this,&Test::onEventListenerGeneric);
		obj.walk();
	}
	
	void onEventListener(const Event* e)///////////////////////////STEP 2 function to get the event
	{

	}
	void onEventListenerInt(const IntEventArgs* e)
	{
	}
	void onEventListenerString(const StringEventArgs* e)
	{

	}
	void onEventListenerVector(const VectorEventArgs<float>* e)
	{

	}
	void onEventListenerGeneric(const ObjectEventArgs<Dummy*>* e)
	{

	}
};
/*
int main()
{
	std::cout << "=== Monster ===" << std::endl; 
	Test t;
	t.Init();
}*/