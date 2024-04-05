#include "Window.h"
#include <graphics.h>

void windowInit(Window* w,int width, int height)
{
	cleardevice();
	w->wid.height = height;
	w->wid.width = width;
	w->isEdit = false;
	w->hWnd = initgraph(width, height, EX_NOCLOSE);
	SetWindowText(w->hWnd, L"ѧ���ɼ�����ϵͳ");
	setbkcolor(WHITE);
	cleardevice();
	ShowWindow(w->hWnd, SW_HIDE);

	// ���û�ͼ��ʽ
	LOGFONT f;
	gettextstyle(&f);
	f.lfQuality = DEFAULT_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setlinecolor(BLACK);
	// ������ť
	

	w->mainWindow_view	 = new Button();
	buttonInit(w->mainWindow_view, (1024 - 200) / 2, 150, 170, 30, L"�鿴ѧ��");
	w->mainWindow_view_admin = new Button();
	buttonInit(w->mainWindow_view_admin, (1024 - 200) / 2, 200, 170, 30, L"�鿴����Ա");
	w->mainWindow_edit = new Button();
	buttonInit(w->mainWindow_edit, (1024 - 200) / 2, 250, 170, 30, L"�༭ѧ��");
	w->mainWindow_edit_admin = new Button();
	buttonInit(w->mainWindow_edit_admin, (1024 - 200) / 2, 300, 170, 30, L"�༭����Ա");
	w->mainWindow_clear = new Button();
	buttonInit(w->mainWindow_clear, (1024 - 200) / 2, 350, 170, 30, L"�������");
	w->mainWindow_exit = new Button();
	buttonInit(w->mainWindow_exit, (1024 - 200) / 2, 400, 170, 30, L"�˳�����");
	w->viewStudents_pageUp = new Button();
	buttonInit(w->viewStudents_pageUp, 10, 380, 80, 30, L"��һҳ");
	w->viewStudents_pageDown = new Button();
	buttonInit(w->viewStudents_pageDown, 210, 380, 80, 30, L"��һҳ");
	w->viewStudents_back = new Button();
	buttonInit(w->viewStudents_back, 412, 380, 80, 30, L"����");
	w->viewStudents_sort = new Button();
	buttonInit(w->viewStudents_sort, 300, 380, 102, 30, L"���ܷ�����");
	w->editStudents_search = new Button();
	buttonInit(w->editStudents_search, 10, 380, 100, 30, L"����ѧ��");
	w->editStudents_add = new Button();
	buttonInit(w->editStudents_add, 137, 380, 100, 30, L"���ѧ��");
	w->editStudents_delete = new Button();
	buttonInit(w->editStudents_delete, 264, 380, 100, 30, L"ɾ��ѧ��");
	w->editStudents_back = new Button();
	buttonInit(w->editStudents_back, 392, 380, 100, 30, L"����");

	showMainWindow(w);	// ��ʾ������

	// �������
	w->table = new Table();
	tableInit(w->table, w->manager, 10, 10, 502 - 20, 420 - 60);

	// ��ȡѧ������
	if (!read("Students.dat", w->manager))
	{
		MessageBox(GetHWnd(), L" ��Students.dat�� �ļ���ʧ�ܣ��޷�������в�����", L"����", MB_OK | MB_ICONERROR);
		exit(-1);
	}
}

void windowDelete(Window* w)
{
	// ����
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
	// ������Ϣѭ��
	ExMessage msg;
	while (true)
	{
		// ��ȡ���ж���Ϣ
		msg = getmessage();

		// �ж���ʾ����
		if (w->state == WindowState::mainWindow)		// ��������ʾ
		{
			if (state(msg, w->mainWindow_view))		// �鿴ѧ��
			{
				showViewStudents(w);
			}
			else if (state(msg, w->mainWindow_edit_admin))	// �༭ѧ��
			{
				showEditAdmins(w);
			}
			else if (state(msg, w->mainWindow_view_admin))	// �༭ѧ��
			{
				showViewAdmins(w);
			}
			else if (state(msg, w->mainWindow_edit))	// �༭ѧ��
			{
				showEditStudents(w);
			}
			else if (state(msg, w->mainWindow_clear))	// �������
			{
				if (MessageBox(GetHWnd(), L"ȷ��Ҫ�������ѧ�����ݣ�", L"�������", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					// ȷ�����
					clear(&(w->manager));
					w->isEdit = true;
				}
			}
			else if (state(msg, w->mainWindow_exit))	// �˳�����
			{
				if (close(w))
				{
					return;
				}
			}
		}
		else if (w->state == WindowState::viewStudents)	// �鿴ѧ��������ʾ
		{
			if (state(msg, w->viewStudents_pageUp) && msg.message != WM_LBUTTONUP)			// ��һҳ
			{
				pageUp(w->table);
			}
			else if (state(msg, w->viewStudents_pageDown) && msg.message != WM_LBUTTONUP)	// ��һҳ
			{
				pageDown(w->table);
			}
			else if (state(msg, w->viewStudents_back))	// ����
			{
				// ��ʾ������
				showMainWindow(w);
			}
			else if (state(msg, w->viewStudents_sort) && msg.message != WM_LBUTTONUP)	// ����
			{
				if (w->viewStudents_sort->text == L"���ܷ�����")
				{
					sortByScore(w->manager);
					tableShow(*w->table);
					w->viewStudents_sort->text = L"��ѧ������";
					state(msg, w->viewStudents_sort);
				}
				else
				{
					sortById(w->manager);
					tableShow(*w->table);
					w->viewStudents_sort->text = L"���ܷ�����";
					state(msg, w->viewStudents_sort);
				}
			}
		}
		else	// �༭ѧ��������ʾ
		{
			if (state(msg, w->editStudents_back))	// ����
			{
				// ��ʾ������
				showMainWindow(w);
			}
			else if (state(msg, w->editStudents_search) && msg.message != WM_LBUTTONUP)	// ����ѧ��
			{
				wchar_t str[10];
				if (InputBox(str, 5, L"������ѧ�Ż���������������", L"����ѧ��", NULL, 0, 0, false))
				{
					int number = _wtoi(str);

					if (number == 0)	//Ϊ�ַ���
					{
						showEditTable(w->table, str);

						if (w->table->searchIndex == -1)	// ����ʧ��
						{
							MessageBox(GetHWnd(), L"δ�ҵ�ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						}
					}
					else				// Ϊ����
					{
						showEditTable(w->table, number);
						
						if (w->table->searchIndex == -1)
						{
							MessageBox(GetHWnd(), L"δ�ҵ�ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						}
					}
				}
			}
			else if (state(msg, w->editStudents_add) && msg.message != WM_LBUTTONUP)		// ���ѧ��
			{
				wchar_t stuString[20];	// ѧ���ַ���

				// ���ȷ����ť�Ž������
				if (InputBox(stuString, 20, L"�밴�� ��ѧ�� ���� �༶ �ܷ֡� �ĸ�ʽ�������ݣ�", L"���ѧ��", NULL, 0, 0, false))
				{
					// ��ʽ�������ַ���
					std::wstringstream format(stuString);
					Student stu = {};
					format >> stu.id >> stu.name >> stu.Class >> stu.score;

					// �жϸ�ʽ
					if (stu.id <= 0)
					{
						MessageBox(GetHWnd(), L"ѧ�Ų���С�ڻ�����㣡", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (std::wstring(stu.name) == L"" || std::wstring(stu.Class) == L"")
					{
						MessageBox(GetHWnd(), L"�����Ͱ༶����Ϊ�գ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}
					else if (stu.score < 0)
					{
						MessageBox(GetHWnd(), L"��������С���㣡", L"��ʾ", MB_OK | MB_ICONINFORMATION);
						continue;
					}

					// ��Ӻ�ˢ������
					addStudent(stu, w->manager);
					showEditTable(w->table, stu.name);
					sortById(w->manager);
					w->isEdit = true;
				}
			}
			else if (state(msg, w->editStudents_delete) && msg.message != WM_LBUTTONUP)	// ɾ��ѧ��
			{
				short i = w->table->searchIndex;

				// �ж��Ƿ�������ѧ��
				if (i != -1)
				{
					std::wstringstream format;
					if (MessageBox(GetHWnd(), L"ȷ��Ҫɾ�����ѧ����", L"ȷ��ɾ��", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						deleteStudent(i, w->manager);
						showEditStudents(w);
						w->isEdit = true;
						w->table->searchIndex = -1;
					}
				}
				else
				{
					MessageBox(GetHWnd(), L"��������ѧ����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
			}
		}
	}
}

bool close(Window* w)
{
	if (w->isEdit)
	{
		// ���б���
		int id = MessageBox(GetHWnd(), L"�Ƿ񱣴����еĲ�����", L"�˳�����", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (id == IDYES)
		{
			// д��ѧ������
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

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ������ʾ����
	RECT rect = { 0, 0, w->wid.width, 200 };
	settextstyle(50, 0, L"΢���ź�");
	drawtext(L"ѧ���ɼ�����ϵͳ", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ��ʾ��ť
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

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
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

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
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

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
	ButtonShow(*w->editStudents_search);
	ButtonShow(*w->editStudents_add);
	ButtonShow(*w->editStudents_delete);
	ButtonShow(*w->editStudents_back);
}

void showEditAdmins(Window* w)
{
	w->state = WindowState::editAdmins;
	cleardevice();

	// ���ر���ͼƬ
	loadimage(NULL, BACKGROUND_IMAGE, 1024, 640);

	// ��ʾ�ؼ�
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
//����Ա��¼
void AdminSignIn() {
	//���ļ����˺ź����������
	FILE* fp;
	fopen_s(&fp, "admins.txt", "r");
	if (fp == NULL) {
		return;
	}
	fscanf_s(fp, "%s\t%s\n", AdminUser.username, len, AdminUser.password, len);//��ȡ����Ӧ�Ĺ���Ա�ṹ������
	fclose(fp);//�ر��ļ�

	wchar_t ReceAcctNumber[20]{ L"admin" }; //��¼������û����ַ���
	TCHAR InputAcct[] = _T("�������û���");
	InputBox(ReceAcctNumber, 20, InputAcct);

	wchar_t ReceAcctpassword[30]{ L"admin" }; //��¼����������ַ���
	TCHAR InputPass[] = _T("����������");
	InputBox(ReceAcctpassword, 30, InputPass);
		int wideStrLen_3 = wcslen(ReceAcctNumber);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctNumber_s = new char[wideStrLen_3 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_3 * 4, NULL, NULL);
	int wideStrLen_4 = wcslen(ReceAcctpassword);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctpassword_s = new char[wideStrLen_4 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_4 * 4, NULL, NULL);

	//����û��������붼��ȷ�Ž��ȵ�����Ա���棬���򵯴���ʾ����
	if (strcmp(AdminUser.username, ReceAcctNumber_s) == 0 && strcmp(AdminUser.password, ReceAcctpassword_s) == 0) {
		cleardevice();
		Window* window = new Window;
		windowInit(window, 1024, 640);
		windowShow(window);
		messageLoop(window);
		windowDelete(window);
		delete window;
	}
	//����������ʾ����Ҫ��ʵ����SignError����
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"�û������������!", L"��ʾ", MB_OK);
	}
	exit(0);
}

//ѧ����¼
void StuSignIn() {
	//���ļ����˺ź����������
	FILE* fp;
	fopen_s(&fp, "students.txt", "r");
	if (fp == NULL) {
		return;
	}
	int flagNowStu = -1;
	//��ȡ����Ӧ��ѧ���ṹ������
	//for (int i = 0; i < NowStudentNums; i++) {
	//	fscanf_s(fp, "%s\t%s\t%s\t%s\t%s\t%s\n",
	//		StuArry[i].ID, 10,
	//		StuArry[i].name, len,
	//		StuArry[i].password, len,
	//		StuArry[i].email, len,
	//		StuArry[i].phone, 15,
	//		StuArry[i].faculty, len);
	//}
	fclose(fp);//�ر��ļ�

	wchar_t* ReceAcctNumber{}; //��¼������û����ַ���
	TCHAR InputAcct[] = _T("�������û���");
	InputBox(ReceAcctNumber, 10, InputAcct);

	wchar_t* ReceAcctpassword{}; //��¼����������ַ���
	TCHAR InputPass[] = _T("����������");
	InputBox(ReceAcctpassword, 10, InputPass);
	int wideStrLen_1 = wcslen(ReceAcctNumber);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctNumber_s = new char[wideStrLen_1 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctNumber, -1, ReceAcctNumber_s, wideStrLen_1 * 4, NULL, NULL);
	int wideStrLen_2 = wcslen(ReceAcctpassword);
	// Ϊchar���͵��ַ��������㹻�Ŀռ�
	char* ReceAcctpassword_s = new char[wideStrLen_2 * 4];
	// �����ַ���ת��Ϊ���ֽ��ַ���
	WideCharToMultiByte(CP_ACP, 0, ReceAcctpassword, -1, ReceAcctpassword_s, wideStrLen_2 * 4, NULL, NULL);

	//����û��������붼��ȷ�Ž��ȵ�ѧ�����棬���򵯴���ʾ����
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
	//����������ʾ����Ҫ��ʵ����SignError����
	else {
		HWND SignError = GetHWnd();
		int isok = MessageBox(SignError, L"�û������������!", L"��ʾ", MB_OK);
	}
	exit(0);
}
//��ҳ
void FirstPage() {
	//ReadInfor();//ֻҪ�������Ͷ�ȡ���ݡ�����ȡ��ǰȫ��ѧ����Ϣ�����ⷴ�����룡
	//ReadHealth();
	//ReadTest();
	//ReadVaccine();
	initgraph(1024, 640);//���ڴ�С
	MOUSEMSG m1;//������1
	cleardevice();
	IMAGE picture1;
	loadimage(&picture1, BACKGROUND_IMAGE, 1024, 640);
	putimage(0, 0, &picture1);
	setbkmode(TRANSPARENT);
	setfillcolor(GREEN);

	//�����
	settextstyle(60, 0,L"����");
	outtextxy(150, 100, L"ѧ���ɼ�����ϵͳ");

	//����ѡ��ı���
	fillrectangle(230, 445, 560, 490);
	fillrectangle(230, 505, 560, 550);
	fillrectangle(230, 565, 560, 610);

	setbkmode(TRANSPARENT);

	//����ѡ�������
	LOGFONT f;//������ʽָ��
	gettextstyle(&f);					//��ȡ������ʽ
	_tcscpy_s(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;    //�������Ч��Ϊ����ݣ�������ôģ��
	f.lfHeight = 40;					//���������С
	settextstyle(&f);                     // ����������ʽ

	RECT R[3] = { {230, 445, 560, 490},{230, 505, 560, 550},{230, 565, 560, 610} };
	//��drawtext������outtextxy������ʵ�����ֵľ���
	drawtext(L"����Ա��������", &R[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"ѧ����������", &R[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"�˳�����", &R[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//����������ѡ���������
	while (1) {
		m1 = GetMouseMsg();//��ȡ������
		if (m1.x >= 230 && m1.x <= 560 && m1.y >= 445 && m1.y <= 490)//����Ա����
		{
			setlinecolor(RED);
			rectangle(230, 445, 560, 490);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //������������ʱ�����¼�
				AdminSignIn(); //����Ա��¼���棬ֻ���˺�������ȷ��ִ��AdminPage����
			}
		}
		else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 505 && m1.y <= 550)//ѧ���û�����
		{
			setlinecolor(RED);
			rectangle(230, 505, 560, 550);
			if (m1.uMsg == WM_LBUTTONDOWN) {     //������������ʱ�����¼�
				StuSignIn();
			}
		}
		else if (m1.x >= 230 && m1.x <= 560 && m1.y >= 565 && m1.y <= 610)//�˳�
		{
			setlinecolor(RED);
			rectangle(230, 565, 560, 610);
			if (m1.uMsg == WM_LBUTTONDOWN) {
				exit(0);
			}
		}
		//��겻��������ͣ
		else {
			setlinecolor(WHITE);
			rectangle(230, 445, 560, 490);
			rectangle(230, 505, 560, 550);
			rectangle(230, 565, 560, 610);
		}
	}

}