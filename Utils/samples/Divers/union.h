#pragma once
#include "stdafx.h"
using namespace std;

struct TrameUDP
{
	enum type_option{ USE_INT, USE_FLOAT, USE_CHAR};
	
	union payload //union: meme endroit de memoire
	{
		int		pos_;
		float	vel_;
		char	id_;
	};
	payload p_; //size == max of [int, float, char]
	type_option typeoption;
};


BEGIN_TEST(Union)
	TrameUDP* udp = new TrameUDP();

	udp->p_.pos_ = 1;
	udp->typeoption = TrameUDP::USE_INT;
	int x = udp->p_.pos_;

	udp->p_.vel_ = 300.4f;
	udp->typeoption = TrameUDP::USE_FLOAT;
	float y = udp->p_.vel_;

	udp->p_.id_ = 'A';
	udp->typeoption = TrameUDP::USE_CHAR;
	char z = udp->p_.id_;

	END_TEST()