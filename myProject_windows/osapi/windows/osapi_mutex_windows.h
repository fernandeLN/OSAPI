#ifndef OSAPI_MUTEX_WINDOWS_H
#define OSAPI_MUTEX_WINDOWS_H

#include <windows.h>

namespace osapi {

class Mutex : public MutexInterface
{
private: 
    HANDLE mutex;
public:
    Mutex() {
		// TODO
        this->mutex = CreateSemaphore(NULL, 1, 1, NULL); //binary semaphore
    }
    virtual ~Mutex() {
		// TODO
        CloseHandle(this->mutex);
    }
    virtual bool lock(unsigned int timeout) {
		// TODO
        DWORD waitResult = WaitForSingleObject(this->mutex, timeout);
        if (waitResult == WAIT_OBJECT_0) {
            return true;
        }
		return false;
    }
    virtual void unlock() {
		// TODO
        ReleaseSemaphore(this->mutex, 1, NULL);
    }
};

} // namespace osapi

#endif // OSAPI_MUTEX_WINDOWS_H
