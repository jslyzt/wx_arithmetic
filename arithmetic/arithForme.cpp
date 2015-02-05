#include "arithForme.h"
#include "wx/dcbuffer.h"

arithForme::arithForme(const wxString& title):wxFrame(NULL, wxID_ANY, title),m_rTimer(this),m_listDialog(NULL)
{
    //文件
    wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(wxID_EXIT, wxT("&退出\tAlt-X"),wxT("退出应用程序"));

	//算法
	wxMenu *arithMenu = new wxMenu;
	arithMenu->Append(airthmeticID_Refresh, wxT("&刷新\tAlt-N"),wxT("重置排序数组"));
	arithMenu->Append(airthmeticID_Group,wxT("&演示顺序\tAlt-G"),wxT("编辑演示顺序"));
	arithMenu->Append(airthmeticID_Start,wxT("&开始\tAlt-S"),wxT("开始演示"));
	arithMenu->Append(airthmeticID_Pause,wxT("&暂停\tAlt-P"),wxT("暂停演示"));
	arithMenu->Append(airthmeticID_Stop,wxT("&结束\tAlt-E"),wxT("结束演示"));

    //帮助
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, wxT("&说明\tF1"),wxT("展示软件信息"));

    // 将菜单项添加到菜单条中
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&文件"));
	menuBar->Append(arithMenu, wxT("&排序"));
    menuBar->Append(helpMenu, wxT("&帮助"));

    //菜单条放置在主窗口上
    SetMenuBar(menuBar);

    // 状态条
    CreateStatusBar(2);
    SetStatusText(wxT("C++算法演示"));

	//dialog
	m_listDialog = new slistDialog(this,wxID_ANY,wxT("编辑演示顺序"),wxDefaultPosition,wxSize( 355,530 ),wxDEFAULT_DIALOG_STYLE);

	//数据初始化
	m_rarithmeticMgr.init(airthmeticID_MaxID);

	m_nSpeed = 100;

	m_bStop = true;

	m_rarithmeticMgr.random();
}

void arithForme::OnAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf(wxT("欢迎使用C++算法演示程序，该程序由%s编写\n%s\n%s\n%s\n"),
		wxVERSION_STRING,
		wxT("支持算法："),
		wxT("	稳定：冒泡 双向冒泡 插入 桶 计数 归并 原地归并 二叉树 基数 Gnome Library"),
		wxT("  不稳定：选择 希尔 堆 快速 Comb Smooth Intro Patience")
		);
	wxMessageBox(msg, wxT("说明"),wxOK | wxICON_INFORMATION, this);
}

void arithForme::OnQuit(wxCommandEvent& event)
{
	Close();
}


void arithForme::OnRefresh(wxCommandEvent& event)
{
	m_rarithmeticMgr.refresh();
}

void arithForme::OnGroup(wxCommandEvent& event)
{
	if(m_listDialog->IsShownOnScreen() == false)
	{
		wxPoint nowPos = GetPosition();
		nowPos.x += 250;
		nowPos.y += 60;
		m_listDialog->SetPosition(nowPos);

		vector<int> rList;
		m_rarithmeticMgr.getShowList(rList);
		m_listDialog->setShowData(rList);

		m_listDialog->Show(true);
	}
	else
	{
		m_listDialog->Show(false);
	}
}

void arithForme::OnStart(wxCommandEvent& event)
{
	m_rarithmeticMgr.start();
	onstart();
}

void arithForme::onpause()
{
	if(m_bStop == true)
	{
		onstart();
	}
	else
	{
		onstop();
	}
}

void arithForme::onstart()
{
	m_rTimer.StartLoop(m_nSpeed);
	m_bStop = false;
}

void arithForme::onstop()
{
	m_rTimer.StopLoop();
	m_bStop = true;
}

void arithForme::OnPause(wxCommandEvent& event)
{
	onpause();
}

void arithForme::OnStop(wxCommandEvent& event)
{
	m_rarithmeticMgr.stop();
	onstop();
}

void arithForme::OnChar(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_SPACE)
	{
		onpause();
	}
}

const arithIdName arithFuncName[] = 
{
	{EarithmeticFunc_None,		"等待"},
	{EarithmeticFunc_MaoPao,	"冒泡排序"},
	{EarithmeticFunc_2Maopao,	"双向冒泡排序"},
	{EarithmeticFunc_Insert,	"插入排序"},
	{EarithmeticFunc_Drum,		"桶排序"},
	{EarithmeticFunc_Tally,		"计数排序"},
	{EarithmeticFunc_Merger,	"归并排序"},
	{EarithmeticFunc_MergerLo,	"原地归并排序"},
	{EarithmeticFunc_BaseM,		"基数排序MSD"},
	{EarithmeticFunc_BaseL,		"基数排序LSD"},
	{EarithmeticFunc_Choose,	"选择排序"},
	{EarithmeticFunc_Quick,		"快速排序"},
	{EarithmeticFunc_Shell,		"希尔排序"},
	{EarithmeticFunc_Heap,		"堆排序"},
	{EarithmeticFunc_BinaryTree,	"二叉树排序"},
	{EarithmeticFunc_Gnome,		"Gnome排序"},
	{EarithmeticFunc_Library,	"Library排序"},
	{EarithmeticFunc_Comb,		"Comb排序"},
	{EarithmeticFunc_Smooth,	"Smooth排序"},
	{EarithmeticFunc_Intro,		"Intro排序"},
	{EarithmeticFunc_Patience,	"Patience排序"},
};

void arithForme::PaintFrame()
{
	//更新
	bool bUpdate = false;
	bool bNext = false;
	arithmeticData& drawData = m_rarithmeticMgr.getarithmeticData();
	if(drawData.toEnd() == true)
	{
		bNext = m_rarithmeticMgr.getNext();
	}
	else
	{
		bUpdate = true;
	}
	
	if(bUpdate == false && bNext == false)
	{
		return;
	}

	//绘制
	int nIndex = m_rarithmeticMgr.current();

	wxClientDC rdc(this);
	wxBufferedDC rbufDc(&rdc);
	rbufDc.Clear();

	rbufDc.SetBackground(*wxWHITE_BRUSH);
	PaintNameInfo(rbufDc,nIndex, drawData.getStep(),drawData.getMaxStep());

	if(bNext == true && bUpdate == false)
	{
		return;
	}

	if(nIndex != EarithmeticFunc_None && bUpdate == true)
	{
		PaintDataInfo(rbufDc,drawData.getStepInfo());
	}
}

void arithForme::PaintNameInfo(wxDC& rdc,int nKey,int nStep,int nMax)
{
	wxPoint rPoint;
	rPoint.x = 30;
	rPoint.y = 20;
	rdc.DrawText(wxT("----------------------------------------------"),rPoint);
	rPoint.y = 30;
	wxString msg;
	msg.Printf(wxT("%s       step: %d / %d"),arithFuncName[nKey].m_strName,nStep,nMax);
	rdc.DrawText(msg,rPoint);
	rPoint.y = 40;
	rdc.DrawText(wxT("----------------------------------------------"),rPoint);
}

void arithForme::PaintDataInfo(wxDC& rdc,vector<int>* pList)
{
	if(pList == NULL)
	{
		return ;
	}

	int nSize = pList->size();
	//起点
	wxPoint rPoint;
	rPoint.x = 30;
	rPoint.y = 65;

	wxColour color(0,0,0);
	
	wxBrush* pBrush = wxTheBrushList->FindOrCreateBrush(color,wxSOLID);
	rdc.SetBrush(*pBrush);

	//规格 775X600
	//间隔 5像素
	int nLength = (755 - 5*nSize)/nSize;
	int nXAdd = 0;
	wxRect rRect;
	for(int i=0;i<nSize;i++)
	{
		int nHight = pList->at(i) * 600 / airthmeticID_MaxID;
		rRect.SetX(rPoint.x + nXAdd);
		rRect.SetY(rPoint.y + 600 - nHight);
		rRect.SetWidth(nLength);
		rRect.SetHeight(nHight);
		rdc.DrawRectangle(rRect);

		wxString msg;
		msg.Printf(wxT("%d"),pList->at(i));
		wxPoint tmpPoint;
		tmpPoint.x = rPoint.x + nXAdd;
		tmpPoint.y = rPoint.y + 600 - nHight - 20;
		rdc.DrawText(msg,tmpPoint);

		nXAdd = nXAdd + 5 + nLength;
	}
}

////////////////////////////////////////////////////////////////////////////////////

slistDialog::slistDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* slistSizer;
	slistSizer = new wxFlexGridSizer( 0, 2, 0, 0 );
	slistSizer->SetFlexibleDirection( wxBOTH );
	slistSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	showgrid = new wxGrid( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	showgrid->CreateGrid(20, 3);
	showgrid->EnableEditing( true );
	showgrid->EnableGridLines( true );
	showgrid->EnableDragGridSize( false );
	showgrid->SetMargins( 0, 0 );

	// Columns
	showgrid->EnableDragColMove( false );
	showgrid->EnableDragColSize( true );
	showgrid->SetColLabelSize( 30 );
	showgrid->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Rows
	showgrid->EnableDragRowSize( true );
	showgrid->SetRowLabelSize( 80 );
	showgrid->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );

	// Label Appearance

	// Cell Defaults
	showgrid->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	
	showgrid->SetColLabelValue(0,wxT("ID"));
	showgrid->SetColLabelValue(1,wxT("算法"));
	showgrid->SetColLabelValue(2,wxT("顺序"));
	showgrid->HideRowLabels();

	slistSizer->Add( showgrid, 0, wxALL, 5 );

	btnSave = new wxButton( this, wxID_SAVE, wxT("保存"), wxDefaultPosition, wxDefaultSize, 0 );
	slistSizer->Add( btnSave, 0, wxALL, 5 );

	btnReset = new wxButton( this, wxID_REVERT, wxT("重置"), wxDefaultPosition, wxDefaultSize, 0 );
	slistSizer->Add( btnReset, 0, wxALL, 5 );

	btnClose = new wxButton( this, wxID_EXIT, wxT("关闭"), wxDefaultPosition, wxDefaultSize, 0 );
	slistSizer->Add( btnClose, 0, wxALL, 5 );


	this->SetSizer( slistSizer );
	this->Layout();

	this->Centre( wxBOTH );
}

slistDialog::~slistDialog()
{
}

void slistDialog::OnSave(wxCommandEvent& event)
{
	vector<int> rList;
	getShowData(rList);

	arithForme* pParent = static_cast<arithForme*>(this->GetParent());
	if(pParent != NULL)
	{
		pParent->getArithmeticMgr().setShowList(rList);
	}
}

void slistDialog::OnReset(wxCommandEvent& event)
{
	updateShowData(rdefList);
}

void slistDialog::OnQuit(wxCommandEvent& event)
{
	Show(false);
}

void slistDialog::OnChar(wxKeyEvent& event)
{
	if(event.AltDown() && event.GetUnicodeKey() == 'G')
	{
		Show(false);
	}
}

void slistDialog::updateShowData(vector<int>& rList)
{
	showgrid->ClearGrid();
	for(int i=0;i<rList.size();i++)
	{
		wxString msg;
		msg.Printf(wxT("%d"),rList[i]);
		showgrid->SetCellValue(i,0,msg);
		showgrid->SetCellValue(i,1,arithFuncName[rList[i]].m_strName);
		msg.Printf(wxT("%d"),i+1);
		showgrid->SetCellValue(i,2,msg);
	}
}

void slistDialog::setShowData(vector<int>& rList)
{
	updateShowData(rList);
	rdefList = rList;
}

void slistDialog::getShowData(vector<int>& rList)
{
	rList.clear();
	map<int,int> sortMap;
	for(int i=0;i<showgrid->GetRows();i++)
	{
		wxString infoId = showgrid->GetCellValue(i,0);
		wxString infoIndex = showgrid->GetCellValue(i,2);
		sortMap[wxAtoi(infoIndex)] = wxAtoi(infoId);
	}
	for(int i=0;i<showgrid->GetRows();i++)
	{
		if(sortMap.find(i+1) != sortMap.end())
		{
			rList.push_back(sortMap[i+1]);
		}
	}
}
