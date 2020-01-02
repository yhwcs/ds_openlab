#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct _Node* treeptr;
typedef struct _Node {
	 int data;
	 struct _Node* left;
	 struct _Node* right;
}Node;

void inorder(Node* tree);
void preorder(Node* tree);
void insertNode(treeptr* tree, int num);
treeptr modifiedSearch(treeptr tree, int num);

int main(void) {
	 FILE* fp1 = NULL;
	 int i, cnt, num, res;
	 Node* tree = NULL;
	 fp1 = fopen("input.txt", "r");
	 if (fp1 == NULL) {
		  printf("Error\n");
		  return -1;
	 }
	 fscanf(fp1, "%d\n", &cnt);
	 for (i = 0; i < cnt; i++) {
		  fscanf(fp1, "%d\n", &num);
		  insertNode(&tree, num);
	 }
	 fclose(fp1);
	 printf("Inorder Traversal\n");
	 inorder(tree);
	 puts("");
	 printf("preorder Traversal\n");
	 preorder(tree);
	 printf("\n");

}
treeptr modifiedSearch(treeptr tree, int num) {
	 /*to do*/
	 if (tree == NULL) return NULL;
	 while (tree) {
		  if (num == tree->data) return NULL;
		  else if (num < tree->data) {
				if (tree->left == NULL) return tree;
				else tree = tree->left;
		  }
		  else {
				if (tree->right == NULL) return tree;
				else tree = tree->right;
		  }
	 }
	 return NULL;
}

void insertNode(treeptr *tree, int num) {
	 /*to do*/
	 treeptr ptr;
	 treeptr temp;
	 temp = modifiedSearch(*tree, num);
	 if (temp || !(*tree)) {
		  ptr = (treeptr)malloc(sizeof(Node));
		  ptr->data = num;
		  ptr->left = ptr->right = NULL;
		  if (*tree)
				if (num < temp->data)
					 temp->left = ptr;
				else
					 temp->right = ptr;
		  else
				*tree = ptr;
	 }
}

void inorder(Node * tree) {
	 /*to do*/
	 if (tree) {
		  inorder(tree->left);
		  printf("%d", tree->data);
		  inorder(tree->right);
	 }
}
void preorder(Node * tree) {
	 /*to do*/
	 if (tree) {
		  printf("%d", tree->data);
		  preorder(tree->left);
		  preorder(tree->right);
	 }
}
