#include <wx/wxprec.h>

#ifndef WX_PRECOMP
  #include <wx/wx.h>
  #include <wx/datetime.h>
  #include "wx/sound.h"
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
    wxStaticText* currTaskDisplay;
    wxTimer timer;
    
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnStart(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnSkip(wxCommandEvent& event);
    void OnUpdateDisplayedTime(wxTimerEvent& event);
    void UpdateDisplayedTime();
    void SetCurrTaskTimeInSeconds();
    std::string GetTimeRemaining();
    void SetCurrTaskDisplay();
    void UpdateTask();
};

PomoTimeFrame::PomoTimeFrame(): wxFrame(nullptr, wxID_ANY, "pomo 🍅 time", wxPoint(-1, -1),  wxSize(400, 200), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN) {

  // MENU BAR STUFF
  wxMenu* menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  wxMenuBar* menuBar = new wxMenuBar;
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar( menuBar );

  // APP

  wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 150));
  wxPanel* bottomPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(400, 50));

  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* verticalButtonSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* horizontalButtonSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* verticalTextSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* horizontalCurrTaskSizer = new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* horizontalTimeRemainingSizer = new wxBoxSizer(wxHORIZONTAL);

  sizer->Add(topPanel, 2, wxEXPAND | wxALL);
  sizer->Add(bottomPanel, 0, wxEXPAND | wxALL);

  this->SetSizerAndFit(sizer);

  wxFont font;

  std::string defaultLabel = "25:00";
  currTaskDisplay = new wxStaticText(topPanel, wxID_ANY, "pomodoro", wxDefaultPosition, wxSize(200, 20), wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
  font.MakeBold();
  currTaskDisplay->SetFont(font);
  currTaskDisplay->SetForegroundColour(wxColor(*wxWHITE));
  SetCurrTaskDisplay();

  timeRemainingDisplay = new wxStaticText(topPanel, wxID_ANY, defaultLabel, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
  font = timeRemainingDisplay->GetFont();
  font.MakeBold().Scale(3.0);
  timeRemainingDisplay->SetForegroundColour(wxColor(*wxWHITE));
  timeRemainingDisplay->SetFont(font);
  SetCurrTaskTimeInSeconds();
  UpdateDisplayedTime();

  horizontalCurrTaskSizer->Add(currTaskDisplay);
  horizontalTimeRemainingSizer->Add(timeRemainingDisplay);
  
  wxButton *playButton = new wxButton(bottomPanel, BUTTON_start, wxT("start"));
  wxButton *stopButton = new wxButton(bottomPanel, BUTTON_stop, wxT("stop"));
  wxButton *skipButton = new wxButton(bottomPanel, BUTTON_skip, wxT("skip"));

  horizontalButtonSizer->Add(playButton);
  horizontalButtonSizer->Add(stopButton);
  horizontalButtonSizer->Add(skipButton);

  verticalTextSizer->Add(horizontalCurrTaskSizer, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER | wxTOP, 30);
  verticalTextSizer->Add(horizontalTimeRemainingSizer, 2, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);
  verticalButtonSizer->Add(horizontalButtonSizer, 0,  wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER);

  topPanel->SetSizer(verticalTextSizer);
  bottomPanel->SetSizer(verticalButtonSizer);

  // EVENTS

  Bind(wxEVT_MENU, &PomoTimeFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &PomoTimeFrame::OnExit, this, wxID_EXIT);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnStart, this, BUTTON_start);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnStop, this, BUTTON_stop);
  Bind(wxEVT_BUTTON, &PomoTimeFrame::OnSkip, this, BUTTON_skip);
  timer.Bind(wxEVT_TIMER, &PomoTimeFrame::OnUpdateDisplayedTime, this);

};

void PomoTimeFrame::OnStart(wxCommandEvent& event) {
  wxSound("./assets/click.wav").Play(wxSOUND_ASYNC);
  timer.Start(1000);
  UpdateDisplayedTime();
}

void PomoTimeFrame::OnStop(wxCommandEvent& event) {
  wxSound("./assets/click.wav").Play(wxSOUND_ASYNC);
  timer.Stop();
}

void PomoTimeFrame::OnSkip(wxCommandEvent& event) {
  wxSound("./assets/click.wav").Play(wxSOUND_ASYNC);
  timer.Stop();
  UpdateTask();
}

void PomoTimeFrame::SetCurrTaskDisplay(){
  std::string currTaskName = cycle.GetCurrentTaskName();
  currTaskDisplay->SetLabel(currTaskName);
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

void PomoTimeFrame::UpdateTask() {
  cycle.SetNextTask();
  SetCurrTaskDisplay();
  SetCurrTaskTimeInSeconds();
  timeRemainingDisplay->SetLabel(GetTimeRemaining());
}

void PomoTimeFrame::OnUpdateDisplayedTime(wxTimerEvent& event) {
  if (timeRemainingInSeconds > 0) {
    UpdateDisplayedTime();
  } else {
    timer.Stop();
    wxSound("./assets/tone.wav").Play(wxSOUND_ASYNC);
    UpdateTask();
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
  frame->SetBackgroundColour(wxColor(222, 100, 91));
  frame->Show(true);
  
  return true;
};
