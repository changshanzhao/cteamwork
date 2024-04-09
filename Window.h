#pragma once

#include "Widget.h"
#include "Button.h"
#include "Manager.h"
#include "Table.h"
#include <iostream>
#include <algorithm>
#define len 80 //�ַ�����
#define n 1000 //ѧ������

// ����ͼƬ���ĳ���
constexpr auto BACKGROUND_IMAGE = L"background_m.png";

enum WindowState
{
    mainWindow,     // ������
    viewStudents,   // �鿴ѧ��
    viewAdmins,
    editStudents,    // �༭ѧ��
    editAdmins,
    cmd,
};


struct Window
{
    // �����ڰ�ť
    Button* mainWindow_edit_admin;
    Button* mainWindow_view_admin;
    Button* mainWindow_view;
    Button* mainWindow_edit;
    Button* mainWindow_exit;
    Button* mainWindow_clear;
    Button* mainWindow_cmd;

    // �鿴ѧ�����ڰ�ť
    Button* viewStudents_pageUp;
    Button* viewStudents_pageDown;
    Button* viewStudents_back;
    Button* viewStudents_sort;

    // �༭ѧ�����ڰ�ť
    Button* editStudents_add;
    Button* editStudents_delete;
    Button* editStudents_back;
    Button* editStudents_search;



    Widget wid;

    WindowState state;  // ����״̬
    Table* table;       // ѧ�����ݱ��
    Manager manager;    // ������
    HWND hWnd;          // ���ھ��
    bool isEdit;        // �Ƿ�༭ѧ��
};
void windowInit(Window* w, int width, int height);
void windowDelete(Window* w);
void windowShow(Window* w);                          // ��ʾ����
void messageLoop(Window* w);                         // ��Ϣѭ��
bool close(Window* w);                               // �رմ���
void showMainWindow(Window* w);                      // ��ʾ������
void showViewStudents(Window* w);                    // ��ʾ�鿴ѧ������
void showViewAdmins(Window* w);
void showEditAdmins(Window* w);
void showEditStudents(Window* w);                    // ��ʾ�༭ѧ������
bool isNumber(Window* w, const std::wstring& string);  // �ж��ܷ�Ϊ����
void FirstPage();
void showCmd();