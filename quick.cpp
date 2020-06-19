// 快排
// 不稳定排序算法
#include<stdio.h>

void swap(int *l, int i, int j) {
	int tmp = l[i];
	l[i] = l[j];
	l[j] = tmp;
}

int patition(int *l, int low, int high) {
	int mid = (low+high)/2;						// 这里本来可以直接取最低标志位作为pivot的，但是为了增加平衡的几率，采用三数取中法
	if(l[mid] > l[high]) swap(l, mid, high);
	if(l[low] > l[mid]) swap(l, mid, low);
	if(l[low] < l[mid]) swap(l, low, mid); 

	int pivot_value = l[low];
	
	while(low<high) {
		while(low<high && pivot_value<l[high]) {
			high--;
		}
		l[low] = l[high];							// NOTE: 这里本来是局部交换但是通过整体交换的方式省了很多交换次数，因为无需保证分区的部分是有序的，只需保证整体来说比pivot小或者大即可

		while(low<high && pivot_value>l[low]) {
			low++;
		}
		l[high] = l[low];
	}
	l[low] = pivot_value;
	return low;
}

void sort(int *l, int low, int high) {
	while(low<high) {
		int pivot = patition(l, low, high);
		sort(l, low, pivot-1);					// NOTE: 这里本来需要调用两个，sort函数的，通过循环的方式只需要调用一个即可了，减少了栈的深度
		low = pivot + 1;
	}
}


int main() {
	int l[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
	sort(l, 0, 8);

	int i;
	printf("排序后的序列:");
	for(i=0; i<9; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");

	return 0;
}
