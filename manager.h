#pragma once
#include"worker.h"
#include<string>
#include<iostream>

using namespace std;

class manager : public worker {
public:
	manager(int id, string name, int did);

	virtual void showinfo();//显示个人信息

	virtual string getDeptName();//获取岗位信息

};