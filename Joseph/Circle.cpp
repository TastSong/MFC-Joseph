#include "stdafx.h"
#include "Circle.h"
#include "Person.h"

CCircle::CCircle()
{
}
//构造函数，对变量初始化
CCircle::CCircle(int headCount, int start, int gap)
{
	this->headCount = headCount;
	this->start = start;
	this->gap = gap;
	this->persons = new CPerson[this->headCount + 1];
	this->roll = new int[this->headCount + 1];	
}

CCircle::~CCircle()
{
}
//构造约瑟夫环,用pHand进行链接
void CCircle::Bulid()
{
	for (int i = 1; i < this->headCount; i++)
	{
		persons[i].pHand = &persons[i + 1];
		persons[i].personNum = i;
	}
	persons[this->headCount].pHand = &persons[1];
	persons[this->headCount].personNum = this->headCount;
}
//对变量是否符合逻辑的判断
bool CCircle::JudgeHeadCount()
{
	if (this->headCount > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CCircle::JudgeStart()
{
	if (this->start <= this->headCount && this->start > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CCircle::JudgeGap()
{
	if (this->gap > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CCircle::Run()
{
	Bulid();
	CPerson* p = &persons[1];
	for (int i = 2; i <= this->start; i++)
	{//查找起始位置
		p = p->pHand;
	}
	CPerson* q = p;  
	int cut = 1;   //计数器
	while (this->headCount)
	{
		for (int i = 2; i <= this->gap; i++)
		{//在gap(间隔)后的位置
			q = p;
			p = p->pHand;
		}//记录编号
		this->roll[cut] = p->personNum;
		q->pHand = p->pHand;  //踢人出局
		p = p->pHand;
		q = p;
		cut++;
		this->headCount--;
	}
}