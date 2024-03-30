#include "Person.h"


int initPerson(Person *p, char* name, int height, int age, int id) {
	if(!isValidInfo(name , height, age , id)){
		return 0;
	}
	p->name = name;
	p->height = height;
	p->age = age;
	p->id = id;
	return 1;

}

int isValidInfo(char* name, int height, int age, int id) { //TODO: finish user interaction function
	for (int i = 0; i < strlen(name); i++){
		if (((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z')) && name[i] != ' ') {
			return 0;
		}
	}
	if (height < 0 || height >300) {
		return 0;
	}
	if (age < 0 || age > 120) {
		return 0;
	}
	if (id < 0) {
		return 0;
	}
	return 1;
}

int comparePersonById(Person* p1, Person* p2) {
	if (p1->id == p2->id) {
		return 0;
	}
	return p1->id - p2->id;
}

int comparePersonByHeight(Person* p1, Person* p2) {
	if (p1->height == p2->height) {
		return 0;
	}
	return p1->height - p2->height;
}


void printPerson(Person* p) {
	printf("Name: %s\n", p->name);
	printf("Age: %d\n", p->age);
	printf("Height: %.2f\n", p->height);
	printf("ID: %d\n", p->id);
}

void freePerson(Person* p) {
	if (p != NULL) {
		free(p);
	}
}