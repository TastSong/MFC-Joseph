#pragma once

class CPerson
{
public:
	CPerson();
	~CPerson();
public:
	int personNum;	//人物编号
	CPerson* pHand;	//人物的手，用作链接
};

