#pragma once
#include<iostream>
#include"worker.h"
#include"Employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;

class WorkManager {
public:
	WorkManager();//���캯��

	~WorkManager();//��������

	void show_Menu();

	void exitSystem(); 

	void Add_emp();//���ְԱ

	void save();//�ļ�����������Ϣ

	int get_EmpNum();//���ļ��л�ȡԱ������

	void init_Emp();//��ʼ�����ļ��ж�ȡ������

	void show_emp();

	void Del_emp();

	int IsExist(int id);//����id�ж�ְ���Ƿ����

	void Mod_emp();//�޸�Ա��

	void Find_emp();//����ְ��

	void sort();

	void Clean_File();

public:
	int m_EmpNum;
	worker** m_EnpArray; //Ա�������ָ��

	bool m_FileIsEmpty;
};

