#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include "common.h"
#include "GraphByList.h"
#include "GraphByMatrix.h"
#define MAXSIZE 100
void MenuMain() 
{
	printf("***************************\n");
	printf("0. 退出\n");
	printf("1. 建立一个不少于10个顶点的带权无向图G\n");
	printf("2. 用邻接矩阵作为储结构存储图G并输出该邻接矩阵\n");
	printf("3. 用邻接链表作为储结构存储图G并输出该邻接链表\n");
	printf("4. 按深度优先遍历(DFS)算法输出图G中顶点的遍历序列\n");
	printf("5. 按广度优先遍历(BFS)算法输出图G中顶点的遍历序列\n");
	printf("6. 编写函数求邻接矩阵（或者邻接表）存储结构的图G中各顶点的入度和出度\n");
	printf("7. 使用Prime算法(或者Kruskal算法)从某个指定的顶点出发输出图G的最小生成树\n");
	printf("***************************\n");

}

int SelectML()
{
	printf("1选择邻接矩阵 0选择邻接链表\n");
	int mode;
	scanf("%d", &mode);
	return mode;
}

void Main(const char *fp)
{
	GraphByMatrix* graphM = NULL;
	GraphByList* graphL = NULL;

	while (true)
	{
		MenuMain();
		int select;
		printf("your select: ");
		scanf("%d", &select);
		if (select == 0)
		{
			printf("退出中-----");
			break;
		}
		else if (select == 1)
		{
			graphM = CreateMByFile(fp);
			graphL = CreateLByFile(fp);
		}
		else if (select == 2)
		{
			PrintMatrix(graphM);
		}
		else if (select == 3)
		{
			PrintList(graphL);
		}
		else if (select == 4)
		{
			int mode = SelectML();
			if (mode == 0)
			{
				if (!graphL)continue;
				int size = graphL->numOfVerts;
				int* visited = (int*)calloc(size + 1, sizeof(int));
				if (!visited)return;
				DFSOrderL(graphL, 'A', visited);
			}
			else
			{
				if (!graphM)continue;
				int size = graphM->Vertices.size;
				int* visited = (int*)calloc(size + 1, sizeof(int));
				if (!visited)return;
				DFSOrderM(graphM, 'A', visited);
			}
			printf("\n");
		}
		else if (select == 5)
		{
			int mode = SelectML();
			if (mode == 0)
			{
				BFSOrderL(graphL, 'A');
			}
			else
			{
				BFSOrderM(graphM, 'A');
			}
			printf("\n");
		}
		else if (select == 6)
		{
			PrintDevsM(graphM);
		}
		else if (select == 7)
		{
			PrimM(graphM, 'A');
		}
	}

}