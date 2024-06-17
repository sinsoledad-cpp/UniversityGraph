#include"SeqList.h"

//��ʼ��
void SLInit(SL* psl)
{
	assert(psl);

	psl->a = NULL;
	psl->size = 0;
	psl->capacity = 0;
}

//����
void SLDestroy(SL* psl)
{
	assert(psl);
	if (psl->a != NULL)
	{
		free(psl->a);
		psl->a = NULL;
		psl->size = 0;
		psl->capacity = 0;
	}
}

//��ӡ
void SLPrint(SL* psl)
{
	assert(psl);
	for (int i = 0; i < psl->size; i++)
	{
		printf("%d ", psl->a[i]);
	}
	printf("\n");
}

//����
void SLCheckCapacity(SL* psl)
{
	assert(psl);
	if (psl->size == psl->capacity)
	{
		int newCapacity = psl->capacity == 0 ? 4 : psl->capacity * 2;
		SLDataType* tmp = (SLDataType*)realloc(psl->a, sizeof(SLDataType) * newCapacity);
		if (tmp == NULL)
		{
			perror("realloc fail");
			return;
		}
		psl->a = tmp;
		psl->capacity = newCapacity;
	}
}

//β��
void SLPushBack(SL* psl, SLDataType x)
{
	assert(psl);

	SLCheckCapacity(psl);

	psl->a[psl->size] = x;
	psl->size++;
}

//ͷ��
void SLPushFront(SL* psl, SLDataType x)
{
	assert(psl);

	SLCheckCapacity(psl);

	// Ų������
	int end = psl->size - 1;
	while (end >= 0)
	{
		psl->a[end + 1] = psl->a[end];
		--end;
	}
	psl->a[0] = x;
	psl->size++;
}

//βɾ
void SLPopBack(SL* psl)
{
	assert(psl->size > 0);
	psl->size--;
}

//ͷɾ
void SLPopFront(SL* psl)
{
	assert(psl->size > 0);
	int begin = 1;
	while (begin < psl->size)
	{
		psl->a[begin - 1] = psl->a[begin];
		++begin;
	}
	psl->size--;
}

int SLFind(SL* psl, SLDataType x)
{
	assert(psl);
	for (int i = 0; i <= psl->size; i++)
	{
		if (psl->a[i] == x)
		{
			return i;
		}
	}
	return -1;
}

// ע��pos���±�
// size�����ݸ����������±�Ļ����������һ�����ݵ���һ��λ��
void SLInsert(SL* psl, int pos, SLDataType x)
{
	assert(psl);
	assert(pos >= 0 && pos <= psl->size);
	SLCheckCapacity(psl);
	int end = psl->size - 1;
	while (end >= pos)
	{
		psl->a[end + 1] = psl->a[end];
		--end;
	}
	psl->a[pos] = x;
	psl->size++;
}

void SLErase(SL* psl, int pos)
{
	assert(psl);
	assert(pos >= 0 && pos < psl->size);
	int begin = pos + 1;
	while (begin < psl->size)
	{
		psl->a[begin - 1] = psl->a[begin];
		++begin;
	}
	psl->size--;
}

SLDataType SLVisit(SL* ps1, int pos)
{
	return ps1->a[pos];
}