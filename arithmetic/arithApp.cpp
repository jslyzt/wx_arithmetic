#include "arithApp.h"

bool arithApp::OnInit()
{
    // 创建主窗口
    arithForme *frame = new arithForme(wxT("C++算法演示程序"));
	//设置宽高
	wxRect rRet(0,0,840,750);
	frame->SetSize(rRet);
    // 显示主窗口
    frame->Show(true);
    return true;
}