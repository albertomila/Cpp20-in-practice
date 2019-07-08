#pragma once
#include "stdafx.h"

namespace nsVisitor
{
	class IVisitorListener
	{
	public:
		virtual void Visit(IVisitorListener* sender) = 0;
	};


	class CVisitor
	{
	public:
		void RegisterListener(IVisitorListener* client)
		{
			_clients.push_back(client);
		}

		void Visit(IVisitorListener* sender)
		{
			for (IVisitorListener* client : _clients)
			{
				if (client != sender)
				{
					client->Visit(sender);
				}
			}
		}

	private:
		std::vector<IVisitorListener*> _clients;
	};


	class CClient : public IVisitorListener
	{
	public:
		CClient(CVisitor* mediator)
			:_mediator(mediator)
		{
		}

		void ExecuteOperation()
		{
			_mediator->Visit(this);
		}

		void Visit(IVisitorListener* client) override
		{

		}

	private:
		CVisitor* _mediator;
	};

}

BEGIN_TEST(Visitor)
	using namespace nsVisitor;

	CVisitor vistorManager;
	CClient client1(&vistorManager);
	CClient client2(&vistorManager);
	CClient client3(&vistorManager);
	CClient client4(&vistorManager);
	CClient client5(&vistorManager);

	vistorManager.RegisterListener(&client1);
	vistorManager.RegisterListener(&client2);
	vistorManager.RegisterListener(&client3);
	vistorManager.RegisterListener(&client4);
	vistorManager.RegisterListener(&client5);

	client1.ExecuteOperation();

END_TEST()
