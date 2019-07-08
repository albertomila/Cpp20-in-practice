#pragma once
#include "stdafx.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include "foncteurs.h"
#include "Singleton.h"


BEGIN_TEST(Functor)
   using std::vector;
	using std::endl;
   using std::cout;
   using std::generate;
   using std::srand;
   using std::rand;
   using std::copy;
   using std::for_each;
   using std::ostream_iterator;
   
   ///////////////////////////////////////////////
   srand(static_cast<unsigned int>(time(0)));
   const int MAX = 10;
   int vals[MAX];
   int vals2[MAX];

   generate(vals, vals + MAX, Random(10));
   
   copy(vals, vals + MAX, ostream_iterator<int>(cout, " "));
   cout << ' ' << endl;
   copy(vals, vals + MAX, vals2);
   copy(vals2, vals2 + MAX, ostream_iterator<int>(cout, " "));

   cout << endl
	   << for_each(vals2, vals2 + MAX, MIN<int>(vals2[0])).value() 
		<< endl;


   ///////////////////////////////////////////////
   cout << ' ' << endl;
   vector<int> v;
   v.push_back(0);
   v.push_back(1);
   v.push_back(2);
   v.push_back(3);
   v.push_back(4);
   v.push_back(5);
   v.push_back(6);
   
   vector<int> v2;
   v2.resize(v.size());   // allocate space for 7 elements
   copy(v.begin(), v.end(), v2.begin());

   v[0] = 99;
   copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
   cout << ' ' << endl;
   copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));


   ///////////////////////////////////////////////
   
   vector<int> v3;
   v3.resize(MAX);  
   generate(v3.begin(), v3.end(), Init(0));
   generate(v3.begin(), v3.end(), Random(10));
   copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, " "));

	Cumul c = for_each(v3.begin(), v3.end(), Cumul());
	cout << c.total() << endl;

	vector<int>::iterator itt = find(v3.begin(), v3.end(), 3);

   END_TEST()