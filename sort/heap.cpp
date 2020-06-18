/*
堆排序
不稳定排序算法
*/
#include<stdio.h>

void swap(int *l, int i, int j) {
	int tmp = l[i];
	l[i] = l[j];
	l[j] = tmp;
}

// 将l[s..m]构建成大顶堆
// 由于是从下到上建立的大顶堆，所以除了根元素(即l[s])外都满足了大顶堆的定义
// 所以其实任务就两个：将最大的放到s的位置；将最小的放到合适的位置
void HeapAdjust(int *l, int s, int m) {
	int i;
	l[0] = l[s];					// 这里一定要将0元素留出来，不然不好处理完全二叉树的在数组中下标的问题
	for(i=2*s; i<=m; i=2*i) {		// NOTE: 其实主要是找到最大的，所以当然是顺着最大的找
		if(i<m && l[i]<l[i+1]) {
			i++;
		}
		if(l[i]<l[s]) break;
		l[s] = l[i];
		s = i;						// NOTE: 这里相当于i成为新的根结点了，以便下次循环
	}
	l[s] = l[0];
}

void sort(int *l, int n) {
	int i;
	for(i=n/2; i>=1; i--) {
		HeapAdjust(l, i, n);		// NOTE: 因为要对一整个数组进行二叉完全树大顶堆的创建
	}

	for(i=n; i>1; i--) {
		swap(l, 1, i);
		HeapAdjust(l, 1, i-1);
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

	return 0;
}
