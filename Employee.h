#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

class Employee : public worker {//�̳�
public:
	//���캯��
	Employee(int ID, string name, int did);

	//��ʾ������Ϣ
	virtual void showinfo();

	virtual string  getDeptName();

};
