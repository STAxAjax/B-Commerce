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

/*
===================================================================================================================================================

FILE PROCESSING

===================================================================================================================================================
*/

void fileWriter (Node* root){
	char tempName[101]; strcpy (tempName,root->key);
	int tempStatus = root->item_Detail.available;
	int tempPrice = root->item_Detail.price;
	int tempQuantity = root->item_Detail.quantity;
	
	FILE *fp;
	fp = fopen ("data/itemdata.txt","w");
	fprintf (fp, "%s:%d:%d:%d:\n",tempName,tempStatus,tempPrice,tempQuantity);
	fclose (fp);
}

void fileAppend (Node* root){
	char tempName[101]; strcpy (tempName,root->key);
	int tempStatus = root->item_Detail.available;
	int tempPrice = root->item_Detail.price;
	int tempQuantity = root->item_Detail.quantity;
	
	FILE *fp;
	fp = fopen ("data/itemdata.txt","a");
	if (fp == NULL){
		fileWriter (root);
	}else {
		fprintf (fp, "%s:%d:%d:%d:\n",tempName,tempStatus,tempPrice,tempQuantity);
	}
	fclose (fp);
}

void fileCopyWriter (Node* root){
	char tempName[101]; strcpy (tempName,root->key);
	int tempStatus = root->item_Detail.available;
	int tempPrice = root->item_Detail.price;
	int tempQuantity = root->item_Detail.quantity;
	
	FILE *fp;
	fp = fopen ("data/itemdatatemp.txt","w");
	fprintf (fp, "%s:%d:%d:%d:\n",tempName,tempStatus,tempPrice,tempQuantity);
	fclose (fp);
}

void fileCopyAppend (Node* root){
	char tempName[101]; strcpy (tempName,root->key);
	int tempStatus = root->item_Detail.available;
	int tempPrice = root->item_Detail.price;
	int tempQuantity = root->item_Detail.quantity;
	FILE *fp;
	fp = fopen ("data/itemdatatemp.txt","a");
	if (fp == NULL){
		fileCopyWriter (root);
	}else {
		fprintf (fp, "%s:%d:%d:%d:\n",tempName,tempStatus,tempPrice,tempQuantity);
	}
	fclose (fp);
}

// file saving

void fileCopyr(){
	FILE *fp;
	Node* tempRoot = createNode("//0");
	char tempString[100];
	
	int i=0;
	fp = fopen ("data/itemdata.txt","r");
	if (fp == NULL){
		return;
	}else {
		while (fscanf(fp,"%[^:]:%d:%d:%d:\n",tempString,tempRoot->item_Detail.available,tempRoot->item_Detail.price,tempRoot->item_Detail.quantity)==4){
			strcpy (tempRoot->key,tempString);
			if (i==0){
				fileCopyWriter(tempRoot);
				i++;
			}else{			
				fileCopyAppend(tempRoot);
			}
		}
	}
	fclose (fp);
	free(tempRoot);
	return;
}


void filePaster(){
	Node* tempRoot=createNode("//0");
	char tempString[101];
	FILE* fpr;
	int i = 0;
	fpr = fopen ("data/itemdatatemp.txt","r");
	while (fscanf(fpr,"%[^:]:%d:%d:%d:\n",tempString,tempRoot->item_Detail.available,tempRoot->item_Detail.price,tempRoot->item_Detail.quantity)==4){
		strcpy (tempRoot->key,tempString);
		if (i==0){
			fileWriter(tempRoot);	
		i++;
		}else{
			fileAppend(tempRoot);
		}
	}
	fclose (fpr);
	free(tempRoot);
	return;
}


void fileUpdate(Node* replacement){//filePaster but for update
	Node* tempRoot =  createNode("//0");
	char tempString[101];
	FILE* fpr;
	int i = 0;
	fpr = fopen ("data/itemdatatemp.txt","r");
	while (fscanf(fpr,"%[^:]:%d:%d:%d:\n",tempString,tempRoot->item_Detail.available,tempRoot->item_Detail.price,tempRoot->item_Detail.quantity)==4){
		strcpy(tempRoot->key,tempString);
		if (i==0){
			fileWriter(replacement);	
		i++;
		}else{
			fileAppend(tempRoot);
		}
	}
	fclose (fpr);
	return;
}
//note make: when if duplicate gone, so theres no 2 entries of the same key, because what happend if i use 2 same thing again yk
//End of File saving





/*

end of File Processing
-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/

*/

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