#include"manager.h"

manager::manager(int id, string name, int did) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DptId = did;
}

void manager::showinfo() {
	cout << "职工编号： " << this->m_ID
		<< "\t职工姓名： " << this->m_Name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成老板交给的任务,并下发任务给员工" << endl;
}

string manager::getDeptName() {
	return string("经理");
}
