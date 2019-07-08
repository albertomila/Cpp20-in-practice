#pragma once
#include "stdafx.h"
using namespace std;


template <class T>
bool EstEntreInclusif (const T &Val, const T &BorneInf, const T &BorneSup)
{
    return BorneInf <= Val && Val <= BorneSup;
}

template <class T>
bool EstEntreExclusif (const T &Val, const T &BorneInf, const T &BorneSup)
{
    return BorneInf < Val && Val < BorneSup;
}


template <class D, class P> 
struct TraitsLieu
{
   typedef typename D distance_type;
   typedef typename P position_type;
   static position_type origineX () { return position_type(0); };
   static position_type origineY () { return position_type(0); };
};

class EcranConsole : 
	public TraitsLieu<short,short>
{
   enum { X_MIN = 0, X_MAX = 79, Y_MIN = 0, Y_MAX = 24 };
public:
   static bool EstLieuLegal (const position_type X, const position_type Y)
   {
      return EstEntreInclusif<const position_type>(X, X_MIN, X_MAX) &&
             EstEntreInclusif<const position_type>(Y, Y_MIN, Y_MAX);
   }
   static position_type origineX () 
   { 
	   return X_MIN; 
   }
   static position_type origineY () 
   { 
	   return Y_MIN; 
   }
};
 
template <class Lieu2D = EcranConsole>
class PointBase
{
public:
    typedef typename Lieu2D Lieu;
	typedef typename Lieu2D::distance_type distance_type;
    typedef typename Lieu2D::position_type position_type;
  class PointDiff
    {
        distance_type m_dX;
        distance_type m_dY;
    public:
        PointDiff (const distance_type dX, const distance_type dY)
        : m_dX (dX), m_dY (dY)
        {
        }
        distance_type GetDX() const { return m_dX; }
        distance_type GetDY() const { return m_dY; }
    };
private:
    position_type m_X, m_Y;
    void SetX (const position_type X) { m_X = X; }
    void SetY (const position_type Y) { m_Y = Y; }
public:
    class PointIllegal {};
    PointBase ()
        : m_X (Lieu::origineX()), m_Y (Lieu::origineY())
    {
    }
    PointBase (const position_type X, const position_type Y) throw (PointIllegal)
        : m_X (X), m_Y (Y)
    {
        if (!Lieu2D::EstLieuLegal (GetX(), GetY())) throw PointIllegal();
    }
    PointBase (const PointBase &p)
        : m_X (p.GetX()), m_Y (p.GetY())
    {
    }
    position_type GetX() const { return m_X; }
    position_type GetY() const { return m_Y; }
    const PointBase & operator= (const PointBase &p)
    {
        SetX (p.GetX ());
        SetY (p.GetY ());
        return *this;
    }
    PointBase & operator+= (const PointDiff &p)
        throw (PointIllegal)
    {
        m_X += p.GetDX ();
        m_Y += p.GetDY ();
        if (!Lieu2D::EstLieuLegal (GetX(), GetY())) throw PointIllegal();
        return *this;
    }
    bool operator== (const PointBase &p) const
    {
        return GetX() == p.GetX() && GetY () == p.GetY();
    }
    bool operator!= (const PointBase &p) const
    {
        return GetX() != p.GetX() || GetY () != p.GetY();
    }
};
typedef PointBase<EcranConsole> Point;

BEGIN_TEST(Traits)
	/*
	short x = 10;
	short y = 20;
	bool b  = EcranConsole::EstLieuLegal(x,y);
	if(b)
	{
		getchar();
	}
	else
	{
		getchar();
	}
	*/

	//typedef PointBase<> Point;

	END_TEST()