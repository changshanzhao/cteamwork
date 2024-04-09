#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>
#define len 80 //字符长度
#define n 1000 //学生个数

// 背景图片名的常量
constexpr auto BACKGROUND_IMAGE = L"background_m.png";

enum WindowState
{
    mainWindow,     // 主窗口
    viewStudents,   // 查看学生
    viewAdmins,
    editStudents,    // 编辑学生
    editAdmins,
    cmd,
};


struct Window
{
    // 主窗口按钮
    Button* mainWindow_edit_admin;
    Button* mainWindow_view_admin;
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;
    Button* mainWindow_cmd;

    // 查看学生窗口按钮
    Button* viewStudents_pageUp;
    Button* viewStudents_pageDown;
    Button* viewStudents_back;
    Button* viewStudents_sort;

    // 编辑学生窗口按钮
    Button* editStudents_add;
    Button* editStudents_delete;
    Button* editStudents_back;
    Button* editStudents_search;



    Widget wid;

    WindowState state;  // 窗口状态
    Table* table;       // 学生数据表格
    Manager manager;    // 管理器
    HWND hWnd;          // 窗口句柄
    bool isEdit;        // 是否编辑学生
};
void windowInit(Window* w, int width, int height);
void windowDelete(Window* w);
void windowShow(Window* w);                          // 显示窗口
void messageLoop(Window* w);                         // 消息循环
bool close(Window* w);                               // 关闭窗口
void showMainWindow(Window* w);                      // 显示主窗口
void showViewStudents(Window* w);                    // 显示查看学生窗口
void showViewAdmins(Window* w);
void showEditAdmins(Window* w);
void showEditStudents(Window* w);                    // 显示编辑学生窗口
bool isNumber(Window* w, const std::wstring& string);  // 判断受否为数字
void FirstPage();
void showCmd();