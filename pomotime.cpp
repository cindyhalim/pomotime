#include <wx/wxprec.h>

#ifndef WX_PRECOMP
  #include <wx/wx.h>
  #include <wx/datetime.h>
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "cycle.hpp"

enum {
  // TODO: htf do we set these ids???
  BUTTON_start = wxID_ANY + 1,
  BUTTON_stop = wxID_STOP,
  BUTTON_skip = wxID_ANY + 2,
};

class PomoTimeFrame : public wxFrame {
  public:
    PomoTimeFrame();

  private:
    PomoCycle cycle = PomoCycle();
    // index with Task Enum 🤷‍♀️;
    const int taskToTimeInMinutes[3] = {25, 5, 15};
    int timeRemainingInSeconds;
    wxStaticText* timeRemainingDisplay;
    wxTimer timer;
    
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnStart(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnSkip(wxCommandEvent& event);
    void UpdateDisplayedTime();
    void OnUpdateDisplayedTime(wxTimerEvent& event);
    void SetCurrTaskTimeInSeconds();
    std::string GetTimeRemaining();
};

PomoTimeFrame::PomoTimeFrame(): wxFrame(NULL, wxID_ANY, "pomo 🍅 time", wxPoint(-1, -1),  wxSize(400, 300)) {

  // MENU BAR STUFF
  wxMenu* menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar( menuBar );

  // APP

  wxPanel *textDisplayPanel = new wxPanel(this, -1, wxDefaultPosition, wxSize(300, 300));
  wxPanel *buttonsPanel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *buttonsRowBox = new wxBoxSizer(wxHORIZONTAL);
  wxFont font;

  std::string defaultLabel = "25:00";
  timeRemainingDisplay = new wxStaticText(buttonsPanel, wxID_ANY, defaultLabel, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
  font = timeRemainingDisplay->GetFont();
  font.MakeBold().MakeLarger();
  timeRemainingDisplay->SetFont(font);
  SetCurrTaskTimeInSeconds();
  UpdateDisplayedTime();


  wxButton *playButton = new wxButton(buttonsPanel, BUTTON_start, wxT("start"));
  wxButton *stopButton = new wxButton(buttonsPanel, BUTTON_stop, wxT("stop"));
  wxButton *skipButton = new wxButton(buttonsPanel, BUTTON_skip, wxT("skip"));

  
  buttonsRowBox->Add(playButton);
  buttonsRowBox->Add(stopButton);
  buttonsRowBox->Add(skipButton);

  vbox->Add(buttonsRowBox, 1, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER, 10);
  buttonsPanel->SetSizer(vbox);

  Centre();




  // EVENTS

  Bind(wxEVT_MENU, &PomoTimeFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &PomoTimeFrame::OnExit, this, wxID_EXIT);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnStart, this, BUTTON_start);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnStop, this, BUTTON_stop);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnSkip, this, BUTTON_skip);
  timer.Bind(wxEVT_TIMER, &PomoTimeFrame::OnUpdateDisplayedTime, this);

};

void PomoTimeFrame::OnStart(wxCommandEvent& event) {
  std::cout << "Start button clicked!" << std::endl;
  timer.Start(1000);
  UpdateDisplayedTime();
}

void PomoTimeFrame::OnStop(wxCommandEvent& event) {
  std::cout << "Stop button clicked!" << std::endl;
  timer.Stop();
}
void PomoTimeFrame::OnSkip(wxCommandEvent& event) {
  std::cout << "Skip button clicked!" << std::endl;
  cycle.SetNextTask();
  Task currentTask = cycle.GetCurrentTask();
  SetCurrTaskTimeInSeconds();
  timeRemainingDisplay->SetLabel(GetTimeRemaining());
}


void PomoTimeFrame::SetCurrTaskTimeInSeconds() {
  Task currentTask = cycle.GetCurrentTask();
  timeRemainingInSeconds = taskToTimeInMinutes[currentTask] * 60;
}

std::string PomoTimeFrame::GetTimeRemaining() {
  int minutes = timeRemainingInSeconds / 60;
  int seconds = timeRemainingInSeconds % 60;

  std::stringstream rv;
  rv << minutes << ":" << std::setfill('0') << std::setw(2) << seconds;
  return rv.str();
}


void PomoTimeFrame::UpdateDisplayedTime() {
  if (timer.IsRunning()) {
    timeRemainingInSeconds--;
  }
  timeRemainingDisplay->SetLabel(GetTimeRemaining());
}

void PomoTimeFrame::OnUpdateDisplayedTime(wxTimerEvent& event) {
  if (timeRemainingInSeconds > 0) {
    UpdateDisplayedTime();
  } else {
    // TODO: add sound functionality
    timer.Stop();
  }
}

void PomoTimeFrame::OnExit(wxCommandEvent& event) {
  Close(true);
};

void PomoTimeFrame::OnAbout(wxCommandEvent& event) {
  wxMessageBox("cindy's first C++ project!", "about pomo time", wxOK | wxICON_INFORMATION);
};


class PomoTime : public wxApp {
  public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(PomoTime);

// opens the app
bool PomoTime::OnInit() {
  PomoTimeFrame *frame = new PomoTimeFrame();
  frame->Show(true);
  
  return true;
};
