#include "Table.h"

void tableInit(Table* t, Manager manager, int x, int y, int width, int height)
{
	t->manager = manager;
	t->w.height = height;
	t->w.width = width;
	t->w.x = x;
	t->w.y = y;
}
void tableShow(Table t)
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
	wchar_t header[4][3] = { L"ѧ��", L"����", L"�༶", L"�ܷ�" };	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// ���ѧ������
	int i = t.curIndex;
	wchar_t buffer[5];
	for (int j = 40; j < 370; j += 30)
	{
		if (i < size(t.manager))	// �ڲ�����������Χ������²Ŷ�ȡ����
		{
			rect = { 10, j, 10 + 120, j + 30 };
			_itow_s(getStudent(i, t.manager).id, buffer, 10);
			drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 130, j, 130 + 120, j + 30 };
			drawtext(getStudent(i, t.manager).name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 250, j, 250 + 120, j + 30 };
			drawtext(getStudent(i, t.manager).Class, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect = { 370, j, 370 + 120, j + 30 };
			_itow_s(getStudent(i, t.manager).score, buffer, 10);
			drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			i++;
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
	tableShow(*t);
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
	tableShow(*t);
}

void showEditTable(Table* t, const wchar_t* searchTerms)
{
	// ����
	int index = searchName(searchTerms, t->manager);

	// �����ɹ��Ž��д�ӡ����
	if (index != -1)
	{
		showTable(*t, index);

		t->searchIndex = index;
	}
	else
	{
		t->searchIndex = -1;
	}
}

void showEditTable(Table* t, int id)
{
	int index = searchId(id, t->manager);
	
	if (index != -1)
	{
		showTable(*t, index);

		t->searchIndex = index;
	}
	else
	{
		t->searchIndex = index;
	}
}

void showTable(Table t, int index)
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
	wchar_t header[4][3] = { L"ѧ��", L"����", L"�༶", L"�ܷ�" };	// ��ͷ����
	for (int i = 10, j = 0; i < 490 && j < 4; i += 120, j++)
	{
		rect = { i, 10, i + 120, 10 + 30 };
		drawtext(header[j], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// ���ѧ������
	wchar_t buffer[10];
	rect = { 10, 40, 10 + 120, 70 };
	_itow_s(getStudent(index, t.manager).id, buffer, 10);
	drawtext(buffer, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 130, 40, 130 + 120, 70 };
	drawtext(getStudent(index, t.manager).name, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 250, 40, 250 + 120, 70 };
	drawtext(getStudent(index, t.manager).Class, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	rect = { 370, 40, 370 + 120, 70 };
	_itow_s(getStudent(index, t.manager).score, buffer, 10);
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
