#ifndef OSAPI_MUTEX_RTX_H
#define OSAPI_MUTEX_RTX_H

#include "osapi_mutex_interface.h"
#include "cmsis_os2.h"


namespace osapi {

class Mutex : public MutexInterface
{
	
private: 
	osMutexId_t _mutex;
	bool _isInit;

public:
	Mutex() {
		// TODO
		_isInit = false;
	}
	virtual ~Mutex() {
		// TODO
		if (_isInit){
			osMutexDelete(_mutex);
		}
	}
	virtual bool lock(unsigned int timeout) {
		// TODO
		if (!_isInit){
			_mutex = osMutexNew(NULL);
			osMutexRelease(_mutex);
			_isInit = true;
		}
		
		if (osMutexAcquire(_mutex, timeout) == osOK){
			return true;
		}
		return false;
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

#endif // OSAPI_MUTEX_RTX_H
