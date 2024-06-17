#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include "common.h"
#include "GraphByMatrix.h"
#include "GraphByList.h"



int main()
{
	Main("graph.txt");
	return 0;
}




int mains()
{
	/*FILE* fp = fopen("graph.txt", "r");*/
	char fp[] = "graph.txt";
	//{
	//	GraphByMatrix* graph = NULL;
	//	graph = CreateMByFile(fp);
	//	PrintMatrix(graph);
	//	printf("---------\n");
	//	{
	//		int arr[11] = { 0 };
	//		DFSOrderM(graph, 'A', arr);
	//	}
	//	printf("\n---------\n");
	//	BFSOrderM(graph, 'A');
	//	printf("\n---------\n");
	//	PrintDevsM(graph);
	//	PrimM(graph, 'A');
	//}
	GraphByList* graphL = CreateLByFile(fp);
	printf("%d\n", GetIndexL(graphL, 'C'));
	printf("%d --- %d\n", graphL->numOfEdages,graphL->numOfVerts);
	PrintList(graphL);
	printf("%d\n", FindWeightL(graphL, 'A','B'));
	int arr[11] = { 0 };
	DFSOrderL(graphL, 'A', arr);
	printf("\n");
	BFSOrderL(graphL, 'A');
	PrintDevsL(graphL);
	return 0;
}