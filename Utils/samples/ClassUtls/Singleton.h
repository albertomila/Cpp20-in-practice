#include "Incopiable.h"

template<typename T>
class Singleton : public Incopiable
{
public:
	static void CreateInstance()
	{
		if( ms_instance == NULL )
		{
			ms_instance = new T();
		}
		else
		{
			//error
		}
	}

	static void DestroyInstance()
	{
		delete ms_instance;
	}

	static inline T* Get()
	{
		return ms_instance;
	}

protected:
	Singleton(){}
	~Singleton(){}

private:
	static T* ms_instance;
};

template< typename T >
T* Singleton<T>::ms_instance = NULL;