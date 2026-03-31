#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct user{
	char username[101];
	
	bool isAdmin = false;
	bool isWorker = false;
	
};
void Register
void loginPage (){
	int slct=0;
	
	do {
		char username [101] = "";
		char password [101]= "";
		printf ("WELCOME TO B-COMMERCE\n");
		printf ("\nLOGIN\n");
		printf ("Username >> ");
		scanf ("%[^\n]",username); getchar();
		
		printf ("Password >> ");
		scanf("%[^\n]",password);getchar();
	}while (1==1);
}
int main (){
	loginPage();
}