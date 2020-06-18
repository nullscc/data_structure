#include<stdio.h>

#define MAXSIZE 100

int M[100];

void merge(int *t, int *l, int i, int mid, int j) {
	int m=i, n=mid;
	int index = i;
	while(m<=mid && n<=j) {
		if(t[m]<t[n]) {
			l[index] = t[m];
			index++;
			m++;
		} else {
			l[index] = t[n];
			index++;
			n++;
		}
	}
	while(m<=mid) {
		l[index] = t[m];
		index++;
		m++;
	}
	while(n<=j) {
		l[index] = t[m];
		index++;
		m++;
	}
}

void sort(int *t, int *l, int i, int j) {
	printf("wtf111....%d %d\n", i, j);
	int tmp[100];
	if(i==j) {
		l[j] = t[j];
	}
	else {
		int mid = (i+j)/2;
		sort(l, tmp, i, mid);
		sort(l, tmp, mid+1, j);
		merge(tmp, l, i, mid, j);
	}
}

int main() {
	int l[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
	sort(l, l, 0, 8);

	int i;
	printf("排序后的序列:");
	for(i=0; i<9; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");
}
