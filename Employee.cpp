#include"Employee.h"

Employee::Employee(int id, string name, int did) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DptId = did;
}

void Employee::showinfo() {
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成经理给的任务" << endl;
}

string Employee::getDeptName() {
	return string("员工");
}