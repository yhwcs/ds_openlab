#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100
int fail[MAX_SIZE];
void f(char *s, int *kc);
int nfind(char *string, char *pat, int *nc);
int kmp(char *string, char *pat, int *kc);
int main() {
	char str[MAX_SIZE], pat[MAX_SIZE];
	freopen("input.txt", "r", stdin);
	scanf("%s %s", str, pat);
	int kc = 0, nc = 0;
	int nfindResult = nfind(str, pat, &nc);
	printf("nfind:\t%s %d\n", nfindResult == -1 ? "NO" : "YES", nc);
	int kmpResult = kmp(str, pat, &kc);
	printf("kmp:\t%s %d\n", kmpResult == -1 ? "NO" : "YES", kc);
	return 0;
}
int nfind(char *str, char *pat, int *nc) {
	int i, j=0, start = 0;
	int lasts = strlen(str) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		(*nc)++;
		if (str[endmatch] == pat[lastp]) {
			for (j = 0, i = start; j < lastp && str[i] == pat[j]; i++, j++){
				(*nc)++;
			}
		}
		if (j == lastp) return start;
	}
	return -1;
}
int kmp(char *str, char *pat, int *kc) {
	f(pat, kc);
	int i = 0, j = 0;
	int lens = strlen(str);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		(*kc)++;
		if (str[i] == pat[j]) {
			i++; j++;
		}
		else if (j == 0) i++;
		else j = fail[j - 1] + 1;
	}
	return ((j == lenp) ? (i - lenp) : -1);
}
void f(char *pat, int *kc) {
	int i, j, n = strlen(pat);
	fail[0] = -1;
	for (j = 1; j < n; j++) {
		i = fail[j - 1];
		(*kc)++;
		while ((pat[j] != pat[i + 1]) && (i >= 0)) {
			i = fail[i];
			(*kc)++;
		}
		if (pat[j] == pat[i + 1])
			fail[j] = i + 1;
		else fail[j] = -1;
	}
}