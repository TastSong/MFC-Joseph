#pragma once
#include "Person.h"

class CCircle
{
public:
	CCircle();
	CCircle(int headCount, int start, int gap);
	~CCircle();
private:
	int headCount;	//总人数
	int start;	//起始位置
	int gap;	//间隔

public:
	CPerson* persons;  //入场人员
	int* roll;	 // //出局名单,零单元不用

private:
	void Bulid();   //创建约瑟夫环
public:
	bool JudgeHeadCount();  //判断总人数是否符合逻辑
	bool JudgeStart();   //判断起始位置是否符合逻辑
	bool JudgeGap();     //判断间隔是否符合逻辑
	void Run();     //执行约瑟夫环规则，找到出局名单
};

