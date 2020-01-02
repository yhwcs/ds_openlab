#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int key;
} element;
typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
} stack;
typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
} queue;
stackPointer top;
queuePointer front, rear;

void push(element item) {
	/* to do !*/
	stackPointer temp = (stackPointer)malloc(sizeof(stack));
	temp->data = item;
	temp->link = top;
	top = temp;
}
int stackEmpty() {
	/* to do !
	empty -> 1;
	else -> 0;
	*/
	if (!top) return 1;
	else return 0;
}
element pop() {
	/* to do !*/
	if (stackEmpty()) {
		printf("The Stack is empty!\n");
		exit(1);
	}
	stackPointer temp = top;
	element item;
	item = temp->data;
	top = temp->link;
	free(temp);
	return item;
}
void addq(element item) {
	/* to do !*/
	queuePointer temp = (queuePointer)malloc(sizeof(queue));
	temp->data = item;
	temp->link = NULL;
	if (front)
		rear->link = temp;
	else
		front = temp;
	rear = temp;
}
int queueEmpty() {
	/* to do !
	empty -> 1;
	else -> 0;
	*/
	if (!front) return 1;
	else return 0;
}
element deleteq() {
	/* to do !*/
	if (queueEmpty()) {
		printf("The Queue is empty!\n");
		exit(1);
	}
	queuePointer temp = front;
	element item;
	item = temp->data;
	front = temp->link;
	free(temp);
	return item;
}
int main() {
	FILE *fp = fopen("input.txt", "r");
	for (int a; ~fscanf(fp, "%d", &a); ) {
		if (a == 0) {
			int b;
			fscanf(fp, "%d", &b);
			element t; t.key = b;
			push(t);
			addq(t);
		}
		else if (a == 1) {
			pop();
			deleteq();
		}
	}
	/*
	print!
	*/
	for (; top; top = top->link)
		printf("%d ", top->data.key);
	printf("\n");
	for (; front; front = front->link)
		printf("%d ", front->data.key);
	printf("\n");
	fclose(fp);
	return 0;
}