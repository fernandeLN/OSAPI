#include "cmsis_os2.h"
#include <cstdio>
#include "test_osapi.h"

extern "C" void exit(int status) {
	while(1) {
		;
	}
}

int main(void) {
	std::printf("RTX OSAPI Test application\n");

	// Initialize the RTOS Kernel.
	osKernelInitialize();
	
	// Run test thread
	const osThreadAttr_t testThreadAttr = {
		NULL, //name of the thread
		0, // attribute bits
		NULL, // memory for control block
		0, // size of provided memory for control block
		NULL, // memory for stack
		4096, // size of stack
		osPriorityNormal, // priority
		0, // TrustZone module identifier
		0 // reserved (must be 0) 
	};
	osThreadNew(taskOSAPI_TEST, NULL, &testThreadAttr);
	
	// Start the OS
	osKernelStart();

}
