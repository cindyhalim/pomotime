#include <iostream>
#include <string>
#include "cycle.hpp"

PomoCycle::PomoCycle() {
  InsertNode(head, POMODORO);
  Node* curr = head;
  InsertNode(curr, SHORT_BREAK);
  InsertNode(curr, POMODORO);
  InsertNode(curr, SHORT_BREAK);
  InsertNode(curr, POMODORO);
  InsertNode(curr, SHORT_BREAK);
  InsertNode(curr, POMODORO);
  InsertNode(curr, SHORT_BREAK);
  InsertNode(curr, POMODORO);
  InsertNode(curr, LONG_BREAK);

};

PomoCycle::~PomoCycle() {
  while (head != end) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }

  delete head;
};

Task PomoCycle::GetCurrentTask() {
  return head->data;
};

std::string PomoCycle::GetCurrentTaskName() {
  switch (GetCurrentTask()) {
    case 0:
      return "pomodoro";
    case 1:
      return "short break";
    case 2:
      return "long break";
    default:
      std::cout << "Task not found" << std::endl;
      return "";
  }
};

void PomoCycle::SetNextTask() {
  head = head->next;
};

void PomoCycle::InsertNode(Node *&curr, Task data) {
  if (head == nullptr) {
    head = new Node;
    head->data = data;
    head->next = head;
    end = head;
  } else {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = end;

    curr->next = newNode;
    curr = newNode;
  }
};