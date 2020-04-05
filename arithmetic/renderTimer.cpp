#include "renderTimer.h"
#include "arithForme.h"

renderTimer::renderTimer(arithForme* pFrame)
{
    m_pFrame = pFrame;
}

renderTimer::~renderTimer(void)
{
    m_pFrame = NULL;
}


void renderTimer::Notify()
{
    m_pFrame->PaintFrame();
}

void renderTimer::StartLoop(int interval)
{
    StopLoop();
    wxTimer::Start(interval);   //º‰∏ÙX∫¡√Î
}

void renderTimer::StopLoop()
{
    wxTimer::Stop();
}
