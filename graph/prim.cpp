// 无向网的Prim算法(找最小生成树)
// 算法基本思路是: 从某个点出发，每次都找与之相连权值最小的路径，知道所有顶点都连上了
// 采用邻接矩阵存储，这个程序的缺陷在于: 主对角线元素必须全为0，且能连上的边的权值不能为0

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
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

void prim(Graph &g) {
	// NOTE: 关键在于理解这两个数组，要记住，他们两个是同时改变储值的
	int lowcost[MAXSIZE];		// lowcost有两个作用: 为0代表已经作为顶点纳入到了最小生成树里面了；存储已经纳入的所有顶点的与之相连边的权值，以便找出代价最小的路径
	int adjvex[MAXSIZE];		// 它的作用仅仅是: 当找到一个最小的顶点坐标k，那么adjvex[k]代表与k相连的顶点坐标
	
	int i, j;
	for(i=0; i<g.vexnum; i++) {
		lowcost[i] = g.edge[0][i];
		adjvex[i] = 0;
	}

	for(i=1; i<g.vexnum; i++) {	// 单纯为了计数而已，找到vexnum-1个就可以了
		int min = INT_MAX;
		int k;
		for(j=0; j<g.vexnum; j++) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
		}
		printf("找到路径:%c->%c\n", g.vex[adjvex[k]], g.vex[k]);

		for(j=0; j<g.vexnum; j++) {
			if(lowcost[j]!=0 && g.edge[k][j] < lowcost[j]) {
				lowcost[j] = g.edge[k][j];
				adjvex[j] = k;
			}
		}
	}
}

// 数据使用《大话数据结构》p247(电子书p271), 图7-6-3
// 执行 a.out < data2 即可
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);
	printf("输入的顶点和边的个数:%d %d\n", g.vexnum, g.edgenum);

	prim(g);
	
	return 0;
}
