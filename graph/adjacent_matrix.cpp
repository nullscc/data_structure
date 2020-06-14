// 图的邻接矩阵（无向、无权）

#include<stdio.h>
#include<stdlib.h>
#include"../common.h"
#include"../queue/link_queue.cpp"

#define MAXSIZE 100

typedef struct {
	char vex[MAXSIZE];
	bool edge[MAXSIZE][MAXSIZE];
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
	int v1, v2;

	for(i=0; i<MAXSIZE; i++) {
		for(j=0; j<MAXSIZE; j++) {
			g.edge[i][j] = false;
		}
	}

	printf("请输入边信息, 格式为1,2 2,3(以1开始), 0,0代表结束:");
	scanf("%d,%d", &v1, &v2);
	i=0;
	while(v1 && v2) {
		g.edge[v1-1][v2-1] = true;
		g.edge[v2-1][v1-1] = true;
		scanf("%d,%d", &v1, &v2);
		i++;
	}
	g.edgenum = i;

	printf("\n");
	return OK;
}

bool IsConnect(Graph g, int v1, int v2) {
	return g.edge[v1-1][v2-1];
}

int GetDegree(Graph g, int v) {
	int i;
	int n=0;
	for(i=0; i<g.vexnum; i++) {
		if(g.edge[v-1][i])  n++;
	}
	return n;
}

char *GetAdjacent(Graph g, int v) {
	char *adjacent = (char*)malloc(sizeof(char)*g.vexnum);
	int i, j=0;
	for(i=0; i<g.vexnum; i++) {
		if(g.edge[v-1][i]) {
			adjacent[j] = g.vex[i];
			j++;
		}
	}
	adjacent[j] = '\0';
	return adjacent;
}

// 这里的v是0为起始下标
void visit(Graph g, int v) {
	printf("%c ", g.vex[v]);
}

// 这里的v是0为起始下标
void DFS(Graph &g, int v, bool *visited) {
	int i;
	visited[v] = true;
	visit(g, v);

	for(i=0; i<g.vexnum; i++) {
		if (!visited[i] && g.edge[v][i]) {	// NOTE: 这里和书上实现不一样
			DFS(g, i, visited);
		}
	}
}

void DFSSearch(Graph &g) {
	int i;

	bool *visited = (bool*)malloc(sizeof(bool)*g.vexnum);
	for(i=0; i<g.vexnum; i++) {
		visited[i] = false;
	}

	for(i=0; i<g.vexnum; i++) {
		if (!visited[i]) DFS(g, i, visited);
	}

	free(visited);
}

void BFS(Graph &g, int v, bool *visited) {
	Queue Q;
	InitQueue(Q);
	
	visit(g, v);
	visited[v] = true;

	EnQueue(Q, v);
	while(!QIsEmpty(Q)) {
		DeQueue(Q, v);
		
		int i;
		for(i=0; i<g.vexnum; i++) { 			// 找到所有与v直连的顶点
			if(!visited[i] && g.edge[v][i]) {
				EnQueue(Q, i);
				visit(g, i);
				visited[i] = true;
			}
		}
	}
}

void BFSSearch(Graph &g) {
	int i;

	bool *visited = (bool*)malloc(sizeof(bool)*g.vexnum);
	for(i=0; i<g.vexnum; i++) {
		visited[i] = false;
	}

	for(i=0; i<g.vexnum; i++) {
		if (!visited[i]) BFS(g, i, visited);	// 解决了多个连通分量的问题
	}

	free(visited);



}

// 数据使用《大话数据结构》p239(电子书p263), 图7-5-2
// 执行 a.out < data 即可
int main() {
	Graph g;
	GetVex(g);
	GetEdge(g);
	printf("输入的顶点和边的个数:%d %d\n", g.vexnum, g.edgenum);
	
	printf("1与5是否有边:%d， 1与2是否有边%d\n", IsConnect(g, 1, 5), IsConnect(g, 1, 2));
	printf("1的度:%d\n", GetDegree(g, 1));
	printf("1的所有邻接顶点:%s\n", GetAdjacent(g, 1));

	printf("深度优先搜索结果:");
	DFSSearch(g);
	printf("\n");

	printf("广度优先搜索结果:");
	BFSSearch(g); // NOTE: 这里的结果和《大话数据结构》p242(电子书p266)不一样，因为在同一层同一双亲的顺序是不定的
	printf("\n");

	
	return 0;
}
