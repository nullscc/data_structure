#include<stdio.h>
#include<assert.h>
#include"stack_sq.cpp"
//#include"my_stack_sq.cpp"

int main() {
	SqStack S;
	InitStack(S);
	
	int i;
	
	for (i=1; i<11; i++) Push(S, i);
	printf("栈内的数据为:\n");
	SElemType *p = S.base;
	while (p <= S.top) {
		printf("%d ", *p);
		p++;
	
	}
	printf("栈的容量为:%d\n", S.stacksize);
	return 0;
	
	int tmp;
	GetTop(S, tmp);
	assert(tmp==11);
	
	for (i=1; i<11; i++){
		int tmp;
		Pop(S, tmp);
		assert(tmp==12-i);
	}
	
	return 0;
}
