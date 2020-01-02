#include <stdio.h>
#include <stdlib.h>
//#define DEBUG
typedef struct Poly Poly;
struct Poly {
	int coef, exp;
	Poly* next;
};
typedef struct _PolyHead {
	Poly*head, *tail;
	int cnt;
}PolyHead;
Poly* _getNewPoly() {
	return (Poly*)calloc(1, sizeof(Poly));
}
Poly* getNewPoly(int coef, int exp) {
	Poly *newPoly = _getNewPoly();
	newPoly->coef = coef; newPoly->exp = exp;
	return newPoly;
}
void polyPushBack(PolyHead*root, Poly*node) {
	if (root->head == NULL) {
		root->head = root->tail = node;
	}
	else {
		root->tail->next = node;
		root->tail = node;
	}
	(root->cnt)++;
	return;
}

void printPoly(Poly* poly) {
	for (Poly* p = poly; p; p = p->next)
		printf("%s(%d,%d)", p == poly ? "" : ", ", p->coef, p->exp);
	puts("");
}
PolyHead* padd(Poly* a, Poly* b) {
	/*To Do*/
	PolyHead* tmp = (PolyHead*)calloc(1, sizeof(PolyHead));
	int coefficient;
	while ((a != NULL) && (b != NULL))
	{
		Poly*node = (Poly*)calloc(1, sizeof(Poly));
		if (a->exp < b->exp) {
			node->coef = b->coef;
			node->exp = b->exp;
			polyPushBack(tmp, node);
			b = b->next;
		}
		else if (a->exp == b->exp) {
			coefficient = (a->coef) + (b->coef);
			if (coefficient) {
				node->coef = coefficient;
				node->exp = a->exp;
			}
			polyPushBack(tmp, node);
			a = a->next;
			b = b->next;
		}
		else if (a->exp > b->exp){
			node->coef = a->coef;
			node->exp = a->exp;
			polyPushBack(tmp, node);
			a = a->next;
		}
	}
	for (; a != NULL; a = a->next) {
		Poly*node = (Poly*)calloc(1, sizeof(Poly));
		node->coef = a->coef;
		node->exp = a->exp;
		polyPushBack(tmp, node);
	}
	for (; b != NULL; b = b->next) {
		Poly*node = (Poly*)calloc(1, sizeof(Poly));
		node->coef = b->coef;
		node->exp = b->exp;
		polyPushBack(tmp, node);
	}
	return tmp;
}

void readInput(PolyHead*root) {
	for (int coef, exp; scanf("%d%d", &coef, &exp) != -1;) {
		Poly*node = (Poly*)calloc(1, sizeof(Poly));
		node->coef = coef, node->exp = exp;
		polyPushBack(root, node);
	}
}
int main() {
	PolyHead *A = (PolyHead*)calloc(1, sizeof(PolyHead));
	PolyHead *B = (PolyHead*)calloc(1, sizeof(PolyHead));
	PolyHead *C = (PolyHead*)calloc(1, sizeof(PolyHead));
	freopen("A.txt", "r", stdin);
	readInput(A);
	freopen("B.txt", "r", stdin);
	readInput(B);
	freopen("C.txt", "r", stdin);
	readInput(C);
	/*printPoly(A->head);
	printPoly(B->head);
	printPoly(C->head);*/
	PolyHead *d = padd(A->head, B->head);
	PolyHead *e = padd(d->head, C->head);
	printPoly(e->head);
	return 0;
}