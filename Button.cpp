#include "Button.h"

void ButtonShow(Button* B)
{
	// 设置样式
	setlinestyle(PS_SOLID, 2);
	setfillcolor(CYAN);
	settextstyle(25, 0, L"微软雅黑");

	// 绘制按钮
	fillrectangle(B->w.x, B->w.y, B->w.x + B->w.width, B->w.y + B->w.height);

	// 绘制文本
	RECT rect = { B->w.x, B->w.y, B->w.x + B->w.width, B->w.y + B->w.height };
	drawtext(B->text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void buttonInit(Button* b, int x, int y, int width, int height, std::wstring text)
{
	b->w.x = x;
	b->w.y = y;
	b->w.width = width;
	b->w.height = height;
	b->text = text;
}
bool state(const ExMessage& msg, Button* B)
{
	if (msg.message == WM_MOUSEMOVE && isIn(msg, B))	// 按钮悬浮
	{
		// 设置样式
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"微软雅黑");

		// 绘制按钮
		fillrectangle(B->w.x, B->w.y, B->w.x + B->w.width, B->w.y + B->w.height);

		// 绘制文本
		RECT rect = { B->w.x, B->w.y, B->w.x + B->w.width, B->w.y + B->w.height };
		drawtext(B->text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		B->isChange = true;
		return false;
	}
	else if ((msg.message == WM_LBUTTONDOWN || msg.message == WM_LBUTTONUP) && isIn(msg, B))	// 按钮被点击
	{
		// 设置样式
		setlinestyle(PS_SOLID, 2);
		setfillcolor(LIGHTBLUE);
		settextstyle(25, 0, L"微软雅黑");

		// 绘制按钮
		fillrectangle(B->w.x, B->w.y, B->w.x + B->w.width, B->w.y + B->w.height);

		// 绘制文本
		RECT rect = { B->w.x, B->w.y, B->w.x + B->w.width, B->w.y + B->w.height };
		drawtext(B->text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		B->isChange = true;
		return true;
	}
	else	// 在按钮状态改变的时候，恢复按钮原来的状态，防止屏闪
	{
		if (B->isChange)
		{
			ButtonShow(B);
			B->isChange = false;
		}
		return false;
	}
}



bool isIn(const ExMessage& msg, Button* B)
{
	if (msg.x >= B->w.x && msg.x <= B->w.x + B->w.width && msg.y >= B->w.y && msg.y <= B->w.y + B->w.height)
	{
		return true;
	}
	return false;
}
