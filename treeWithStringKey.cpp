#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
	char key[101];
	struct Node* left;
	struct Node* right;
}Node;

Node* createNode (char *key){
	Node* newNode = (Node*)malloc (sizeof (Node));
	strcpy(newNode->key, key);
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}
!//!ada error disini ga tau kenapa rootnya malah pindah ke element yang di add
Node* insertNode(Node* root, char *key){
	if (root==NULL) return createNode(key);
	
	if (strcmp(key,root->key)<0){
		printf("\n%s goes left because %s is %d\n",key,root->key,strcmp(key,root->key));
		root->left = insertNode(root->left,key);
	}else if (strcmp (key, root->key)>0){
		printf("\n%s goes right because %s is %d\n",key,root->key,strcmp(key,root->key));
		root->right= insertNode(root->right, key);
	}else {
		return root;	
	}
}

int findSigma (Node* root, char *key,int height, char *LR){
	puts("test1");
	if (strcmp(root->key,key)==0)return height + 1;
	
	if (strcmp (key,root->key)<0){
		printf ("\n%s %s\n",key,root->key);
		if (root->left==NULL){
			puts("test L null");
			return ((height*-1) -1);
		}
		LR[height] ='L';
		height++;
		return findSigma (root->left,key,height,LR);
 	}else if (strcmp (key,root->key)>0){
		if (root->right ==NULL){
			puts("right Null");
			return ((height*-1)-1);
		}
		LR[height]='R';
		height++;
		return findSigma (root->right,key,height,LR);
	}
}


int main (){
	Node*root=NULL;
	char data[]={"Hello"};

	root=insertNode(root,data);
		printf ("\n%s\n",root->key);
	root=insertNode(root,"Hi");
		printf ("\n%s\n",root->key);

	root=insertNode(root,"sigmatou");
		printf ("\n%s\n",root->key);

	int height=0;
	char direction[1000];
	printf ("\n%s\n",root->key);
	height = findSigma(root,"sigmatou",height,direction);
	printf ("%d, %s",height, direction);
}