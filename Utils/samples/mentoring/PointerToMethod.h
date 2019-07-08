
#include "stdafx.h"
#include <ctime>
#include <array>

#define STDAFTX "stdafx.h"
#include STDAFTX

namespace nsPointerToMethod
{
	void TestFoo()
	{

	}

	void DoSomething(int value)
	{

	}

	class CTest
	{
	public:
		void TestFoo()
		{

		}

		void DoSomething(int value)
		{

		}
	};


	class CSystem
	{
		enum EStates
		{
			state_1,
			state_2,
			state_3,
			state_4,
			MAX_STATES
		};

		using TUpdateCall = void (CSystem::*)();

	public:
		CSystem()
			:m_stateMachine
			{
				&CSystem::UpdateState1,
				&CSystem::UpdateState2,
				&CSystem::UpdateState3,
				&CSystem::UpdateState4
			}
			, m_currentState(EStates::state_1)
		{
		}

		void Update()
		{
			TUpdateCall updateCall = m_stateMachine[m_currentState];
			(this->*updateCall)();
		}

		void UpdateState1()
		{
			//go to state 2 randomly
			bool hasStateChanged = (rand() % 2) == 0;
			if (hasStateChanged)
			{
				GoToState(EStates::state_2);
				m_currentState = EStates::state_2;
			}
		}

		void UpdateState2()
		{
			//go to state 3
			GoToState(EStates::state_3);
		}

		void UpdateState3()
		{
			GoToState(EStates::state_4);
		}

		void UpdateState4()
		{
			//back to state 1
			GoToState(EStates::state_1);
		}

		void GoToState(EStates targetState)
		{
			m_currentState = targetState;
		}

	private:
		std::array<TUpdateCall, EStates::MAX_STATES> m_stateMachine;
		EStates m_currentState;
	};


	class CSystem2
	{
		enum EStates
		{
			state_1,
			state_2,
			state_3,
			state_4,
			MAX_STATES
		};

		using TUpdateCall = void (CSystem2::*)();

	public:
		CSystem2()
			: m_stateMachine
			{
				&CSystem2::UpdateState1,
				&CSystem2::UpdateState2,
				&CSystem2::UpdateState3,
				&CSystem2::UpdateState4
			}
			, m_currentState(&CSystem2::UpdateState1)
		{
		}

		void Update()
		{
			(this->*m_currentState)();
		}

		void UpdateState1()
		{
			//go to state 2 randomly
			bool hasStateChanged = (rand() % 2) == 0;
			if (hasStateChanged)
			{
				GoToState(EStates::state_2);
			}
		}

		void UpdateState2()
		{
			//go to state 3
			GoToState(EStates::state_3);
		}

		void UpdateState3()
		{
			GoToState(EStates::state_4);
		}

		void UpdateState4()
		{
			//back to state 1
			GoToState(EStates::state_1);
		}

		void GoToState(EStates targetState)
		{
			m_currentState = m_stateMachine[targetState];
		}

	private:
		TUpdateCall m_currentState;
		std::array<TUpdateCall, EStates::MAX_STATES> m_stateMachine;
	};


}

BEGIN_TEST(PointerToMethod)
using namespace nsPointerToMethod;

using TReturnType = void;
using TArgType = int;

//old C++
typedef TReturnType(*TCallbackName2)(TArgType);

//C++11
using TCallbackName = TReturnType (*)(TArgType);

using TClassType = CTest;

//old C++
typedef TReturnType(TClassType::*TClassCallbackName)(TArgType);

//C++11
using TClassCallbackName2 = TReturnType(TClassType::*)(TArgType);


void (*callback)(int)  = DoSomething;
callback(99);

using TCallbackName3 = void(*)(int);
TCallbackName3 callback2 = DoSomething;
callback2(99);

using TCallbackName4 = void(CTest::*)(int);
TCallbackName4 callback3 = &CTest::DoSomething;

using TCallbackName5 = void(CTest::*)();
TCallbackName5 callback5 = &CTest::TestFoo;

CTest objectTest;
(objectTest.*callback3)(99);

CTest* objectTestPtr = new CTest();
(objectTestPtr->*callback3)(99);
delete objectTestPtr;


CSystem system;
for(int i = 0; i<10; ++i)
{
	system.Update();
}


CSystem2 system2;
for (int i = 0; i<10; ++i)
{
	system2.Update();
}



using TVoidCallback = void(*)();
TVoidCallback voidCallback = &TestFoo;

const long long CYCLES = 1000000000;
clock_t startTimestamp = clock();
for (long long i = 0; i < CYCLES; ++i)
{
	(objectTest.*callback5)();
}
clock_t duration = clock() - startTimestamp;
std::cout << "duration callback :" << duration << std::endl;

std::function<void()> voidCallbackFunction = &TestFoo;
startTimestamp = clock();
for (long long i = 0; i < CYCLES; ++i)
{
	voidCallbackFunction();
}
duration = clock() - startTimestamp;
std::cout << "duration std::function :" << duration << std::endl;

END_TEST()
