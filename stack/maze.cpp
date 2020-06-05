// 走迷宫，找方向的时候应该优先往出口的方向
// 主要点在于: 走过的路不能再走了

#include<stdio.h>
#include<assert.h>
#include"maze_stack.cpp"

void FootPrint(bool f[][10], int x, int y) {
	f[x][y] = true;
}

bool Can(bool (*f)[10], int maze[][10], int x, int y) { // NOTE: 由于寻址问题，二维数组不能直接用指针的指针作为形参，看f和maze的参数传递方式
	return !f[x][y];
}

Status FindPath(SqStack &S, bool f[][10], int maze[][10], int &next_x, int &next_y) {
	// TODO: 总感觉这个函数实现的有点臃肿
	SElemType tmp;
	while (true) {
		if (S.top <= S.base)  {
			return ERROR;
		};
		Pop(S, tmp);
		switch (tmp.di) {
			case 2:
				if (Can(f, maze, tmp.x, tmp.y-1)) {
					tmp.di++;
					next_x = tmp.x;
					next_y = tmp.y-1;	
					Push(S, tmp);
					return OK;
				} else {
					tmp.di++;
					Push(S, tmp);
				}
				break;
			case 1:
				if (Can(f, maze, tmp.x-1, tmp.y)) {
					tmp.di++;
					next_x = tmp.x-1;
					next_y = tmp.y;	
					Push(S, tmp);
					return OK;
				} else {
					tmp.di++;
					Push(S, tmp);
				}
				break;
			case 0:
				if (Can(f, maze, tmp.x, tmp.y+1)) {
					tmp.di++;
					next_x = tmp.x;
					next_y = tmp.y+1;	
					Push(S, tmp);
					return OK;
				} else {
					tmp.di++;
					Push(S, tmp);
				}
				break;
			case -1:
				if (Can(f, maze, tmp.x+1, tmp.y)) {
					tmp.di++;
					next_x = tmp.x+1;
					next_y = tmp.y;	
					Push(S, tmp);
					return OK;
				} else {
					tmp.di++;
					Push(S, tmp);
				}
				break;
			default:
				break;
		}
	}
	return OK;
}

int main() {
	// 找得到路的迷宫
	int maze[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 0
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1}, // 1
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},	// 2
		{1, 0, 0, 0, 0, 1, 1, 0, 0, 1},	// 3
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 1},	// 4
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 5
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 1}, // 6
		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1}, // 7
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 1}, // 8
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 9
	};
	// 找不到路的迷宫
	/*
	int maze[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 0
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1}, // 1
		{1, 0, 0, 1, 0, 0, 0, 1, 0, 1},	// 2
		{1, 0, 0, 0, 0, 1, 1, 0, 0, 1},	// 3
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 1},	// 4
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 5
		{1, 0, 1, 0, 0, 1, 1, 0, 0, 1}, // 6
		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1}, // 7
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 1}, // 8
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 9
	};
	*/

	bool footprint[10][10]; // NOTE: 这里默认是随机的
	
	int i, j;
	printf("输入的迷宫为:\n");
	for (i=0;i<10;i++) { // NOTE: 不知道为啥必须在这里初始化
		for (j=0;j<10;j++) {
			footprint[i][j] = false;
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	
	SqStack S;
	InitStack(S);

	SElemType start = {-1, 1, 1};
	FootPrint(footprint, 1, 1);
	Push(S, start);
	int next_x, next_y;
	bool unsolve = false;
	while (true) {
		// 1. 找路，得到下一个位置的坐标
		if (!FindPath(S, footprint, maze, next_x, next_y)) {
			unsolve = true;
			printf("unsolvable maze!!! exit!\n");
			break;
		}

		FootPrint(footprint, next_x, next_y);
		// 2. 验证坐标是否可走
		// 3.1 如果不可走，就找下一个可走的坐标
		if (maze[next_x][next_y]) continue;

		// 3.2 如果可走，就将这个位置压入栈
		SElemType tmp;
		tmp.di = -1;
		tmp.x = next_x;
		tmp.y = next_y;
		Push(S, tmp);

		// 4. 如果检测到可走并且到了终点了，就退出
		if (next_x == 8 && next_y == 8) {
			printf("amazing, you have found the path\n\n");
			break;
		}
	}
	bool path[10][10];
	
	for (i=0;i<10;i++) {
		for (j=0;j<10;j++) {
			path[i][j] = false;
		}
	}
	if (unsolve) return 0;
	printf("路线为:");
	while (S.top > S.base) {
		SElemType tmp;
		Pop(S, tmp);
		path[tmp.x][tmp.y] = true;
	}

	for (i=0;i<10;i++) { // NOTE: 不知道为啥必须在这里初始化
		for (j=0;j<10;j++) {
			if (path[i][j]) printf("*");
			else printf(" ");
		}
		printf("\n");
	}

	return 0;
}
