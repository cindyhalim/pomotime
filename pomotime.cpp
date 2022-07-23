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
    void OnPlay(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnSkip(wxCommandEvent& event);
};

wxIMPLEMENT_APP(PomoTime);

// opens the app
bool PomoTime::OnInit() {
  PomoTimeFrame *frame = new PomoTimeFrame();
  frame->Show(true);
  
  return true;
};

enum {
  // TODO: htf do we set these ids???
  BUTTON_play = wxID_ANY + 1,
  BUTTON_stop = wxID_STOP,
  BUTTON_skip = wxID_ANY + 2,
};

PomoTimeFrame::PomoTimeFrame(): wxFrame(NULL, wxID_ANY, "pomo 🍅 time") {
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuHelp, "&Help");

  
  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText *timeRemaining = new wxStaticText(panel, wxID_ANY, wxT("25:00"));

  wxButton *playButton = new wxButton(panel, BUTTON_play, wxT("play"));
  wxButton *stopButton = new wxButton(panel, BUTTON_stop, wxT("stop"));
  wxButton *skipButton = new wxButton(panel, BUTTON_skip, wxT("skip"));

  
  hbox2->Add(playButton);
  hbox2->Add(stopButton);
  hbox2->Add(skipButton);

  vbox->Add(hbox2, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER, 10);
  panel->SetSizer(vbox);
  Centre();

  SetMenuBar( menuBar );

  Bind(wxEVT_MENU, &PomoTimeFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &PomoTimeFrame::OnExit, this, wxID_EXIT);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnPlay, this, BUTTON_play);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnStop, this, BUTTON_stop);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnSkip, this, BUTTON_skip);

};

void PomoTimeFrame::OnPlay(wxCommandEvent& event) {
  std::cout << "Play button clicked!" << std::endl;
}
void PomoTimeFrame::OnStop(wxCommandEvent& event) {
  std::cout << "Stop button clicked!" << std::endl;
}
void PomoTimeFrame::OnSkip(wxCommandEvent& event) {
  std::cout << "Skip button clicked!" << std::endl;
}

void PomoTimeFrame::OnExit(wxCommandEvent& event) {
  Close(true);
};

void PomoTimeFrame::OnAbout(wxCommandEvent& event) {
  wxMessageBox("cindy's first C++ project!", "about pomo time", wxOK | wxICON_INFORMATION);
};



