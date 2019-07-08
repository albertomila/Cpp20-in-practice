#pragma once
#include "stdafx.h"
#include <typeinfo>
#include <vector>
#include <string>
#include <map>
#include <array>
#include <unordered_map>
#include <iostream>
using namespace std;

namespace nsTechnicalTest2
{
	template<class T>
	class CMergeSort
	{
	public:
		CMergeSort(std::vector<T>& values)
			:_values(values)
		{
			_buffer.resize(_values.size());

			PrintValues();
			if (_values.size() > 1)
			{
				SortValues();
			}
			PrintValues();
		}

		void SortValues()
		{
			SortRange(0, _values.size() - 1);
		}

		void SortRange(int leftIndex, int rightIndex)
		{
			int amountValues = rightIndex - leftIndex;
			if (amountValues <= 1)
			{
				return;
			}

			int midIndex = leftIndex + static_cast<int>(floor(amountValues / 2.0f));
			SortRange(leftIndex, midIndex);
			SortRange(midIndex + 1, rightIndex);
			MergeBothSides(leftIndex, midIndex, rightIndex);
		}

		void MergeBothSides(int leftIndex, int midIndex, int rightIndex)
		{
			int i = leftIndex;
			int j = midIndex + 1;
			int k = leftIndex;
			while (i <= midIndex && j <= rightIndex)
			{
				if (_values[i] <= _values[j])
				{
					_buffer[k] = _values[i];
					++i;
				}
				else
				{
					_buffer[k] = _values[j];
					++j;
				}
				++k;
			}

			for (; i <= midIndex; ++i)
			{
				_buffer[k] = _values[i];
				++k;
			}

			for (; j <= rightIndex; ++j)
			{
				_buffer[k] = _values[j];
				++k;
			}

			for (k = leftIndex; k <= rightIndex; ++k)
			{
				_values[k] = _buffer[k];
			}
		}

		void PrintValues() const
		{
			for (const T& value : _values)
			{
				std::cout << value << ",";
			}
			std::cout << std::endl;
		}

	private:
		std::vector<T>& _values;
		std::vector<T> _buffer;
	};
}

BEGIN_TEST(TechnicalTest2)
	using namespace nsTechnicalTest2;
	
	std::vector<int> values;
	for (int i = 0; i < 10;  ++i)
	{
		values.push_back(rand() % 100);
	}

	CMergeSort<int> mergeSort(values);

END_TEST()