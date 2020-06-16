#include<stdio.h>

// 这是我自己的实现
int BinarySearch(int *l, int m, int n) {
	int a=0, b=n;
	int i;
	while(a != b) {
		i = (a+b)/2;
		if(l[i] > m) {
			b = i;
		} else if(l[i] < m) {
			a = i;
		} else return i;
	}
	return -1;
}

// 书上的实现
// 这个实现好些
int BinarySearch2(int *l, int m, int n) {
	int a=0, b=n;
	int i;
	while(a <= b) {
		i = (a+b)/2;
		if(l[i] > m) {
			b = i-1;		// NOTE: i已经搜索过了是无效的，当然不能再搜了
		} else if(l[i] < m) {
			a = i+1;
		} else return i;
	}
	return -1;
}

// 插值查找，对于表长较大，且数据分布较均匀的表，平均所花费的时间要比普通折半查找好很多
int InterpolationSearch(int *l, int m, int n) {
	int a=0, b=n;
	int i;
	while(a <= b) {
		i = a + (b-a)*((m-l[a])/(l[b]-l[a]));		// NOTE: 根据要查找的数据在当前要查找的区间中的占比来分配比例，而不是固定的1/2
		if(l[i] > m) {
			b = i-1;		// NOTE: i已经搜索过了是无效的，当然不能再搜了
		} else if(l[i] < m) {
			a = i+1;
		} else return i;
	}
	return -1;
}

int main() {
	int l[] = {0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99};
	printf("查找62的索引结果为:%d\n", BinarySearch(l, 62, 11));
	printf("插值查找62的索引结果为:%d\n", InterpolationSearch(l, 62, 11));

}
