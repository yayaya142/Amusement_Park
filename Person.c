#include "Person.h"
#include "General.h"
#define MAX_HEIGHT 300
#define MAX_AGE 120

Person* initPerson(char* name, double height, int age) {
	Person* person = NULL;
	if(!isValidInfo(name , height, age)){
		return NULL;
	}
	
 	person = (Person*)malloc(sizeof(Person));			
	if (!person) {
		printf("Memory allocation failed\n");
		return NULL;
	}
	person->pDerived = NULL;
	person->name = name;
	person->height = height;
	person->age = age;

	//init the interfaces
	person->printPerson = printPerson;
	person->freePerson = freePerson;
	person->comparePersonByHeight = comparePersonByHeight;


	return person;

}

Person* initPersonByUser() {
	Person* person = NULL;
	int flag = 0;
	char* name = NULL;
	int age;
	double height;
	do {
		if (flag > 0) {
			printf("Please try again\n");
			free(name);
		}
		name = getStrExactName("Enter name :\n");
		
		printf("Enter age:\n");
		scanf("%d", &age);

		printf("Enter height:\n");
		scanf("%lf", &height);
		flag=1;
		person = initPerson(name, height, age);
	} while (!person);
	return person; 
}

int isValidInfo(char* name, double height, int age) { 
	if (!validName(name)) {
		printf("Invalid name\n");
		return 0;
	}
	if (height <= 0 || height >MAX_HEIGHT) {
		printf("Height valid only between 0 and %d\n", MAX_HEIGHT);
		return 0;
	}
	if (age <= 0 || age > MAX_AGE) {
		printf("Age valid only between 0 and %d\n", MAX_AGE);
		return 0;
	}
	return 1;
}

int comparePersonByHeight(const Person* p1, const Person* p2) {
	if (p1 == NULL || p2 == NULL) {
		return 0;
	}
	if (p1->height == p2->height) {
		return 0;
	}
	return (int)(p1->height - p2->height);
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
	
	if(p == NULL){
		return;
	}
	else {
		if (p->name != NULL) {
			free(p->name);
		}
		free(p);
	}
}
//void* pDerived;
//char* name;
//int age;
//float height;
//---------function pointers (interfaces)-------
//fptrinitPersonByUser initPersonByUser;
//fptrPrintPerson printPerson;
//fptrFreePerson freePerson;
//fptrComparePersonByHeight comparePersonByHeight;

// save and load functions
int savePersonToTextFile(const Person* person, FILE* fp){
	//validate the input
	if (person == NULL || fp == NULL) {
		return 0;
	}
	if(!isValidInfo(person->name, person->height, person->age)){
		return 0;
	}

	//save the name
	if (writeStringToTextFile(fp, person->name) == 0) {
		return 0;
	}
	//save the age
	if (writeIntToTextFile(fp, person->age) == 0) {
		return 0;
	}
	//save the height
	if (writeDoubleToTextFile(fp, person->height) == 0) {
		return 0;
	}
	return 1;
}
int loadPersonFromTextFile(Person** person, FILE* fp){
	//validate the input
	if (fp == NULL) {
		return 0;
	}
	char* name;
	int age;
	double height;

	//load the name
	char buffer[MAX_BUFFER_SIZE];
	if(readStringFromTextFile(fp, buffer, MAX_BUFFER_SIZE) == 0){
		return 0;
	}
	//load the age
	if(readIntFromTextFile(fp, &age) == 0){
		return 0;
	}
	//load the height
	if(readDoubleFromTextFile(fp, &height) == 0){
		return 0;
	}
	//init the person
	name = (char*)malloc(strlen(buffer) + 1);
	if(!name){
		return 0;
	}
	strcpy(name, buffer);
	*person = initPerson(name, height, age);
	if(!*person){
		return 0;
	}
	return 1;
}
int savePersonToBinFile(const Person* person, FILE* fp){
	if (fp==NULL) {
		return 0;
	}
	if(!isValidInfo(person->name, person->height, person->age)){
		return 0;
	}
	//save the name
	if (writeStringTobinFile(fp, person->name) == 0) {
		return 0;
	}
	//save the age
	if(writeGeneralToBinFile(fp, &person->age, sizeof(int)) == 0){
		return 0;
	}
	//save the height
	if(writeGeneralToBinFile(fp, &person->height, sizeof(double)) == 0){
		return 0;
	}
	return 1;
}
int loadPersonFromBinFile(Person** person, FILE* fp){
	if(fp == NULL){
		return 0;
	}
	char* name;
	int age;
	double height;
	//load the name
	name = readStringFromBinFile(fp);
	if(name == NULL){
		return 0;
	}
	//load the age
	if(readGeneralFromBinFile(fp, &age, sizeof(int)) == 0){
		free(name);
		return 0;
	}
	//load the height
	if(readGeneralFromBinFile(fp, &height, sizeof(double)) == 0){
		free(name);
		return 0;
	}

	//init the person
	*person = initPerson(name, height, age);
	if(!person){
		free(name);
		return 0;
	}
	return 1;


}