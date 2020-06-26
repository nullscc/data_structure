// 要是边集数组表示边，且边已经按从小到大排好了

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"../common.h"

#define MAXSIZE 100
#define MAXEDGE MAXSIZE*(MAXSIZE-1)/2

typedef struct {
	int begin;
	int end;
	int weight;
}Edge;

typedef struct {
	char vex[MAXSIZE];
	Edge edge[MAXEDGE];
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

// NOTE: 这里输入时已经按顺序排好了
// 见文件data2
Status GetEdge(Graph &g) {
	int i, j;
	int v1, v2, weight;

	printf("请输入边信息, 格式为1,2,10 2,3,20(以1开始，前面两个代表边，最后一个代表权重), 0,0,0代表结束:");
	scanf("%d,%d,%d", &v1, &v2, &weight);
	i=0;
	while(v1 && v2 && weight) {
		g.edge[i] = {v1-1, v2-1, weight};
		scanf("%d,%d,%d", &v1, &v2, &weight);
		i++;
	}
	g.edgenum = i;

	printf("\n");
	return OK;
}

// NOTE: 主要用来发现是否组成了回路，主要是理解parent是用来干啥的
// 返回的其实是连通分量中最后一个加入的end的顶点坐标
int find(int *parent, int f) {
	while(parent[f]>0) f = parent[f];
	return f;
}

void kruskal(Graph &g) {
	int i, n, m;
	int parent[MAXSIZE];
	for(i=0; i<MAXSIZE; i++) {
		parent[i] = 0;
	}
	for(i=0; i<g.edgenum; i++) {
		m = find(parent, g.edge[i].begin);
		n = find(parent, g.edge[i].end);

		if(m != n) { 	// 如果begin所在的连通分量与end所在的连通分量的最后加入的一个是同一个，那么说明形成了回路
			parent[m] = n;
			printf("找到路径: %c->%c\n", g.vex[g.edge[i].begin], g.vex[g.edge[i].end]);
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

	kruskal(g);
	
	return 0;
}
