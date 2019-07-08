#include "stdafx.h"
#include "Thread.h"

//*********************************************************
//default constructor for class Thread
//*********************************************************
Thread::Thread ()
{
	this->hThread		= NULL;
	this->hThreadId		= 0;
	this->hMainThread	= ::GetCurrentThread ();
	this->hMainThreadId = ::GetCurrentThreadId ();
	this->Timeout		= 2000; //milliseconds
}

//*********************************************************
//destructor for class CObject
//*********************************************************
Thread::~Thread ()
{
	//waiting for the thread to terminate
	if (this->hThread) 
	{
		if (::WaitForSingleObject (this->hThread, this->Timeout) == WAIT_TIMEOUT)
		{
			::TerminateThread (this->hThread, 1);
		}
		::CloseHandle (this->hThread);
	}
}

//*********************************************************
//working method
//*********************************************************
unsigned long Thread::Process (void* parameter)
{
	//a mechanism for terminating thread should be implemented
	//not allowing the method to be run from the main thread
	if (::GetCurrentThreadId () == this->hMainThreadId)
		return 0;
	else {

		return 0;
	}
}



//*********************************************************
//creates the thread
//*********************************************************
bool Thread::CreateThread ()
{

	if (!this->IsCreated ()) {
		param*	this_param = new param;
		this_param->pThread	= this;
		this->hThread = ::CreateThread (NULL, 0, (unsigned long (__stdcall *)(void *))this->runProcess, (void *)(this_param), 0, &this->hThreadId);
		return this->hThread ? true : false;
	}
	return false;

}

//*********************************************************
//creates the thread
//*********************************************************
int Thread::runProcess (void* Param)
{
	Thread*	thread;
	thread			= (Thread*)((param*)Param)->pThread;
	delete	((param*)Param);
	return thread->Process (0);
}