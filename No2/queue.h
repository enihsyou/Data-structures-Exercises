//
// Created by enihsyou on 17/03/21.
//

#ifndef NO2_QUEUE_H
#define NO2_QUEUE_H
#include <ostream>
#include <stdexcept>
#include <queue>

template <class T>
class Queue {
public:
  /**
   * \brief ��ʼ��ѭ�����У�front_��rear_��������ָʾ����λ�ã�����(-1)��������
   * \param capacity ������������������������ʼ��1��С����
   */
  explicit Queue(int const capacity) : capacity_{capacity > 0 ? capacity : 1}, front_{0}, rear_{-1}, datum_{new T[capacity]} { }

  virtual ~Queue() { delete[] datum_; }

  void Enqueue(const T data);
  T Dequeue();
  T Peek() const;

  bool EmptyQ() const { return rear_ < 0; }
  bool FullQ() const { return rear_ >= 0 && (rear_ + 1) % capacity_ == front_; }
  int Size() const { return rear_ < 0 ? 0 : (rear_ - front_) % capacity_ + 1; }

  int capacity() const { return capacity_; }

  friend std::ostream& operator<<(std::ostream& os, const Queue& obj) {
    auto size = obj.Size();
    os << "Size: " << size;
    if (size > 0) os << "\nDatum: " << std::endl;
    else return os;

    int ptr = obj.front_;
    while (ptr % obj.capacity_ != obj.rear_) {
      os << obj.datum_[ptr] << " ";
      ptr++;
    }
    return os << obj.datum_[ptr] << std::endl;
  }

private:
  int const capacity_;
  int front_;
  int rear_;
  T* const datum_;
};

template <class T>
void Queue<T>::Enqueue(const T data) {
  if (FullQ()) throw std::overflow_error("��������"); // Full
  rear_ = rear_ < 0 ? front_ : (rear_ + 1) % capacity_;
  datum_[rear_] = data;
}

template <class T>
T Queue<T>::Dequeue() {
  if (EmptyQ()) throw std::underflow_error("����Ϊ��"); // Empty
  T data = datum_[front_];
  front_ = (front_ + 1) % capacity_;
  if (front_ == rear_) { rear_ = -1; }
  return data;
}

template <class T>
T Queue<T>::Peek() const {
  if (EmptyQ()) throw std::underflow_error("����Ϊ��"); // Empty
  return datum_[front_];
}

#endif //NO2_QUEUE_H
