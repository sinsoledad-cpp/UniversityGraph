#pragma once
#pragma warning(disable:6031)
#include "SeqList.h"
#define  MaxVertices 100

typedef struct GraphByMatrix {

	SL Vertices;
	int edge[MaxVertices][MaxVertices];
	int isDirect;
	int numOfEdges;
}GraphByMatrix;
int GetIndexM(GraphByMatrix* pg, SLDataType v);
void AddEdgeM(GraphByMatrix* pg, SLDataType v1, SLDataType v2, int weight);
GraphByMatrix* CreateGByM(SLDataType* arrayV, int n, int flag);
GraphByMatrix* CreateMByFile(const char* file);
void PrintMatrix(GraphByMatrix* pg);
void VisitVM(SLDataType v);
void DFSOrderM(GraphByMatrix* pg, SLDataType src, int* isVisited);
void BFSOrderM(GraphByMatrix* pg, SLDataType src);
void PrintDevOfVM(GraphByMatrix* pg, SLDataType v);
void PrintDevsM(GraphByMatrix* pg);
void PrimM(GraphByMatrix* pg, SLDataType src);
SLDataType FindOtherM(GraphByMatrix* pg, SLDataType src, int weight);