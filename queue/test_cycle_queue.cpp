#include<stdio.h>
#include<assert.h>
#include"cycle_queue.cpp"

int main() {
	Queue Q;
	InitQueue(Q);
	
	int i;
	for (i=0;i<10;i++) {
		assert(EnQueue(Q, i));
	}

	for (i=0;i<10;i++) {
		assert(Q.base[i+1]==i);
	}
	assert(GetLength(Q)==10);
	assert(!EnQueue(Q, 10));
	
	ElemType e;
	for(i=0;i<5;i++) {
		DeQueue(Q, e);
		assert(e==i);
	}

	assert(GetLength(Q)==5);
	for(i=5;i<9;i++) {
		EnQueue(Q, i);
	}
	assert(GetLength(Q)==9);
	
	printf("\ndata in queue:\n");
	for (i=0; i<MAXSIZE; i++) {
		printf("%d ", Q.base[i]);
	}
	printf("front:%d, rear:%d\n", Q.front, Q.rear);
	
	return 0;
}
