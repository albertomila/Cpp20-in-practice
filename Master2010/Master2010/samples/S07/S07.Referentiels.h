#pragma once
#include "stdafx.h"
using std::string;

class Celsius {};
class Fahrenheit {};
class Kelvin {};


template <class T>
struct temperature_traits;

template <>
struct temperature_traits<Celsius>
{
    typedef int value_type;
    static value_type to_neutral(const value_type val) throw()
    { 
		return val; 
	}
    static value_type to_local(const value_type val) throw()
    { 
		return val; 
	}
    static std::string nom()
    {
        static const std::string NOM = "Celsius";
        return NOM;
    }
    static value_type gel_eau() throw()
    {
        static const value_type SEUIL_GEL_EAU = 0;
        return SEUIL_GEL_EAU;
    }
};

template <>
struct temperature_traits<Kelvin>
{
    typedef unsigned int value_type;
private:
    static const value_type DELTA_ZERO_ABSOLU = 273;
public:
    static value_type to_neutral(const value_type val) throw()
    { 
		return val - DELTA_ZERO_ABSOLU; 
	}
    static value_type to_local(const value_type val) throw()
    { 
		return val + DELTA_ZERO_ABSOLU; 
	}
    static std::string nom()
    {
        static const std::string NOM = "Kelvin";
        return NOM;
    }
    static value_type gel_eau() throw()
    {
        static const value_type SEUIL_GEL_EAU = 273;
        return SEUIL_GEL_EAU;
    }
};

template <>
struct temperature_traits<Fahrenheit>
{
    typedef double value_type;
    static value_type to_neutral(const value_type val) throw()
    { 
		return (val - gel_eau()) * 5.0 / 9.0; 
	}
    static value_type to_local(const value_type val) throw()
    { 
		return gel_eau() + 9.0 / 5.0 * val; 
	}
    static std::string nom()
    {
        static const std::string NOM = "Fahrenheit";
        return NOM;
    }
    static value_type gel_eau() throw()
    {
        static const value_type SEUIL_GEL_EAU = 32.0;
        return SEUIL_GEL_EAU;
    }
};


template <class T>
class Temperature
{
public:
	typedef typename temperature_traits<T>::value_type value_type;
private:
	value_type valeur_;
public:
	value_type valeur() const
	{ 
		return valeur_; 
	}
public:
	Temperature(const value_type valeur = temperature_traits<T>::gel_eau()) : valeur_(valeur)
	{
	}
	// Sainte-Trinité Ok
	void swap(Temperature &temp)
	{ 
		std::swap(valeur_, temp.valeur_); 
	}
	
	template <class U>
	Temperature(const Temperature<U> &temp) : valeur_(temperature_cast<T,U>(temp.valeur()))
	{
	}
	~Temperature()
	{
	}

	template <class U>
	Temperature& operator=(const Temperature<U> &temp)
	{
		Temperature(temp).swap(*this);
		return *this;
	}

	bool operator==(const Temperature &temp) const
	{ 
		return valeur() == temp.valeur();
	}
	bool operator!=(const Temperature &temp) const
	{ 
		return ! (*this == temp); 
	}
	bool operator<(const Temperature &temp) const
	{ 
		return valeur() < temp.valeur(); 
	}
	bool operator<=(const Temperature &temp) const
	{ 
		return !(temp.valeur() < valeur()); 
	}
	bool operator>(const Temperature &temp) const
	{ 
		return temp.valeur() < valeur(); 
	}
	bool operator>=(const Temperature &temp) const
	{ 
		return !(valeur() < temp.valeur()); 
	}
};

template <class T>
std::ostream& operator<< (std::ostream &os, const Temperature<T> &temp)
{
    return os << temp.valeur();
}

template <class Dest, class Src>
typename temperature_traits<Dest>::value_type 
temperature_cast(const typename temperature_traits<Src>::value_type &src)
{
    return temperature_traits<Dest>::to_local( temperature_traits<Src>::to_neutral(src) );
}

BEGIN_TEST(TemperatureTraits)
	using std::cout;
	using std::endl;

	Temperature<Kelvin> k = 10;
	Temperature<Celsius> c = k;
	
	cout << c << " " << temperature_traits<Celsius>::nom() << endl;
	k = c;
	cout << k << " "  << temperature_traits<Kelvin>::nom() << endl;
	
	bool b1 = (k==k);

	if (k == c)
		cout << c << " " << temperature_traits<Celsius>::nom() << " == " << k << " " << temperature_traits<Kelvin>::nom()  << endl;
	else
		cout << c << " " << temperature_traits<Celsius>::nom() << " != " << k << " " << temperature_traits<Kelvin>::nom()  << endl;

	Temperature<Fahrenheit> f = Temperature<Celsius>(5);
	cout << f << " " << temperature_traits<Fahrenheit>::nom() << endl;

	END_TEST()