// 无向网的Floyd算法(找最短路径)
// 采用邻接矩阵存储

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>
#include"../common.h"

#define MAXSIZE 100

typedef struct {
	char vex[MAXSIZE];
	int edge[MAXSIZE][MAXSIZE];
	int vexnum, edgenum;

}Graph, *pGraph;

Status GetVex(Graph &g) {
	printf("请输入顶点信息, 以空格分隔:");
	char ch;
	scanf("%c", &ch);
	int i=0;
	while(ch && ch != '\n') {
		g.vex[i] = ch;
		scanf("%c", &ch);
		i++;
	}
	g.vexnum = i;

	printf("\n");
	return OK;
}

Status GetEdge(Graph &g) {
	int i, j;
	int v1, v2, weight;

	for(i=0; i<MAXSIZE; i++) {
		for(j=0; j<MAXSIZE; j++) {
			if (i == j) g.edge[i][j] = 0;
			else g.edge[i][j] = INT_MAX;
		}
	}

	printf("请输入边信息, 格式为1,2,10 2,3,20(以1开始，前面两个代表边，最后一个代表权重), 0,0,0代表结束:");
	scanf("%d,%d,%d", &v1, &v2, &weight);
	i=0;
	while(v1 && v2 && weight) {
		g.edge[v1-1][v2-1] = weight;
		g.edge[v2-1][v1-1] = weight;
		scanf("%d,%d,%d", &v1, &v2, &weight);
		i++;
	}
	g.edgenum = i;

	printf("\n");
	return OK;
}

void floyd(Graph &g, int D[MAXSIZE][MAXSIZE], int P[MAXSIZE][MAXSIZE]) {
	int k, i, j;
	for(i=0; i<g.vexnum; i++) {
		for(j=0; j<g.vexnum; j++) {
			P[i][j] = j;			// NOTE: P初始化成和列标相同
			D[i][j] = g.edge[i][j];	// NOTE: D初始化成和邻接矩阵相同
		}
	}

	for(k=0; k<g.vexnum; k++) {			// 中转点
		for(i=0; i<g.vexnum; i++) {		// 起点
			for(j=0; j<g.vexnum; j++) {	// 终点
				if((D[i][k] != INT_MAX && D[k][j] !=INT_MAX) && (D[i][k]+D[k][j]) < D[i][j]) {	// 如果从起点到终点经过某个中转会更近
					D[i][j] = D[i][k]+D[k][j];		// NOTE: 这里不用手动维持对称矩阵了，算法已经实现了
					P[i][j] = P[i][k];				// NOTE: 这里不要直接写成 P[i][j]=k 了
				}
			}
		}
	}

}

void FindPath(Graph &g, int P[MAXSIZE][MAXSIZE], int start, int end) {
	int tmp=start;
	while(tmp != end) {
		printf("V%c -> ", g.vex[tmp]);
		tmp = P[tmp][end];
	}
	printf("V%c\n", g.vex[end]);
}

// 数据使用《大话数据结构》p259(电子书p283), 图7-7-2
// 执行 a.out < data3 即可
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);
	printf("输入的顶点和边的个数:%d %d\n", g.vexnum, g.edgenum);

	int D[MAXSIZE][MAXSIZE];
	int P[MAXSIZE][MAXSIZE];
	floyd(g, D, P);
	FindPath(g, P, 0, 8);
	printf("从V0->V8(结点坐标)需要的最短里程为:%d\n", D[0][8]);

	return 0;
}
