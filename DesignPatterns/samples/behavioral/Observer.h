#pragma once
#include "stdafx.h"

namespace nsObserver
{
	class IObserverListener
	{
	public:
		virtual void Notify() = 0;
	};

	class CObject : public IObserverListener
	{
		void Notify() override
		{

		}
	};

	class CObservers
	{
	public:
		void RegisterListener(IObserverListener* client)
		{
			_clients.push_back(client);
		}

		void Notify()
		{
			for (IObserverListener* client : _clients)
			{
				client->Notify();
			}
		}

	private:
		std::vector<IObserverListener*> _clients;
	};

}

BEGIN_TEST(Observer)
	using namespace nsObserver;

	CObservers observers;
	CObject client1;
	CObject client2;
	CObject client3;
	CObject client4;
	CObject client5;

	observers.RegisterListener(&client1);
	observers.RegisterListener(&client2);
	observers.RegisterListener(&client3);
	observers.RegisterListener(&client4);
	observers.RegisterListener(&client5);

	observers.Notify();

END_TEST()
