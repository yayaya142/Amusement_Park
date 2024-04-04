#pragma once
#ifndef __EXE__
#define __EXE__


#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include "LunaPark.h"

typedef enum {
	eShowAllSystem, eShowSubSystems, eAddSubSystem, eSort, eSearch, eEXIT, eNofMenuOptionTypes
} eMenuOptions;

static const char* MenuOptionStr[eNofMenuOptionTypes] = { "Witness the Wonders of Luna Park Unfold",
														"Reveal Mysterious Components",
														"Add Components","Join Ticket Sorting Extravaganza",
														"Embark on a Quest Of The Ticket Searching"
														,"Exit Menu" };



void printMenu();
void runManualProgram();
void printSubSystems(LunaPark* park);
void saveProgram(LunaPark* park);
void addMenu(LunaPark* park);


#endif 