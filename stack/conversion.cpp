// 十进制数转换成八进制数

#include<stdio.h>
#include<assert.h>
#include"stack_sq.cpp"

typedef struct {
	int div;
	int mod;
}Opresult;

Opresult op(int num) {
	Opresult r;
	r.div = num / 8;
	r.mod = num % 8;

	return r;
}

int conversion(SqStack &S, int input) {
	int op_num = input;
	for (;;) {
		Opresult tmp = op(op_num);
		printf("push:%d\n",tmp.mod);
		Push(S, tmp.mod);
		op_num = tmp.div;
	
		if (tmp.div == 0) {
			break;	
		}
	}

	return OK;
}

int main() {
	SqStack S;
	InitStack(S);

	int input;
	printf("please input a number:");
	scanf("%d", &input);

	conversion(S, input);	

	printf("your input is:%d\n", input);
	printf("the output is:");
	
	int tmp;
	while (S.top > S.base) {
		Pop(S, tmp);
		printf("%d", tmp);
	}
	printf("\n");

	return 0;
}
