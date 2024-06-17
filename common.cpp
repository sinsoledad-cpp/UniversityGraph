#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include "common.h"
#include "GraphByList.h"
#include "GraphByMatrix.h"
#define MAXSIZE 100
void MenuMain() 
{
	printf("***************************\n");
	printf("0. �˳�\n");
	printf("1. ����һ��������10������Ĵ�Ȩ����ͼG\n");
	printf("2. ���ڽӾ�����Ϊ���ṹ�洢ͼG��������ڽӾ���\n");
	printf("3. ���ڽ�������Ϊ���ṹ�洢ͼG��������ڽ�����\n");
	printf("4. ��������ȱ���(DFS)�㷨���ͼG�ж���ı�������\n");
	printf("5. ��������ȱ���(BFS)�㷨���ͼG�ж���ı�������\n");
	printf("6. ��д�������ڽӾ��󣨻����ڽӱ��洢�ṹ��ͼG�и��������Ⱥͳ���\n");
	printf("7. ʹ��Prime�㷨(����Kruskal�㷨)��ĳ��ָ���Ķ���������ͼG����С������\n");
	printf("***************************\n");

}

int SelectML()
{
	printf("1ѡ���ڽӾ��� 0ѡ���ڽ�����\n");
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
			printf("�˳���-----");
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