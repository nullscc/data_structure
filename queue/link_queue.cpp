#include<stdio.h>
#include<stdlib.h>
#include"../common.h"

typedef int ElemType;

typedef struct QNode{ // 这里必须要先"证明"这个结构体名是QNode，不然在里面没法定义next
	ElemType data;
	struct QNode *next;
}QNode, *pQNode;

typedef struct {
	pQNode front;
	pQNode rear;
}Queue;

Status InitQueue(Queue &Q) {
	Q.front = (pQNode)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);

	Q.front->next = NULL;
	Q.rear = Q.front;
	return OK;
}

Status EnQueue(Queue &Q, ElemType e) {
	// NOTE: 插入不存在队列满的情况
	
	pQNode tmp = (pQNode)malloc(sizeof(QNode));
	if (!tmp) exit(OVERFLOW);

	tmp->data = e;
	tmp->next = NULL;
	
	Q.rear->next = tmp;
	Q.rear = tmp;

	return OK;
}

Status DeQueue(Queue &Q, ElemType &e) {
	if (Q.front == Q.rear) return ERROR;

	pQNode tmp = Q.front->next;
	e = tmp->data; // NOTE: 队头是空的
	Q.front->next = tmp->next;

	if (tmp == Q.rear) Q.rear = Q.front;
	free(tmp);

	return OK;
}


