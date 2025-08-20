#include "CUnit/CUnitCI.h"
#include "osapi.h"

class TestThread09 : public osapi::Thread
{
public:
    TestThread09() : Thread(0, 0, osapi::NOT_JOINABLE) { }
private:
    virtual void job() { ; }
};


void TEST_ThreadSuspendInactive(void) {

    printf("Running test 09: thread suspend inactive\n");
    fflush(stdout);

    // create thread
    TestThread09 t;
    // check that the thread is in INACTIVE state
    CU_ASSERT(osapi::INACTIVE == t.getState());

    // at this point it sould be impossible to suspend the thread
    CU_ASSERT(false == t.suspend());
    // nor resume it
    CU_ASSERT(false == t.resume());
}
