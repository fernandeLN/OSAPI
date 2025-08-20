#ifndef OSAPI_RECURSIVE_MUTEX_WINDOWS_H
#define OSAPI_RECURSIVE_MUTEX_WINDOWS_H

#include <Windows.h>

namespace osapi {

class RecursiveMutex : public MutexInterface
{

private: 
	HANDLE recursiveMutex;
	DWORD myThread;
	int count;

public:
	RecursiveMutex() : myThread(0), count(0) {
		// TODO
		recursiveMutex = CreateMutex(NULL, FALSE, NULL);
	}
	virtual ~RecursiveMutex() {
		// TODO
		CloseHandle(recursiveMutex);
	}
	virtual bool lock(unsigned int timeout) {
		// TODO
		DWORD currentThread = GetCurrentThreadId();
		DWORD result;

		if (myThread == currentThread) {
			count++;
		}
		else {
			result = WaitForSingleObject(recursiveMutex, timeout);
			if (result == WAIT_OBJECT_0 || result == WAIT_ABANDONED) {
				myThread = currentThread;
				count = 1;
			}
			else {
				//handle error
				return false;
			}
		}
		return true;
	}
	virtual void unlock() {
		// TODO
		if (count > 0) {
			count--;
			if (count == 0) {
				myThread = 0;
				ReleaseMutex(recursiveMutex);
			}
		}
	}
};

} // namespace osapi

#endif // OSAPI_RECURSIVE_MUTEX_WINDOWS_H
