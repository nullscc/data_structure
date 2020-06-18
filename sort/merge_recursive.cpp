#include<stdio.h>
#include<stdlib.h>

void merge(int *t, int *l, int i, int mid, int j) {
	int m=i, n=mid+1;
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


void sort(int *t, int *l, int i, int j) {
	int tmp[100];				// TODO: 这里感觉不太好，每一次递归都申请了好多临时变量，想来想去没啥好的解决办法，还是用非递归的方式好点~~
	if(i==j) {
		l[j] = t[j];			// 这里的l实际上是tmp数组了，要给tmp数据赋值，不然merge的时候值是不对的
	}
	else {
		int mid = (i+j)/2;
		sort(t, tmp, i, mid);	// NOTE: 这里很容易错，千万不要把t写成了l，不然就乱套了,这里的逻辑是想从t copy 到l(并且l有序),那么需要借助一个临时数组tmp，所以应该是t->tmp然后tmp 被merge到l
		sort(t, tmp, mid+1, j);
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
