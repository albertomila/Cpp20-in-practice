//#include "StdAfx.h"
#include <algorithm>
#include <numeric>
using namespace std;

template <class T>
   struct traits_nombre;

template <>
struct traits_nombre<int>
{
    typedef long cumul_type;
    typedef float reel_type;
};

template<>
struct traits_nombre<float>
{
	typedef long cumul_type;
	typedef float reel_type;
};

struct Cumul
{
	float cumul_;
	Cumul() : cumul_(0.0f){}
	void operator() (float value)
	{
		cumul_+=value;
	}
};

template <class T>
typename traits_nombre	<
							typename iterator_traits<T>::value_type
						>::reel_type 
MidValue(const T init, const T end)
{
    using std::distance;
	using std::accumulate;

    typedef typename iterator_traits<T>::difference_type				difference_type;
    typedef typename iterator_traits<T>::value_type						value_type;
	typedef typename traits_nombre<value_type>::cumul_type				cumul_type;
	typedef typename traits_nombre<value_type>::reel_type				reel_type;

	cumul_type cumul = cumul_type();
	difference_type num = std::distance(init, end);

	Cumul c = for_each(init, end, Cumul());
	reel_type r = accumulate(init, end,0.0f);
    return static_cast<reel_type>( c.cumul_) / num;
}

