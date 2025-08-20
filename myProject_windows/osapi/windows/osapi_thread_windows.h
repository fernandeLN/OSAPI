#ifndef OSAPI_THREAD_WINDOWS_H
#define OSAPI_THREAD_WINDOWS_H

#include "windows.h"
#include <stdlib.h>
#include "windows_proc_info.h"

namespace osapi {

/** Thread interface implementation for Windows. */
    class Thread : public ThreadInterface
    {
    private:
        int myPriority;
        const char* myName;
        unsigned int myStackSize;
        Joinable myIsJoinable;
        HANDLE taskHandle;
        HANDLE joinSemaphore;
        bool isInactive;
        bool isSleeping;

    public:

        static DWORD WINAPI threadFunction(void* argument) {
            Thread* osapiThreadObject = reinterpret_cast<Thread*>(argument);
            if (osapiThreadObject) {
                osapiThreadObject->job();
            }

            osapiThreadObject->isInactive = true;
            if (osapiThreadObject->isJoinable()) {
                ReleaseMutex(osapiThreadObject->joinSemaphore);
            }
            return 0;
        }

        /** Thread constructor.
         *  @param[in] priority thread priority
         *  @param[in] stackSize thread stack size in bytes
         *  @param[in] isJoinable decides if the thread supports join operation or not
         *  @param[in] name optional thread name
         */
        Thread(int priority, unsigned int stackSize, Joinable isJoinable, const char* name = "unnamed") : myPriority(priority), myStackSize(stackSize), myIsJoinable(isJoinable), myName(name) {
            if (this->isJoinable()) {
                joinSemaphore = CreateMutex(NULL, TRUE, NULL);
            }
            isSleeping = false;
            isInactive = true;
            // TODO
        }

        /** Virtual destructor required to properly destroy derived class objects. */
        virtual ~Thread() {
            // TODO
        }

        /** Runs the thread.
         *  @retval true if the thread was started successfully,
         *  @retval false if the thread was not started successfully, or the thread was already running
         */
        virtual bool run() {
            // TODO
            if (!isInactive) {
                return false;
            }

            taskHandle = CreateThread(
                NULL,                //default security attributes
                myStackSize,           //default stack size
                threadFunction,      //function to be executed by the thread
                this,                //argument to the function
                0,                   //default creation flags
                NULL                 //receive thread identifier
            );

            this->setPriority(myPriority);
            isInactive = false;
            return true;

        }

        /** Checks if the thread is running.
         *  @retval true if the thread is running
         *  @retval false if the thread is not running
         */
        virtual bool isRunning() {
            // TODO
            return (!isInactive);
        }

        /** Waits for the thread to finish executing, with a given timeout.
         *  @param timeout[in] number of milliseconds to wait for the thread to finish executing
         *  @retval true if the thread was successfully joined in the given time
         *  @retval false if the thread was not joined within the given time or the thread is not joinable at all
         */
        virtual bool join(unsigned int timeout) {
            // TODO
            if (myIsJoinable) {
                WaitForSingleObject(taskHandle, timeout);
                    return true;
            }
            return false;
        }

        /** Checks, if the thread is joinable.
         *  @retval true if the thread is joinable
         *  @retval false if the thread is not joinable
         */
        virtual bool isJoinable() {
            // TODO

            return (myIsJoinable == JOINABLE);
        }

        /** Suspends thread execution.
         *  @retval true if the thread was suspended successfully
         *  @retval false if the thread was not suspended for some reason
         */
        virtual bool suspend() {
            // TODO
            if (isInactive) {
                return false;
            }
            SuspendThread(taskHandle);
            return true;
        }

        /** Resumes thread execution.
         *  @retval true if the thread was resumed successfully
         *  @retval false if the thread was not resumed for some reason
         */
        virtual bool resume() {
            // TODO
            if (isInactive) {
                return false;
            }
            ResumeThread(taskHandle);
            return true;
        }

        /** Sets thread priority
         *  @param[in] priority new thread priority
         *  @retval true if the priority for the thread was set successfully
         *  @retval false if the priority for the thread was not set successfully for some reason
         */
        virtual bool setPriority(int priority) {
            // TODO
            if (!SetThreadPriority(taskHandle, priority)) {
                return false;
            }
            return true;
        }

        /** Gets the thread priority
         *  @return current thread priority
         */
        virtual int getPriority() {
            // TODO
            return GetThreadPriority(taskHandle);
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
            if (isInactive) {
                return INACTIVE;
            }

            CONTEXT context;
            context.ContextFlags = CONTEXT_ALL;
            GetThreadContext(taskHandle, &context);
            bool isSuspended = (context.ContextFlags & CONTEXT_INTEGER) == CONTEXT_INTEGER;
            WindowsProcInfo procInfo;
            procInfo.Capture();
            SYSTEM_PROCESS_INFORMATION* processInformation = procInfo.FindProcessByPid(GetCurrentProcessId());
            SYSTEM_THREAD_INFORMATION* threadInformation = procInfo.FindThreadByTid(processInformation, GetThreadId(taskHandle));

            if (threadInformation == NULL) {
                return UNKNOWN;
            }

            switch (threadInformation->ThreadState) {
            case StateReady: 
                return READY;
                break;
            case StateRunning:
                return RUNNING;
                break;
            case StateWait:
                if (isSleeping) {
                    return BLOCKED;
                }
                return SUSPENDED;
                break;
            case StateUnknown: 
                return UNKNOWN;
                break;
            case StateStandby:
                return INACTIVE;
                break;
            case StateTerminated: 
                return SUSPENDED;
                break;
            case StateTransition: 
                return BLOCKED;
                break;
            default: 
                return UNKNOWN;
                break;

            }
        }

        
        /** Gets the total size of the stack assigned for this thread
         *  @return total stack size in number of bytes
         */
        virtual unsigned int getTotalStackSize() {
			// TODO
        	return WindowsProcInfo::getTotalStackSize(taskHandle);
        }

        /** Gets the size of the used stack for this thread
         *  @return number of bytes used on the stack
         */
        virtual unsigned int getUsedStackSize() {
			// TODO
            return WindowsProcInfo::getUsedStackSize(taskHandle);
        }

    protected:

        /** Delays thread execution for a given time.
         *  @param time[in] number of milliseconds to delay thread execution
         */
        virtual void sleep(unsigned int time) {
        	// TODO
            isSleeping = true;
            Sleep(time);
            isSleeping = false;
        }
};

} // namespace osapi

#endif // OSAPI_THREAD_WINDOWS_H
