#include <iostream>
#include <string>
#include "cycle.hpp"

PomoCycle::PomoCycle() {
  insertNode(head, 'p');
  Node* curr = head;
  insertNode(curr, 's');
  insertNode(curr, 'p');
  insertNode(curr, 's');
  insertNode(curr, 'p');
  insertNode(curr, 's');
  insertNode(curr, 'p');
  insertNode(curr, 's');
  insertNode(curr, 'p');
  insertNode(curr, 'l');

  currTask = head;
};

PomoCycle::~PomoCycle() {
  while (head != end) {
    Node* temp = head;
    head = head->next;
    delete temp;
  }

  delete head;
};

char PomoCycle::getCurrentTask() {
  std::cout << "curr task: " << currTask->data << std::endl;
  return currTask->data;
};

void PomoCycle::setNextTask() {
  currTask = currTask->next;
};

void PomoCycle::insertNode(Node *&curr, char data) {
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

// TODO: for debug only
int main () {
  PomoCycle c = PomoCycle();

  for (int i=0; i<21; i++) {
    c.getCurrentTask();
    c.setNextTask();
  }
};