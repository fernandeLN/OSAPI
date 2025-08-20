// 
// 
// TODO: replace this with your own implementation !!!

//done

#ifndef OSAPI_MORTAL_THREAD_H
#define OSAPI_MORTAL_THREAD_H
 
namespace osapi {

class MortalThread : public Thread
{
    public:
        MortalThread(int priority, unsigned int stackSize, const char* name = "unnamed") : Thread(priority, stackSize, JOINABLE, name), killSignal(0) { ; }
        
        virtual ~MortalThread() { ; }
        
        void kill() {
            killSignal = 1;
        }      

		//bool run() { return false; }
		//bool join(unsigned int timeout) { return false; }
		//void sleep(unsigned int time) { ; }
    

    protected:
        virtual void begin() { ; }
        virtual void loop() = 0;
        virtual void end() { ; }

    private:
        sig_atomic_t killSignal;
        //job method
        virtual void job(void) {
            begin();
            while (killSignal == 0) {
                loop();
            }
            end();
        }
    };

} // namespace osapi
 
#endif // OSAPI_MORTAL_THREAD_H