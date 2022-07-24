#include <string>
#ifndef cycle_H
  #define cycle_H

  enum Task {
    POMODORO,
    SHORT_BREAK,
    LONG_BREAK,
  };

  struct Node 
  {
    Task data;
    struct Node *next;
  };


  class PomoCycle {
    public:
      PomoCycle();
      ~PomoCycle();

      Task GetCurrentTask();
      std::string GetCurrentTaskName();
      void SetNextTask();

    private:
      Node* head = nullptr;
      Node* end = nullptr;

      void InsertNode(Node *&curr, Task data);
  };

#endif