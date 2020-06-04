// NOTE: 位序是从带数据的节点开始算的，这样静态链表的位序刚好和数组下标是一样的 
// 静态链表: static list
// 用数组来实现线性表的操作，方便在有些没有指针的程序语言里面使用

#include<stdio.h>

#define MAXSIZE 1000

typedef int ElemType;

typedef struct {
	ElemType data;
	int cur; 
}component, SLinkList[MAXSIZE];

int LocateElem_SL(SLinkList S, ElemType e) {
	int i = S[0].cur;
	while (i && S[i].data != e) i = S[i].cur;
	
	return i; 
}

void InitSpace_SL(SLinkList &space) {
	int i;
	for (i=0; i<MAXSIZE-1; ++i) space[i].cur = i+1;
	space[MAXSIZE-1].cur = 0;
}

int Malloc_SL(SLinkList &space) {
	int i = space[0].cur;
	if (space[0].cur) space[0].cur = space[i].cur;                                                                      
	return i;
}

void Free_SL(SLinkList &space, int k) {
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

// 这个书本上的函数实现的太乱了
// BUG: 如果输入A: 1 2 3 B: 2 3 2 结果是1 2，显然不对
void difference(SLinkList &space, int &S) {
	InitSpace_SL(space);
	S = Malloc_SL(space);
	int r = S;
	int m, n;
	printf("请输入A和B的元素个数:");
	scanf("%d %d", &m, &n);
	
	int j;
	printf("请输入%d个A中的元素:", m);
	for (j=1; j<=m; ++j) {
		int i = Malloc_SL(space); 	// BUG: 浪费了位序为2的数据空间
		scanf("%d", &space[i].data);
		space[r].cur = i;
		r = i;
	}
	space[r].cur = 0;
	printf("尾节点:%d\n", r);
	printf("space数据为:\n");
	for (j=0; j<10; j++) {
		printf("%d %d\n", space[j].cur, space[j].data);
	}

	printf("请输入%d个B中的元素:", n);
	for (j=1; j<=n; ++j) {
		int b;
		scanf("%d", &b);
		int p = S;
		int k = space[S].cur;
		

		while(k != space[r].cur && space[k].data != b) {
			p = k;
			k = space[k].cur;
		}
		
		if (k == space[r].cur) { // B里面有A没有的元素，增加之 即B-A的操作
			int i = Malloc_SL(space);
			space[i].data = b;
			space[i].cur = space[r].cur;
			space[r].cur = i;
			r = i;				// BUG: 浪费增加操作后l尾指针应该增加
			printf("增加操作后的尾节点:%d\n", r);
		} else {				// A里面有B的元素，增加之 即A-B的操作
			space[p].cur = space[k].cur;
			Free_SL(space, k);
			if (r == k) r = p; // NOTE: 删除的如果是最后一个，则需要修改尾指针 
			printf("删除操作后的尾节点:%d\n", r);
		}
		printf("b:%d, space数据为:\n", b);
		int tmp;
		for (tmp=0; tmp<10; tmp++) {
			printf("%d %d\n", space[tmp].cur, space[tmp].data);
		}

	}
}

int main() {
	SLinkList h;
	int s;
	difference(h, s);
	return 0;
}
