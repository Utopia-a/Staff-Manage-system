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
		cout << "请输入您的选择" << endl;
		cin >> choice;


		switch (choice)
		{
		case 0://退出
			wm.exitSystem();
			break;

		case 1://增加
			wm.Add_emp();
			break;

		case 2://显示
			wm.show_emp();
			break;

		case 3://删除
			wm.Del_emp();
			break;

		case 4://修改
			wm.Mod_emp();
			break;

		case 5://查找
			wm.Find_emp();
			break;

		case 6://排序
			wm.sort();
			break;

		case 7://清空所有
			wm.Clean_File();
			break;

		default:
			break;
		}
	}

	return 0;
}
