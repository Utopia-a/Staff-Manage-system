#pragma once
#include<iostream>
#include"worker.h"
#include"Employee.h"
#include"manager.h"
#include"boss.h"

using namespace std;

class WorkManager {
public:
	WorkManager();//构造函数

	~WorkManager();//析构函数

	void show_Menu();

	void exitSystem(); 

	void Add_emp();//添加职员

	void save();//文件操作保存信息

	int get_EmpNum();//从文件中获取员工数量

	void init_Emp();//初始化从文件中读取的数据

	void show_emp();

	void Del_emp();

	int IsExist(int id);//按照id判断职工是否存在

	void Mod_emp();//修改员工

	void Find_emp();//查找职工

	void sort();

	void Clean_File();

public:
	int m_EmpNum;
	worker** m_EnpArray; //员工数组的指针

	bool m_FileIsEmpty;
};

