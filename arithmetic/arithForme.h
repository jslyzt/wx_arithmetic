#pragma once

#include "wx/wx.h"
#include "wx/grid.h"

#include "renderTimer.h"
#include "arithmeticMgr.h"
#include "arithmeticNode.h"

enum EairthmeticID
{
	airthmeticID_Refresh = wxID_HIGHEST,
	airthmeticID_Group,
	airthmeticID_Start,
	airthmeticID_Pause,
	airthmeticID_Stop,

	airthmeticID_MaxID = 100,
};

struct arithIdName
{
	int		m_nID;
	wxString	m_strName;
};

class slistDialog;
// 定义主窗口类
class arithForme : public wxFrame
{
public:
    // 主窗口类的构造函数
    arithForme(const wxString& title);

    // 事件处理函数
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

	//自定义事件
	void OnRefresh(wxCommandEvent& event);
	void OnGroup(wxCommandEvent& event);
	void OnStart(wxCommandEvent& event);
	void OnPause(wxCommandEvent& event);
	void OnStop(wxCommandEvent& event);
	void OnChar(wxKeyEvent& event);

	void PaintFrame();
	arithmeticMgr& getArithmeticMgr(){return m_rarithmeticMgr;}
private:
	void PaintNameInfo(wxDC& rdc,int nKey,int nStep,int nMax);
	void PaintDataInfo(wxDC& rdc,vector<int>* pList);
	void onpause();
	void onstart();
	void onstop();

private:
    // 声明事件表
    DECLARE_EVENT_TABLE()

private:
	renderTimer		m_rTimer;
	arithmeticMgr	m_rarithmeticMgr;
	int				m_nSpeed;
	bool			m_bStop;
	slistDialog*	m_listDialog;
};

////////////////////////////////////////////////////////////////////////
class slistDialog : public wxDialog 
{
public:

	slistDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style); 
	~slistDialog();

	void OnSave(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnChar(wxKeyEvent& event);

	void setShowData(vector<int>& rList);
	void getShowData(vector<int>& rList);
private:
	void updateShowData(vector<int>& rList);
private:
	DECLARE_EVENT_TABLE()

protected:
	wxGrid* showgrid;
	wxButton* btnSave;
	wxButton* btnReset;
	wxButton* btnClose;
	vector<int>	rdefList;
};