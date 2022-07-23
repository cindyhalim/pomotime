#include <wx/wxprec.h>
#include <iostream>

#ifndef WX_PRECOMP
  #include <wx/wx.h>
#endif

class PomoTime : public wxApp {
  public:
    virtual bool OnInit();
};

class PomoTimeFrame : public wxFrame {
  public:
    PomoTimeFrame();

  private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

wxIMPLEMENT_APP(PomoTime);

// opens the app
bool PomoTime::OnInit() {
  PomoTimeFrame *frame = new PomoTimeFrame();
  frame->Show(true);
  
  return true;
};

PomoTimeFrame::PomoTimeFrame(): wxFrame(NULL, wxID_ANY, "pomo 🍅 time") {
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar( menuBar );

  Bind(wxEVT_MENU, &PomoTimeFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &PomoTimeFrame::OnExit, this, wxID_EXIT);

};

void PomoTimeFrame::OnExit(wxCommandEvent& event) {
  Close(true);
};

void PomoTimeFrame::OnAbout(wxCommandEvent& event) {
  wxMessageBox("cindy's first C++ project!", "about pomo time", wxOK | wxICON_INFORMATION);
};



