#include<stdio.h>
#include<assert.h>
#include"stack_sq.cpp"

int main() {
	SqStack S;
	InitStack(S);
	char ch;
	int tmp;
	while (true) {
		// scanf("%c", &ch);
		ch = getchar(); // scanf will jump space, tab, \n and EOF, so here must be function getchar
		if (ch == EOF) {printf("EOF.....\n"); break;}
		
		if (ch == '#') Pop(S, tmp);
		else if (ch == '@') ClearStack(S);
		else if (ch == '\n') {
			printf("let following string writen to file:\n");
			PrintStack(S);
			ClearStack(S);
		}
		else Push(S, ch);
	}
	printf("content in stack:\n");
	PrintStack(S);
	printf("\nend...\n");

	return 0;
}
