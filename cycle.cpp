#include <iostream>
#include <string>
#include "cycle.hpp"

class PomoCycle {
  public:

    PomoCycle() {
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

    ~PomoCycle() {
      // delete the CLL
      while (head != end) {
        Node* temp = head;
        head = head->next;
        delete temp;
      }

      delete head;
    };

    char getCurrentTask() {
      std::cout << "curr task: " << currTask->data << std::endl;
      return currTask->data;
    }

    void setNextTask() {
        currTask = currTask->next;
    }

    private:
      Node* head = nullptr;
      Node* end = nullptr;
      Node* currTask = nullptr;

      void insertNode(Node *&curr, char data) {
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

      }
};

