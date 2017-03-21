//
// Created by Shane on 2017/3/8.
//

#ifndef NO1_LINKED_LIST_H
#define NO1_LINKED_LIST_H
#include "node.h"
#include <iostream>

template <class T>
class linked_list {
public:
  linked_list() : size_(0), start_(nullptr) {}
  linked_list(const linked_list<T>& a);
  linked_list(linked_list<T>& a, linked_list<T>& b);
  virtual ~linked_list();
  int insert(const T data);
  void remove(const int where);
  void remove(const T mink, const T maxk);
  void reverse();
  int where(const T key) const;
  void print() const;
  bool is_empty() const { return size_ == 0; }
  int size() const { return size_; }
  node<T>* start() const { return start_; }
  void set_start(node<T>* start) { start_ = start; }
private:
  int size_;
  node<T>* start_;
};

/**
 * \brief Deep copy
 * \param a Another list
 */
template <class T>
linked_list<T>::linked_list(const linked_list<T>& a) {
  start_ = a.start_;
  size_ = a.size_;
  node<T>* ptr = a.start_;

  while (ptr->next_node()) {
    insert(ptr->data());
    ptr = ptr->next_node();
  }
}

/**
 * \brief 假设列表a和b是递增排列的单链表，合并成一个递减的单列表，利用a和b的数据空间
 * \param a 列表a
 * \param b 列表b
 */
template <class T>
linked_list<T>::linked_list(linked_list<T>& a, linked_list<T>& b)
  : size_(0), start_(nullptr) {
  node<T> *p1 = a.start(), *p2 = b.start();

  while (p1 && p2) {
    node<T>* old = start_;
    if (*p1 < *p2) {
      start_ = p1;
      p1 = p1->next_node();
      start_->set_next_node(old);
    } else {
      start_ = p2;
      p2 = p2->next_node();
      start_->set_next_node(old);
    }
  }

  while (p1) {
    node<T>* old = start_;
    start_ = p1;
    p1 = p1->next_node();
    start_->set_next_node(old);
  }
  while (p2) {
    node<T>* old = start_;
    start_ = p2;
    p2 = p2->next_node();
    start_->set_next_node(old);
  }
}

/**
 * \brief 在第i个位置插入数据，从零开始计数，递增排序
 *  |o|o|o|o|
 *  ^ ^ ^ ^ ^
 *  0 1 2 3 4
 * \param data 要插入的数据
 * \return 插入的位置
 */
template <class T>
int linked_list<T>::insert(const T data) {
  int count = 0;
  node<T>* ptr = start_;
  while (ptr) {
    count++;
    if (!ptr->next_node() || data < ptr->next_node()->data()) break;
    ptr = ptr->next_node();
  }
  node<T>* new_node = new node<T>(data, nullptr);
  if (ptr) new_node->set_next_node(ptr->next_node());
  if (!start_) start_ = new_node;
  else ptr->set_next_node(new_node);

  size_++;
  return count;
}

/**
 * \brief 移除第i个元素
 *  |o|o|o|o|
 *   ^ ^ ^ ^
 *   0 1 2 3
 * \return
 */
template <class T>
void linked_list<T>::remove(const int where) {
  if (where >= size_ || where < 0) return;
  if (where == 0) {
    if (size_ > 0) start_ = start_->next_node();
    return;
  }
  node<T>* ptr = start_;
  int count = 1;
  while (count < where) { // 停在前一个节点
    ptr = ptr->next_node();
    count++;
  }

  node<T>* old_node = ptr->next_node();
  ptr->set_next_node(ptr->next_node()->next_node());
  delete old_node;

  size_--;
}

/**
 * \brief 删除范围内的数据，假设内容可比较
 * \param mink 删除下限
 * \param maxk 删除上限
 */
template <class T>
void linked_list<T>::remove(const T mink, const T maxk) {
  node<T>* ptr = start_;
  while (ptr->next_node() && ptr->next_node()->data() < mink) {
    ptr = ptr->next_node();
  }
  node<T>* ptr_e = ptr;
  int count = 0;
  while (ptr_e->next_node() && ptr_e->next_node()->data() < maxk) {
    ptr_e = ptr_e->next_node();
    count++;
  }
  ptr->set_next_node(ptr_e->next_node());
  size_ -= count;
}

/**
 * \brief 寻找元素的位置，-1表示未找到
 * \param key 寻找的元素
 * \return 元素的位置
 */
template <class T>
int linked_list<T>::where(const T key) const {
  node<T>* processing = start_;
  auto count = 0;
  while (processing && processing->data() != key) {
    processing = processing->next_node();
    count++;
  }
  if (count == size_) return -1;
  return count;
}

/**
 * \brief 对单链表实现就地逆置
 */
template <class T>
void linked_list<T>::reverse() {
  if (size_ < 2) return; // no more need to do
  auto ptr = start_; // now processing
  auto head = start_;
  auto next_node = head->next_node(); // act as temp variable
  ptr->set_next_node(nullptr);
  while (next_node) {
    head = next_node;
    next_node = next_node->next_node();
    head->set_next_node(ptr);
    ptr = head;
  }
  set_start(head);
}

template <class T>
void linked_list<T>::print() const {
  auto next = start_;
  std::cout << "List size: " << size_ << std::endl;
  while (next) {
    std::cout << next->data() << " ";
    next = next->next_node();
  }
  std::cout << std::endl;
}
template<class T>
linked_list::~linked_list() {
  while (start_){
    auto old_node = start_;
    delete start_;
    start_ = old_node;
  }
}
#endif //NO1_LINKED_LIST_H
