#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define MAX_SIZE 10001
void insertion_sort(int *a, int n) {
	/* to do! */
	int i, j, tmp;
	for (i = 1; i < n; i++) {
		tmp = a[i];
		for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
			a[j + 1] = a[j];
		}
		a[j + 1] = tmp;
	}
}
void print_array(char *ment, int *a, int n) {
	printf("%s", ment);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	puts("");
}
int main() {
	FILE *fp = fopen("lab1.data", "r");
	int n = 0, t;
	while (~fscanf(fp, "%d", &t)) n++;
	fclose(fp);

	fp = fopen("lab1.data", "r");
	int *a = (int*)malloc(sizeof(int)*n);
	for (int i = 0; ~fscanf(fp, "%d", &t); )
		a[i++] = t;
	fclose(fp);

	print_array("Input : ", a, n);
	insertion_sort(a, n);
	print_array("Sorted : ", a, n);

	// re init variable for worst case test
	int worst_i, worst_n, step = 1000;
	int worst_a[MAX_SIZE];
	double duration;
	time_t first = clock();
	printf("	n 	repetitions	time\n");
	//worst_n이 입력에 대한 크기, 증가하면 repetition을 그에 반비례해서
	//줄어들면 된다.
	for (worst_n = 1000; worst_n <= 10000; worst_n += step) {
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;
			// init worst case data
			for (worst_i = 0; worst_i < worst_n; worst_i++)
				worst_a[worst_i] = worst_n - worst_i;
			insertion_sort(worst_a, worst_n);
		} while (clock() - start < 1000);
		// repeat until enough time has elapsed

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;

		duration /= repetitions;
		printf("%6d	%9d	%f\n", worst_n, repetitions, duration);
		for (int i = 0; i + 1 < worst_n; i++) {
			assert(worst_a[i] <= worst_a[i + 1]);
		}
	}
	printf("Finished in %.1fs\n", (double)(clock() - first) / CLOCKS_PER_SEC);
	return 0;
}