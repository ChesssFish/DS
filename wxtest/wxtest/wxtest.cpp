// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include"wx/wx.h"
enum EVT_ID
{
	QUIT = 1,
	SHOW_INDEXES,
	CHASE,
};
class testFrame : public wxFrame
{
public:
	testFrame(const wxString& titile);

	void OnQuit( wxCommandEvent& evt);
	void OnMotion(wxMouseEvent& evt)
	{
		if (evt.LeftDClick())
		{
			wxMessageBox("ooo");
			wxClientDC dc(this);
			wxColour wxWhite = wxTheColourDatabase->Find(wxT("WHITE"));
			wxBrush *whiteBrush = wxTheBrushList->FindOrCreateBrush(wxWhite, wxSOLID);
			dc.SetBrush(*wxWHITE_BRUSH);
			dc.DrawRectangle(0, 0, 300, 300);
		}
	}
	void OnRadio(wxCommandEvent& evt)
	{
		char a[] = { '0','1','2','3' };
		wxMessageBox(a[evt.GetSelection()]);
	}
	void OnCheck(wxCommandEvent& evt)
	{
		char a[] = { '0','1','2','3' };
		wxMessageBox(a[evt.GetSelection()]);
	}
private:
	wxPanel* p;
	wxRadioBox* radio_box;

	DECLARE_EVENT_TABLE()
};

testFrame::testFrame(const wxString& title)
	:wxFrame(NULL, wxID_ANY, title)
{
	wxMenuBar* menubar = new wxMenuBar();
	wxMenu* menuExit = new wxMenu();
	menubar->Append(menuExit, "EXIT");
	menuExit->Append(0, "exit");
	SetMenuBar(menubar);
	wxPanel* panel = new wxPanel(this,wxID_ANY,wxDefaultPosition, wxSize(100,100));
	wxCheckBox* check_box = new wxCheckBox(panel,0, wxT("test"));
	wxRadioButton* but1 = new wxRadioButton(this,wxID_ANY,"test");
	wxString* choices = new wxString[2];
	choices[0] = "test1";
	choices[1] = "test2";
	radio_box = new wxRadioBox
		(this,5,"test",
		wxPoint(50,50),
		wxDefaultSize,
		2,choices);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(radio_box);
	sizer->Add(but1);
	sizer->Add(panel);
	SetSizerAndFit(sizer);
}

class testApp : public wxApp
{
public:
	virtual bool OnInit();
};
bool testApp::OnInit()
{
	testFrame* frame = new testFrame(wxT("Wx Test App"));
	frame->Show();
	return true;
}

DECLARE_APP(testApp);
IMPLEMENT_APP(testApp);

BEGIN_EVENT_TABLE(testFrame, wxFrame)
	EVT_MENU(0, testFrame::OnQuit)
	EVT_MOUSE_EVENTS(testFrame::OnMotion)
	EVT_RADIOBOX(5, testFrame::OnRadio)
	EVT_RADIOBUTTON(1, testFrame::OnRadio)
	EVT_CHECKBOX(0, testFrame::OnCheck)
END_EVENT_TABLE()

void testFrame::OnQuit( wxCommandEvent& evt)
{
	wxMessageBox("exit");
}