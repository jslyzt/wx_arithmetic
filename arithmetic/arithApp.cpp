#include "arithApp.h"

bool arithApp::OnInit()
{
    // ����������
    arithForme *frame = new arithForme(wxT("C++�㷨��ʾ����"));
	//���ÿ��
	wxRect rRet(0,0,840,750);
	frame->SetSize(rRet);
    // ��ʾ������
    frame->Show(true);
    return true;
}