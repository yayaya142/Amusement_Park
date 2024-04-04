#ifndef __EXE__
#define __EXE__


#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include "LunaPark.h"

typedef enum {
	eShowAllSystem, eShowSubSystems, eAddSubSystem, eSort, eSearch, eEXIT, eNofMenuOptionTypes
} eMenuOptions;

static const char* MenuOptionStr[eNofMenuOptionTypes] = { "","Exit Menu" };



void printMenu();
void runManualProgram();
void saveProgram(LunaPark* park);


#endif 
