#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
/*Notes

in user state:
	0=user
	1=worker
	2=admin
	99=debugger

End of Notes*/


typedef struct User{
	char username[101];
	bool isAdmin = false;
	bool isWorker = false;
}User;

//File Abstraction

long hashFunction (char *p){
    long temp=0;
    long h=5381;
    while ( temp = *p++){
        h = (h<<5)+h+temp;
    }
    return h;
}

//End of File Abstraction


/*
===================================================================================================================================================

FILE PROCESSING

===================================================================================================================================================
*/

void fileWriter (char *name, long hashed_Pass, int user_State){
	FILE *fp;
	fp = fopen ("data/userdata.txt","w");
	fprintf (fp, "%[^:]:%ld:%d\n",name,hashed_Pass,user_State);
	fclose (fp);
}

void fileAppend (char *name, long hashed_Pass, int user_State){
	FILE *fp;
	fp = fopen ("data/userdata.txt","a");
	if (fp == NULL){
		fileWriter (name,hashed_Pass,user_State);
	}else {
		fprintf (fp, "%[^:]:%ld:%d\n",name,hashed_Pass,user_State);
	}
	fclose (fp);
}

void fileCopyWriter (char *name, long hashed_Pass, int user_State){
	FILE *fp;
	fp = fopen ("data/userdatatemp.txt","w");
	fprintf (fp, "%[^:]:%ld:%d\n",name,hashed_Pass,user_State);
	fclose (fp);
}

void fileCopyAppend (char *name, long hashed_Pass, int user_State){
	FILE *fp;
	fp = fopen ("data/userdatatemp.txt","a");
	if (fp == NULL){
		fileCopyWriter (name,hashed_Pass,user_State);
	}else {
		fprintf (fp, "%[^:]:%ld:%d\n",name,hashed_Pass,user_State);
	}
	fclose (fp);
}

// file saving

void fileCopyr(){
	FILE *fp;
	char tempN[100];
	long tempP;
	int tempS;
	int i=0;
	fp = fopen ("data/userdata.txt","r");
	if (fp == NULL){
		return;
	}else {
		while (fscanf(fp,"%[^:]:%ld:%d\n",name,hashed_Pass,user_State)==3){
			if (i==0){
				fileCopyWriter(tempN,tempP,tempS);
				i++;
			}else{			
				fileCopyAppend(tempN,tempP,tempS);
			}
		}
	}
	fclose (fp);
	return;
}


void filePaster(){
	char tempN[100];
	long tempP;
	int tempS;
	FILE* fpr;
	int i = 0;
	fpr = fopen ("data/userdatatemp.txt","r");
	while (fscanf(fpr,"%[^:]:%ld:%d\n",name,hashed_Pass,user_State)==3){
		if (i==0){
			fileWriter(tempN,tempP,tempS);	
		i++;
		}else{
			fileAppend(tempN,tempP,tempS);
		}
	}
	fclose (fpr);
	return;
}

//End of File saving





/*

end of File Processing
-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/

*/

void Register(){
}
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