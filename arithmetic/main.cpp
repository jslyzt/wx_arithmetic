#include "arithApp.h"
#include "arithForme.h"

DECLARE_APP(arithApp)

IMPLEMENT_APP(arithApp)

// arithForme类的事件表
BEGIN_EVENT_TABLE(arithForme, wxFrame)
    EVT_MENU(wxID_ABOUT, arithForme::OnAbout)
    EVT_MENU(wxID_EXIT,  arithForme::OnQuit)

	EVT_MENU(airthmeticID_Refresh,  arithForme::OnRefresh)
	EVT_MENU(airthmeticID_Group,  arithForme::OnGroup)
	EVT_MENU(airthmeticID_Start,  arithForme::OnStart)
	EVT_MENU(airthmeticID_Pause,  arithForme::OnPause)
	EVT_MENU(airthmeticID_Stop,  arithForme::OnStop)
	EVT_KEY_DOWN(arithForme::OnChar)
END_EVENT_TABLE()

// slistDialog类的事件表
BEGIN_EVENT_TABLE(slistDialog, wxDialog)
	EVT_BUTTON(wxID_SAVE, slistDialog::OnSave)
	EVT_BUTTON(wxID_REVERT, slistDialog::OnReset)
	EVT_BUTTON(wxID_EXIT,  slistDialog::OnQuit)
	EVT_KEY_DOWN(slistDialog::OnChar)
END_EVENT_TABLE()