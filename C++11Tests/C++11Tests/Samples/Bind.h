#include "stdafx.h"
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::placeholders;

int multiply(int a, int b, int c)
{
    return (a * b) + c;
}

BEGIN_TEST(TestBind)
                            //fixed arg, variable arg, fixed arg.
    auto f = std::bind(multiply, 5, std::placeholders::_1, 1);
    for (int i = 0; i < 10; i++)
    {
        cout << "5 * " << i << " = " << f(i) << endl;
    }

	std::function<int(int,int,int)> rnd = std::bind(multiply, 5, std::placeholders::_1, 1);
	for (int i = 0; i < 10; i++)
	{
		cout << "5 * " << i << " = " << f(i) << endl;
	}


END_TEST()