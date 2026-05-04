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
}Node;

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

Node* createNode (char *key){
	Node* newNode = (Node*)malloc (sizeof (Node));
	strcpy(newNode->key, key);
	newNode->left=NULL;
	newNode->right=NULL;
	fillDetailDefault(newNode);
	return newNode;
}

Node* insertNode(Node* root, char *key){
	if (root==NULL) return createNode(key);
	
	if (strcmp(key,root->key)<0){
		root->left = insertNode(root->left,key);
//		printf ("\n%s goes left because %s with diffrence %d \n",key,root->key,strcmp(key,root->key));
	}else if (strcmp (key, root->key)>0){
		root->right= insertNode(root->right, key);
//		printf ("\n%s goes right because %s with diffrence %d \n",key,root->key,strcmp(key,root->key));
	}
	int isBalance = checkBallance(root);
	if (!(isBalance <=1 && isBalance>=-1)){
		return doAVL(root);
	}
	return root;
}


int findSigma (Node* root, char *key,int height, char *LR){
	if (strcmp(root->key,key)==0)return height + 1;
	
	if (strcmp (key,root->key)<0){
		printf ("\n%s %s\n",key,root->key);
		if (root->left==NULL){
			return ((height*-1) -1);
		}
		LR[height] ='L';
		height++;
		return findSigma (root->left,key,height,LR);
 	}else if (strcmp (key,root->key)>0){
		if (root->right ==NULL){
			return ((height*-1)-1);
		}
		LR[height]='R';
		height++;
		return findSigma (root->right,key,height,LR);
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

void doAVL (Node* root){ // (maybe fixed) potential error because root is not connected to main tree?
	//need 4 things to check, LL, RR, LR, RL
	if (checkBallance(root->left>0)){ //LL
		return rightRotate(root);
	}
	if (checkBallance(root->right)<0){ //RR
		return leftRotate(root);
	}
	if (checkBallance(root->left)<0){ //LR
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (checkBallance(root->right)>0){//RL
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}



int checkBallance (Node* root){
	if (root == NULL){
		return 0;
	}
	int diff=0;
	
	int Lheight = checkBallance(root->left);
	int Rheight = checkBallance(root->right);
//	if (Lheight ==-10 || Rheight ==-10)return -10;
	diff = Lheight-Rheight;
	if (diff <=1 && diff>=-1){
		return checkMax (Lheight,Rheight)+1;
	}else {
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
/*
void printSpace(){
	for (int i = 0; i<1;i++)printf(" ");
	return;
}
void printTree(Node* root,int isMainRoot,int iteration){
	int maxHeight = findHeight(root);
	if (isMainRoot){
		for (int i =0;i<maxHeight;i++){
			printSpace();
		}
		
		printf("%s\n",root->key);
	}
	
		for (int i =0;i<(maxHeight-iteration);i++){
			printSpace();
		}
	if(root->left!=NULL){
		printf ("/");
	}
	
		
	
		for (int i =0;i<(maxHeight+(iteration*2));i++){
			printSpace();
		}
	if (root->right!=NULL){
		printf ("\\");
	}
	printf("\n");
	
	for (int i =0;i<(maxHeight-iteration);i++){
		printSpace();
	}
	if (root->left!=NULL){
		printf("%s",root->left->key);
	}

	for (int i =0;i<(maxHeight+(iteration*2));i++){
		printSpace();
	}

	if (root->right!=NULL){
		printf("%s",root->right->key);
	}
	if(root->left!=NULL){
		if (root->left->left!=NULL||root->left->right!=NULL)printTree(root->left,0,iteration+2);
	}
	if(root->right!=NULL){
		if (root->right->right!=NULL||root->right->left!=NULL)printTree(root->right,0,iteration+2);
	}
	printf("\n");
	return;
}
*/
int main (){
	Node* root=NULL;
	root=insertNode (root,"Hello");
	root=insertNode (root,"Hi");
	root=insertNode (root,"Ab");
	root=insertNode (root,"Aa");
	root=insertNode (root,"Ba");
	root=insertNode (root,"Jello");
	root=insertNode (root,"Zello");
	printf ("\n\n%s\n",root->key);
	printf ("\nright child  %s\n",root->right->key);
	printf ("\nleft child  %s\n",root->left->key);
	char LR[100];
	int height= findSigma(root,"Aa",0,LR);
	printf ("\n%d",findHeight(root));
	puts("start");
	printTree(root,1,0);
	puts("end");
	
	printf ("\n\n\n\n\n%d\n",checkBallance(root));
}