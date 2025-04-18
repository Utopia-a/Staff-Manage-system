#pragma once
#include<iostream>
#include<string>

using namespace std;

class worker {
public:
	//显示个人信息
	virtual void showinfo() = 0;

	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_ID;//职工编号
	string m_Name;//职工姓名
	int m_DptId;//职工部门名称编号

};