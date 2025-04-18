#include"WorkManager.h"
#include<iostream>
#include<fstream>

#define FILENAME "empFile.txt"


WorkManager :: WorkManager() {
	this->m_EmpNum = 0;//初始化人数
	this->m_EnpArray = NULL;//初始化数组指针

	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1、文件不存在情况
	if (!ifs.is_open()) {
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EnpArray = NULL;
		ifs.close();
		return;
	}
	//2、文件存在且数据为空
		char ch;
		ifs >> ch;
		if (ifs.eof()) {
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
			this->m_EnpArray = NULL;
			ifs.close();
			return;
		}
	   
		this->m_EmpNum = this->get_EmpNum();//若是上面两种不成立，则获取

		this->m_EnpArray = new worker * [this->m_EmpNum];
		init_Emp();
}

WorkManager :: ~WorkManager() {//析构函数空实现

}

void WorkManager :: show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;

}

void WorkManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	exit(0);
}

void WorkManager::Add_emp() {
	cout << "输入的人数" << endl;
	int addnum = 0;
	cin >> addnum;

	if(addnum > 0) {
		//计算新空间大小
		int newsize = this->m_EmpNum + addnum;

		//开辟新空间
		worker** newspace = new worker* [newsize];

		//原数据转移到新开辟的空间中
		if (this->m_EnpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newspace[i] = this->m_EnpArray[i];
			}	
		}

		//输入新员工
		for (int i = 0; i < addnum; i++) {
			int id;
			string name;
			int dselect;
			
			cout << "请输入第" << i + 1 << "个新员工的编号" << endl;
			cin >> id;
			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

		//删除原有空间
		delete[] this->m_EnpArray;
		
		//以旧换新
		this->m_EnpArray = newspace;
		
		this->m_EmpNum = newsize;

		this->m_FileIsEmpty = false;//文件不为空

		cout << "成功添加" << addnum << "名新职工！" << endl;
		this->save();

	}
	else {
		cout << "输入错误" << endl;
	}
	system("pause");
	system("cls");//清屏
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
	while (ifs >> id  >> name  >> did) {//文件的格式化读取, 注意顺序
		num++;
	}
	ifs.close();
	return num;
}

void WorkManager::init_Emp() {//从文件中读取的
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
		cout << "文件不存在or为空" << endl;
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
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		cout << "请输入要删除员工的职工编号" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1) {
			for (int i = index; i < this->m_EmpNum; i++) {
				this->m_EnpArray[i] = this->m_EnpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();//同步到文件
			cout << "删除成功" << endl;
		}
		else {
			cout << "删除失败，查无此人" << endl;
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
		cout << "文件不存在或者为空" << endl;
	}
	else {
		cout << "请输入修改职工的编号" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EnpArray[ret];//释放原有位置的内存
			this->m_EnpArray[ret] = nullptr;//防止悬空指针
			
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
			cin >> newId;

			cout << "请输入新姓名： " << endl;
			cin >> newName;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			cout << "修改成功" << endl;
			this->save();
		}
		else {
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Find_emp() {
	//根据编号查找
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		cout << "请输入查找方式" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			int id;
			cout << "请输入需要查找员工的编号" << endl;
			cin >> id;
			
			int index = this->IsExist(id);
			if (index != -1) {
				cout << "查找成功，该职工信息如下" << endl;
				this->m_EnpArray[index]->showinfo();
			}
			else {
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入查找的名字" << endl;
			cin >> name;
			
			bool flag = false;
			for(int i = 0; i < this->m_EmpNum; i++){
				if (this->m_EnpArray[i]->m_Name == name) {
					cout << "查找成功，职工编号为"
						<< this->m_EnpArray[i]->m_ID
						<< "号的信息如下" << endl;
					flag = true;
					this->m_EnpArray[i]->showinfo();

				}
			}
			if (flag == false) {
				cout << "查找失败，查找失败" << endl;
			}
		}
		else {
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::sort() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在or记录为空";
	}
	else {
		cout << "请选择排序方式" << endl
			<< "1.按照工号进行升序" << endl
			<< "2.按照工号进行降序" << endl;
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
		cout << "排序成功，结果如下：" << endl;
		this->save();
		this->show_emp();

	}
	system("puase");
	system("cls");
}

void WorkManager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ifs(FILENAME, ios::trunc);//trunc模式下，若是有文件，先清空，在写入
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
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");

}