#pragma once
#include "common.h"
typedef char SLDataType;

typedef struct SeqList
{
	SLDataType* a;
	int size;		//有效数据
	int capacity;	//空间容量
}SL;

void SLInit(SL* ps1);	//初始化顺序表
void SLDestroy(SL* ps1);//销毁

void SLPrint(SL* ps1);			//打印
void SLCheckCapacity(SL* ps1);	//扩容

// 头尾插入删除
void SLPushBack(SL* ps1, SLDataType x);
void SLPushFront(SL* ps1, SLDataType x);
void SLPopBack(SL* ps1);
void SLPopFront(SL* ps1);

//在任意下标位置的插入删除
void SLInsert(SL* psl, int pos, SLDataType x);
void SLErase(SL* psl, int pos);

//查找
int SLFind(SL* psl, SLDataType x);

SLDataType SLVisit(SL* ps1, int pos);