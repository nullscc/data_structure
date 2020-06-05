#include<stdio.h>
#include<assert.h>
#include"stack_sq.cpp"

int match(char p, char q) {
	if (p == '[' and q == ']') return OK;
	if (p == '(' and q == ')') return OK;

	return ERROR;
}
/********************************************
// only check for error that lvalue to rvalue
// lvalue: 1. container 
// rvalue: 1. temporary and short lived 2. thing in container

void check_helper(long int &a) {
	;
}

void check() {
	int b = 10;
	check_helper(b);
}
*********************************************/

int main() {
	return 0;
	SqStack S;
	InitStack(S);
	
	char s[100];
	
	printf("Please input your brackets:");
	scanf("%s", s);
	printf("your input is:%s\n", s);

	int i=0;
	for(; s[i] != '\0'; i++) {
		int at_top; // can't define at_top as char type, it will cause the error of rvalue to lvalue
		GetTop(S, at_top);

		if (match(at_top, s[i])) {
			int tmp;
			Pop(S, tmp);
		} else {
			Push(S, s[i]);
		}	
	}
	if (S.top == S.base) printf("check pass\n");
	else printf("check failed\n");

	return 0;
}
