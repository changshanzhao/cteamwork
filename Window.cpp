#include "Window.h"
#include <graphics.h>

void windowInit(Window* w,int width, int height)
{
	cleardevice();
	w->wid.height = height;
	w->wid.width = width;
	w->isEdit = false;
	w->hWnd = initgraph(width, height, EX_NOCLOSE);
	SetWindowText(w->hWnd, L"学生成绩管理系统");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(w->hWnd, SW_HIDE);

	// 设置绘图样式
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	// 创建按钮
	

	w->mainWindow_view	 = new Button();
	buttonInit(w->mainWindow_view, (1024 - 200) / 2, 150, 170, 30, L"查看学生");
	w->mainWindow_view_admin = new Button();
	buttonInit(w->mainWindow_view_admin, (1024 - 200) / 2, 200, 170, 30, L"查看管理员");
	w->mainWindow_edit = new Button();
	buttonInit(w->mainWindow_edit, (1024 - 200) / 2, 250, 170, 30, L"编辑学生");
	w->mainWindow_edit_admin = new Button();
	buttonInit(w->mainWindow_edit_admin, (1024 - 200) / 2, 300, 170, 30, L"编辑管理员");
	w->mainWindow_clear = new Button();
	buttonInit(w->mainWindow_clear, (1024 - 200) / 2, 350, 170, 30, L"清空数据");
	w->mainWindow_exit = new Button();
	buttonInit(w->mainWindow_exit, (1024 - 200) / 2, 400, 170, 30, L"退出程序");
	w->viewStudents_pageUp = new Button();
	buttonInit(w->viewStudents_pageUp, 10, 380, 80, 30, L"上一页");
	w->viewStudents_pageDown = new Button();
	buttonInit(w->viewStudents_pageDown, 210, 380, 80, 30, L"下一页");
	w->viewStudents_back = new Button();
	buttonInit(w->viewStudents_back, 412, 380, 80, 30, L"返回");
	w->viewStudents_sort = new Button();
	buttonInit(w->viewStudents_sort, 300, 380, 102, 30, L"按总分排序");
	w->editStudents_search = new Button();
	buttonInit(w->editStudents_search, 10, 380, 100, 30, L"搜索学生");
	w->editStudents_add = new Button();
	buttonInit(w->editStudents_add, 137, 380, 100, 30, L"添加学生");
	w->editStudents_delete = new Button();
	buttonInit(w->editStudents_delete, 264, 380, 100, 30, L"删除学生");
	w->editStudents_back = new Button();
	buttonInit(w->editStudents_back, 392, 380, 100, 30, L"返回");

	showMainWindow(w);	// 显示主界面

	// 创建表格
	w->table = new Table();
	tableInit(w->table, w->manager, 10, 10, 502 - 20, 420 - 60);

	// 读取学生数据
	if (!read("Students.dat", w->manager))
	{
		MessageBox(GetHWnd(), L" “Students.dat” 文件打开失败，无法对其进行操作！", L"错误", MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

void windowDelete(Window* w)
{
	// 销毁
	delete w->mainWindow_view;
	delete w->mainWindow_edit;
	delete w->mainWindow_clear;
	delete w->mainWindow_exit;

	delete w->viewStudents_pageUp;
	delete w->viewStudents_pageDown;
	delete w->viewStudents_sort;
	delete w->viewStudents_back;

	delete w->editStudents_search;
	delete w->editStudents_add;
	delete w->editStudents_delete;
	delete w->editStudents_back;

	delete w->table;
}

void windowShow(Window* w)
{
	ShowWindow(w->hWnd, SW_SHOW);
}

void messageLoop(Window* w)
{
	// 开启消息循环
	ExMessage msg;
	while (true)
	{
		// 获取并判断消息
		msg = getmessage();

		// 判断显示界面
		if (w->state == WindowState::mainWindow)		// 主窗口显示
		{
			if (state(msg, w->mainWindow_view))		// 查看学生
			{
				showViewStudents(w);
			}
			else if (state(msg, w->mainWindow_edit_admin))	// 编辑学生
			{
				showEditAdmins(w);
			}
			else if (state(msg, w->mainWindow_view_admin))	// 编辑学生
			{
				showViewAdmins(w);
			}
			else if (state(msg, w->mainWindow_edit))	// 编辑学生
			{
				showEditStudents(w);
			}
			else if (state(msg, w->mainWindow_clear))	// 清空数据
			{
				if (MessageBox(GetHWnd(), L"确定要清空所有学生数据？", L"清空数据", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					// 确定清空
					clear(&(w->manager));
					w->isEdit = true;
				}
			}
			else if (state(msg, w->mainWindow_exit))	// 退出程序
			{
				if (close(w))
				{
					return;
				}
			}
		}
		else if (w->state == WindowState::viewStudents)	// 查看学生窗口显示
		{
			if (state(msg, w->viewStudents_pageUp) && msg.message != WM_LBUTTONUP)			// 上一页
			{
				pageUp(w->table);
			}
			else if (state(msg, w->viewStudents_pageDown) && msg.message != WM_LBUTTONUP)	// 下一页
			{
				pageDown(w->table);
			}
			else if (state(msg, w->viewStudents_back))	// 返回
			{
				// 显示主窗口
				showMainWindow(w);
			}
			else if (state(msg, w->viewStudents_sort) && msg.message != WM_LBUTTONUP)	// 排序
			{
				if (w->viewStudents_sort->text == L"按总分排序")
				{
					sortByScore(w->manager);
					tableShow(*w->table);
					w->viewStudents_sort->text = L"按学号排序";
					state(msg, w->viewStudents_sort);
				}
				else
				{
					sortById(w->manager);
					tableShow(*w->table);
					w->viewStudents_sort->text = L"按总分排序";
					state(msg, w->viewStudents_sort);
				}
			}
		}
		else	// 编辑学生窗口显示
		{
			if (state(msg, w->editStudents_back))	// 返回
			{
				// 显示主窗口
				showMainWindow(w);
			}
			else if (state(msg, w->editStudents_search) && msg.message != WM_LBUTTONUP)	// 搜索学生
			{
				wchar_t str[10];
				if (InputBox(str, 5, L"请输入学号或姓名进行搜索：", L"搜索学生", NULL, 0, 0, false))
				{
					int number = _wtoi(str);

					if (number == 0)	//为字符串
					{
						showEditTable(w->table, str);

						if (w->table->searchIndex == -1)	// 搜索失败
						{
							MessageBox(GetHWnd(), L"未找到学生！", L"提示", MB_OK | MB_ICONINFORMATION);
						}
					}
					else				// 为数字
					{
						showEditTable(w->table, number);
						
						if (w->table->searchIndex == -1)
						{
							MessageBox(GetHWnd(), L"未找到学生！", L"提示", MB_OK | MB_ICONINFORMATION);
						}
					}
				}
			}
			else if (state(msg, w->editStudents_add) && msg.message != WM_LBUTTONUP)		// 添加学生
			{
				wchar_t stuString[20];	// 学生字符串

				// 点击确定按钮才进行添加
				if (InputBox(stuString, 20, L"请按照 “学号 姓名 班级 总分” 的格式输入数据：", L"添加学生", NULL, 0, 0, false))
				{
					// 格式化输入字符串
					std::wstringstream format(stuString);
					Student stu = {};
					format >> stu.id >> stu.name >> stu.Class >> stu.score;

					// 判断格式
					if (stu.id <= 0)
					{
						MessageBox(GetHWnd(), L"学号不能小于或等于零！", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (std::wstring(stu.name) == L"" || std::wstring(stu.Class) == L"")
					{
						MessageBox(GetHWnd(), L"姓名和班级不能为空！", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (stu.score < 0)
					{
						MessageBox(GetHWnd(), L"分数不能小于零！", L"提示", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					// 添加和刷新数据
					addStudent(stu, w->manager);
					showEditTable(w->table, stu.name);
					sortById(w->manager);
					w->isEdit = true;
				}
			}
			else if (state(msg, w->editStudents_delete) && msg.message != WM_LBUTTONUP)	// 删除学生
			{
				short i = w->table->searchIndex;

				// 判断是否搜索了学生
				if (i != -1)
				{
					std::wstringstream format;
					if (MessageBox(GetHWnd(), L"确定要删除这个学生吗？", L"确定删除", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						deleteStudent(i, w->manager);
						showEditStudents(w);
						w->isEdit = true;
						w->table->searchIndex = -1;
					}
				}
				else
				{
					MessageBox(GetHWnd(), L"请先搜索学生！", L"提示", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}
}

bool close(Window* w)
{
	if (w->isEdit)
	{
		// 进行保存
		int id = MessageBox(GetHWnd(), L"是否保存所有的操作？", L"退出程序", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
		{
			// 写入学生数据
			sortById(w->manager);
			write("Students.dat", w->manager);
			closegraph();
			return true;
		}
		else if (id == IDNO)
		{
			return true;
		}
	}
	else
	{
		return true;
	}
	return false;
}

void showMainWindow(Window* w)
{
	w->state = WindowState::mainWindow;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 绘制提示文字
	RECT rect = { 0, 0, w->wid.width, 200 };
	settextstyle(50, 0, L"微软雅黑");
	drawtext(L"学生成绩管理系统", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 显示按钮
	ButtonShow(*w->mainWindow_view);
	ButtonShow(*w->mainWindow_view_admin);
	ButtonShow(*w->mainWindow_edit);
	ButtonShow(*w->mainWindow_edit_admin);
	ButtonShow(*w->mainWindow_exit);
	ButtonShow(*w->mainWindow_clear);
}

void showViewStudents(Window* w)
{
	w->state = WindowState::viewStudents;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
	tableShow(*w->table);
	ButtonShow(*w->viewStudents_pageUp);
	ButtonShow(*w->viewStudents_pageDown);
	ButtonShow(*w->viewStudents_back);
	ButtonShow(*w->viewStudents_sort);
}
void showViewAdmins(Window* w)
{
	w->state = WindowState::viewAdmins;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
	tableShow(*w->table);
	ButtonShow(*w->viewStudents_pageUp);
	ButtonShow(*w->viewStudents_pageDown);
	ButtonShow(*w->viewStudents_back);
	ButtonShow(*w->viewStudents_sort);
}

void showEditStudents(Window* w)
{
	w->state = WindowState::editStudents;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
	ButtonShow(*w->editStudents_search);
	ButtonShow(*w->editStudents_add);
	ButtonShow(*w->editStudents_delete);
	ButtonShow(*w->editStudents_back);
}

void showEditAdmins(Window* w)
{
	w->state = WindowState::editAdmins;
	cleardevice();

	// 加载背景图片
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// 显示控件
	ButtonShow(*w->editStudents_search);
	ButtonShow(*w->editStudents_add);
	ButtonShow(*w->editStudents_delete);
	ButtonShow(*w->editStudents_back);
}

bool isNumber(Window* w, const std::wstring& string)
{
	if (_wtoi(string.c_str()) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


AdminInfo AdminUser;
StudentInfo StuArry[n];
int NowStudentNums = 0;
//管理员登录
void AdminSignIn() {
	//打开文件将账号和密码读过来
	FILE* fp;
	fopen_s(&fp, "admins.txt", "r");
	if (fp == NULL) {
		return;
	}
	fscanf_s(fp, "%s\t%s\n", AdminUser.username, len, AdminUser.password, len);//读取到对应的管理员结构体数组
	fclose(fp);//关闭文件

	wchar_t ReceAcctNumber[20]{ L"admin" }; //记录输入的用户名字符串
	TCHAR InputAcct[] = _T("请输入用户名");
	InputBox(ReceAcctNumber, 20, InputAcct);

	wchar_t ReceAcctpassword[30]{ L"admin" }; //记录输入的密码字符串
	TCHAR InputPass[] = _T("请输入密码");
	InputBox(ReceAcctpassword, 30, InputPass);
		int wideStrLen_3 = wcslen(ReceAcctNumber);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
	int wideStrLen_4 = wcslen(ReceAcctpassword);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);

	//如果用户名和密码都正确才进度到管理员界面，否则弹窗提示错误
	if (strcmp(AdminUser.username, ReceAcctNumber_s) == 0 && strcmp(AdminUser.password, ReceAcctpassword_s) == 0) {
		cleardevice();
		Window* window = new Window;
		windowInit(window, 1024, 640);
		windowShow(window);
		messageLoop(window);
		windowDelete(window);
		delete window;
	}
	//弹窗错误提示，需要先实例化SignError对象
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"用户名或密码错误!", L"提示", MB_OK);
	}
	exit(0);
}

//学生登录
void StuSignIn() {
	//打开文件将账号和密码读过来
	FILE* fp;
	fopen_s(&fp, "students.txt", "r");
	if (fp == NULL) {
		return;
	}
	int flagNowStu = -1;
	//读取到对应的学生结构体数组
	//for (int i = 0; i < NowStudentNums; i++) {
	//	fscanf_s(fp, "%s\t%s\t%s\t%s\t%s\t%s\n",
	//		StuArry[i].ID, 10,
	//		StuArry[i].name, len,
	//		StuArry[i].password, len,
	//		StuArry[i].email, len,
	//		StuArry[i].phone, 15,
	//		StuArry[i].faculty, len);
	//}
	fclose(fp);//关闭文件

	wchar_t* ReceAcctNumber{}; //记录输入的用户名字符串
	TCHAR InputAcct[] = _T("请输入用户名");
	InputBox(ReceAcctNumber, 10, InputAcct);

	wchar_t* ReceAcctpassword{}; //记录输入的密码字符串
	TCHAR InputPass[] = _T("请输入密码");
	InputBox(ReceAcctpassword, 10, InputPass);
	int wideStrLen_1 = wcslen(ReceAcctNumber);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctNumber_s = new char[wideStrLen_1 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_1 * 4, NULL, NULL);
	int wideStrLen_2 = wcslen(ReceAcctpassword);
	// 为char类型的字符串分配足够的空间
	char* ReceAcctpassword_s = new char[wideStrLen_2 * 4];
	// 将宽字符串转换为多字节字符串
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_2 * 4, NULL, NULL);

	//如果用户名和密码都正确才进度到学生界面，否则弹窗提示错误
	for (int j = 0; j < NowStudentNums; j++) {
		if (strcmp(StuArry[j].studentID, ReceAcctNumber_s) == 0 && strcmp(StuArry[j].password, ReceAcctpassword_s) == 0) {
			cleardevice();
			flagNowStu = j;
		}
	}

	if (flagNowStu != -1) {
		cleardevice();
		Window* window = new Window;
		windowInit(window, 1024, 640);
		windowShow(window);
		messageLoop(window);
		windowDelete(window);
		delete window;
	}
	//弹窗错误提示，需要先实例化SignError对象
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"用户名或密码错误!", L"提示", MB_OK);
	}
	exit(0);
}
//首页
void FirstPage() {
	//ReadInfor();//只要进入程序就读取数据——获取当前全部学生信息，避免反复读入！
	//ReadHealth();
	//ReadTest();
	//ReadVaccine();
	initgraph(1024, 640);//窗口大小
	MOUSEMSG m1;//鼠标操作1
	cleardevice();
	IMAGE picture1;
	loadimage(&picture1, BACKGROUND_IMAGE, 1024, 640);
	putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	setfillcolor(GREEN);

	//大标题
	settextstyle(60, 0,L"宋体");
	outtextxy(150, 100, L"学生成绩管理系统");

	//三个选项的背景
	fillrectangle(230, 445, 560, 490);
	fillrectangle(230, 505, 560, 550);
	fillrectangle(230, 565, 560, 610);

	setbkmode(TRANSPARENT);

	//三个选项的文字
	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	_tcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;    //设置输出效果为抗锯齿，不会那么模糊
	f.lfHeight = 40;					//设置字体大小
	settextstyle(&f);                     // 设置字体样式

	RECT R[3] = { {230, 445, 560, 490},{230, 505, 560, 550},{230, 565, 560, 610} };
	//用drawtext而不是outtextxy，可以实现文字的居中
	drawtext(L"管理员操作界面", &R[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"学生操作界面", &R[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"退出程序", &R[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//进入主界面选项操作界面
	while (1) {
		m1 = GetMouseMsg();//获取鼠标操作
		if (m1.x >= 230 && m1.x <= 560 && m1.y >= 445 && m1.y <= 490)//管理员界面
		{
			setlinecolor(RED);
			rectangle(230, 445, 560, 490);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //当单击鼠标左键时触发事件
				AdminSignIn(); //管理员登录界面，只有账号密码正确才执行AdminPage函数
			}
		}
		else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 505 && m1.y <= 550)//学生用户界面
		{
			setlinecolor(RED);
			rectangle(230, 505, 560, 550);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //当单击鼠标左键时触发事件
				StuSignIn();
			}
		}
		else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 565 && m1.y <= 610)//退出
		{
			setlinecolor(RED);
			rectangle(230, 565, 560, 610);
			if (m1.uMsg == WM_LBUTTONDOWN) {
				exit(0);
			}
		}
		//鼠标不在上面悬停
		else {
			setlinecolor(WHITE);
			rectangle(230, 445, 560, 490);
			rectangle(230, 505, 560, 550);
			rectangle(230, 565, 560, 610);
		}
	}

}