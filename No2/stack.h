//
// Created by enihsyou on 17/03/21.
//

#ifndef NO2_STACK_H
#define NO2_STACK_H
#include <ostream>
#include "node.h"
template<class T>
class stack {
 private:
  node<T> *first_;
  int size_;
 public:
  stack() : first_{nullptr}, size_{0} {}
  void push(const T data);
  virtual ~stack();
  T pop();
  T peak() const;
  int size() const {
    return size_;
  }
  bool is_empty() const { return first_ == nullptr; };
  friend std::ostream &operator<<(std::ostream &ostream, const stack &s);
};
template<class T>
void stack::push(const T data) {
  auto old_first = first_;
  first_ = new node<T>(data, old_first);
  size_++;
  delete old_first;
}
template<class T>
T stack::pop() {
  if (is_empty()) return nullptr;
  T item = first_->data();
  first_ = first_->next_node();
  size_--;
  return item;
}
template<class T>
T stack::peak() const {
  if (is_empty()) return nullptr;
  return first_->data();
}
template<class T>
std::ostream &operator<<(std::ostream &ostream, const stack &s) {
  return <#initializer#>;
}
template<class T>
stack::~stack() {
  while (first_) {
    auto n = first_;
    first_ = first_->next_node();
    delete n;
  }
}

#endif //NO2_STACK_H
