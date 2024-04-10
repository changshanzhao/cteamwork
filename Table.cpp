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
	static wchar_t wstr[256]; // ������󳤶�Ϊ256
	MultiByteToWideChar(CP_ACP, 0, str, -1, wstr, 256);
	return wstr;
}

//��ʾѧ�����
void tableShow_stu(Table t)
{
	// ���û�ͼ��ʽ
	setfillcolor(WHITE);

	// ���Ʊ��
	fillrectangle(t.w.x, t.w.y, t.w.x + t.w.width, t.w.y + t.w.height);

	// ������
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// ������
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// ���Ʊ�ͷ
	wchar_t header[4][3] = { L"ѧ��", L"����", L"�༶", L"����" };	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// ���ѧ������
	StudentInfo* tmp = t.manager.students;

	wchar_t buffer[100];
	for (int j = 40; j < 370; j += 30)
	{
		if (tmp != NULL)	// �ڲ�����������Χ������²Ŷ�ȡ����
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
	// ����ҳ����ʾ
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"��" << (t.curIndex + 11) / 11 << L"ҳ" << L"/" << L"��" << (size(t.manager) + 11) / 11 << L"ҳ";
	outtextxy(98, 380, format.str().c_str());
	setbkmode(TRANSPARENT);
}

//��ʾ����Ա���
void tableShow_admin(Table t)
{
	// ���û�ͼ��ʽ
	setfillcolor(WHITE);

	// ���Ʊ��
	fillrectangle(t.w.x, t.w.y, t.w.x + t.w.width, t.w.y + t.w.height);

	// ������
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 360);
	}

	// ������
	for (int j = 40; j <= 340; j += 30)
	{
		line(10, j, 10 + 482, j);
	}

	RECT rect;

	// ���Ʊ�ͷ
	wchar_t header[2][3] = { L"�˺�", L"����" };	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 2; i += 120, j++)
	{
		rect = { i, 10, i + 240, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// �������Ա����
	AdminInfo* tmp = t.manager.admins;
	wchar_t buffer[5];
	for (int j = 40; j < 370; j += 30)
	{
		if (tmp != NULL)	// �ڲ�����������Χ������²Ŷ�ȡ����
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
	// ����ҳ����ʾ
	std::wstringstream format;
	setbkmode(OPAQUE);
	format << L"��" << (t.curIndex + 11) / 11 << L"ҳ" << L"/" << L"��" << (size(t.manager) + 11) / 11 << L"ҳ";
	outtextxy(98, 380, format.str().c_str());
	setbkmode(TRANSPARENT);
}

void pageUp(Table* t)
{
	// ���ѧ������
	t->curIndex -= 11;
	if (t->curIndex < 0)	// ��ȡ����һҳֹͣ����
	{
		t->curIndex += 11;
		return;
	}
	tableShow_stu(*t);
}

void pageDown(Table* t)
{
	// ���ѧ������
	t->curIndex += 11;
	if (t->curIndex > size(t->manager))	// ��ȡ�����һҳֹͣ����
	{
		t->curIndex -= 11;
		return;
	}
	tableShow_stu(*t);
}
// ��ѧ�Ų���ѧ��
StudentInfo* findStudentByID_ui(const char* studentID, StudentInfo* studentsList) {
	// ����ѧ���б�����ָ��ѧ�ŵ�ѧ��
	// ��ѧ���б��ͷ����ʼ����
	StudentInfo* currentStudent = studentsList;

	// ��������ѧ���б�
	while (currentStudent != NULL) {
		// �Ƚϵ�ǰѧ����ѧ���������ѧ��
		if (strcmp(currentStudent->studentID, studentID) == 0) {
			// ����ҵ�ƥ���ѧ�ţ����ص�ǰѧ������Ϣ
			return currentStudent;
		}
		// �ƶ����������һ���ڵ�
		currentStudent = currentStudent->next;
	}
	// ��������������б�û���ҵ�ƥ���ѧ�ţ�����NULL
	return NULL;
}
void showEditTable(Table* t, char* searchTerms)
{
	// ����
	//��Ϊyz�İ���ID����
	StudentInfo* index = findStudentByID_ui(searchTerms, t->manager.students);

	// �����ɹ��Ž��д�ӡ����
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
	// ���û�ͼ��ʽ
	setfillcolor(WHITE);

	// ���Ʊ��
	fillrectangle(t.w.x, t.w.y, t.w.x + t.w.width, t.w.y + 60);

	// ������
	for (int i = 130; i <= 370; i += 120)
	{
		line(i, 10, i, 10 + 60);
	}

	// ������
	line(10, 40, 490, 40);

	RECT rect;

	// ���Ʊ�ͷ
	wchar_t header[4][3] = { L"ѧ��", L"����", L"�༶", L"����" };	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// ���ѧ������
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
	// TODO: �ڴ˴����� return ���
	return t.searchIndex;
}

void setSearchIndex(Table t, int index)
{
	t.searchIndex = index;
}
