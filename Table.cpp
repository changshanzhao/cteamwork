#include "Table.h"
#include"function.h"
#include <iostream>

void tableInit(Table* t, Manager manager, int x, int y, int width, int height)
{
	t->manager = manager;
	t->w.height = height;
	t->w.width = width;
	t->w.x = x;
	t->w.y = y;
}
LPCTSTR ConvertToLPCTSTR(const char* str) {
	static wchar_t wstr[256]; // 假设最大长度为256
	MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, 256);
	return wstr;
}

//显示学生表格
void tableShow_stu(Table t)
{
	// 设置绘图样式
	setfillcolor(WHITE);

	// 绘制表格
	fillrectangle(t.w.x, t.w.y, t.w.x + t.w.width, t.w.y + t.w.height);

	// 画竖线
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// 画横线
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// 绘制表头
	wchar_t header[4][3] = { L"学号", L"姓名", L"班级", L"绩点" };	// 表头数据
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 输出学生数据
	StudentInfo* tmp = t.manager.students;

	wchar_t buffer[100];
	for (int j = 40; j < 370; j += 30)
	{
		if (tmp != NULL)	// 在不超出索引范围的情况下才读取数据
		{
			rect = { 10, j, 10 + 120, j + 30 };
			LPCTSTR lpctstr = ConvertToLPCTSTR(tmp->studentID);
			drawtext(lpctstr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 130, j, 130 + 120, j + 30 };
			lpctstr = ConvertToLPCTSTR(tmp->name);
			drawtext(lpctstr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 250, j, 250 + 120, j + 30 };
			_itow_s(tmp->classNumber, buffer, 10);
			//lpctstr = ConvertToLPCTSTR(tmp->classNumber);
			drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 370, j, 370 + 120, j + 30 };
			//_itow_s(tmp->gpa, buffer, 10);
			swprintf(buffer, 20, L"%.2f", tmp->gpa);
			drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			tmp = tmp->next;
		}
		else
		{
			break;
		}
	}
	// 绘制页数提示
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"第" << (t.curIndex + 11) / 11 << L"页" << L"/" << L"共" << (size(t.manager) + 11) / 11 << L"页";
	outtextxy(98, 380, format.str().c_str());
	setbkmode(TRANSPARENT);
}

//显示管理员表格
void tableShow_admin(Table t)
{
	// 设置绘图样式
	setfillcolor(WHITE);

	// 绘制表格
	fillrectangle(t.w.x, t.w.y, t.w.x + t.w.width, t.w.y + t.w.height);

	// 画竖线
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// 画横线
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// 绘制表头
	wchar_t header[2][3] = { L"账号", L"密码" };	// 表头数据
	for (int i = 10, j = 0; i < 490 && j < 2; i += 120, j++)
	{
		rect = { i, 10, i + 240, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 输出管理员数据
	AdminInfo* tmp = t.manager.admins;
	wchar_t buffer[5];
	for (int j = 40; j < 370; j += 30)
	{
		if (tmp != NULL)	// 在不超出索引范围的情况下才读取数据
		{
			rect = { 10, j, 10 + 120, j + 30 };
			LPCTSTR lpctstr = ConvertToLPCTSTR(tmp->username);
			drawtext(lpctstr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			lpctstr = ConvertToLPCTSTR(tmp->password);
			rect = { 250, j, 250 + 120, j + 30 };
			drawtext(lpctstr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


			tmp = tmp->next;
		}
		else
		{
			break;
		}
	}
	// 绘制页数提示
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"第" << (t.curIndex + 11) / 11 << L"页" << L"/" << L"共" << (size(t.manager) + 11) / 11 << L"页";
	outtextxy(98, 380, format.str().c_str());
	setbkmode(TRANSPARENT);
}

void pageUp(Table* t)
{
	// 输出学生数据
	t->curIndex -= 11;
	if (t->curIndex < 0)	// 读取到第一页停止操作
	{
		t->curIndex += 11;
		return;
	}
	tableShow_stu(*t);
}

void pageDown(Table* t)
{
	// 输出学生数据
	t->curIndex += 11;
	if (t->curIndex > size(t->manager))	// 读取到最后一页停止操作
	{
		t->curIndex -= 11;
		return;
	}
	tableShow_stu(*t);
}
// 按学号查找学生
StudentInfo* findStudentByID_ui(const char* studentID, StudentInfo* studentsList) {
	// 遍历学生列表，查找指定学号的学生
	// 从学生列表的头部开始遍历
	StudentInfo* currentStudent = studentsList;

	// 遍历整个学生列表
	while (currentStudent != NULL) {
		// 比较当前学生的学号与给定的学号
		if (strcmp(currentStudent->studentID, studentID) == 0) {
			// 如果找到匹配的学号，返回当前学生的信息
			return currentStudent;
		}
		// 移动到链表的下一个节点
		currentStudent = currentStudent->next;
	}
	// 如果遍历完整个列表都没有找到匹配的学号，返回NULL
	return NULL;
}
void showEditTable(Table* t, char* searchTerms)
{
	// 搜索
	//改为yz的按照ID搜索
	StudentInfo* index = findStudentByID_ui(searchTerms, t->manager.students);

	// 搜索成功才进行打印操作
	if (index != NULL)
	{
		showTable(*t, index);

	}
	else
	{
		t->searchIndex = -1;
	}
}

//void showEditTableByID(Table* t, char* searchTerms)
//{
//	int index = searchId(id, t->manager);
//
//	if (index != -1)
//	{
//		showTable(*t, index);
//
//		t->searchIndex = index;
//	}
//	else
//	{
//		t->searchIndex = index;
//	}
//}

void showTable(Table t, StudentInfo* index)
{
	// 设置绘图样式
	setfillcolor(WHITE);

	// 绘制表格
	fillrectangle(t.w.x, t.w.y, t.w.x + t.w.width, t.w.y + 60);

	// 画竖线
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 60);
	}

	// 画横线
	line(10, 40, 490, 40);

	RECT rect;

	// 绘制表头
	wchar_t header[4][3] = { L"学号", L"姓名", L"班级", L"绩点" };	// 表头数据
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 输出学生数据
	wchar_t buffer[10];
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rect = { 10, 40, 10 + 120, 40 + 30 };
	LPCTSTR lpctstr = ConvertToLPCTSTR(index->studentID);
	drawtext(lpctstr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 130, 40, 130 + 120, 40 + 30 };
	lpctstr = ConvertToLPCTSTR(index->name);
	drawtext(lpctstr, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 250, 40, 250 + 120, 40 + 30 };
	_itow_s(index->classNumber, buffer, 10);
	//lpctstr = ConvertToLPCTSTR(tmp->classNumber);
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 370, 40, 370 + 120, 40 + 30 };
	//_itow_s(tmp->gpa, buffer, 10);
	swprintf(buffer, 20, L"%.2f", index->gpa);
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

int getSearchIndex(Table t)
{
	// TODO: 在此处插入 return 语句
	return t.searchIndex;
}

void setSearchIndex(Table t, int index)
{
	t.searchIndex = index;
}
