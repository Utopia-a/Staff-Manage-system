#pragma once
#include"worker.h"
#include<string>
#include<iostream>

using namespace std;

class manager : public worker {
public:
	manager(int id, string name, int did);

	virtual void showinfo();//��ʾ������Ϣ

	virtual string getDeptName();//��ȡ��λ��Ϣ

};