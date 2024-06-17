#define _CRT_SECURE_NO_WARNINGS

#include "SeqList.h"
#include "GraphByMatrix.h"
#include "common.h"

int GetIndexM(GraphByMatrix* pg, SLDataType v)
{
	return SLFind(&(pg->Vertices), v);
}
void AddEdgeM(GraphByMatrix* pg, SLDataType v1, SLDataType v2, int weight)
{
	int src = GetIndexM(pg, v1);
	int dst = GetIndexM(pg, v2);
	if (dst != -1 && src != -1 && dst != src)
	{
		pg->edge[src][dst] = weight;
		pg->numOfEdges++;
		if (!pg->isDirect)
		{
			pg->edge[dst][src] = weight;
			pg->numOfEdges++;
		}
	}
}
GraphByMatrix* CreateGByM(SLDataType* arrayV, int n, int flag)
{
	GraphByMatrix* pg = (GraphByMatrix*)malloc(sizeof(GraphByMatrix));
	if (!pg)return NULL;
	pg->isDirect = flag;
	pg->numOfEdges = 0;
	SLInit(&(pg->Vertices));
	for (int i = 0; i < n; i++)
	{
		SLPushBack(&(pg->Vertices), arrayV[i]);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				(pg->edge)[i][j] = 0;
			}
			else
			{
				(pg->edge)[i][j] = INT_MAX;
			}
		}
	}
	return pg;
}
GraphByMatrix* CreateMByFile(const char* file)
{
	FILE* pf = fopen(file, "r");
	int n = 0;
	int flag = 0;
	fscanf(pf, "%d %d", &n, &flag);
	SLDataType* arrayV = (SLDataType*)malloc((n + 1) * sizeof(SLDataType));
	fscanf(pf, "%s\n", arrayV);
	GraphByMatrix* pg = CreateGByM(arrayV, n, flag);
	SLDataType dst, src;
	int weight;
	while (true)
	{
		int num = fscanf(pf, "%c %c %d\n", &src, &dst, &weight);
		if (num != 3)break;
		AddEdgeM(pg, src, dst, weight);
	}
	fclose(pf);
	return pg;
}
void PrintMatrix(GraphByMatrix* pg)
{
	int n = pg->Vertices.size;
	//printf("%d %d ", n, pg->isDirect);
	printf("   ");
	for (int i = 0; i < n; i++)
	{
		printf("[%c]", pg->Vertices.a[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("[%c]", pg->Vertices.a[i]);
		for (int j = 0; j < n; j++)
		{
			if (pg->edge[i][j] == INT_MAX)
			{
				printf(" ∞ ");
			}
			else
			{
				printf(" %d ", pg->edge[i][j]);
			}
		}
		printf("\n");
	}
}
void VisitVM(SLDataType v)
{
	printf("%c", v);
}
void DFSOrderM(GraphByMatrix* pg, SLDataType src, int* isVisited)
{
	int srcindex = GetIndexM(pg, src);
	VisitVM(src);
	isVisited[srcindex] = 1;
	for (int i = 0; i < pg->Vertices.size; i++)
	{
		if (!isVisited[i] && pg->edge[srcindex][i] != INT_MAX)
			DFSOrderM(pg, SLVisit(&(pg->Vertices),i), isVisited);
	}
}
void BFSOrderM(GraphByMatrix* pg, SLDataType src)
{
	int size = pg->Vertices.size;
	int* visited = (int*)calloc(size+1, sizeof(int));
	if (!visited)return;
	std::queue<char> q;
	q.push(src);
	while (!q.empty())
	{
		int srcindex = GetIndexM(pg, q.front());
		visited[srcindex] = 1;
		printf("%c", q.front());
		q.pop();
		for (int i = 0; i < pg->Vertices.size; i++)
		{
			if (!visited[i] && pg->edge[srcindex][i] != INT_MAX)
			{
				q.push(SLVisit(&(pg->Vertices), i));
				visited[i] = 1;
			}
		}
	}

}
void PrintDevOfVM(GraphByMatrix* pg, SLDataType v)
{
	int indexV = GetIndexM(pg, v);
	int n = pg->Vertices.size;
	int count1 = 0;
	for (int i = 0; i < n; i++) {
		if (pg->edge[indexV][i] != INT_MAX && indexV != i) {
			count1++;
		}
	}
	if (!pg->isDirect) {
		printf("无向图顶点%c，出度 = 入度 = %d\n", v, count1);
	}
	else {
		int count2 = 0;
		for (int i = 0; i < n; i++) {
			if (pg->edge[i][indexV] != INT_MAX && indexV != i) {
				count2++;
			}
		}
		printf("有向图顶点%c，出度 = %d，入度 = %d\n", v, count1, count2);
	}
}
void PrintDevsM(GraphByMatrix* pg)
{
	for (int i = 0; i < pg->Vertices.size; i++)
	{
		PrintDevOfVM(pg, pg->Vertices.a[i]);
	}
}
SLDataType FindOtherM(GraphByMatrix* pg, SLDataType src,int weight)
{
	int srcindex = GetIndexM(pg, src), Vsize = pg->Vertices.size;
	for (int i = 0; i < Vsize; i++)
	{
		if (pg->edge[i][srcindex] == weight)
		{
			return SLVisit(&(pg->Vertices), i);
		}
	}

}
typedef struct MinSpanTreeNode
{
	SLDataType Vsrc;
	SLDataType Vdst;
	int weight;
}MinSpanTreeNode;
void PrimM(GraphByMatrix* pg, SLDataType src)
{
	int srcindex = GetIndexM(pg, src);
	int Vsize = pg->Vertices.size, MinTreeIndex = 0;
	MinSpanTreeNode* MinSpanTree = (MinSpanTreeNode*)malloc(sizeof(MinSpanTreeNode) * Vsize);
	if (!MinSpanTree)return;
	int* lowCost = (int*)malloc(sizeof(int) * Vsize);
	if (!lowCost)return;
	for (int i = 0; i < Vsize; i++)lowCost[i] = pg->edge[srcindex][i];
	//for (int i = 0; i < Vsize; i++)printf("%d ", lowCost[i]);
	//printf("\n");
	//MinSpanTree[MinTreeIndex].Vsrc = src;
	//lowCost[srcindex] = -1;
	for (int i = 0; i < Vsize-1; i++)
	{
		//if (lowCost[i] == 0)continue;
		int minCost = INT_MAX, minIndex = -1;
		for (int j = 0; j < Vsize; j++)
		{
			if (lowCost[j] < minCost && lowCost[j]>0)
			{
				minCost = lowCost[j];
				minIndex = j;
			}
		}
		if(minIndex!=-1)
		{
			MinSpanTree[MinTreeIndex].Vdst = SLVisit(&(pg->Vertices), minIndex);
			MinSpanTree[MinTreeIndex].Vsrc = FindOtherM(pg, MinSpanTree[MinTreeIndex].Vdst, minCost);
			
			MinSpanTree[MinTreeIndex++].weight = minCost;
			/*printf("%d---", minCost);*/
			lowCost[minIndex] = 0;
			for (int j = 0; j < Vsize; j++)
			{
				if (pg->edge[minIndex][j] < lowCost[j] && lowCost[j]>0)
				{
					lowCost[j] = pg->edge[minIndex][j];
				}
			}
		}
		//for (int i = 0; i < Vsize; i++)printf("%d ", lowCost[i]);
		//printf("\n");
	}
	for (int i = 0; i < MinTreeIndex; i++)
	{
		printf("(%c-%c-%d)", MinSpanTree[i].Vsrc, MinSpanTree[i].Vdst, MinSpanTree[i].weight);
	}
	printf("\n");	
}