#pragma once
#include "common.h"
typedef char SLDataType;

typedef struct SeqList
{
	SLDataType* a;
	int size;		//��Ч����
	int capacity;	//�ռ�����
}SL;

void SLInit(SL* ps1);	//��ʼ��˳���
void SLDestroy(SL* ps1);//����

void SLPrint(SL* ps1);			//��ӡ
void SLCheckCapacity(SL* ps1);	//����

// ͷβ����ɾ��
void SLPushBack(SL* ps1, SLDataType x);
void SLPushFront(SL* ps1, SLDataType x);
void SLPopBack(SL* ps1);
void SLPopFront(SL* ps1);

//�������±�λ�õĲ���ɾ��
void SLInsert(SL* psl, int pos, SLDataType x);
void SLErase(SL* psl, int pos);

//����
int SLFind(SL* psl, SLDataType x);

SLDataType SLVisit(SL* ps1, int pos);