#include <stdio.h>
#include <crtdbg.h> // TODO: remove before release
#include <stdlib.h>
#include <time.h>
#include "TestsShai.h"
#include "time.h"
#include "General.h"
#include "def.h"
#include "Date.h"
#include "Weather.h"
#include "Time.h"
#include "Shop.h"
#include "Ticket.h"
#include "TicketMaster.h"
#include "TestsDaniel.h"
#include "LunaPark.h"
#include "exe.h"

int main() {
	srand((unsigned int)time(NULL)); // TODO NEED TO ADD TO FINAL PROJECT

	runAllTestsShai();
	runAllTestsDaniel();



	for (int i = 0; i < 20; i++)
	{
		printf("\n");
	}
	//runManualProgram();


	// Debug memory leaks
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW); // this is the pop up message (disable for memory leek location)
	_CrtDumpMemoryLeaks();
	return 0;
}
