#include <ostream>

class Print
{
	std::ostream &os_;
public:
	Print(std::ostream &os) throw() : os_(os) {}

	template <class T>
	void operator()(const T &value) 
	{
		os_ << value;
	}
};

template<class T>
class Min
{
	T val_;
public:
	Min(const T &val) throw() : val_(val){}
	void operator() (const T &currentValue)
	{ 
		if(val_ > currentValue)
		{
			val_ = currentValue;
		}
	}
	T value() const
	{
		return val_;
	}
};

template<class T>
class Max
{
	T val_;
public:
	Max(const T &val) throw() : val_(val){}
	void operator() (const T &currentValue)
	{
		if(val_ < currentValue)
		{
			val_ = currentValue;
		}
	}
	T value() const
	{
		return val_;
	}
};

struct Random
{
	int max_;
	Random(int max) throw() : max_(max){}
	int operator() ()
	{ 
		return (rand() % max_); 
	}
};

struct Remove
{
	Remove(){}
	template <class T>
	bool operator()(const T& t)
	{
		delete t;
		return true;
	}
};

struct Delete
{
	Delete(){}
	template <class T>
	void operator()(const T& t)
	{
		delete t;
	}
};

struct Init
{
	Init(){}
	template <class T>
	void operator()(const T& t)
	{
		t->Init();
	}
};
struct Update
{
	Update(){}
	template <class T>
	void operator()(const T& t)
	{
		t->Update();
	}
};
struct Draw
{
	Draw(){}
	template <class T>
	void operator()(const T& t)
	{
		t->Draw();
	}
};

template <class T, class Arg>
struct GenericMethod
{
	typedef void (T::*type_method)(Arg);
	type_method method_;

	typedef T type_value;
	type_value* value_;

	GenericMethod(T* value, type_method method) : method_(method), value_(value)
	{
	}
	void operator()(Arg& t)
	{
		(value_->*method_)(t);
	}
};

template <class T, class Arg>
struct GenericMethodBool
{
	typedef bool (T::*type_method)(Arg);
	type_method method_;

	typedef T type_value;
	type_value* value_;

	GenericMethodBool(T* value, type_method method) : method_(method), value_(value)
	{
	}
	bool operator()(Arg& t)
	{
		return (value_->*method_)(t);
	}
};

template <class T>
struct GenericFunction
{
	typedef void (T::*typefunction)();
	typefunction Tf_;
	GenericFunction(typefunction Tf) : Tf_(Tf)
	{
	}
	void operator()(T& t)
	{
		(t.*Tf_)();
	}
};

template <class T, class Arg1>
struct GenericFunctionArg
{
	typedef void (T::*typefunction)(Arg1);
	typefunction Tf_;
	Arg1 arg1_;
	GenericFunctionArg(typefunction Tf, Arg1 arg1) : Tf_(Tf), arg1_(arg1)
	{
	}
	void operator()(T& t)
	{
		(t.*Tf_)(arg1_);
	}
};

template <class T, class Arg1>
struct GenericFunctionArgPtr
{
	typedef void (T::*typefunction)(Arg1*);
	typefunction Tf_;
	Arg1* arg1_;
	GenericFunctionArgPtr(typefunction Tf, Arg1* arg1) : Tf_(Tf), arg1_(arg1)
	{
	}
	void operator()(T& t)
	{
		(t.*Tf_)(arg1_);
	}
};