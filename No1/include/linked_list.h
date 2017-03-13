//
// Created by Shane on 2017/3/8.
//

#ifndef NO1_LINKED_LIST_H
#define NO1_LINKED_LIST_H
#include "node.h"
#include <iostream>

template<class T>
class linked_list {
 public:
  linked_list() : size_(0), start_(nullptr) {}
  /*Deep copy*/
  linked_list(const linked_list<T> &a);
  /*Assuming that a & b are in ascending order, merge a & b into this, in descending order*/
  linked_list(const linked_list<T> &a, const linked_list<T> &b);
  linked_list(linked_list<T> &a, linked_list<T> &b);
  bool insert(const T data);
  /*
 * Insert item into the i-th place, start_ from 0
 *  |o|o|o|o|
 *  ^ ^ ^ ^ ^
 *  0 1 2 3 4
 *
 * */
  bool insert(const T data, const int where);
  bool remove();
  bool remove(const node<T> &mink, const node<T> &maxk);
  /*
  * remove the i-th item, count start_ from 0
  *  |o|o|o|o|
  *   ^ ^ ^ ^
  *   0 1 2 3
  *
  * */
  bool remove(const int where);
  void print() const;
  inline bool is_empty() const { return size_ == 0; }
  /*search for key from head to tail, return the first occurrence*/
  int where(const int key) const;
  void reverse();
  inline int size() const { return size_; }
  inline node<T> *start() const { return start_; }
  inline void set_start(node<T> *start) { start_ = start; }
 private:
  int size_;
  node<T> *start_;
  /*return a pointer, which point to the i-th item, [0, N)*/
  node<T> *moveTo(const int index) const;
};

template<class T>
linked_list<T>::linked_list(const linked_list<T> &a) {
  start_ = a.start_;
  size_ = a.size();
  auto ptr = a.start_;
  auto next = start_;

  while (ptr->next_node()) {
    auto new_node = new node<T>(ptr->data());
    next->set_next_node(new_node);
  }
}
template<class T>
linked_list<T>::linked_list(const linked_list<T> &a, const linked_list<T> &b)
    : size_(0), start_(nullptr) {
  int N1 = 0, N2 = 0;
  node<T> *p1, *p2;
  while (N1 < a.size() && N2 < b.size()) {
    p1 = a.moveTo(N1);
    p2 = b.moveTo(N2);

    if (*p1 < *p2) {
      insert(p1->data());
      N1++;
    }
    else {
      insert(p2->data());
      N2++;
    }
  }
  while (N1 < a.size()) {
    p1 = a.moveTo(N1);
    insert(p1->data());
    N1++;
  }
  while (N2 < b.size()) {
    p2 = b.moveTo(N2);
    insert(p2->data());
    N2++;
  }
}
template<class T>
linked_list<T>::linked_list(linked_list<T> &a, linked_list<T> &b)
    : size_(a.size() + b.size()), start_(nullptr) {
  node<T> *p1 = a.start(), *p2 = b.start();
  node<T> *tmp_ptr;
  while (p1 && p2) {
    if (*p1 < *p2) {
      tmp_ptr = p1->next_node();
      p1->set_next_node(start_);
      start_ = p1;
      p1 = tmp_ptr;
    } else {
      tmp_ptr = p2->next_node();
      p2->set_next_node(start());
      start_ = p2;
      p2 = tmp_ptr;
    }
  }
  while (p1) {
    tmp_ptr = p1->next_node();
    p1->set_next_node(start_);
    start_ = p1;
    p1 = tmp_ptr;
  }
  while (p2) {
    tmp_ptr = p2->next_node();
    p2->set_next_node(start_);
    start_ = p2;
    p2 = tmp_ptr;
  }
}
template<class T>
bool linked_list<T>::insert(const T data) {
  auto new_start = new node<T>(data, start());
  set_start(new_start);

  size_++;
  return true;
}
template<class T>
bool linked_list<T>::insert(const T data, const int where) {
  if (where > size() || where < 0) return false;
  if (where == 0) {
    insert(data);
    return true;
  }

  auto next_item = start_;
  auto count = 1;
  while (count < where) { //&& next_item->next != nullptr) {
    next_item = next_item->next_node();
    count++;
  }

  auto new_item = new node<T>(data, next_item->next_node());
  next_item->set_next_node(new_item);

  size_++;
  return true;
}
template<class T>
bool linked_list<T>::remove() {
  if (size() < 1 || !start_->next_node()) return false;

  auto old_start = start_;
  set_start(old_start->next_node());
  delete old_start;

  size_--;
  return true;
}
template<class T>
bool linked_list<T>::remove(const int where) {
  if (where >= size() || where < 0) return false;
  if (where == 0) {
    remove();
    return true;
  }

  auto next_item = start_;
  auto count = 1;
  while (count < where) { //&& next_item->next != nullptr) {
    next_item = next_item->next_node();
    count++;
  }
  auto deleted = next_item->next_node();
  if (where == size() - 1) next_item->set_next_node(nullptr);
  else next_item->set_next_node(next_item->next_node()->next_node());
  delete deleted;

  size_--;
  return true;
}
template<class T>
void linked_list<T>::print() const {
  auto next = start_;
  std::cout << size() << " items in the list" << std::endl;
  while (next) {
    std::cout << next->data() << " ";
    next = next->next_node();
  }
  std::cout << std::endl;
}
template<class T>
int linked_list<T>::where(const int key) const {
  auto next = start();
  auto count = 0;
  while (next && next->data() != key) {
    next = next->next_node();
    count++;
  }
  if (count == size())return -1;
  return count;
}
template<class T>
void linked_list<T>::reverse() {
  if (size() < 2) return;  // no more need to do
  auto ptr = start(); // now processing
  auto head = start();
  auto next_node = head->next_node(); // act as temp variable
  ptr->set_next_node(nullptr);
  while (next_node) {
    head = next_node;
    next_node = next_node->next_node();
    head->set_next_node(ptr);
    ptr = head;
  }
  set_start(head);

//  auto new_start = moveTo(size() - 1);
//  auto now_item = new_start;
//  for (auto i = size() - 2; i >= 0; --i) {
//    now_item->set_next_node(moveTo(i));
//    now_item = now_item->next_node();
//  }
//  now_item->next_node();
//  set_start(new_start);
}
template<class T>
node<T> *linked_list<T>::moveTo(const int index) const {
  if (index < 0 || index >= size())return nullptr;
  auto pointer = start();
  int counter = 0;
  while (counter < index) {
    pointer = pointer->next_node();
    counter++;
  }
  return pointer;
}
template<class T>
bool linked_list<T>::remove(const node<T> &mink, const node<T> &maxk) {
  auto ptr = start_;
  while (ptr->next_node() && *(ptr->next_node()) < const_cast<node<T> &>(mink)) {
    ptr = ptr->next_node();
  }
  auto ptr_e = ptr;
  auto count = 0;
  while (ptr_e->next_node() && *(ptr_e->next_node()) < const_cast<node<T> &>(maxk)) {
    ptr_e = ptr_e->next_node();
    count++;
  }
  ptr->set_next_node(ptr_e->next_node());
  size_ -= count;
}

#endif //NO1_LINKED_LIST_H
