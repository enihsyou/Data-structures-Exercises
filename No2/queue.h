//
// Created by enihsyou on 17/03/21.
//

#ifndef NO2_QUEUE_H
#define NO2_QUEUE_H
#include <iosfwd>
#include "node.h"
template<class T>
class queue {
 private:
  int size_;
  T *datum_;
  int front_;
  int rear_;
 public:
  queue(int size) : size_{0}, front_{0}, rear_{0} { datum_ = new T[size]; }
  virtual ~queue();
  bool is_empty() const { return size_ == 0; };
  int size() const { return size_; }
  T peek() const;
  void enqueue(const T data);
  T dequeue();
  friend std::ostream &operator<<(std::ostream &ostream, const queue q);
};
template<class T>
void queue::enqueue(const T data) {
  if ((rear_ - front_) % size_ == 0) return;// full
  datum_[++rear_] = data;
}
template<class T>
queue::~queue() {
  delete datum_[];
}
template<class T>
T queue::peek() const {

  return nullptr;
}
#endif //NO2_QUEUE_H
