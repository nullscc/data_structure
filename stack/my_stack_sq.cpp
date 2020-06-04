#include<stdio.h>
#include<stdlib.h>
#include"../common.h"

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10

typedef int SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S) {
	S.base = (SElemType*)malloc(sizeof(SElemType)*STACK_INIT_SIZE);
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack &S, SElemType &e) {
	if (S.top == S.base) {
		return ERROR;
	}
	
	e = *(S.top-1);
	return OK;
}

Status Push(SqStack &S, SElemType e) {
	if (S.top - S.base >= S.stacksize) {
		S.base = (SElemType *)realloc(S.base, S.stacksize+STACKINCREMENT);
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize; // NOTE: 这里S.top必须重新赋值，因为S.base变化了 
		S.stacksize +=  STACKINCREMENT;
	}
	
	*S.top = e;
	S.top++;
	
	return OK;
}

Status Pop(SqStack &S, SElemType &e) {
	if (S.top == S.base) {
		return ERROR;
	}
	
	e = *(--S.top);
	
	return OK;
}

