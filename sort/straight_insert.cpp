#include<stdio.h>

// 无哨兵版本
// NOTE: 无哨兵版本要多很多个比较语句
void sort2(int *l, int n) {
	int i, j;
	
	int tmp;
	for(i=1; i<n; i++) {
		if(l[i] < l[i-1]) {
			tmp = l[i];
			for(j=i-1; j>=0 && l[j]>tmp; j--) {		// NOTE: 多的比较语句在这里 j>=0
				l[j+1] = l[j];
			}
			l[j+1] = tmp;
		}
	}
}

// 哨兵版本
void sort(int *l, int n) {
	int i, j;
	for(i=2; i<=n; i++) {
		if(l[i] < l[i-1]) {
			l[0] = l[i];
			for(j=i-1; l[j]>l[0]; j--) {
				l[j+1] = l[j];
			}
			l[j+1] = l[0];
		}
	}
}


int main() {
	int l[10] = {0, 9, 1, 5, 8, 3, 7, 4, 6, 2};
	sort(l, 9);
	int i;
	printf("排序后的序列:");
	for(i=1; i<=9; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");
}
