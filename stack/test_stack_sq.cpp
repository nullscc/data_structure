#include<stdio.h>
#include<assert.h>
//#include"stack_sq.cpp"
#include"my_stack_sq.cpp"

int main() {
	SqStack S;
	InitStack(S);
	
	int i;
	
	for (i=1; i<12; i++) Push(S, i);
	
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
