#pragma once

#include "Widget.h"
#include <string>

struct Button {
    // ��ť��
    Widget w;
    std::wstring text;                      // ��ť�ı�
    bool isChange;                          // ��ť״̬�Ƿ�ı�
};
void buttonInit(Button* b, int x, int y, int width, int height, std::wstring text);
void ButtonShow(Button B);                      // ��ʾ��ť
bool state(const ExMessage& msg, Button* B);       // ��ť״̬��true ��ʾ��ť����
bool isIn(const ExMessage& msg, Button B);  // �ж�����Ƿ��ڰ�ť����


