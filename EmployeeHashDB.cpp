#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conio.h"

typedef struct employee {
	char name [75];
	short isFull;
	struct employee* next;
}emp;

emp* createNode (char* name){
	emp* newNode = (emp*)malloc (sizeof(emp));
	strcpy(newNode->name,name);
	newNode->isFull=0;
	newNode->next=NULL;
	return newNode;
}

emp employeeHDB[26];

int hashFunction (char* letter){
	int code = letter[0];
	if (code>=97 && code<123){
		code -=97;
	}else if (code >= 65 && code<91){
		code -=65;
	}
	return code%26;
}

void putDataInHash(emp* hashIndex, emp* employeeData){
	strcpy(hashIndex->name,employeeData->name);
	hashIndex->isFull=1;
	return;
}

void hashingFunction (emp* employeeData){
	int index = hashFunction(employeeData->name);
	if (employeeHDB[index].isFull!=0){
		emp* temp = employeeHDB+index;
		while (temp->next!=NULL) temp = temp->next;
		temp->next=employeeData;
	}else{                                 
		putDataInHash(employeeHDB+index,employeeData);
		
	}
	employeeData=NULL;
	return;
}

void insertWorker (){
	char name [101];
	printf ("masukan nama pekerja >>");
	scanf ("%[^\n]",name);getchar();
	hashingFunction(createNode(name));
	return;
}

//void insertSubNode(emp* employeeData, char key){
//	
//} untuk nanti lah

void printWorker(){
	for (int i =0;i<26;i++){
		printf("-%s\n",employeeHDB[i].name);
		if (employeeHDB[i].next!=NULL){
			emp* temp = employeeHDB[i].next;
			while (temp!=NULL){
				printf("	%s\n",temp->name);
				temp=temp->next;
			}
		}
	}
}

int main () {
	insertWorker ();
	insertWorker ();
	insertWorker ();
	insertWorker ();

	printWorker();
}