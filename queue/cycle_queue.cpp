#include<stdio.h>
#include<stdlib.h>
#include"../common.h"

#define MAXSIZE	11
typedef int ElemType;

typedef struct {
	ElemType *base;
	int front;
	int rear;
}Queue;

Status InitQueue(Queue &Q) {
	Q.base = (ElemType *)malloc(sizeof(ElemType)*MAXSIZE);
	if (!Q.base) exit(OVERFLOW);
	
	Q.front = 0;
	Q.rear = 1;		// 书上是在头结尾浪费一个空间，我这里的实现是在开头就浪费一个空间
					// 书上的好些~

	return OK;
}

Status EnQueue(Queue &Q, ElemType e) {
	if ((Q.rear)%MAXSIZE == Q.front) {	// NOTE: 重要技巧
		return ERROR;
	}
	
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear+1) % MAXSIZE;

	return OK;
}

Status DeQueue(Queue &Q, ElemType &e) {
	if ((Q.front+1)%MAXSIZE == Q.rear) {	// NOTE: 重要技巧
		return ERROR;
	}
	
	e = Q.base[Q.front+1];
	Q.front = (Q.front+1) % MAXSIZE;

	return OK;
}


int GetLength(Queue &Q) {
	return (Q.rear - Q.front - 1 + MAXSIZE) % MAXSIZE;  // NOTE: 重要技巧
}
