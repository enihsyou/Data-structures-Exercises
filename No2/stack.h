//
// Created by enihsyou on 17/03/21.
//

#ifndef NO2_STACK_H
#define NO2_STACK_H
#include <ostream>
#include "node.h"

template <class T>
class Stack {
public:
  Stack() : first_{nullptr}, size_{0} {}
  virtual ~Stack();
  /**
   * \brief 入栈，元素插入到链表头部
   * \param data 插入的数据
   */
  void Push(const T data);
  /**
   * \brief 弹栈，移除栈顶元素并返回
   * \return 弹出的栈顶的元素内容
   */
  T Pop();
  /**
   * \brief 查看栈顶元素内容，但不弹出
   * \return 栈顶元素
   */
  T Peek() const;

  int size() const { return size_; }

  bool EmptyQ() const { return first_ == nullptr; };

  friend std::ostream& operator<<(std::ostream& os, const Stack& obj) {
    auto size = obj.size(); 
    os << "Size: " << size;
    if (size > 0) os << "\nDatum: " << std::endl; // 非空栈继续操作
    else return os << std::endl;

    node<T>* ptr = obj.first_;
    while (ptr) {
      os << ptr->data() << " ";
      ptr = ptr->next_node();
    }
    return os << std::endl;
  }

private:
  node<T>* first_;
  int size_;
};

template <class T>
void Stack<T>::Push(const T data) {
  first_ = new node<T>(data, first_);
  size_++;
}

template <class T>
T Stack<T>::Pop() {
  if (EmptyQ()) throw std::underflow_error("堆栈为空");
  T item = first_->data();
  auto old_first = first_;
  first_ = old_first->next_node();
  delete old_first;
  size_--;
  return item;
}

template <class T>
T Stack<T>::Peek() const {
  if (EmptyQ())throw std::underflow_error("堆栈为空");
  return first_->data();
}

template <class T>
Stack<T>::~Stack() {
  while (first_) {
    auto n = first_;
    first_ = first_->next_node();
    delete n;
  }
}

#endif //NO2_STACK_H
