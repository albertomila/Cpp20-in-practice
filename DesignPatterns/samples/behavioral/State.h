#pragma once
#include "stdafx.h"

namespace nsState
{
	class IObjectState
	{
	public:
		IObjectState(int maxTime)
			:_maxTime(maxTime)
		{
		}
		virtual void Init() = 0;
		virtual void Update()
		{
			IncreaseTime();
			DoUpdate();
		}
		virtual void DoUpdate() = 0;

		bool HasFinished() const
		{
			return _time == _maxTime;
		}

	protected:
		void IncreaseTime()
		{
			++_time;
		}

	private:
		int _time = 0;
		const int _maxTime = 0;
	};

	class CObjectStateLoad : public IObjectState
	{
	public:
		CObjectStateLoad()
			: IObjectState(10)
		{
		}
		void Init() {}
		void DoUpdate() override{}
	};

	class CObjectStateIdle : public IObjectState
	{
	public:
		CObjectStateIdle()
			: IObjectState(10)
		{
		}
		void Init() {}
		void DoUpdate() override {}
	};

	class CObjectStateUnload : public IObjectState
	{
	public:
		CObjectStateUnload()
			: IObjectState(10)
		{
		}
		void Init() {}
		void DoUpdate() override {}
	};

	class CObject
	{
	public:
		CObject()
		{
			_state = new CObjectStateLoad();
		}

		void Update()
		{
			_state->Update();
			if (_state->HasFinished())
			{
				if (dynamic_cast<CObjectStateLoad*>(_state) != 0)
				{
					delete _state;
					_state = new CObjectStateIdle();
				}
				else if (dynamic_cast<CObjectStateIdle*>(_state) != 0)
				{
					delete _state;
					_state = new CObjectStateUnload();
				}
				else if (dynamic_cast<CObjectStateUnload*>(_state) != 0)
				{
					delete _state;
					_state = nullptr;
				}
			}
		}

		bool HasFinished() const
		{
			return _state == nullptr;
		}

	private:
		IObjectState* _state;
	};
}

BEGIN_TEST(State)
	using namespace nsState;

	CObject object;
	while (!object.HasFinished())
	{
		object.Update();
	}


END_TEST()