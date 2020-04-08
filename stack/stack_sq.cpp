#include<stdio.h>
#include<stdlib.h>
#include"../common.h"

typedef int SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10


Status InitStack(SqStack &S) {
	S.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S.base) exit(OVERFLOW);
	
	S.top = S.base; // ��ʼ��ʱ����֪ 
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType &e) {
	if (S.top == S.base) return ERROR;
	e = *(S.top-1);
	return OK;
}

Status Push(SqStack &S, SElemType e) {
	if (S.top - S.base >= S.stacksize) { // NOTE: ��ջ��ʱ��S.topָ��һ�������ڴ˳���ĵ�ַ��(ע��ջ��ʱ����֪��)������������ 
		S.base = (SElemType *) realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		
		if (!S.base) exit(OVERFLOW);
		
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	
	*S.top++ = e;
}

Status Pop(SqStack &S, SElemType &e) {
	if (S.top == S.base) return ERROR;
	
	e = *--S.top;
	return OK;
}
