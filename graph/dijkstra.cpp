// 无向网的Dijkstra算法(找最短路径)
// 算法基本思路是: 每次都只设法找到除已找到的最短路径结点
// 采用邻接矩阵存储

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

void Dijkstra(Graph &g, int start, int *parent_path, int *shortest_weight) {
	int i, j;
	bool f[MAXSIZE];
	for(i=0; i<g.vexnum; i++) {
		shortest_weight[i] = g.edge[start][i];
		f[i] = 0;
		parent_path[i] = start;
	}
	shortest_weight[start] = 0;
	f[start] = 1;

	for(i=1; i<g.vexnum; i++) {		// 仅用于计数
		int min = INT_MAX;
		int k;
		for(j=0; j<g.vexnum; j++) {		// 一定能找到除已经找过的最短路径，它依据这个for循环所在的大for循环的下一个for的不断更新的数据来找
			if(!f[j] && shortest_weight[j] < min) {
				min = shortest_weight[j];
				k = j;
			}
		
		}
		f[k] = 1;							// 因为下面的for循环已经将数据更新进shortest_weight，所以这里找到的最小的权重的值就是start到其最短的路径
		for(j=0; j<g.vexnum; j++) {			// 依据找到的最短路径k去更远的地方找
			if(!f[j] && g.edge[k][j]!=INT_MAX && min+g.edge[k][j] < shortest_weight[j]) {		// NOTE: 中转比直接到耗费更小
				// NOTE: 如果边的权重本身已经是无穷大了，加上某个数不可能比shortest_weight[j], 所以要判断g.edge[k][j]本身是否已经是无穷大了，如果是无穷大说明它们本身就不相连，也就不存在判断了
				shortest_weight[j] = min+g.edge[k][j];
				parent_path[j] = k;
			}
		}
	}
}


// 数据使用《大话数据结构》p259(电子书p283), 图7-7-2
// 执行 a.out < data3 即可
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);
	printf("输入的顶点和边的个数:%d %d\n", g.vexnum, g.edgenum);

	int parent_path[MAXSIZE];
	int start = 0;
	int shortest_weight[MAXSIZE];
	Dijkstra(g, start, parent_path, shortest_weight);
	printf("从%d->9(结点坐标)需要的最短里程为:%d\n", start+1, shortest_weight[8]);

	printf("从终点到源点的路径为:\n");
	int v = 8;
	while(v!=start) {
		printf("%d <- %d\n", parent_path[v], v);
		v = parent_path[v];
	}

	return 0;
}
