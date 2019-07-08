#pragma once
#include "stdafx.h"

namespace nsRAII
{
	class CResource
	{
	public:
		CResource()
		{
			_data = new char[1024];
		}

		void ProcesssData()
		{
			for (int i = 0; i<1024; ++i)
			{
				_data[i] = '9';
			}
		}


		void ClearData()
		{
			for (int i = 0; i<1024; ++i)
			{
				_data[i] = '\0';
			}
		}

		~CResource()
		{
			ClearData();
			delete _data;
		}
	
	private:
		char* _data;
	};

	class CItem
	{
	public:
		CItem()
		{
			CResource resource;
			resource.ProcesssData();
		}
	};
}

BEGIN_TEST(RAII)
	using namespace nsRAII;

	CItem item;
	
END_TEST()
