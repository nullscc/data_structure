#include<stdio.h>
#include<stdlib.h>
#include"../common.h"


typedef pNode SElemType;

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
	
	S.top = S.base; // 初始化时即可知 
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType &e) {
	if (S.top == S.base) return ERROR;
	e = *(S.top-1);
	return OK;
}

Status Push(SqStack &S, SElemType e) {
	if (S.top - S.base >= S.stacksize) { // NOTE: 当栈满时，S.top指向一个不属于此程序的地址，(注意栈满时即可知道)可能有隐患？ 
		S.base = (SElemType *) realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		
		if (!S.base) exit(OVERFLOW);
		
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack &S, SElemType &e) {
	if (S.top == S.base) return ERROR;
	
	e = *--S.top;
	return OK;
}

Status ClearStack(SqStack &S) {
	S.top = S.base; // NOTE: 这里有一次错误的将其写成S.base=S.top，结果总是报realloc invalid pointer，因为realloc的第一个参数必须要是malloc返回的等堆区的地址，所以不能乱改S.base的地址

	return OK;	
}

Status IsEmpty(SqStack &S) {
	return S.base == S.top;
}
