#include "stdafx.h"
#include "EventHandler.h"

EventHandler::~EventHandler()
{
	Handlers::iterator it = _handlers.begin();
	while(it != _handlers.end())
	{
		delete it->second;
		++it;
	}
	_handlers.clear();
}

void EventHandler::callEvent(const Event* ev)
{
	Handlers::iterator it = _handlers.find(TypeInfo(typeid(*ev)));
	if(it != _handlers.end())
	{
		it->second->exec(ev);
	}
	delete ev;
}
void EventHandler::callEvent()
{
	Event* ev = new Event();
	Handlers::iterator it = _handlers.find(TypeInfo(typeid(*ev)));
	if(it != _handlers.end())
	{
		it->second->exec(ev);
	}
	delete ev;
}