#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include "GraphByList.h"
#define NoWeight -1
GraphByList* CreateLByFile(const char* file)
{
	FILE* pf = fopen(file, "r");
	int n = 0;
	int flag = 0;
	fscanf(pf, "%d %d", &n, &flag);
	SLDataType* arrayV = (SLDataType*)malloc((n + 1) * sizeof(SLDataType));
	fscanf(pf, "%s\n", arrayV);
	GraphByList* pg = CreateGByL(arrayV, n, flag);
	SLDataType dst, src;
	int weight;
	while (true)
	{
		int num = fscanf(pf, "%c %c %d\n", &src, &dst, &weight);
		if (num != 3)break;
	
		AddEdgeL(pg, src, dst, weight);
	}
	fclose(pf);
	return pg;
}
GraphByList* CreateGByL(SLDataType* arrayV, int n, int flag)
{
	GraphByList* pg = (GraphByList*)malloc(sizeof(GraphByList));
	if (!pg)return NULL;
	pg->isDirect = flag;
	pg->numOfEdages = 0;
	pg->numOfVerts = 0;
	for (int i = 0; i < n; i++)
	{
	//	pg->verticeS[i] = (VerticeL*)malloc(sizeof(VerticeL));
		pg->verticeS[i].data = arrayV[i];
		pg->numOfVerts++;
		pg->verticeS[i].source = i;
		pg->verticeS[i].rear = NULL;
	}
	return pg;
}
int GetIndexL(GraphByList* pg, SLDataType v) {
	for (int i = 0; i < MaxVertices; i++) {
		if (pg->verticeS[i].data == v) {
			return i;
		}
	}
	return -1;
}
EdgeL* NewNode(char dest, int weight)
{
	EdgeL* newnode = (EdgeL*)malloc(sizeof(EdgeL));
	if (!newnode)return NULL;
	newnode->next = NULL;
	newnode->dest = dest;
	newnode->weight = weight;
	return newnode;
}
void AddEdgeL(GraphByList* pg, SLDataType src, SLDataType dst, int weight)
{
	int srcindex = GetIndexL(pg, src);
	int dstindex = GetIndexL(pg, dst);
	if (srcindex == -1 || dstindex == -1 || srcindex == dstindex)return;
	EdgeL* cur = pg->verticeS[srcindex].rear;
	EdgeL* newnode = NewNode(dst, weight);
	newnode->next = pg->verticeS[srcindex].rear;
	pg->verticeS[srcindex].rear = newnode;
	pg->numOfEdages++;
	if (!pg->isDirect)
	{
		newnode = NewNode(src, weight);
		newnode->next = pg->verticeS[dstindex].rear;
		pg->verticeS[dstindex].rear = newnode;
		pg->numOfEdages++;
	}
	cur = NULL;
	newnode = NULL;
}
void PrintList(GraphByList* pg) {
	int n = pg->numOfVerts;
	for (int i = 0; i < n; i++) {

		EdgeL* cur = pg->verticeS[i].rear;
		SLDataType src = pg->verticeS[i].data;
		printf("[%c]", src);
		if (cur == NULL) {
			printf("\n");
			continue;
		}
		while (cur != NULL) {
			printf("( %c -> %c = %d )", src, cur->dest, cur->weight);
			if (cur->next != NULL) {
				printf(" -> ");
			}
			cur = cur->next;
		}
		printf("\n");
	}
}
void VisitVL(SLDataType v)
{
	printf("%c", v);
}
int FindWeightL(GraphByList* pg, SLDataType src, SLDataType dst)
{
	int srcindex = GetIndexL(pg,src);
	EdgeL* temp = pg->verticeS[srcindex].rear;
	while (temp!=NULL)
	{
		if (temp->dest == dst)
		{
			return temp->weight;
		}
		temp = temp->next;
	}
	return NoWeight;
}
void DFSOrderL(GraphByList* pg, SLDataType src, int* isVisited)
{
	int srcindex = GetIndexL(pg, src);
	VisitVL(src);
	isVisited[srcindex] = 1;
	for (int i = 0; i < pg->numOfVerts; i++)
	{
		if (!isVisited[i] && FindWeightL(pg, src, pg->verticeS[i].data) != NoWeight)
			DFSOrderL(pg, pg->verticeS[i].data, isVisited);
	}
}
void BFSOrderL(GraphByList* pg, SLDataType src)
{
	int size = pg->numOfVerts;
	int* visited = (int*)calloc(size + 1, sizeof(int));
	if (!visited)return;
	std::queue<char> q;
	q.push(src);
	while (!q.empty())
	{
		SLDataType srcdata = q.front();
		visited[GetIndexL(pg, srcdata)] = 1;
		VisitVL(srcdata);
		q.pop();
		for (int i = 0; i < pg->numOfVerts; i++)
		{
			if (!visited[i] && FindWeightL(pg, srcdata, pg->verticeS[i].data) != NoWeight)
			{
				q.push(pg->verticeS[i].data);
				visited[i] = 1;
			}
		}
	}

}
void PrintDevsL(GraphByList* pg)
{
	for (int i = 0; i < pg->numOfVerts; i++)
	{
		int count1 = 0;
		EdgeL* temp = pg->verticeS[i].rear;
		while (temp!=NULL)
		{
			count1++;
			temp = temp->next;
		}
		if (pg->isDirect)
		{
			int count2 = 0;
			for (int j = 0; j < pg->numOfVerts; j++)
			{
				if (j == i)continue;
				int t = FindWeightL(pg, pg->verticeS[j].data, pg->verticeS[i].data);
				if(t!=NoWeight) count2++;
			}
			printf("有向图顶点%c，出度 = %d，入度 = %d\n", pg->verticeS[i].data, count1, count2);
		}
		else
		{
			printf("无向图顶点%c，出度 = 入度 = %d\n", pg->verticeS[i].data, count1);
		}
	}
}
