// NOTE: 位序是从带数据的节点开始算的，这样静态链表的位序刚好和数组下标是一样的 

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

void difference(SLinkList &space, int &S) {
	InitSpace_SL(space);
	S = Malloc_SL(space);
	int r = S;
	int m, n;
	scanf("%d %d", &m, &n);
	
	int j;
	for (j=1; j<=m; ++j) {
		int i = Malloc_SL(space);
		scanf("&d", &space[i].data);
		space[r].cur = i;
		r = i;
	}
	space[r].cur = 0;
	
	for (j=1; j<=n; ++j) {
		int b;
		scanf("%d", b);
		int p = S;
		int k = space[S].cur;
		
		while(k != space[r].cur && space[k].data != b) {
			p = k;
			k = space[k].cur;
		}
		
		if (k == space[r].cur) {
			int i = Malloc_SL(space);
			space[i].data = b;
			space[i].cur = space[r].cur;
			space[r].cur = i;
		} else {
			space[p].cur = space[k].cur;
			Free_SL(space, k);
			if (r == k) r = p; // NOTE: 删除的如果是最后一个，则需要修改尾指针 
		}
	}
}

int main() {
	return 0;
}
