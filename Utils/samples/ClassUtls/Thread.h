#pragma once
#include <windows.h>

class Thread 
{
public:
	Thread ();
	virtual ~Thread ();

	bool CreateThread ();
	int	IsCreated (){	return (this->hThread != NULL);	}

	DWORD	Timeout;
	HANDLE	GetThreadHandle (){		return this->hThread;		}
	DWORD	GetThreadId (){			return this->hThreadId;		}
	HANDLE	GetMainThreadHandle (){	return this->hMainThread;	}
	DWORD	GetMainThreadId (){		return this->hMainThreadId;	}

protected:

	//overrideable
	virtual unsigned long Process (void* parameter) = 0;	

	DWORD		hThreadId;
	HANDLE		hThread;
	DWORD		hMainThreadId;
	HANDLE		hMainThread;
	
private:
	static int runProcess (void* Param);

};

struct param 
{
	Thread*	pThread;
};


/*

///ExampleProcess.h

class ExampleProcess : public Thread
{
public:
	ExampleProcess(void);
	~ExampleProcess(void);
	unsigned long Process (void* parameter);
};

///ExampleProcess.cpp
unsigned long ScreenMenuLoader::Process (void* parameter)
{
		if (::GetCurrentThreadId () == this->hMainThreadId)
		{
			return 0;
		}
		else 
		{
			//put of the new process here
			return 0;
		}
}


///main.cpp
ExampleProcess* exampleProcess = new ExampleProcess();
exampleProcess->CreateThread();



*/