#ifndef OSAPI_THREAD_RTX_H
#define OSAPI_THREAD_RTX_H

#include "osapi_thread_interface.h"
#include "cmsis_os2.h"
#include <stdlib.h>
//#include <rtx_os.h>
#include <cstring>
#include <cstdio>

namespace osapi {

/** Thread interface implementation for FreeRTOS. */
class Thread : public ThreadInterface
{
	private :
		const char* myName;
		osPriority_t myPriority;
		unsigned int myStackSize; 
		Joinable myIsJoinable;
		osThreadId_t myId;
		bool isRunningFlag;
		ThreadState myState;
		osThreadAttr_t thread1_attr;
		
    public:
			
				static void threadFunction(void* argument){
					Thread* osapiThreadObject = reinterpret_cast<Thread*>(argument);
					if (osapiThreadObject){
						osapiThreadObject -> job();
					}
				
				}
        /** Thread constructor.
         *  @param[in] priority thread priority
         *  @param[in] stackSize thread stack size in bytes
         *  @param[in] isJoinable decides if the thread supports join operation or not
         *  @param[in] name optional thread name
         */
        Thread(int priority, unsigned int stackSize, Joinable isJoinable, const char* name = "unnamed") : myPriority((osPriority_t)priority), myStackSize(stackSize), myIsJoinable(isJoinable), myName(name), myId(NULL), isRunningFlag(false), myState(INACTIVE){
					  // TODO //done
        }
        
        /** Virtual destructor required to properly destroy derived class objects. */
        virtual ~Thread() { 
					  // TODO
					if (myIsJoinable == JOINABLE) {
						free(thread1_attr.stack_mem);
						free(thread1_attr.cb_mem);
					}
        }
        
        /** Runs the thread.
        *  @retval true if the thread was started successfully, 
        *  @retval false if the thread was not started successfully, or the thread was already running
        */
        virtual bool run() {
					  // TODO
					if (myId != NULL){
						return false;
					}
          
					memset(&thread1_attr, 0, sizeof(thread1_attr));
					thread1_attr.priority = osPriority_t(myPriority);
					thread1_attr.name = myName;
					thread1_attr.stack_size = myStackSize;
					
					if (myIsJoinable == JOINABLE){
						thread1_attr.attr_bits = osThreadJoinable;
					}
					
					myId = osThreadNew(threadFunction, this, &thread1_attr);
					
					if(myId != NULL) {
						isRunningFlag = true;
						myState = RUNNING;
						return true;					
					}
					else {
						return false;				
					}
					
        }

        /** Checks if the thread is running.
        *  @retval true if the thread is running
        *  @retval false if the thread is not running
        */
        virtual bool isRunning() {
					  // TODO
            if (myId != NULL){
							if (isRunningFlag == false){
								return false;
							}
							return true;
						}
						else {
							return false; 
						}
        }
        
        /** Waits for the thread to finish executing, with a given timeout.
         *  @param timeout[in] number of milliseconds to wait for the thread to finish executing
         *  @retval true if the thread was successfully joined in the given time
         *  @retval false if the thread was not joined within the given time or the thread is not joinable at all
         */
        virtual bool join(unsigned int timeout) {
					  // TODO
            if (myId != NULL) {
							osStatus_t joinStatus = osThreadJoin(myId);
							if (joinStatus == osOK) {
								isRunningFlag = false;
								return true;
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
        }

        /** Checks, if the thread is joinable.
         *  @retval true if the thread is joinable
         *  @retval false if the thread is not joinable
         */
        virtual bool isJoinable() {
					  // TODO
            if (myId != NULL) {
							if (myIsJoinable == JOINABLE) {
								thread1_attr.attr_bits = osThreadJoinable | osThreadDetached;
								return true;
							}
							else {
								return false; 
							}
						}
						else {
							return false;
						}
        }

        /** Suspends thread execution.
         *  @retval true if the thread was suspended successfully
         *  @retval false if the thread was not suspended for some reason
         */
        virtual bool suspend() {
					  // TODO
            if (myId != NULL && myState == RUNNING) {
							if (osThreadSuspend (myId) == osOK ){
								myState = SUSPENDED;
								return true;
							}
						}
						return false;
        }           

        /** Resumes thread execution.
         *  @retval true if the thread was resumed successfully
         *  @retval false if the thread was not resumed for some reason
         */
        virtual bool resume() {
					  // TODO
            if (myId != NULL && myState == SUSPENDED) {
							if (osThreadResume(myId) == osOK) {
								myState = RUNNING;
								return true;
							}
						}
						return false;
        }           

        /** Sets thread priority
         *  @param[in] priority new thread priority
         *  @retval true if the priority for the thread was set successfully
         *  @retval false if the priority for the thread was not set successfully for some reason
         */
        virtual bool setPriority(int priority) {
					  // TODO
						if (myId != NULL) {
							myPriority = (osPriority_t)priority;
							if (osThreadSetPriority(myId, myPriority) == osOK){
								return true;
							}
						}
            return false;
        }

        /** Gets the thread priority
         *  @return current thread priority
         */
        virtual int getPriority() {
					  // TODO
						if (myId != NULL) {
							return osThreadGetPriority(myId);
						}
            return 0;
        }
        
        /** Gets thread name
         *  @return name of the thread
         */
        virtual const char* getName() {
					  // TODO
            return myName;
        }

        /** Gets the current state of the thread
         *  @return current state of the thread
         */
        virtual ThreadState getState() {
					  // TODO
            if (myId != NULL) {
							osThreadState_t threadState = osThreadGetState(myId);
							switch(threadState) {
								case osThreadRunning: return RUNNING;
								case osThreadReady: return READY;
								case osThreadBlocked: {
									if (myState == SUSPENDED){
										return SUSPENDED;
									}
									else {
										return BLOCKED;
									}
									
								}
								case osThreadTerminated: return INACTIVE;
								case osThreadError: return INACTIVE;
								default: return UNKNOWN;
							}
							return INACTIVE;
						}
						else {
							return INACTIVE;
						}
        }

        /** Gets the total size of the stack assigned for this thread
         *  @return total stack size in number of bytes
         */
        virtual unsigned int getTotalStackSize() {
					  // TODO
            return myStackSize;
        }

        /** Gets the size of the used stack for this thread
         *  @return number of bytes used on the stack
         */
        virtual unsigned int getUsedStackSize() {
					  // TODO
            if (myId != NULL) {
							uint32_t stackUsed = osThreadGetStackSpace(myId);
							return myStackSize - stackUsed-1;
						}
						else {
							return 0;
						}
        }

    protected:
        /** Delays thread execution for a given time.
         *  @param time[in] number of milliseconds to delay thread execution
         */
        virtual void sleep(unsigned int time) {
					  // TODO
					osDelay(time);
        }

};

} // namespace osapi

#endif // OSAPI_THREAD_RTX_H
