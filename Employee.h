#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Employee : public worker {//继承
public:
	//构造函数
	Employee(int ID, string name, int did);

	//显示个人信息
	virtual void showinfo();

	virtual string  getDeptName();

};
