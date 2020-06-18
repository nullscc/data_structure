// 归并排序非递归版本
#include<stdio.h>
#include<stdlib.h>
void merge(int *t, int *l, int i, int mid, int j) {
	int m=i, n=mid+1;
	/*
	 * 如果这里写成了n=mid; 且程序排序的数组是3个，那么程序会报下列错误:
	 * *** stack smashing detected ***: <unknown> terminated
	 * Aborted (core dumped)
	 * 原因是会导致l[index]数组越界...
	 */
	int index = i;
	while(m<=mid && n<=j) {
		if(t[m]<t[n]) {
			l[index++] = t[m];
			m++;
		} else {
			l[index++] = t[n];
			n++;
		}
	}
	while(m<=mid) {
		l[index++] = t[m++];
	}
	while(n<=j) {
		l[index++] = t[n++];
	}
}

void merge_multi(int *t, int *l, int k, int n) {
	int i=0;
	while((i+2*k)<=n) {
		merge(t, l, i, i+k-1, i+2*k-1);
		i = i+2*k;
	}

	int j;
	if(i+k<n) {							// NOTE: 剩下的数目可以组成大于1个小于两个的k小组序列
		// 相当于上面merge的最后一个下标是i-1, 如果最后一个下标加上k刚好等于n-1，即i-1+k=n-1，说明刚好剩下k个，那这种情况就是单个子序列，如果小于n-1就是还剩两个子序列
		merge(t, l, i, i+k-1, n);		// NOTE: 这里的i-1 + k代表分界点，其实以什么为分解都无所谓~
	} else {							// NOTE: 剩下的数目不足以组成1个k小组序列
		for(j=i; j<=n; j++) {
			l[j] = t[j];				// NOTE: 这里由于是以递增的间隔来两两配对的，这种情况下单个序列其实已经是有序的了，当分块的间隔继续增大，它就会和另外一个整块进行归并了，所以只需要将数据从临时区域拷贝过来就好了
		}
	}
}

void sort(int *l, int n) {
	int *tmp  = (int *)malloc(sizeof(int)*n);

	int k=1;
	while(k<n) {
		merge_multi(l, tmp, k, n);		// NOTE: 这里相当于将l当成中间转换空间
		k = 2*k;
		merge_multi(tmp, l, k, n);		// NOTE: 这里相当于将tmp当成中间转换空间

		k = 2*k;
	}
	
}

int main() {
	int l[11] = {50, 10, 90, 30, 70, 40, 80, 60, 20, 100, 0};
	sort(l, 11);
	int i;
	printf("排序后的序列:");
	for(i=0; i<11; i++) {
		printf("%d ", l[i]);
	}
	printf("\n");

}
