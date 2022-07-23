#ifndef cycle_H
#define cycle_H

struct Node 
{
  char data;
  struct Node *next;
};


class PomoCycle {
  public:
    PomoCycle();
    ~PomoCycle();

    char getCurrentTask();
    void setNextTask();

  private:
    Node* head = nullptr;
    Node* end = nullptr;
    Node* currTask = nullptr;

    void insertNode(Node *&curr, char data);
};

#endif