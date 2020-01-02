#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1

typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
}node;

typedef struct {
	int test;
	int cost;
	int edgeN;
}element;

typedef struct {
	int islandU;
	int islandV;
}road;

nodePointer* graph;
element* heap;
int* visited;
int* parent;
road** bridge;
element* price;
int b;

void insert(int u, int v) {
	nodePointer new = (nodePointer)malloc(sizeof(node));
	new->vertex = v;
	new->link = NULL;

	nodePointer cur;
	cur = graph[u];
	if (graph[u] == NULL)
		graph[u] = new;
	else {
		for (; cur->link; cur = cur->link);
		cur->link = new;
	}
}

void dfs(int v, int t) {
	nodePointer w;
	visited[v] = true;
	for (w = graph[v]; w; w = w->link) {
		if (!visited[w->vertex]) {
			bridge[t][b].islandU = v;
			bridge[t][b++].islandV = w->vertex;
			dfs(w->vertex, t);
		}
	}
}

int find(int i) {
	while (parent[i])
		i = parent[i];
	return i;
}

int uni(int i, int j) {
	if (i != j) {
		parent[i] = j;
		return 1;
	}
	return 0;
}

void push(element item, int *n) {
	int i;
	i = ++(*n);
	while ((i != 1) && (item.cost < heap[i / 2].cost)) {
		heap[i].test = heap[i / 2].test;
		heap[i].cost = heap[i / 2].cost;
		heap[i].edgeN = heap[i / 2].edgeN;
		i /= 2;
	}
	heap[i].test = item.test;
	heap[i].cost = item.cost;
	heap[i].edgeN = item.edgeN;
}

element pop(int *n) {
	int p, c;			//parent, child
	element item, temp;
	item.test = heap[1].test;
	item.cost = heap[1].cost;
	item.edgeN = heap[1].edgeN;
	temp.test = heap[(*n)].test;
	temp.cost = heap[(*n)].cost;
	temp.edgeN = heap[(*n)--].edgeN;
	p = 1;
	c = 2;
	while (c <= *n) {
		if ((c < *n) && (heap[c].cost > heap[c + 1].cost))
			c++;
		if (temp.cost <= heap[c].cost) break;
		heap[p].test = heap[c].test;
		heap[p].cost = heap[c].cost;
		heap[p].edgeN = heap[c].edgeN;
		p = c;
		c *= 2;
	}
	heap[p].test = temp.test;
	heap[p].cost = temp.cost;
	heap[p].edgeN = temp.edgeN;
	return item;
}

int main() {
	int i, j, t, testcase;
	int u, v, tree, ne;	//ne : number of edge
	int vn, bn, vp, bp; //vertex_num, bridge_num, vertex_price, bridge_price
	int tempU, tempV;			//parent_u, parent_v
	int* result;
	int n = 0;
	element min;
	FILE* fp;
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &testcase);
	price = (element*)malloc(sizeof(element)*testcase);
	heap = (element*)malloc(sizeof(element)*testcase);
	bridge = (road**)malloc(sizeof(road*)*testcase);
	result = (int*)malloc(sizeof(int)*testcase);
	for (i = 0; i < testcase; i++)
		result[i] = 0;
	b = 0;
	for (t = 0; t < testcase; t++) {
		tree = 0;
		ne = 0;
		b = 0;
		fscanf(fp, "%d %d %d %d", &vn, &bn, &vp, &bp);

		if (vp > bp) {
			bridge[t] = (road*)malloc(sizeof(road)*bn);
			graph = (nodePointer*)malloc(sizeof(nodePointer)*vn);
			for (i = 0; i < vn; i++) {
				graph[i] = NULL;
			}
			visited = (int*)malloc(sizeof(int)*vn);
			parent = (int*)malloc(sizeof(int)*vn);
			for (i = 0; i < vn; i++) {
				visited[i] = false;
				parent[i] = 0;
			}

			for (i = 0; i < bn; i++) {
				fscanf(fp, "%d %d", &u, &v);
				u--; v--;
				tempU = u; tempV = v;
				u = find(u);
				v = find(v);
				if (uni(u, v)) {
					ne++;
					insert(tempU, tempV);
					insert(tempV, tempU);
				}
			}
			for (i = 0; i < vn; i++) {
				if (visited[i] == false) {
					dfs(i,t);
					tree++;
				}
			}
			price[t].cost = tree * vp + ne * bp;
			price[t].test = t;
			price[t].edgeN = ne;
		}
		else {
			for (i = 0; i < bn; i++) {
				fscanf(fp, "%d %d", &u, &v);
			}
			price[t].cost = vn * vp;
			price[t].test = t;
			price[t].edgeN = 0;
		}
		b++;
	}
	fclose(fp);
	for (t = 0; t < testcase; t++)
	{
		push(price[t], &n);
	}
	min = pop(&n);
	result[0] = min.test;
	i = 1;
	for (j = 1; j < testcase; j++) {
		if (heap[1].cost == min.cost) {
			min = pop(&n);
			result[i++] = min.test;
		}
		else break;
	}
	//sort for print! (not for search)
	int temp;
	if (result[1] != 0) {
		for (t = 0; t < i - 1; t++) {
			for (j = 0; j < i - t - 1; j++) {
				if (result[j] > result[j + 1]) {
					temp = result[j];
					result[j] = result[j + 1];
					result[j + 1] = temp;
				}
			}
		}
	}
	for (t = 0; t < i; t++) {
		printf("%d\n", result[t]+1);
		for (j = 0; j < price[result[t]].edgeN; j++) {
			printf("%d %d\n", bridge[result[t]][j].islandU+1, bridge[result[t]][j].islandV+1);
		}
	}
	printf("%d\n", min.cost);

	return 0;
}