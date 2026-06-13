#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


typedef struct product_Detail{
	int quantity;
	int price;
	bool available;
}Detail;

typedef struct Node {
	char key[101];
	struct Node* left;
	struct Node* right;
	Detail item_Detail;
	// can use height variable, may be useful for other data structures, B-Tree?
}Node;
void buyerMenu (Node* root);
void Menu (Node* root);
//====================================================================================================

typedef struct user{
	char name[50];
	char pass[50];
	short role;
	struct user *next;
}User;

User currentUser;
void emptyCurrUser (){
	strcpy (currentUser.name,"\0");
	strcpy (currentUser.pass,"\0");
	currentUser.role = 0;
	currentUser.next = NULL;
}


void transferDataToCurrUser (User* src){
//	printf ("%s",src->pass);
	strcpy (currentUser.name, src->name);
	strcpy (currentUser.pass, src->pass);
	currentUser.role=src->role;
	currentUser.next= NULL;
	printf ("%s",currentUser.pass);
}

User* createNodeUser(char* name,short role,char* pass){
	User* newNode = (User*)malloc(sizeof(User));
	strcpy (newNode->name, name);
	strcpy (newNode->pass, pass);
	newNode->role = role;
	newNode->next=NULL;
	return newNode;
}
User* userHash = (User*)calloc(26,sizeof(User));

int hasFunction(char *dst){
	int temp = dst[0];
	if (temp < 97) {
	return -1;
	}
	int key = temp - 97;
	return key;
}

void tolowerstr(const char *src, char *dst){
	int i;
	for (i = 0; i < strlen(src); i++){
		dst[i] = tolower(src[i]);
	}
	dst[i] = '\0';
}
void hashTable(User a){
	short key;
	char temp[100];
	tolowerstr(a.name, temp);
	key = hasFunction(temp);
	if(userHash[key].role != 0){
		User* temp2 = NULL;
		temp2 = &userHash[key];
		while (temp2->next!=NULL){
			temp2=temp2->next;
		}
		temp2->next = createNodeUser(a.name,a.role,a.pass);
		temp2=NULL;
		return;
	}else{
		strcpy(userHash[key].name, a.name);
		strcpy(userHash[key].pass, a.pass);
		userHash[key].role = a.role;
		return;
	}
	return;
}

//====================================================================================================



int createUser (char* userN, char* passN, short role) {
	User* tempUser = createNodeUser(userN,role,passN);
	hashTable(*tempUser);
	return 1;
}

void Register () {
	char tempName[50];
	char tempPass[50];
	int inptVldt =0;
	while (inptVldt != 1){
		printf ("Masukan Username>> ");
		scanf ("%[^\n]",tempName);getchar();
		printf ("Masukan Password>> ");
		scanf ("%[^\n]",tempPass);getchar();
		inptVldt = createUser (tempName,tempPass,1);

	}
	
	return;
}
//==================================================================================================
int findName (char * username ){
	char lowerUsername [50];
	tolowerstr(username,lowerUsername);
	short key = hasFunction (lowerUsername);
	User * temp =  &userHash [key];
	while (temp != NULL){
		if (strcmp(username, temp->name)==0){
		printf ("%s\n%s", temp->pass,temp->name);
			transferDataToCurrUser(temp);
			return 1;
			break;
		}
		temp=temp->next;
	}
	return  0;
}
short Login () {
	char tempName[50];
	char tempPass[50];
	short validation = 0;
	short cntValidation = 0;
	while (validation != 1){
		printf ("Masukan Username>> ");
		scanf ("%[^\n]",tempName);getchar();
		if (findName (tempName)){
			cntValidation = 1;
		}else {
			cntValidation = 0;
		}
		if (cntValidation){
			
			printf ("Masukan Password>> ");
			scanf ("%[^\n]",tempPass);getchar();
			printf ("%s\n",currentUser.pass);
			if (strcmp (tempPass,currentUser.pass)==0){
				validation = 1;	
				return 1;
			}else {
				emptyCurrUser ();
				validation = 0;
			}
		}
	
	}
}


void startUpMenu () {
	short slct=0;
	Node* root=NULL;
	do {
		short isLogin = 0;
		printf ("\n=====================\n");
		printf("Welcome to B-Commerce \n");
		printf ("\n=====================\n");
		printf ("1. Login\n"); 
		printf ("2. Register\n"); 
		printf ("3. About Us\n"); 
		printf ("4. Career\n"); 
		printf ("5. Exit\n"); 
		printf ("pick your selection (1-5) >>"); scanf ("%d",&slct);getchar();
		
		switch (slct){
			case 1:
				isLogin = Login();
				break;
			case 2:
				Register ();
				break;
			case 3:
				
				break;
			case 4:
				
				break;
			case 5:
				printf ("bye bye %s",currentUser.name);
				emptyCurrUser();
				break;
			default:
				printf ("Invalid Selection");
				break;
		}
		
		if (isLogin){
				
			switch (currentUser.role){
			
				case 1:
					buyerMenu (root);
					break;
				case 2:
					Menu (root);
					break;
				case 99:
					break;
				default :
					break;
			}
		}
	}while (slct != 5 );
}



/* ===============================================================================================
	MAIN PRODUCT PAGE, AVL BST
==============================================================================================*/

void printProduct (Node* root){
	printf ("\n========================\n");
	printf ("Nama Product : %s \n",root->key);
	printf ("Status Ketersediaan : %s \n",root->item_Detail.available? "true":"false");
	printf ("Harga Barang : %d \n",root->item_Detail.price);
	printf ("Quantitas Tersedia : %d \n",root->item_Detail.quantity);
	printf ("\n========================\n");
	}

void fillDetail (Node* root,int price, int quanity, bool availablity){
	root->item_Detail.available=availablity;
	root->item_Detail.price=price;
	root->item_Detail.quantity=quanity;
}

void fillDetailDefault (Node* root){
	root->item_Detail.available=false;
	root->item_Detail.price=-99;
	root->item_Detail.quantity=-99;
}
int checkBallance (Node* root,Node* mainRoot);
Node* doAVL (Node* root);

Node* createNode (char *key){
	Node* newNode = (Node*)malloc (sizeof (Node));
	strcpy(newNode->key, key);
	newNode->left=NULL;
	newNode->right=NULL;
	fillDetailDefault(newNode);
	return newNode;
}

Node* insertNode(Node* root, char *key,int price, int quantity, bool availablity){
	if (root==NULL){
	Node* found =  createNode(key);	
	fillDetail(found,price,quantity,availablity );
	return found;
	} 
	
	if (strcmp(key,root->key)<0){
		root->left = insertNode(root->left,key,price,quantity,availablity);
//		printf ("\n%s goes left because %s with diffrence %d \n",key,root->key,strcmp(key,root->key));
	}else if (strcmp (key, root->key)>0){
		root->right= insertNode(root->right, key,price,quantity,availablity);
//		printf ("\n%s goes right because %s with diffrence %d \n",key,root->key,strcmp(key,root->key));
	}
	int isBalance = checkBallance(root,root);
	printf("%d",isBalance);
	if (!(isBalance <=1 && isBalance>=-1)){
		return doAVL(root);
	}
		puts("hi");
	return root;
}


int findSigma (Node* root, char *key){
	if (strcmp(root->key,key)==0)
		printProduct(root);
		return 1;
	
	if (strcmp (key,root->key)<0){
		printf ("\n%s %s\n",key,root->key);
		if (root->left==NULL){
			return (-1);
		}

		return findSigma (root->left,key);
 	}else if (strcmp (key,root->key)>0){
		if (root->right ==NULL){
			return (-1);
		}
		return findSigma (root->right,key);
	}
}

Node* leftRotate (Node* root){
	Node* temp=root->right->left;
	root->right->left=root;
	root=root->right;
	root->left->right=temp;
	temp=NULL;
	return root;
}

Node* rightRotate (Node* root){
	Node* temp=root->left->right;
	root->left->right=root;
	root=root->left;
	root->right->left=temp;
	temp=NULL;
	return root;
}



int checkMax (int num1, int num2){
	
	if (num1<0){
		num1*=-1;
	}
	if (num2<0){
		num2*=-1;
	}
	
	if(num1 > num2){
		return num1;
	}else{
		return num2;
	}
}

Node* doAVL (Node* root){ // (maybe fixed) potential error because root is not connected to main tree?
	//need 4 things to check, LL, RR, LR, RL
	if (checkBallance(root->left,root->left)>0){ //LL
		return rightRotate(root);
	}
	if (checkBallance(root->right,root->right)<0){ //RR
		return leftRotate(root);
	}
	if (checkBallance(root->left,root->left)<0){ //LR
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (checkBallance(root->right,root->right)>0){//RL
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}



int checkBallance (Node* root,Node* mainRoot){
	if (root == NULL){
		return 0;
	}
	int diff=0;
	
	int Lheight = checkBallance(root->left,mainRoot);
	int Rheight = checkBallance(root->right,mainRoot);
//	if (Lheight ==-10 || Rheight ==-10)return -10;
	diff = Lheight-Rheight;
	if ((diff <=1 && diff>=-1)&& root != mainRoot){
		return checkMax (Lheight,Rheight)+1;
	}else{
		return diff;
	}
	return 0;
}


int findHeight (Node* root){
	int leftHeight=0;
	int rightHeight=0;
	if (root->left==NULL && root->right==NULL){
		return 1;
	}
	if (root->left) leftHeight=findHeight (root->left);
	if (root->right)rightHeight=findHeight (root->right);
	return checkMax(leftHeight,rightHeight)+1;
}


void printSpace (int num){
	for (int i = 0 ; i<(num*5);i++){
		printf (" ");
	}
}//this function purpouse is to prit space alot

void printTree (Node* root,int spaceAmmount, char symbol ){
	if (root->right)printTree (root->right,spaceAmmount+1,'/');
	printProduct(root);
	if (root->left)printTree (root->left,spaceAmmount+1,'\\');
	return;
}


Node* AddProduct (Node* root){
	printf ("Product name >> ");
	char name [101];
	int price = 0;
	int q= 0;
	bool a= true;
	scanf ("%[^\n]",name);getchar();
	printf ("masukan harga>> ");scanf ("%d", &price);
	printf ("masukan quantitas>> ");scanf ("%d", &q);
	return insertNode(root,name,price,q,a);
	
}

void Menu (Node* root) {
	int inpt= 0;
	do{
		printf("==============================================\n");
		printf("Welcome to B- Commerce for Worker %s \n\n",currentUser.name);
		printf("Choose your selection\n");
		printf("1. Add product\n");
		printf("2. Look at product list\n");
		printf("3. Exit\n>> ");
		scanf ("%d",&inpt);getchar();
		system ("cls");
		
		switch (inpt){
			case 1:
				root = AddProduct (root);
				break;
			case 2:
				printTree(root,0,' ');
				break;
			case 3:
				printf ("bye bye %s", currentUser.name);
				break;
			default:
				printf ("Wrong input\n");
				break;
		}
		
	}while (inpt != 3);
}

/*====================================================================================================
QUEUE
================*/
struct Que{
    char nama[50];
    char barang[50];
    int qty;
    int harga;
    struct Que *next;
};

struct Que *head = NULL;
struct Que *tail = NULL;


void addQueue(char nama[], char barang[], int qty, int harga){
    struct Que *newNode = (struct Que*)malloc(sizeof(struct Que));

    strcpy(newNode->nama, nama);
    strcpy(newNode->barang, barang);
    newNode->qty = qty;
    newNode->harga = harga;
    newNode->next = NULL;

    if(head == NULL){
        head = tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
}

void viewQueue(){
    system("cls");

    printf("=== DATA ANTRIAN ===\n\n");

    if(head == NULL){
        printf("Queue is empty.\n");
    }
    else{
        struct Que *temp = head;
        int no = 1;

        printf("No\tNama\tBarang\tQty\tHarga\n");
        printf("=========================================\n");

        while(temp != NULL){
            printf("%d\t%s\t%s\t%d\t%d\n",
                   no++,
                   temp->nama,
                   temp->barang,
                   temp->qty,
                   temp->harga);

            temp = temp->next;
        }
    }

    printf("\n");
    
}

Node * searchWhere (Node* root,char * key){
	if (strcmp(root->key,key)==0)
		return root;
	
	if (strcmp (key,root->key)<0){
		printf ("\n%s %s\n",key,root->key);
	

		return searchWhere (root->left,key);
 	}else if (strcmp (key,root->key)>0){
		
		
		return searchWhere (root->right,key);
	}
}
void inptTQue (Node* root){
	printf ("apa yang anda ingin beli, nama >> ");
	char productName [100];
	scanf ("%[^\n]",productName);getchar ();
	Node* productSearched = searchWhere(root, productName);
	addQueue(productSearched->key,"",productSearched->item_Detail.quantity,productSearched->item_Detail.price);
}
/* =======================================================
HISTORY
===================*/
struct hist{
    char nama[50];
    char barang[50];
    int qty;
    int harga;
    struct hist *next;
};

struct hist *Hhead = NULL;
struct hist *Htail = NULL;

void addHistory(char nama[], char barang[], int qty, int harga){
    struct hist *newNode = (struct hist*)malloc(sizeof(struct hist));

    strcpy(newNode->nama, nama);
    strcpy(newNode->barang, barang);
    newNode->qty = qty;
    newNode->harga = harga;
    newNode->next = NULL;

    if(head == NULL){
        Hhead = Htail = newNode;
    }
    else{
    	newNode->next = Hhead;
    	Hhead= newNode;
		newNode=NULL;
    }
}

void popQueueHeadIntoHistory (){
	addHistory(head->nama,head->barang,head->qty,head->harga);
	struct Que* temp = head;
	head=head->next;
	free (temp);
	temp = NULL;
	return;
}
void viewHistory(){
    system("cls");

    printf("=== DATA ANTRIAN ===\n\n");

    if(Hhead == NULL){
        printf("Queue is empty.\n");
    }
    else{
        struct hist *temp = Hhead;
        int no = 1;

        printf("No\tNama\tBarang\tQty\tHarga\n");
        printf("=========================================\n");

        while(temp != NULL){
            printf("%d\t%s\t%s\t%d\t%d\n",
                   no++,
                   temp->nama,
                   temp->barang,
                   temp->qty,
                   temp->harga);

            temp = temp->next;
        }
    }

    printf("\n");
    
}
//===================

void buyerMenu (Node* root) {
		int inpt= 0;
		root= insertNode(root,"bom",100,101,true);
		root= insertNode(root,"bom2",1200,1201,true);
	do{
		printf("==============================================\n");
		printf("Welcome to B- Commerce %s \n\n",currentUser.name);
		printf("Choose your selection\n");
		printf("1. search for product\n");
		printf("2. Look at product list\n");
		printf("3. Input to queue\n");
		printf("4. View current queue\n");
		printf("5. buy top of the queue\n");
		printf("6. view buy history\n");
		printf("7. Exit\n>> ");
		scanf ("%d",&inpt);getchar();
		system ("cls");
		
		switch (inpt){
			case 1:{
				char searchedProduct [100];
				scanf ("%[^\n]",searchedProduct);getchar();
				short isFind= findSigma(root,searchedProduct);
				if (!isFind){
					printf ("Product tidak ditemukan \n");
				}
				break;
				}
				
			case 2:
				printTree(root,0,' ');
				break;
			case 3:
				inptTQue(root);
				break;
			case 4:
				viewQueue();
				break;
			case 5:
				popQueueHeadIntoHistory();
				break;
			case 6:
				viewHistory();
				break;
			case 7:
				printf ("bye bye %s", currentUser.name);
				break;
			default:
				printf ("Wrong input\n");
				break;
		}
		
	}while (inpt != 7);
}
int main () {
	
	createUser("Worker1","cepetanKerja",2);
	createUser("Admin1","AdminSigma",99);
	emptyCurrUser ();
	printf ("%d",userHash[10].next);
	startUpMenu();
	printf ("%s \n",currentUser.name);
}