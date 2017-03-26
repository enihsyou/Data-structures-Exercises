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
   * \brief ��ջ��Ԫ�ز��뵽����ͷ��
   * \param data ���������
   */
  void Push(const T data);
  /**
   * \brief ��ջ���Ƴ�ջ��Ԫ�ز�����
   * \return ������ջ����Ԫ������
   */
  T Pop();
  /**
   * \brief �鿴ջ��Ԫ�����ݣ���������
   * \return ջ��Ԫ��
   */
  T Peek() const;

  int size() const { return size_; }

  bool EmptyQ() const { return first_ == nullptr; };

  friend std::ostream& operator<<(std::ostream& os, const Stack& obj) {
    auto size = obj.size(); 
    os << "Size: " << size;
    if (size > 0) os << "\nDatum: " << std::endl; // �ǿ�ջ��������
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
  if (EmptyQ()) throw std::underflow_error("��ջΪ��");
  T item = first_->data();
  auto old_first = first_;
  first_ = old_first->next_node();
  delete old_first;
  size_--;
  return item;
}

template <class T>
T Stack<T>::Peek() const {
  if (EmptyQ())throw std::underflow_error("��ջΪ��");
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
