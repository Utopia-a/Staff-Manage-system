#include"boss.h"

boss::boss(int id, string name, int did) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DptId = did;
}

void boss :: showinfo() {
	cout << "ְ����ţ� " << this->m_ID
		<< "\tְ�������� " << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ�𣺹���˾��������" << endl;

}

string boss::getDeptName()
{
	return string("�ܲ�");
}