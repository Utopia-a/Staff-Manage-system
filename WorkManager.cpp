#include"WorkManager.h"
#include<iostream>
#include<fstream>

#define FILENAME "empFile.txt"


WorkManager :: WorkManager() {
	this->m_EmpNum = 0;//��ʼ������
	this->m_EnpArray = NULL;//��ʼ������ָ��

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1���ļ����������
	if (!ifs.is_open()) {
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EnpArray = NULL;
		ifs.close();
		return;
	}
	//2���ļ�����������Ϊ��
		char ch;
		ifs >> ch;
		if (ifs.eof()) {
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
			this->m_EnpArray = NULL;
			ifs.close();
			return;
		}
	   
		this->m_EmpNum = this->get_EmpNum();//�����������ֲ����������ȡ

		this->m_EnpArray = new worker * [this->m_EmpNum];
		init_Emp();
}

WorkManager :: ~WorkManager() {//����������ʵ��

}

void WorkManager :: show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;

}

void WorkManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

void WorkManager::Add_emp() {
	cout << "���������" << endl;
	int addnum = 0;
	cin >> addnum;

	if(addnum > 0) {
		//�����¿ռ��С
		int newsize = this->m_EmpNum + addnum;

		//�����¿ռ�
		worker** newspace = new worker* [newsize];

		//ԭ����ת�Ƶ��¿��ٵĿռ���
		if (this->m_EnpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newspace[i] = this->m_EnpArray[i];
			}	
		}

		//������Ա��
		for (int i = 0; i < addnum; i++) {
			int id;
			string name;
			int dselect;
			
			cout << "�������" << i + 1 << "����Ա���ı��" << endl;
			cin >> id;
			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dselect;

			worker* worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new Employee(id, name, 1); 
					break;
			case 2:
				worker = new manager(id, name, 2);
					break;
			case 3:
				worker = new boss(id, name, 3);
					break;
			default:
				break;
			}

			newspace[i + this->m_EmpNum] = worker;
		}

		//ɾ��ԭ�пռ�
		delete[] this->m_EnpArray;
		
		//�Ծɻ���
		this->m_EnpArray = newspace;
		
		this->m_EmpNum = newsize;

		this->m_FileIsEmpty = false;//�ļ���Ϊ��

		cout << "�ɹ����" << addnum << "����ְ����" << endl;
		this->save();

	}
	else {
		cout << "�������" << endl;
	}
	system("pause");
	system("cls");//����
}


void WorkManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EnpArray[i]->m_ID << " "
			<< this->m_EnpArray[i]->m_Name << " "
			<< this->m_EnpArray[i]->m_DptId << endl;
	}
	ofs.close();
}

int WorkManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id  >> name  >> did) {//�ļ��ĸ�ʽ����ȡ, ע��˳��
		num++;
	}
	ifs.close();
	return num;
}

void WorkManager::init_Emp() {//���ļ��ж�ȡ��
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id >> name >> did) {
		worker* worker = NULL;
		if (did == 1) {
			worker = new Employee(id, name, did);
		}
		else if (did == 2) {
			worker = new manager(id, name, did);
		}
		else if(did == 3) {
			worker = new boss(did, name, did);
		}
		this->m_EnpArray[index] = worker;
		index++;
	}
}

void WorkManager::show_emp() {

	if (this->m_FileIsEmpty) {
		cout << "�ļ�������orΪ��" << endl;
	}
	else{
		for (int i = 0; i < m_EmpNum; i++) {
			this->m_EnpArray[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Del_emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		cout << "������Ҫɾ��Ա����ְ�����" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1) {
			for (int i = index; i < this->m_EmpNum; i++) {
				this->m_EnpArray[i] = this->m_EnpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();//ͬ�����ļ�
			cout << "ɾ���ɹ�" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum - 1; i++) {
		if (this->m_EnpArray[i]->m_ID == id) {
			index = i;
			break;
		}
	}
	return index;
}

void WorkManager::Mod_emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else {
		cout << "�������޸�ְ���ı��" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EnpArray[ret];//�ͷ�ԭ��λ�õ��ڴ�
			this->m_EnpArray[ret] = nullptr;//��ֹ����ָ��
			
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽�� " << id << "��ְ������������ְ���ţ� " << endl;
			cin >> newId;

			cout << "�������������� " << endl;
			cin >> newName;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			this->m_EnpArray[ret] = worker;
			cout << "�޸ĳɹ�" << endl;
			this->save();
		}
		else {
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Find_emp() {
	//���ݱ�Ų���
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		cout << "��������ҷ�ʽ" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.����������" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "��������Ҫ����Ա���ı��" << endl;
			cin >> id;
			
			int index = this->IsExist(id);
			if (index != -1) {
				cout << "���ҳɹ�����ְ����Ϣ����" << endl;
				this->m_EnpArray[index]->showinfo();
			}
			else {
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "��������ҵ�����" << endl;
			cin >> name;
			
			bool flag = false;
			for(int i = 0; i < this->m_EmpNum; i++){
				if (this->m_EnpArray[i]->m_Name == name) {
					cout << "���ҳɹ���ְ�����Ϊ"
						<< this->m_EnpArray[i]->m_ID
						<< "�ŵ���Ϣ����" << endl;
					flag = true;
					this->m_EnpArray[i]->showinfo();

				}
			}
			if (flag == false) {
				cout << "����ʧ�ܣ�����ʧ��" << endl;
			}
		}
		else {
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::sort() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ�������or��¼Ϊ��";
	}
	else {
		cout << "��ѡ������ʽ" << endl
			<< "1.���չ��Ž�������" << endl
			<< "2.���չ��Ž��н���" << endl;
		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++) {
			int minorMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++) {
				if (select == 1) {
					if (this->m_EnpArray[minorMax]->m_ID > this->m_EnpArray[j]->m_ID) {
						minorMax = j;
					}
				}
				else {
					if (this->m_EnpArray[minorMax]->m_ID < this->m_EnpArray[j]->m_ID) {
						minorMax = j;
					}
				}
			}
			if (i != minorMax) {
				worker* temp = this->m_EnpArray[i];
				this->m_EnpArray[i] = this->m_EnpArray[minorMax];
				this->m_EnpArray[minorMax] = temp;
			}

		}
		cout << "����ɹ���������£�" << endl;
		this->save();
		this->show_emp();

	}
	system("puase");
	system("cls");
}

void WorkManager::Clean_File() {
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ifs(FILENAME, ios::trunc);//truncģʽ�£��������ļ�������գ���д��
		ifs.close();
		if (this->m_EnpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EnpArray[i] != NULL) {
					delete this->m_EnpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[]this->m_EnpArray;
			this->m_EnpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");

}