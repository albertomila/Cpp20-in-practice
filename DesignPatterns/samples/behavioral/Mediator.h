#pragma once
#include "stdafx.h"

namespace nsMediator
{
	class IMediatorListener
	{
	public:
		virtual void MediatorMessage(std::string& message) = 0;
	};


	class CMediator
	{
	public:
		void RegisterListener(IMediatorListener* client)
		{
			_clients.push_back(client);
		}

		void SendMessage(IMediatorListener* sender, std::string& message)
		{
			for (IMediatorListener* client : _clients)
			{
				if (client != sender)
				{
					client->MediatorMessage(message);
				}
			}
		}

	private:
		std::vector<IMediatorListener*> _clients;
	};


	class CClient : public IMediatorListener
	{
	public:
		CClient(CMediator* mediator)
			:_mediator(mediator)
		{
		}

		void SendMessage(std::string& message)
		{
			_mediator->SendMessage(this, message);
		}

		void MediatorMessage(std::string& message) override
		{

		}

	private:
		CMediator* _mediator;
	};

}

BEGIN_TEST(Mediator)
	using namespace nsMediator;

	CMediator mediator;
	CClient client1(&mediator);
	CClient client2(&mediator);
	CClient client3(&mediator);
	CClient client4(&mediator);
	CClient client5(&mediator);

	mediator.RegisterListener(&client1);
	mediator.RegisterListener(&client2);
	mediator.RegisterListener(&client3);
	mediator.RegisterListener(&client4);
	mediator.RegisterListener(&client5);

	client1.SendMessage(std::string("Hello"));

END_TEST()
