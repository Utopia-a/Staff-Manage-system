#include"WorkManager.h"
#include"worker.h"
#include"Employee.h"
#include"boss.h"
#include"manager.h"


int main() {
	WorkManager wm;

	while (1) {
	wm.show_Menu();
		int choice;
		cout << "����������ѡ��" << endl;
		cin >> choice;


		switch (choice)
		{
		case 0://�˳�
			wm.exitSystem();
			break;

		case 1://����
			wm.Add_emp();
			break;

		case 2://��ʾ
			wm.show_emp();
			break;

		case 3://ɾ��
			wm.Del_emp();
			break;

		case 4://�޸�
			wm.Mod_emp();
			break;

		case 5://����
			wm.Find_emp();
			break;

		case 6://����
			wm.sort();
			break;

		case 7://�������
			wm.Clean_File();
			break;

		default:
			break;
		}
	}

	return 0;
}
