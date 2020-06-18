#include<stdio.h>
#include<stdlib.h>

void merge(int *t, int *l, int i, int mid, int j) {
	int m=i, n=mid;
	int index = i;
	printf("merge, index:%d i:%d mid:%d j:%d\n", index, i, mid, j);
	while(m<=mid && n<=j) {
		printf("merge in while m:%d mid:%d n:%d j:%d, index:%d, t[n]:%d\n", m, mid, n, j, index, t[n]);
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
		l[index] = t[n];
		index++;
		n++;
	}
}

int tmp[100];
void sort(int *t, int *l, int i, int j) {
	printf("tmp:%p\n", l);
	if(i==j) {
		printf("2222 tmp:%p\n", l);
		l[j] = t[j];
		printf("j:%d t[j]:%d l[j]:%d\n", j, t[j], l[j]);
	}
	else {
		int mid = (i+j)/2;
		sort(t, tmp, i, mid);
		sort(t, tmp, mid+1, j);
		merge(tmp, l, i, mid, j);
	}
}

int main() {
	int l[3] = {9, 1, 5};
	sort(l, l, 0, 2);

	int i;
	printf("排序后的序列:");
	for(i=0; i<3; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");

	// int l[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
	// sort(l, l, 0, 8);
	// int i;
	// printf("排序后的序列:");
	// for(i=0; i<9; i++) {
	// 	printf("%d ", l[i]);
	// }
	// printf("\n");
}
