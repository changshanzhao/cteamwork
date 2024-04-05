#pragma once

#include "Widget.h"
#include "Manager.h"
#include <sstream>

// �����
struct Table
{
    int curIndex;                                   // ��ǰѧ������
    int searchIndex;                                // ��������
    Manager manager;                         // ������
    Widget w;
};
void tableInit(Table* t, Manager manager, int x = 0, int y = 0, int width = 100, int height = 60);
void tableShow(Table t);                              // ��ʾ���
void pageUp(Table* t);                                  // ��һҳ
void pageDown(Table* t);                                // ��һҳ
void showEditTable(Table* t, const wchar_t* searchTerms); // ��ʾ�༭����ַ���������
void showEditTable(Table* t, int id);						// ��ʾ�༭���ѧ��������
void showTable(Table t, int index);                      // ��ʾ�༭����±�������
int getSearchIndex(Table t);                     // ��ȡ��������
void setSearchIndex(Table t, int index);                 // ����ѧ������

