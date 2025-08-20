#include <cstdio>
#include "FreeRTOS.h"
#include "task.h"
#include "test_osapi.h"

extern "C" void exit(int status) {
    while(1) { ; }
}

int main(void) {
    std::printf("Running tests\n");
    xTaskCreate(taskOSAPI_TEST, "test", configMINIMAL_STACK_SIZE + 512, NULL, 3, NULL);
    vTaskStartScheduler();
}

// Stack overflow handler for FreeRTOS
extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    std::printf("Stack overflow in task: %s\n", pcTaskName);
    while(1) {
        ;
    }
}

