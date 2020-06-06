#include<stdio.h>
#include<assert.h>
#include"link_queue.cpp"

int main() {
	Queue Q;
	InitQueue(Q);
	
	int i;
	for (i=0;i<10;i++) {
		assert(EnQueue(Q, i));
	}

	pQNode p = Q.front->next;
	for (i=0;i<10;i++) {
		assert(p->data==i);
		p = p->next;
	}
	assert(!p);
	
	ElemType e;
	for(i=0;i<10;i++) {
		DeQueue(Q, e);
		assert(e==i);
	}
	
	assert(Q.front==Q.rear);

	return 0;
}
