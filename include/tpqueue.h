// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

struct SYM {
  char ch;
  int prior;
};

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& data) : data(data), next(nullptr) {}
  };

  Node* head;

 public:

  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    Node* currentt = head;
    while (currentt) {
      Node* tempp = currentt;
      currentt = currentt->next;
      delete tempp;
    }
  }

  void push(const T& value) {
    Node* newNode = new Node(value);
    if (!head || value.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
    } else {
      Node* currentt = head;
      while (currentt->next && value.prior <= currentt->next->data.prior) {
        currentt = currentt->next;
      }
      newNode->next = currentt->next;
      currentt->next = newNode;
    }
  }

  T pop() {
    if (!head) {
      throw std::out_of_range("Queue is empty!!");
    }
    Node* tempp = head;
    T result = head->data;
    head = head->next;
    delete tempp;
    return result;
  }
};

#endif  // INCLUDE_TPQUEUE_H_
