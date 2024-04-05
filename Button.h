#pragma once

#include "Widget.h"
#include <string>

struct Button {
    // 按钮类
    Widget w;
    std::wstring text;                      // 按钮文本
    bool isChange;                          // 按钮状态是否改变
};
void buttonInit(Button* b, int x, int y, int width, int height, std::wstring text);
void ButtonShow(Button B);                      // 显示按钮
bool state(const ExMessage& msg, Button* B);       // 按钮状态，true 表示按钮按下
bool isIn(const ExMessage& msg, Button B);  // 判断鼠标是否在按钮里面


