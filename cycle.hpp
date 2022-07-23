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

    Task getCurrentTask();
    void setNextTask();

  private:
    Node* head = nullptr;
    Node* end = nullptr;
    Node* currTask = nullptr;

    void insertNode(Node *&curr, Task data);
};

#endif