#include"Employee.h"

Employee::Employee(int id, string name, int did) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DptId = did;
}

void Employee::showinfo() {
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ����ɾ����������" << endl;
}

string Employee::getDeptName() {
	return string("Ա��");
}