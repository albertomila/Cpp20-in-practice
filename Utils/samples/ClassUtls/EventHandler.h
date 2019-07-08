#pragma once
#include "EventArgs.h"
#include <map>
#include <typeinfo.h>

class TypeInfo
{
private:
	const type_info& _typeInfo;
public:
	explicit TypeInfo(const type_info& info) : _typeInfo(info) {};

	bool operator < (const TypeInfo& rhs) const
	{
		return _typeInfo.before(rhs._typeInfo) != 0;
	}

};











class HandlerFunctionBase
{
public:
	virtual ~HandlerFunctionBase() {};
	void exec(const Event* event) {call(event);}

private:
	virtual void call(const Event*) = 0;
};







template <class T, class EventT>
class MemberFunctionHandler : public HandlerFunctionBase
{
public:
	typedef void (T::*MemberFunc)(EventT*);
	MemberFunctionHandler(T* instance, MemberFunc memFn) : _instance(instance), _function(memFn) {};

	void call(const Event* event)
	{
		(_instance->*_function)(static_cast<EventT*>(event));
	}

private:
	T* _instance;
	MemberFunc _function;
};








class EventHandler
{
public:
	~EventHandler();
	void callEvent(const Event*);
	void callEvent();

	template <class T, class EventT>
	void AddEventListener(T*, void (T::*memFn)(EventT*));

private:
	typedef std::map<TypeInfo, HandlerFunctionBase*> Handlers;
	Handlers _handlers;
};










template <class T, class EventT>
void EventHandler::AddEventListener(T* obj, void (T::*memFn)(EventT*))
{
	_handlers[TypeInfo(typeid(EventT))]= new MemberFunctionHandler<T, EventT>(obj, memFn);
}