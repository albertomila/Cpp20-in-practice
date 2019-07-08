#pragma once
#include "stdafx.h"
#include <typeinfo>
#include <vector>
#include <string>
#include <map>
#include <array>
#include <unordered_map>
#include <iostream>
#include <memory>
using namespace std;

namespace Test4
{
	struct SData
	{
		int value = 99;
	};

	class COwner
	{
	public:
		~COwner()
		{
			_data.release();
		}

		void Init()
		{
			_data.reset(new SData());
		}

		void UnInit()
		{
			_data.release();
		}

		SData* GetData() const
		{
			int value = _data->value;
			assert(_data.get() && "Ptr must be initialized");
			return _data.get();
		}

	private:
		unique_ptr<SData> _data;
	};

	class CUser
	{
	public:
		CUser(SData* data)
			:_data(data)
		{
		}

	private:
		SData* _data; //I am not the owner of this pointer.
	};



	namespace nsTechnicalTest4
	{
	}


	bool IsPalindrome(char* buffer, int size)
	{
		if (size <= 1)
		{
			return true;
		}

		int midLeft = size / 2;
		for (int i = 0; i <= midLeft; ++i)
		{
			int j = (size - 1) - i;

			if (*(buffer + i) != *(buffer + j))
				//if (buffer[i] != buffer[j])
			{
				return false;
			}
		}

		return true;
	}

	struct IHandler
	{
		virtual void DoSomething() = 0;
	};


	struct CHandler : public IHandler
	{
		void DoSomething() override
		{

		}
	};
}

BEGIN_TEST(TechnicalTest4)
using namespace Test4;

	{
		COwner owner;
		owner.Init();
		CUser user(owner.GetData());
		owner.UnInit();
	}

	constexpr std::size_t size1 = sizeof(SData);
	constexpr std::size_t size2 = sizeof(IHandler);
	constexpr std::size_t size3 = sizeof(CHandler);

	char* buffer = new char[256];
	std::cout << "input text\n";
	std::cin >> buffer;
	std::cout << buffer << strlen(buffer);

	bool isPalindrome = IsPalindrome(buffer, strlen(buffer));
	std::cout << "isPalindrome: " << isPalindrome;

	delete[] buffer;

END_TEST()