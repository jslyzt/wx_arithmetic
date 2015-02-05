#pragma once

#include "wx/wx.h"

class arithForme;
class renderTimer:public wxTimer
{
public:
	renderTimer(arithForme* pFrame);
	~renderTimer(void);

	virtual void	Notify();
	void	StartLoop(int interval);
	void	StopLoop();
private:
	arithForme*		m_pFrame;
};
