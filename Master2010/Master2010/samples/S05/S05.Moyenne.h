#pragma once
#include "stdafx.h"
using namespace std;

template <class T>
   struct traits_nombre;

template <>
struct traits_nombre<int>
{
    typedef long cumul_type;
    typedef float reel_type;
};

#include <iterator>
using std::iterator_traits;

template <class Itt>
typename traits_nombre	<
							typename iterator_traits<Itt>::value_type
						>::reel_type 
moyenne (Itt debut, Itt fin)
{
    using std::distance;
    typedef typename iterator_traits<Itt>::difference_type		difference_type;
    typedef typename iterator_traits<Itt>::value_type			value_type;
    typedef typename traits_nombre<value_type>::cumul_type		cumul_type;
    typedef typename traits_nombre<value_type>::reel_type		reel_type;

    difference_type n = distance(debut, fin);
    cumul_type cumul = cumul_type();
    for (; debut != fin; ++debut)
        cumul += *debut;

    return static_cast<reel_type>(cumul) / n;
}

template<>
struct traits_nombre<float>
{
	typedef long cumul_type;
	typedef float reel_type;
};

struct Moyenne_Cumul
{
	float cumul_;
	Moyenne_Cumul() : cumul_(0.0f){}
	void operator() (float value)
	{
		cumul_+=value;
	}
};

#include <numeric>
template <class T>
typename traits_nombre	<
							typename iterator_traits<T>::value_type
						>::reel_type 
moyenne2(const T init, const T end)
{
    using std::distance;
	using std::accumulate;

    typedef typename iterator_traits<T>::difference_type				difference_type;
    typedef typename iterator_traits<T>::value_type						value_type;
	typedef typename traits_nombre<value_type>::cumul_type				cumul_type;
	typedef typename traits_nombre<value_type>::reel_type				reel_type;

	cumul_type cumul = cumul_type();
	difference_type num = std::distance(init, end);

	Moyenne_Cumul c = for_each(init, end, Moyenne_Cumul());
	reel_type r = accumulate(init, end,0.0f);
    return static_cast<reel_type>( c.cumul_) / num;
}

BEGIN_TEST(Media)
   using std::cout;
   using std::endl;
   int tab[] = { 2, 3, 5, 7, 11 };
   float tab2[] = { 1.1, 1.1, 1.1, 1.1, 1.1 };
   enum { N = sizeof(tab)/ sizeof(tab[0]) };
   enum { N1 = sizeof(tab2)/ sizeof(tab2[0]) };
   cout << moyenne(tab, tab + N) << endl;
   cout << moyenne2(tab2, tab2 + N1) << endl;

   END_TEST()