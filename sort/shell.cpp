/* 希尔排序
非稳定排序算法
精髓在于将比较小的数一下就移动到比较前面的位置，这样很快就能保证序列是基本有序了，那么需要比较和移动的次数就少了很多了
只要理解这个增量序列是用来干什么就好办
其实有点不明白为什么数组的第一个数要做暂存位(或者说哨兵)，没有一样可以
*/
#include<stdio.h>

void shell(int *l, int n) {
	int inc;
	int i, j, tmp;
	for(inc=n/2; inc>=1; inc=inc/2) {	// NOTE: 增量序列，这个增量序列是个经验值；只要保证最后一个inc是1即可
		for(i=inc; i<n; i++) {
			if(l[i]<l[i-inc]) {
				tmp = l[i];
				for(j=i-inc; j>=0 && l[j]>tmp; j=j-inc) {
					l[j+inc] = l[j];
				}
				l[j+inc] = tmp;
			}
		}
	}
}

int main() {
	int l[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
	shell(l, 9);

	int i;
	printf("排序后的序列:");
	for(i=0; i<9; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");

	return 0;
}
