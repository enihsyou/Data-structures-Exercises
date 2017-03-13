//
// Created by Shane on 2017/3/9.
//

#ifndef NO1_SEQUENTIAL_LIST_H
#define NO1_SEQUENTIAL_LIST_H
#include <iostream>
template<class T>
class sequential_list {
 public:
  sequential_list(const int capacity = 0) : size_(0), capacity_(capacity), list_(nullptr) {}
  bool put(const T data);
  bool del(const int index);
  /*Return one of data's index*/
  int search(const T data);
  void print() const;
  inline int size() const { return size_; }
  inline int capacity() const { return capacity_; }
  virtual ~sequential_list();

 private:
  int size_;
  int capacity_;
  T *list_;

  void resize(const int new_size);
  void offset(const int start, const int end, const int offset = 1);
  bool put(const T data, const int where);
  int search(const T data, const int lo, const int hi);
  int insert_place(const T target);
};

template<class T>
void sequential_list<T>::offset(const int start, const int end, const int offset) {
  if (size_ + offset > capacity_)resize(2 * capacity_ + 1);
  if (offset > 0) {
    for (int i = end; i > start; --i) {
      list_[i] = list_[i - offset];
    }
  } else {
    for (int i = start; i < end; ++i) {
      list_[i] = list_[i - offset];
    }
  }
}
template<class T>
void sequential_list<T>::resize(const int new_size) {
  auto new_location = new T[new_size];
  auto pointer = list_;
  auto new_pointer = new_location;
  for (int i = 0; i < size_; ++i) {
    *new_pointer = *pointer;
    ++pointer;
    ++new_pointer;
  }
  delete[] list_;
  list_ = new_location;
  capacity_ = new_size;
}
template<class T>
void sequential_list<T>::print() const {
  std::cout << "List size: " << size_ << std::endl;
  for (int i = 0; i < size_; ++i) {
    std::cout << list_[i] << " ";
  }
  std::cout << std::endl;
}
template<class T>
int sequential_list<T>::search(const T data, const int lo, const int hi) {
  if (lo > hi) return -1;
  int mid = (lo + hi) / 2;
  if (list_[mid] > data) {
    return search(data, lo, mid - 1);
  } else if (list_[mid] < data) {
    return search(data, mid + 1, hi);
  } else { return mid; }
}
template<class T>
int sequential_list<T>::insert_place(const T target) {
  /*Find the one which is smaller than *data*.*/
  int start = 0, end = size_ - 1;
  while (start <= end) {
    auto mid = (start + end) / 2;
    if (target < list_[mid]) {
      end = mid - 1;
    } else if (target > list_[mid]) {
      start = mid + 1;
    } else {
      return mid;
    }
  }
  while (start < size() && list_[start] < target) start++;
  return start;
}
template<class T>
bool sequential_list<T>::del(const int index) {
  if (index < 0 || index > size_)return false;
  offset(index, size_ - 1, -1);
  size_--;
  return true;
}
template<class T>
bool sequential_list<T>::put(const T data) {
  if (size_ == 0) return put(data, 0);
  return put(data, insert_place(data));
}
template<class T>
bool sequential_list<T>::put(const T data, const int where) {
  if (where < 0 || where > size_) return false;
  if (size_ >= capacity_) resize(2 * capacity_ + 1);
  offset(where, size_);
  list_[where] = data;
  size_++;
  return true;
}
template<class T>
sequential_list<T>::~sequential_list() {
  delete[] list_;
}
template<class T>
int sequential_list<T>::search(const T data) {
  return search(data, 0, size_ - 1);
}
#endif //NO1_SEQUENTIAL_LIST_H
