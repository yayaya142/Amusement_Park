#include <stdio.h>
#include <crtdbg.h> // TODO: remove before release
#include "def.h"
#include "TestsDaniel.h"
int main() {
	
	runAllTestsDaniel();

	// Debug memory leaks
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW); // this is the pop up message (disable for memory leek location)
	_CrtDumpMemoryLeaks();
	return 0;
}