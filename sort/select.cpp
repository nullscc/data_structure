#include<stdio.h>

void swap(int *l, int i, int j) {
	int tmp = l[i];
	l[i] = l[j];
	l[j] = tmp;
}

void sort(int *l, int n) {
	int i, j, min;
	for(i=0; i<n-1; i++) {			// NOTE: i不必一直到最后一个下标，因为在倒数第二个排序之后已经整体有序了
		min = i;
		for(j=i; j<n; j++) {
			if(l[j] < l[min]) {
				min = j;
			}
		}
		
		if(min != i) {
			swap(l, min, i);
		}
	}
}

int main() {
	int l[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
	sort(l, 9);

	int i;
	printf("排序后的序列:");
	for(i=0; i<9; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");


}
