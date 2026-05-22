#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <stdbool.h>

typedef struct User{
	
	char username[31];
	char password[16];
	short status;// 0=not filled, 1=buyer, 2=worker, 999=admin
	struct User * next;
	
}User;

User* userHash =(User*)calloc (26,sizeof (User));

//username;password;status

//masukan input hashing menggunakan chaining collision handling

void startUpMenu () {
	short slct=0;
	do {
		printf ("\n=====================\n");
		printf("Welcome to B-Commerce \n");
		printf ("\n=====================\n");
		printf ("1. Login\n"); 
		printf ("2. Register\n"); 
		printf ("3. About Us\n"); 
		printf ("4. Career\n"); 
		printf ("5. Exit\n"); 
		printf ("pick your selection (1-5) >>"); scanf ("%d",&slct);
		
		switch (slct){
			case 1:
				
				break;
			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
				
				break;
			case 5:
				printf ("bye bye");
				break;
			default:
				printf ("Invalid Selection");
				break;
		}
		
		
	}while (slct != 5 );
}

int main () {
	printf ("%d",userHash[10].next);
	startUpMenu();
}