#include "Person.h"
#include "General.h"
#define MAX_HEIGHT 300
#define MAX_AGE 120

int initPerson(Person *p, char* name, int height, int age) {
	if(!isValidInfo(name , height, age)){
		return 0;
	}
	p->name = name;
	p->height = height;
	p->age = age;
	//p->id = id;
	return 1;

}

int isValidInfo(char* name, int height, int age) { //TODO: finish user interaction function
	if (!validName(name)) {
		return 0;
	}
	if (height < 0 || height >MAX_HEIGHT) {
		return 0;
	}
	if (age < 0 || age > MAX_AGE) {
		return 0;
	}
	/*if (id < 0) {
		return 0;
	}*/
	return 1;
}

int comparePersonByHeight(const Person* p1, const Person* p2) {
	if (p1->height == p2->height) {
		return 0;
	}
	return p1->height - p2->height;
}


void printPerson(const Person* p) {
	if (p == NULL) {
		printf("Person is NULL\n");
		return;
	}
	else {
		printf("Name: %s\n", p->name);
		printf("Age: %d\n", p->age);
		printf("Height: %.2f\n", p->height);
	}
}

void freePerson(Person* p) {
	/*if (p->name != NULL) {
		free(p->name);
	}*/
	if (p != NULL) {
		free(p);
	}
}