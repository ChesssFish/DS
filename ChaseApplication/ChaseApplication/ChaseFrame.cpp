#include "ChaseFrame.h"
#include "ChaseMap.h"
#include <ctime>
#include <string>
bool ChaseApp::OnInit()
{
	m_frame = new ChaseFrame;

	return true;
}

ChaseFrame* ChaseApp::GetFrame()
{
	return m_frame;
}

enum EVT
{
	GENERATENAV,
	SEARCHMETHOD,
	AUTO,
	STEP,
	TIMER,
};
enum METHOD
{
	ASTAR,
	NAVTABLE
}method;
BEGIN_EVENT_TABLE(ChaseFrame, wxFrame)
	EVT_BUTTON(GENERATENAV, ChaseFrame::OnButton)
	EVT_CHECKBOX(AUTO, ChaseFrame::OnCheck)
	EVT_RADIOBOX(SEARCHMETHOD, ChaseFrame::OnRadio)
	EVT_KEY_DOWN(ChaseFrame::OnKeyDown)
	EVT_TIMER(TIMER, ChaseFrame::OnTimer)
END_EVENT_TABLE()

ChaseFrame::ChaseFrame():
	wxFrame(NULL, wxID_ANY, wxT("ChaseDemo"),wxDefaultPosition,
		wxSize(1200,1200), wxDEFAULT_DIALOG_STYLE | wxMINIMIZE_BOX)
{
	m_frame_interval = 100;
	m_timer  = new wxTimer(this, TIMER);
	m_canvas = new ChaseCanvas(this);
	m_output = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_READONLY | wxTE_AUTO_SCROLL | wxTE_MULTILINE);

	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* menuFile = new wxMenu;

	SetMenuBar(menuBar);

	wxArrayString choices;
	choices.Add("A*");
	choices.Add("NavTable");
	wxRadioBox* searchMethod = new wxRadioBox(this, SEARCHMETHOD, "寻路方法",
		wxDefaultPosition, wxDefaultSize,choices, 1);
	wxCheckBox* automatic = new wxCheckBox(this, AUTO, "自动");
	wxButton* generateNavTable= new wxButton(this, GENERATENAV, wxT("生成导航表"));
	
	wxBoxSizer* control = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* canvas = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* top = new wxBoxSizer(wxVERTICAL);



	control->Add(searchMethod, 5, wxEXPAND);
	control->AddSpacer(10);
	control->Add(automatic, 1, wxEXPAND);
	control->AddSpacer(10);
	control->Add(generateNavTable, 4, wxEXPAND);

	canvas->Add(m_output,2,wxEXPAND);
	canvas->Add(m_canvas,8);
	

	top->Add(control,1,wxEXPAND);
	top->Add(canvas);
	
	SetSizerAndFit(top);
	
	Center(wxBOTH);
	Show();
	m_canvas->DrawAll();
}
ChaseFrame::~ChaseFrame()
{
}

void ChaseFrame::OnButton(wxCommandEvent& evt)
{
	m_output->AppendText("开始生成导航表\n");
	time_t start = clock();
	m_canvas->GenerateNavTable();
	m_output->AppendText("生成导航表完成\n");
	m_output->AppendText("耗时: ");
	m_output->AppendText(std::to_string(clock() - start) + " ms\n");
	
}
void ChaseFrame::OnCheck(wxCommandEvent& evt)
{
	if (evt.GetSelection() == 1)
	{
		m_timer->Start(m_frame_interval);
		m_canvas->SetAuto(true);
		m_canvas->DrawAll();
	}
	if (evt.GetSelection() == 0)
	{
		m_timer->Stop();
		m_canvas->SetAuto(false);
	}
}
void ChaseFrame::OnRadio(wxCommandEvent& evt)
{
	if (evt.GetSelection() == 0)
	{
		method = ASTAR;
	}
	if (evt.GetSelection() == 1)
	{
		method = NAVTABLE;
	}
}
void ChaseFrame::OnKeyDown(wxKeyEvent& evt)
{
	if (evt.GetKeyCode() == 'Z')
	{
		wxMessageBox("z");
	}
}
void ChaseFrame::OnTimer(wxTimerEvent& WXUNUSED(evt))
{
	m_canvas->UpDate();
}
void ChaseFrame::OutPutInfomation(std::string infomation)
{
	m_output->AppendText(infomation);
}
BEGIN_EVENT_TABLE(ChaseCanvas, wxPanel)
EVT_MOUSE_EVENTS(ChaseCanvas::OnMouseEvent)
EVT_KEY_DOWN(ChaseCanvas::OnKeyDown)
END_EVENT_TABLE()
ChaseCanvas::ChaseCanvas(wxFrame* parent) :
	wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 1000)),
	m_player_brush(wxGREEN_BRUSH),
	m_chaser_brush(wxBLACK_BRUSH),
	m_block_brush(wxRED_BRUSH),
	m_empty_brush(wxWHITE_BRUSH),
	m_searched_brush(wxLIGHT_GREY_BRUSH),
	m_path_brush(wxBLUE_BRUSH),
	m_lineWidth(1),
	m_auto(false)
{
	m_cellWidth = this->GetSize().x / MAPXN;
	m_cellHeight = this->GetSize().y / MAPYN;
	this->SetSize(MAPXN * m_cellWidth + m_lineWidth,
		MAPYN * m_cellHeight + m_lineWidth);
	m_map = new ChaseMap;
	m_map->GenerateAdjList();
}

Table NavTable;
void ChaseCanvas::UpDate()
{
	if (method == ASTAR && m_map->Chase())
	{
		AstarPath p = m_map->GetPath();

		int pos = p[m_map->GetID(m_map->GetPlayer().x, m_map->GetPlayer().y)].first;
		int c_pos = m_map->GetID(m_map->GetChaser().x, m_map->GetChaser().y);
		int p_pos = 0;
		while (pos != c_pos)
		{
			p_pos = pos;
			pos = p[pos].first;
		}
		DestroyChaser();
		m_map->SetChaser(p_pos % MAPXN, p_pos / MAPYN);
		DrawChaser();
	}
	else if (method == NAVTABLE)
	{
		int chaser_pos = m_map->GetID(m_map->GetChaser().x, m_map->GetChaser().y);
		int player_pos = m_map->GetID(m_map->GetPlayer().x, m_map->GetPlayer().y);
		int next_pos = 0;
		time_t start = clock();
		next_pos = NavTable[chaser_pos][player_pos];
		if (next_pos == player_pos)
			next_pos = 0;
		wxGetApp().GetFrame()->OutPutInfomation("查询导航表耗时：");
		wxGetApp().GetFrame()->OutPutInfomation(std::to_string(clock()-start) + "ms\n");
		DestroyChaser();
		m_map->SetChaser(next_pos % MAPXN, next_pos / MAPYN);
		DrawChaser();
	}
}
void ChaseCanvas::SetAuto(bool x)
{
	m_auto = x;
}
void ChaseCanvas::DrawTile(int tileX, int tileY, const wxBrush* brush)
{
	wxClientDC dc(this);
	dc.SetBrush(*brush);
	dc.DrawRectangle(tileX * m_cellWidth, tileY* m_cellHeight, 
		m_cellWidth + m_lineWidth, m_cellHeight + m_lineWidth);
}

void ChaseCanvas::DrawPlayer()
{
	wxPoint player = m_map->GetPlayer();
	DrawTile(player.x, player.y, m_player_brush);
}
void ChaseCanvas::DrawChaser()
{
	wxPoint chaser = m_map->GetChaser();
	DrawTile(chaser.x, chaser.y, m_chaser_brush);
}
void ChaseCanvas::DestroyPlayer()
{
	wxPoint player = m_map->GetPlayer();
	DrawTile(player.x, player.y, m_empty_brush);
}
void ChaseCanvas::DestroyChaser()
{
	wxPoint chaser = m_map->GetChaser();
	DrawTile(chaser.x, chaser.y, m_empty_brush);
}
void ChaseCanvas::DrawSearchedNodes()
{
	std::bitset<MAX> vis = m_map->GetSearchedNodes();
	for (int i = 0; i < MAPXN * MAPYN; ++i)
	{
		if (vis[i])
		{
			DrawTile(i % MAPXN, i / MAPXN, m_searched_brush);
		}
	}
	DrawPlayer();
	DrawChaser();
}
void ChaseCanvas::DrawPath()
{
	if (method == ASTAR)
	{
		AstarPath p = m_map->GetPath();

		int pos = p[m_map->GetID(m_map->GetPlayer().x, m_map->GetPlayer().y)].first;
		int c_pos = p[m_map->GetID(m_map->GetChaser().x, m_map->GetChaser().y)].first;

		while (pos != c_pos)
		{
			DrawTile(pos % MAPXN, pos / MAPYN, m_path_brush);
			pos = p[pos].first;
		}
		DrawPlayer();
		DrawChaser();
	}
	if (method == NAVTABLE)
	{

	}
}
void ChaseCanvas::DrawAll()
{
	wxClientDC dc(this);
	dc.SetBrush(*m_empty_brush);
	dc.DrawRectangle(
		this->GetClientAreaOrigin().x,
		this->GetClientAreaOrigin().y,
		this->GetSize().x,
		this->GetSize().y);
	wxPen pen(*wxBLACK, m_lineWidth);
	dc.SetPen(pen);
	for (int i = 0; i <= MAPXN; ++i)
	{
		dc.DrawLine(wxPoint(i * m_cellWidth, 0),
			wxPoint(i * m_cellWidth, MAPYN * m_cellHeight));
	}
	for (int i = 0; i <= MAPYN; ++i)
	{
		dc.DrawLine(wxPoint(0, i * m_cellHeight),
			wxPoint(MAPXN * m_cellWidth, i * m_cellHeight));
	}
	for (int i = 0; i < MAPXN; ++i)
	{
		for (int j = 0;j < MAPYN; ++j)
		{
			if (m_map->IsBlock(i, j))
				DrawTile(i, j, m_block_brush);
		}
	}
	DrawPlayer();
	DrawChaser();
}

void ChaseCanvas::GenerateAdjList()
{
	m_map->GenerateAdjList();
}
void ChaseCanvas::GenerateNavTable()
{
	m_map->GenerateNavTable();
	NavTable = m_map->GetNavTable();
}
void ChaseCanvas::OnMouseEvent(wxMouseEvent& evt)
{
	static int tileX1, tileY1;
	static int tileX2, tileY2;
	SetFocus();
	if (evt.LeftDown())
	{
		tileX1 = evt.GetX() / m_cellWidth;
		tileY1 = evt.GetY() / m_cellHeight;
	}
	if (evt.LeftUp())
	{
		tileX2 = evt.GetX() / m_cellWidth;
		tileY2 = evt.GetY() / m_cellHeight;

		if (tileX2 < tileX1)
			tileX2 ^= tileX1 ^= tileX2 ^= tileX1;
		if(tileY2 < tileY1)
			tileY2 ^= tileY1 ^= tileY2 ^= tileY1;

		for (int x = tileX1; x <= tileX2 && x < MAPXN; ++x)
			for (int y = tileY1; y <= tileY2 && y < MAPYN; ++y)
			{
				if (!m_map->IsChaser(x, y) && !m_map->IsPlayer(x, y))
				{
					m_map->ChageState(x, y);
					DrawTile(x, y,
						m_map->IsBlock(x, y) ? m_block_brush : m_empty_brush);
				}
			}
		GenerateAdjList();
	}
}

void ChaseCanvas::OnKeyDown(wxKeyEvent& evt)
{
	int keyCode = evt.GetKeyCode();
	switch (keyCode)
	{
	case 'W':
		DestroyPlayer();
		m_map->TranslatePlayer(0, -1);
		DrawPlayer();
		break;
	case 'S':
		DestroyPlayer();
		m_map->TranslatePlayer(0, 1);
		DrawPlayer();
		break;
	case 'A':
		DestroyPlayer();
		m_map->TranslatePlayer(-1, 0);
		DrawPlayer();
		break;
	case 'D':
		DestroyPlayer();
		m_map->TranslatePlayer(1, 0);
		DrawPlayer();
		break;
	case 'Z':
		if (m_auto)
			break;
		else
		{
			time_t start = clock();
			if (m_map->Chase())
			{
				wxGetApp().GetFrame()->OutPutInfomation("寻路完成，耗时: ");
				wxGetApp().GetFrame()->OutPutInfomation(
					std::to_string(clock() - start) + "ms\n");
				DrawAll();
				DrawSearchedNodes();
				DrawPath();
			}
			else
			{
				wxGetApp().GetFrame()->OutPutInfomation("无路径,搜索耗时:");
				wxGetApp().GetFrame()->OutPutInfomation(
					std::to_string(clock() - start) + "ms\n");
				DrawSearchedNodes();
			}
		}
		break;
	default:
		break;
	}
}
IMPLEMENT_APP(ChaseApp);