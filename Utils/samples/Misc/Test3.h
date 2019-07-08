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

namespace nsTechnicalTest3
{

	struct arg
	{
		arg(int value)
			:_value(value)
		{
		}

		~arg()
		{
			std::cout << "~arg()" << std::endl;
			_value = 0;
		}

		int _value;
	};

	struct arg2
	{
		int _x;
		int _y;
	};

	struct SIndexes
	{
		std::size_t x;
		std::size_t y;
	};

	template<class T, int M, int N >
	class static_matrix
	{
	private:
		static const int SIZE = M * N;

		class SIndexProxy
		{
			friend class static_matrix;

		public:
			T& operator[](int y)
			{
				_y = y;
				return _matrix->operator[](*this);
			}

		private:
			SIndexProxy(static_matrix* matrix, int x)
				:_matrix(matrix)
				, _x(x)
			{
			}

			static_matrix* _matrix;
			int _x;
			int _y;
		};

	public:
		static_matrix()
		{
			for (T& value : _data)
			{
				value = T();
			}
		}

		static_matrix(T& defaultValue)
		{
			for (T& value : _data)
			{
				value = defaultValue;
			}
		}

		void SetValue(const T& value, int x, int y)
		{
			_data[x + M * y] = value;
		}

		const T& GetValue(int x, int y) const
		{
			return _data[x + M * y];
		}

		T& GetValue(int x, int y)
		{
			return _data[x + M * y];
		}

		T& operator()(int x, int y)
		{
			return _data[x + M * y];
		}
				
		T& operator [] (const std::pair<const arg&, const arg&>& values)
		{
			int x = values.first._value;
			int y = values.second._value;
			return _data[x + M * y];
		}

		
		T& operator [] (const std::initializer_list<int>& values)
		{
			assert(values.size() == 2 && "Invalid size, only 2 values are allowed!");
			int x = *(values.begin());
			int y = *(values.begin() + 1);
			return _data[x + M * y];
		}

		T& operator [] (const arg2& indexes)
		{
			return _data[indexes._x + M * indexes._y];
		}

		SIndexProxy operator[](int x)
		{
			return SIndexProxy(this, x);
		}

	private:
		T& operator[](const SIndexProxy& indexProxy)
		{
			assert(this == indexProxy._matrix);
			return _data[indexProxy._x + M * indexProxy._y];
		}


		T _data[SIZE];
	};

	std::pair<const arg&, const arg&> operator , (const arg& p1, const arg& p2)
	{
		return std::pair<const arg&, const arg&>(p1, p2);
	}

}

BEGIN_TEST(TechnicalTest3)
	using namespace nsTechnicalTest3;
	
	int defaultValue = 0;
	static_matrix<int, 1, 4> matrix(defaultValue);
	matrix.SetValue(9, 0, 3);

	matrix[0][3] = 99;
	int value = matrix[0][3];

	/*
	int value1 = matrix(0, 3);
	int value2 = matrix[{2, 3}];
	int value3 = matrix[arg(1), arg(3)];
	int value4 = matrix[arg2{ 2, 3 }];
	int value5 = matrix[make_pair(2, 3)];
	*/
END_TEST()