#include "Worker.h"

Person* initWorker(Department dep, char* name, float height, int age){
	Worker* pWorker;
	Person* pBase;
	pBase = initPerson(name, height, age);
	if (!pBase) {
		return NULL;
	}
	pWorker = (Worker*)malloc(sizeof(Worker));
	if (!pWorker) {
		printf("Memory allocation failed\n");
		pBase->freePerson(pBase);
		return NULL;
	}
	//init derived object
	pBase->pDerived = pWorker;
	
	if(!isValidInfoWorker(dep)) {
		return 0;
	}
	pWorker->WorkerId = generateWorkerID();
	pWorker->department = dep;

	//change base class interfacese
	pBase->freePerson = freeWorker;
	pBase->printPerson = printWorker;

    return pBase;
}

Person* initWorkerByUser(Worker* w) {
	/*Person* p = malloc(sizeof(Person));
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
	} while (!initWorker(dep,name, height, age));*/
	return NULL;
}


int generateWorkerID() {
	int id_temp = randomNum(1, 9);
	for (int i = 0; i < WORK_ID; i++) {
			id_temp= id_temp*10 + randomNum(1, 9);
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

void printWorker(const Person* pWorker) {
	const Worker* w = pWorker->pDerived;
	
	printPerson(pWorker);
	printf("Worker ID: %d\n", w->WorkerId);
	printf("Department: %s\n", typeTilte[w->department]);
}

void freeWorker(Person* worker) {
	Worker* w ;
	w = worker->pDerived;
	free(w);
	freePerson(worker);
	
}