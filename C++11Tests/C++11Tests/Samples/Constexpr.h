#include "stdafx.h"

class Point 
{
public:
    constexpr Point(int xVal = 0, int yVal = 0) noexcept
        : x(xVal), y(yVal)
    {
    }

    constexpr int xValue() const noexcept 
    { 
        return x; 
    }
    constexpr int yValue() const noexcept 
    { 
        return y; 
    }

    void setX(int newX) noexcept
    { 
        x = newX; 
    }
    void setY(int newY) noexcept 
    { 
        y = newY; 
    }
    

private:
    int x;
    int y;
};

constexpr Point midpoint(const Point& p1, const Point& p2) noexcept
{
    return Point(   (p1.xValue() + p2.xValue()) / 2,    // call constexpr
                    (p1.yValue() + p2.yValue()) / 2 );  // member funcs
}


class ArraySize
{
public:
	constexpr ArraySize(int size = 0)
		: _size(size)
	{
	}

	constexpr int GetSize() const noexcept
	{
		return _size;
	}

	void SetSize(int size) noexcept
	{
		_size = size;
	}


private:
	int _size;
};

constexpr int GetSize() noexcept
{
	ArraySize p(10);
	return p.GetSize();
}

BEGIN_TEST(TestConstExpr)
    constexpr Point p1(10, 10);      // fine, "runs" constexpr
                                        // ctor during compilation

    constexpr Point p2(5, 0);      // also fine

    constexpr Point mid = midpoint(p1, p2);     // init constexpr
                                               // object w/result of
                                               // constexpr function

	int values[GetSize()];

END_TEST()
