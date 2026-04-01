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
	struct *Node left;
	struct *Node right;
}Node;

Node* createNode (char *key){
	Node* newNode = (Node*)malloc (sizeof (Node));
	strcpy(newNode->key, key);
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

Node* insertNode(Node* root, char *key){
	if (root==NULL) return createNode(key);
	
	if (strcmp(key,root->key)<0){
		root->left = insertNode(root->left,key);
	}else if (strmcp (key, root->key)>0){
		root->right= insertNode(root->right, key);
	}else return root;
}

Node* findSigma (Node* root, char *key,int height, char *LR){
	if (strcmp(root->key,key)==0)return height + 1;
	
	if (strcmp (key,root->key)<0){
		if (root->left==NULL){
			return ((height*-1) -1)
		}
	}
}


int main (){
	
}