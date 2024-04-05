#pragma once

#include "Widget.h"
#include "Manager.h"
#include <sstream>

// 表格类
struct Table
{
    int curIndex;                                   // 当前学生索引
    int searchIndex;                                // 搜索索引
    Manager manager;                         // 管理器
    Widget w;
};
void tableInit(Table* t, Manager manager, int x = 0, int y = 0, int width = 100, int height = 60);
void tableShow(Table t);                              // 显示表格
void pageUp(Table* t);                                  // 上一页
void pageDown(Table* t);                                // 下一页
void showEditTable(Table* t, const wchar_t* searchTerms); // 显示编辑表格（字符串搜索）
void showEditTable(Table* t, int id);						// 显示编辑表格（学号搜索）
void showTable(Table t, int index);                      // 显示编辑表格（下标索引）
int getSearchIndex(Table t);                     // 获取搜索索引
void setSearchIndex(Table t, int index);                 // 设置学生索引

