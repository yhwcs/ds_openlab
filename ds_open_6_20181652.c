#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
	int value;
	node* link;
};

node* pushBack(node* tail, int value) {
	/*to do*/
	node* new;
	new = (node*)malloc(sizeof(node));
	new->value = value;
	if (!tail) {
		tail = new;
		new->link = tail;
	}
	else {
		new->link = tail->link;
		tail->link = new;
		tail = new;
	}
	return tail;
}

void printCircularList(node* tail) {
	/*to do*/
	node* temp;
	if (tail) {
		temp = tail;
		do {
			temp = temp->link;
			printf("%d ", temp->value);
		} while (temp != tail);
		printf("\n");
	}
}

node* deleteNode(node * tail, int value) {
	/*to do*/
	node* cur = tail->link;
	node* pre = tail;
	if (!tail) return NULL;
	do {
		if (cur->value == value) {
			node* del = cur;
			pre->link = cur->link;
			if (cur == tail) tail = pre;
			cur = cur->link;
			free(del);
		}
		else {
			pre = cur;
			cur = cur->link;
		}
	} while (cur != tail->link);

	return tail;
}

node* concatenateCircularList(node * tailA, node * tailB) {
	/*to do*/
	if (!tailA) return tailB;
	else {
		if (tailB) {
			node* temp;
			temp = tailA->link;
			tailA->link = tailB->link;
			for (; tailA != tailB; tailA = tailA->link);
			tailA->link = temp;
		}
	}
	return tailA;
}

int main() {

	node* a = NULL, *b = NULL;
	FILE* fp = fopen("A.txt", "r");
	for (int t; ~fscanf(fp, "%d", &t); )
		a = pushBack(a, t);
	fclose(fp);
	fp = fopen("B.txt", "r");
	for (int t; ~fscanf(fp, "%d", &t); )
		b = pushBack(b, t);
	fclose(fp);

	node * d = concatenateCircularList(a, b);
	printCircularList(d);
	puts("");
	fp = fopen("C.txt", "r");
	for (int t; ~fscanf(fp, "%d", &t); ) {

		d = deleteNode(d, t);

	}
	fclose(fp);
	printCircularList(d);

	return 0;
}