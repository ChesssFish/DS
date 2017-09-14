#pragma once
#ifndef CHASE_APPLICATION_CHASEFRAME_H
#define CHASE_APPLICATION_CHASEFRAME_H
#include"ChaseDef.h"
#include"wx/wx.h"
#include"ChaseMap.h"
#include<string>
#include<memory>

class ChaseFrame;
class ChaseApp : public wxApp
{
public:
	virtual bool OnInit();
	ChaseFrame* GetFrame();
private:
	ChaseFrame* m_frame;
};

DECLARE_APP(ChaseApp)

class ChaseCanvas;

class ChaseFrame :public wxFrame
{
public:
	ChaseFrame();
	~ChaseFrame();
	void OutPutInfomation(std::string infomation);
private:
	ChaseCanvas* m_canvas;
	wxTextCtrl* m_output;
	wxTimer* m_timer;
	int m_frame_interval;
	void OnButton(wxCommandEvent& evt);
	void OnCheck(wxCommandEvent& evt);
	void OnRadio(wxCommandEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);
	void OnTimer(wxTimerEvent& WXUNUSED(evt));
	DECLARE_EVENT_TABLE()
};

class ChaseCanvas : public wxPanel
{
public:
	ChaseCanvas(wxFrame* parent);
	void UpDate();
	void SetAuto(bool x = false);
	void DrawTile(int tileX, int tileY, const wxBrush* brush);
	void DrawPlayer();
	void DestroyPlayer();
	void DrawChaser();
	void DestroyChaser();
	void DrawSearchedNodes();
	void DrawPath();
	void DrawAll();
	void GenerateAdjList();
	void GenerateNavTable();
private:
	void OnMouseEvent(wxMouseEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);

	ChaseMap* m_map;

	const wxBrush* m_player_brush;
	const wxBrush* m_chaser_brush;
	const wxBrush* m_block_brush;
	const wxBrush* m_empty_brush;
	const wxBrush* m_searched_brush;
	const wxBrush* m_path_brush;
	int m_lineWidth;
	int m_cellWidth;
	int m_cellHeight;
	bool m_auto;
	DECLARE_EVENT_TABLE()
};

#endif