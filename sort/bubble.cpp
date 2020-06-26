#include<stdio.h>

void swap(int *l, int i, int j) {
	int tmp = l[i];
	l[i] = l[j];
	l[j] = tmp;
}

// NOTE: 冒泡排序的优点在于每次将最小的数提到数组的最开头，那么最开头的数不用再参与比较；其次它还顺带在未碰见最小的数之前将其它较小的数移到了前面，减小了比较次数和交换次数
void sort(int *l, int n) {
	int i, j;
	bool flag = true;
	for(i=0; i<n-1 && flag; i++) {
		flag = false;				// NOTE: 加上flag标志是对冒泡排序的优化
		for(j=n-1; j > i; j--) {
			if(l[j] < l[j-1]) {
				swap(l, j-1, j);
				flag = true;		// NOTE: 如果没有交换发生说明已经整体有序了，不必进行不必要的下一轮循环了
			}
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
