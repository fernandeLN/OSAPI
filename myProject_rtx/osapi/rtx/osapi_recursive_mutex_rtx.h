#ifndef OSAPI_RECURSIVE_MUTEX_RTX_H
#define OSAPI_RECURSIVE_MUTEX_RTX_H

#include "osapi_mutex_interface.h"
#include "cmsis_os2.h"

static const osMutexAttr_t Thread_Mutex_attr = {
			"myThreadMutex",     
			osMutexRecursive,    // attr_bits
			NULL,                   
			0U                   // size for control block
		};

namespace osapi {
	
class RecursiveMutex : public MutexInterface
{
private: 
	osMutexId_t _mutex;
bool _isInit;

public:
	RecursiveMutex() {
		// TODO
		_isInit = false;
	}
	virtual ~RecursiveMutex() {
		// TODO
		osMutexDelete(_mutex);
	}
	virtual bool lock(unsigned int timeout) {
		// TODO
		
		if(!_isInit){
			_mutex = osMutexNew(&Thread_Mutex_attr);
			osMutexRelease(_mutex);
			_isInit = true;
		}
		
		if (osMutexAcquire(_mutex, timeout) == osOK) {
			return true;
		}
		else {
			return false;
		}
		
	}
	virtual void unlock() {
		// TODO
		if (!_isInit) {
			_mutex = osMutexNew(NULL);
			osMutexRelease(_mutex);
			_isInit = true;
		}
		osMutexRelease(_mutex);
	}
};

} // namespace osapi

#endif // OSAPI_RECURSIVE_MUTEX_RTX_H
