#ifndef OSAPI_MORTAL_THREAD_H
#define OSAPI_MORTAL_THREAD_H

#include "osapi_thread_interface.h"
#include "cmsis_os2.h"
#include <stdlib.h>
//#include <rtx_os.h>
#include <cstring>
#include <cstdio>

namespace osapi {

	class MortalThread : public osapi::Thread
{
    public:
        MortalThread(int priority, unsigned int stackSize, const char* name = "unnamed") : Thread(priority, stackSize, JOINABLE, name),	killSignal(0) {
            ;
        }
        virtual ~MortalThread() { ; }
				
        void kill() { 
					killSignal = 1;
				}
		private: 
				sig_atomic_t killSignal;
				//bool run() { return false; }
				//bool join(unsigned int timeout) { return false; }
				//void sleep(unsigned int time) { ; }
		
				/** Implementation of the job method */
        virtual void job(void) {
            begin();
            while (killSignal == 0) {
                loop();
            }
            end();
    }
    protected:
        virtual void begin() { ; }
        virtual void loop() = 0;
        virtual void end() { ; }
};

} // namespace osapi
 
#endif // OSAPI_MORTAL_THREAD_H