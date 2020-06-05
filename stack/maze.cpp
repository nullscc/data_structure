#include<stdio.h>
#include<assert.h>
#include"maze_stack.cpp"

void FootPrint(bool f[][10], int x, int y) {
	f[x][y] = true;
}

bool Can(bool f[][10], int maze[][10], int x, int y) {
	// printf("in Can %d %d %d ", x, y, f[x][y]);
	return !f[x][y];
}

Status FindPath(SqStack &S, bool f[][10], int maze[][10], int &next_x, int &next_y) {
	SElemType tmp;

	while (true) {
		GetTop(S, tmp);
		if (S.top <= S.base)  {
			return ERROR;

		};
		// printf("tmp: %d %d %d\n", tmp.di, tmp.x, tmp.y);
		switch (tmp.di) {
			case -1:
				if (Can(f, maze, tmp.x-1, tmp.y)) {
					tmp.di++;
					next_x = tmp.x-1;
					next_y = tmp.y;	
					return OK;
				}
				break;
			case 0:
				if (Can(f, maze, tmp.x, tmp.y-1)) {
					tmp.di++;
					next_x = tmp.x;
					next_y = tmp.y-1;	
					return OK;
				}
				break;
			case 1:
				if (Can(f, maze, tmp.x, tmp.y+1)) {
					tmp.di++;
					next_x = tmp.x;
					next_y = tmp.y+1;	
					return OK;
				}
				break;
			case 2:
				if (Can(f, maze, tmp.x+1, tmp.y)) {
					tmp.di++;
					next_x = tmp.x+1;
					next_y = tmp.y;	
					return OK;
				}
				break;
			case 3:
				Pop(S, tmp);
				break;
		}

	}
	return OK;
}

int main() {
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
	bool footprint[10][10];
	
	int i=0, j=0;
	for (;i<9;i++) {
		for (;j<9;j++) {
			printf("i:%d j:%d\n", i, j);
			// footprint[i][j] = false;
		}
	}
	
	return 0;
	SqStack S;
	InitStack(S);

	SElemType start = {-1, 1, 1};
	FootPrint(footprint, 1, 1);
	Push(S, start);
	int next_x, next_y;
	while (true) {
		// 1. 找路，得到下一个位置的坐标
		if (!FindPath(S, footprint, maze, next_x, next_y)) {
			printf("unsolvable maze!!! exit!\n");
			break;
		}
		printf("next coordinate %d %d\n", next_x, next_y);

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
		if (next_x == 8 && next_y == 8) break;
	}

	return 0;
}
