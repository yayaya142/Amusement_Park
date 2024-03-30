#include "Worker.h"

int initWorker(Worker* w, int workerId, Department dep) {
    if (!initPerson(&w->person, "worker name",170, 21, 1212)) {
        freePerson(&w->person);
        free(w);
        return 0;
	}
	if(!isValidInfoWorker(workerId, dep)) {
		return 0;
	}
    w->WorkerId = workerId;
	w->department = dep;
    return 1;
}
int isValidInfoWorker(int WorkerId, Department department) {
	if (WorkerId < 0) {
		return 0;
	}
	if (department < 0 || department >= NofTypes) {
		return 0;
	}
	return 1;
}

int compareWorkerById(Worker* w1, Worker* w2) {
	if (w1->WorkerId == w2->WorkerId) {
		return 0;
	}
	return w1->WorkerId - w2->WorkerId;
}

void printWorker(Worker* w) {
	printPerson(&w->person);
	printf("Worker ID: %d\n", w->WorkerId);
	printf("Department: %s\n", typeTilte[w->department]);
}

void freeWorker(Worker* w) {
	//freePerson(&(w->person)); TODO: remove when user interaction is done
	if (w != NULL) {
		free(w);
	}
}