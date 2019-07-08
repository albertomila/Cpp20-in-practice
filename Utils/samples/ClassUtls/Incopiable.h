class Incopiable
{
	Incopiable(const Incopiable &value){}
	Incopiable& operator = ( const Incopiable &value){}
protected:
	Incopiable() throw() {}
	virtual ~Incopiable() throw() {}
};