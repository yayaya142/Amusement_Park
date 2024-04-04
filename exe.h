#pragma once
#ifndef __EXE__
#define __EXE__


#include <crtdbg.h> // TODO: remove before release
#include <stdio.h>
#include <time.h>
#include "LunaPark.h"
#include <windows.h> // we use for the demo program to use Sleep()

typedef enum {
	eShowAllSystem, eShowSubSystems, eAddSubSystem, eSort, eSearch, eChangeTime, eChangeWeather, ePrintProfit, eAutomaticRun, eEXIT, eNofMenuOptionTypes
} eMenuOptions;

static const char* MenuOptionStr[eNofMenuOptionTypes] = { "Witness the Wonders of Luna Park (print luna park)",
														"Reveal Mysterious Components (Print Subsystem components)",
														"Add Components"
														,"Join Ticket Sorting Extravaganza (Sort)",
														"Embark on a Quest Of The Ticket Searching (search)",
														"Shift the Magic Hour of Opening (Change time)",
														"Command the Weather at Luna Park (Change Weather)",
														"Reveal the Mystical Profit of Luna Park (Print Profit)",
														"Run Demo Program",
														"Exit Menu" };



void printMenu();
void runManualProgram();
void printSubSystems(LunaPark* park);
void saveProgram(LunaPark* park);
void addMenu(LunaPark* park);
void runDemoProgram();
void printWaitingDot();
void printEndCredits();
#endif 