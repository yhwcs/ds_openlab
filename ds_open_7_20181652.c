#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
} threadedTree;

threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer parent, threadedPointer child);
void insertLeft(threadedPointer parent, threadedPointer child);
threadedPointer getNewNode(char data);

int main() {
	/* image 5.23 */
	threadedPointer root = getNewNode('-');
	insertLeft(root, getNewNode('A'));
	insertLeft(root->leftChild, getNewNode('B'));
	insertLeft(root->leftChild->leftChild, getNewNode('D'));
	insertLeft(root->leftChild->leftChild->leftChild, getNewNode('H'));
	insertRight(root->leftChild->leftChild->leftChild, getNewNode('I'));
	insertRight(root->leftChild->leftChild, getNewNode('E'));
	insertRight(root->leftChild, getNewNode('C'));
	insertLeft(root->leftChild->rightChild, getNewNode('F'));
	insertRight(root->leftChild->rightChild, getNewNode('G'));

	tinorder(root);
	return 0;
}
threadedPointer getNewNode(char data) {
	threadedPointer newNode = (threadedPointer)malloc(sizeof(threadedTree));
	newNode->leftThread = true;
	newNode->leftChild = newNode;
	newNode->data = data;
	newNode->rightChild = newNode;
	newNode->rightThread = false;
	return newNode;
}

threadedPointer insucc(threadedPointer tree) {
	threadedPointer temp;
	temp= tree->rightChild;
	if (!tree->rightThread)
		while (!temp->leftThread)
			temp = temp->leftChild;
	return temp;
}
void tinorder(threadedPointer tree) {
	threadedPointer temp = tree;
	while(1){
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
	printf("\n");
}
void insertRight(threadedPointer parent, threadedPointer child) {
	threadedPointer temp;
	child->rightChild = parent->rightChild;
	child->rightThread = parent->rightThread;
	child->leftChild = parent;
	child->leftThread = true;
	parent->rightChild = child;
	parent->rightThread = false;
	if (!child->rightThread) {
		temp = insucc(child);
		temp->leftChild = child;
	}
}
void insertLeft(threadedPointer parent, threadedPointer child) {
	threadedPointer temp;
	child->leftChild = parent->leftChild;
	child->leftThread = parent->leftThread;
	child->rightChild = parent;
	child->rightThread = true;
	parent->leftChild = child;
	parent->leftThread = false;
	if (!child->leftThread) {
		temp = child->leftChild;
		while (!temp->rightThread)
			temp = temp->rightChild;
		temp->rightChild = child;
	}
}
