#include "Worker.h"

int initWorker(Worker* w,Person* p, Department dep) { 
	if(!isValidInfoWorker(dep)) {
		return 0;
	}
	w->person = p;
    w->WorkerId = generateWorkerID();
	w->department = dep;
    return 1;
}
void initWorkerByUser(Worker* w) {
	Person* p = malloc(sizeof(Person));
	if (!p) {
		printf("Memory allocation failed\n");
		return ;
	}
	initPersonByUser(p);
	int flag = 0;
	int dep;
	do {
		if (flag > 0) {
			printf("Please try again\n");
		}
		printf("Enter department:\n");
		for (int i = 0; i < eNofTypes; i++) {
			printf("%d. %s\n", i, typeTilte[i]);
		}
		scanf("%d", &dep);
		flag++;
	} while (!initWorker(w, p, dep));
}


int generateWorkerID() {
	int id_temp = randomNum(65, 90);
	// Generate a random ID of 10 characters. so it can generate 36^10 different IDs
	for (int i = 0; i < WORK_ID; i++) {
			// Generate a random uppercase letter (65-90 in ASCII table ---> A-Z )
			id_temp= id_temp*10 + randomNum(65, 90);
	}
	return id_temp;
}

int isValidInfoWorker(Department department) {
	if (department < 0 || department >= eNofTypes) {
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

void printWorker(const Worker* w) {
	printPerson(w->person);
	printf("Worker ID: %d\n", w->WorkerId);
	printf("Department: %s\n", typeTilte[w->department]);
}

void freeWorker(Worker* w) {
	freePerson((w->person));
	if (w != NULL) {
		free(w);
	}
}