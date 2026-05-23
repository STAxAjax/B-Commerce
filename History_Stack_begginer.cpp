#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    char item[50];
    struct Node* next;
};

struct Node* top = NULL;


void history(char name[]){
    struct Node* newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->item, name);
    newNode->next = top;
    top = newNode;
}


void viewHistory(){
    int choice;
    system("cls");
    printf("=== Purchase History ===\n\n");

    struct Node* temp = top;
    int num = 1;
    
    if(top == NULL){
    	printf("No History\n");
	}

    while(temp != NULL){
        printf("%d. %s\n", num, temp->item);
        temp = temp->next;
        num++;
    }

    printf("\n1. Delete Latest History\n");
    printf("2. Back\n");
    printf("Choose: ");
    scanf("%d", &choice);


    if(choice == 1){
        if(top == NULL){
            printf("\nHistory is empty\n");
            system("pause");
        }
        else{
            struct Node* del = top;
            top = top->next;
            free(del);
            printf("\nLatest history deleted\n");
            system("pause");
        }
    }
}

int main(){
    int menu;
    do{
        system("cls");
        printf("=== History Page ===\n\n");
        printf("1. View History\n");
        printf("2. Exit\n");
        printf("Choose: ");
        scanf("%d", &menu);

        if(menu == 1){
            viewHistory();
        }

    }while(menu != 2);

    return 0;
}