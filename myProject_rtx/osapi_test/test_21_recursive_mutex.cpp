#include "CUnit.h"
#include "osapi.h"

static osapi::RecursiveMutex m;

void TEST_RecursiveMutex(void) {

    printf("Running test 21: recursive mutex                 ");
    
    for (int i = 0; i < 3; i++) {
        // lock mutex
        CU_ASSERT(true == m.lock(100));
        // another lock should not fail too
        CU_ASSERT(true == m.lock(100));
        // another lock should not fail too
        CU_ASSERT(true == m.lock(100));
        // check unlock
        m.unlock();
        // check unlock
        m.unlock();
        // check unlock
        m.unlock();
    }
}
