
#ifndef WX_PRECOMP
  #include <wx/wx.h>
  #include <wx/datetime.h>
  #include "wx/sound.h"
#endif
#include "cycle.hpp"

#ifndef MAIN_H
  #define MAIN_H

  enum {
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


  class PomoTime : public wxApp {
    public:
      virtual bool OnInit();
  };

#endif