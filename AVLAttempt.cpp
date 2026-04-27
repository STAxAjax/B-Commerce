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

void doAVL (Node* root){
	printf ("kys bish");
}

int checkBallance (Node* root){
	if (root == NULL){
		return 0;
	}
	int diff=0;
	
	int Lheight = checkBallance(root->left);
	int Rheight = checkBallance(root->right);
	if (Lheight ==-10 || Rheight ==-10)return -10;
	diff = Lheight-Rheight;
	if (diff <=1 && diff>=-1){
		return checkMax (Lheight,Rheight)+1;
	}
	doAVL(root);
	return checkMax (Lheight,Rheight)-1

	
	return -10;
}


int main (){
	Node* root=NULL;
	root=insertNode (root,"Hello");
	root=insertNode (root,"Hi");
	root=insertNode (root,"Aa");
	root=insertNode (root,"Jello");
	printf ("\n\n%s\n",root->key);
	printf ("\nright child  %s\n",root->right->key);
	printf ("\nleft child  %s\n",root->left->key);
	char LR[100];
	
	int height= findSigma(root,"Aa",0,LR);
	printf ("%d %s",height,LR);
}