#include "arithForme.h"
#include "wx/dcbuffer.h"

arithForme::arithForme(const wxString& title):wxFrame(NULL, wxID_ANY, title),m_rTimer(this),m_listDialog(NULL)
{
    //�ļ�
    wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(wxID_EXIT, wxT("&�˳�\tAlt-X"),wxT("�˳�Ӧ�ó���"));

	//�㷨
	wxMenu *arithMenu = new wxMenu;
	arithMenu->Append(airthmeticID_Refresh, wxT("&ˢ��\tAlt-N"),wxT("������������"));
	arithMenu->Append(airthmeticID_Group,wxT("&��ʾ˳��\tAlt-G"),wxT("�༭��ʾ˳��"));
	arithMenu->Append(airthmeticID_Start,wxT("&��ʼ\tAlt-S"),wxT("��ʼ��ʾ"));
	arithMenu->Append(airthmeticID_Pause,wxT("&��ͣ\tAlt-P"),wxT("��ͣ��ʾ"));
	arithMenu->Append(airthmeticID_Stop,wxT("&����\tAlt-E"),wxT("������ʾ"));

    //����
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, wxT("&˵��\tF1"),wxT("չʾ�����Ϣ"));

    // ���˵�����ӵ��˵�����
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&�ļ�"));
	menuBar->Append(arithMenu, wxT("&����"));
    menuBar->Append(helpMenu, wxT("&����"));

    //�˵�����������������
    SetMenuBar(menuBar);

    // ״̬��
    CreateStatusBar(2);
    SetStatusText(wxT("C++�㷨��ʾ"));

	//dialog
	m_listDialog = new slistDialog(this,wxID_ANY,wxT("�༭��ʾ˳��"),wxDefaultPosition,wxSize( 355,530 ),wxDEFAULT_DIALOG_STYLE);

	//���ݳ�ʼ��
	m_rarithmeticMgr.init(airthmeticID_MaxID);

	m_nSpeed = 100;

	m_bStop = true;

	m_rarithmeticMgr.random();
}

void arithForme::OnAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf(wxT("��ӭʹ��C++�㷨��ʾ���򣬸ó�����%s��д\n%s\n%s\n%s\n"),
		wxVERSION_STRING,
		wxT("֧���㷨��"),
		wxT("	�ȶ���ð�� ˫��ð�� ���� Ͱ ���� �鲢 ԭ�ع鲢 ������ ���� Gnome Library"),
		wxT("  ���ȶ���ѡ�� ϣ�� �� ���� Comb Smooth Intro Patience")
		);
	wxMessageBox(msg, wxT("˵��"),wxOK | wxICON_INFORMATION, this);
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
	{EarithmeticFunc_None,		"�ȴ�"},
	{EarithmeticFunc_MaoPao,	"ð������"},
	{EarithmeticFunc_2Maopao,	"˫��ð������"},
	{EarithmeticFunc_Insert,	"��������"},
	{EarithmeticFunc_Drum,		"Ͱ����"},
	{EarithmeticFunc_Tally,		"��������"},
	{EarithmeticFunc_Merger,	"�鲢����"},
	{EarithmeticFunc_MergerLo,	"ԭ�ع鲢����"},
	{EarithmeticFunc_BaseM,		"��������MSD"},
	{EarithmeticFunc_BaseL,		"��������LSD"},
	{EarithmeticFunc_Choose,	"ѡ������"},
	{EarithmeticFunc_Quick,		"��������"},
	{EarithmeticFunc_Shell,		"ϣ������"},
	{EarithmeticFunc_Heap,		"������"},
	{EarithmeticFunc_BinaryTree,	"����������"},
	{EarithmeticFunc_Gnome,		"Gnome����"},
	{EarithmeticFunc_Library,	"Library����"},
	{EarithmeticFunc_Comb,		"Comb����"},
	{EarithmeticFunc_Smooth,	"Smooth����"},
	{EarithmeticFunc_Intro,		"Intro����"},
	{EarithmeticFunc_Patience,	"Patience����"},
};

void arithForme::PaintFrame()
{
	//����
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

	//����
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
	//���
	wxPoint rPoint;
	rPoint.x = 30;
	rPoint.y = 65;

	wxColour color(0,0,0);
	
	wxBrush* pBrush = wxTheBrushList->FindOrCreateBrush(color,wxSOLID);
	rdc.SetBrush(*pBrush);

	//��� 775X600
	//��� 5����
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
	showgrid->SetColLabelValue(1,wxT("�㷨"));
	showgrid->SetColLabelValue(2,wxT("˳��"));
	showgrid->HideRowLabels();

	slistSizer->Add( showgrid, 0, wxALL, 5 );

	btnSave = new wxButton( this, wxID_SAVE, wxT("����"), wxDefaultPosition, wxDefaultSize, 0 );
	slistSizer->Add( btnSave, 0, wxALL, 5 );

	btnReset = new wxButton( this, wxID_REVERT, wxT("����"), wxDefaultPosition, wxDefaultSize, 0 );
	slistSizer->Add( btnReset, 0, wxALL, 5 );

	btnClose = new wxButton( this, wxID_EXIT, wxT("�ر�"), wxDefaultPosition, wxDefaultSize, 0 );
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
