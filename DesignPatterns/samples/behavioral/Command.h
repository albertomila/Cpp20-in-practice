#pragma once
#include "stdafx.h"

namespace nsCommand
{
	class CReceiver
	{
	public:
		void ProcessCall()
		{
		}
	};

	class ICommand
	{
	public:
		ICommand(CReceiver* receiver)
		{
			_receiver = receiver;
		}

		virtual void Execute() = 0;

	protected:
		CReceiver* GetReceiver() { return _receiver; }

	private:
		CReceiver* _receiver;
	};

	class CConcreteCommand : public ICommand
	{
	public:
		CConcreteCommand(CReceiver* receiver)
			:ICommand(receiver)
		{
		}

	protected:
		void Execute() override
		{
			GetReceiver()->ProcessCall();
		}
	};

	class CObject
	{
	public:
		void SetCommand(ICommand* command)
		{
			_command = command;
		}
		
		void ExecuteCommand()
		{
			_command->Execute();
		}

	private:

		ICommand* _command;
	};

}

BEGIN_TEST(Command)
	using namespace nsCommand;

	CObject mainObject;
	CReceiver mainReciever;
	ICommand* command = new CConcreteCommand(&mainReciever);
	mainObject.SetCommand(command);
	mainObject.ExecuteCommand();

END_TEST()