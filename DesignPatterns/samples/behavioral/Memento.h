#pragma once
#include "stdafx.h"
#include <stack>

namespace nsMemento
{
	class CObjectStatus
	{
	public:
		CObjectStatus(int intValue, float floatValue, char charValue)
			: _dataInt(intValue)
			, _dataFloat(floatValue)
			, _dataString(charValue)
		{

		}

		int GetDataInt() const { return _dataInt; }
		float GetDataFloat() const { return _dataFloat; }
		char GetDataString() const { return _dataString; }

	private:
		int _dataInt;
		float _dataFloat;
		char _dataString;
	};


	class CObjectHistory
	{
	public:
		void StackData(int intValue, float floatValue, char charValue)
		{
			_history.push(CObjectStatus(intValue, floatValue, charValue));
		}

		bool HasStatusToRestore() const
		{
			return _history.size() > 0;
		}
		CObjectStatus RestoreLastStatus()
		{
			CObjectStatus lastStatus = _history.top();
			_history.pop();
			return lastStatus;
		}

	private:
		std::stack<CObjectStatus> _history;
	};

	class CObject
	{
	public:
		CObject()
			: _dataInt(0)
			, _dataFloat(0.5)
			, _dataString('0')
		{
		}

		void Increase()
		{
			_objectHistory.StackData(_dataInt, _dataFloat, _dataString);
			++_dataInt;
			_dataFloat += 1.f;
			_dataString += 1;
		}

		void RestoreData()
		{
			if (_objectHistory.HasStatusToRestore())
			{
				CObjectStatus objectStatus = _objectHistory.RestoreLastStatus();
				_dataInt = objectStatus.GetDataInt();
				_dataFloat = objectStatus.GetDataFloat();
				_dataString = objectStatus.GetDataString();
			}
		}

		int GetDataInt() const { return _dataInt; }
		float GetDataFloat() const { return _dataFloat; }
		char GetDataString() const { return _dataString; }

	private:
		int _dataInt;
		float _dataFloat;
		char _dataString;
		CObjectHistory _objectHistory;
	};


}

BEGIN_TEST(Memento)
	using namespace nsMemento;

	CObject object;
	object.Increase();
	object.Increase();
	object.Increase();
	object.Increase();
	object.Increase();
	object.Increase();

	for (int i = 0; i < 10; ++i)
	{
		object.RestoreData();
	}

END_TEST()