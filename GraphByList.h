#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MaxVertices 100
#include "SeqList.h"

typedef struct EdgeL
{
	char dest;
	int weight;
	struct EdgeL* next;
}EdgeL;
typedef struct VerticeL
{
	SLDataType data;
	int source;
	EdgeL* rear;
}VerticeL;
typedef struct GraphByList
{
	VerticeL verticeS[MaxVertices];
	int isDirect;
	int numOfEdages;
	int numOfVerts;
}GraphByList;
GraphByList* CreateLByFile(const char* file);
GraphByList* CreateGByL(SLDataType* arrayV, int n, int flag);
int GetIndexL(GraphByList* pg, SLDataType v);
EdgeL* NewNode(char dest, int weight);
void AddEdgeL(GraphByList* pg, SLDataType v1, SLDataType v2, int weight);
void PrintList(GraphByList* pg);
void VisitVL(SLDataType v);
int FindWeightL(GraphByList* pg, SLDataType src, SLDataType dst);
void DFSOrderL(GraphByList* pg, SLDataType src, int* isVisited);
void BFSOrderL(GraphByList* pg, SLDataType src);
void PrintDevsL(GraphByList* pg);