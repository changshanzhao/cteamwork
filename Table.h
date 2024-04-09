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
void tableShow_admin(Table t); // ��ʾ����Ա��� 
void tableShow_stu(Table t); // ��ʾѧ�����
void pageUp(Table* t);                                  // ��һҳ
void pageDown(Table* t);                                // ��һҳ
void showEditTable(Table* t, char* searchTerms); // ��ʾ�༭����ַ���������
void showEditTableByID(Table* t, char* id);						// ��ʾ�༭���ѧ��������
void showTable(Table t, StudentInfo* index);                      // ��ʾ�༭����±�������
int getSearchIndex(Table t);                     // ��ȡ��������
void setSearchIndex(Table t, int index);                 // ����ѧ������

