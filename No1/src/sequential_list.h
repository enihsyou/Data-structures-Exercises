//
// Created by Shane on 2017/3/9.
//

#ifndef NO1_SEQUENTIAL_LIST_H
#define NO1_SEQUENTIAL_LIST_H
#include <iostream>

template <class T>
class sequential_list {
public:
  explicit sequential_list(const int capacity = 0) : size_(0), capacity_(capacity), list_(nullptr) {}

  bool put(const T data);
  bool del(const int index);
  int search(const T data);
  void print() const;

  int size() const { return size_; }
  int capacity() const { return capacity_; }
  virtual ~sequential_list();

private:
  void resize(const int new_size);
  bool put(const T data, const int where);

  int insert_place(const T target);

  int size_;
  int capacity_;
  T* list_;
};


template <class T>
bool sequential_list<T>::put(const T data) {
  if (size_ == 0) return put(data, 0);
  return put(data, insert_place(data));
}

/**
 * \brief 在第i个位置插入数据，从零开始计数
 *  |o|o|o|o|
 *  ^ ^ ^ ^ ^
 *  0 1 2 3 4
 * \param data 插入的数据
 * \param where 插入的位置
 * \return 是否插入成功
 */
template <class T>
bool sequential_list<T>::put(const T data, const int where) {
  if (where < 0 || where > size_) return false;
  if (size_ + 1 >= capacity_) resize(2 * capacity_ + 1);
  /*移动后面的元素，一个位置*/
  for (int i = size_; i > where; --i) {
    list_[i] = list_[i - 1];
  }
  list_[where] = data;
  size_++;
  return true;
}

template <class T>
bool sequential_list<T>::del(const int where) {
  if (where < 0 || where > size_) return false;
  /*后面的元素向前移动，一个位置*/
  for (int i = where; i < size_ - 1; ++i) {
    list_[i] = list_[i + 1];
  }
  size_--;
  return true;
}

/**
 * \brief 将现有的空间扩容，复制数据
 * \param new_size 新的列表容量
 */
template <class T>
void sequential_list<T>::resize(const int new_size) {
  auto new_location = new T[new_size];
  auto old_pointer = list_;
  auto new_pointer = new_location;
  for (int i = 0; i < size_; ++i) {
    *new_pointer = *old_pointer;
    ++old_pointer;
    ++new_pointer;
  }
  delete[] list_;
  list_ = new_location;
  capacity_ = new_size;
}

template <class T>
void sequential_list<T>::print() const {
  std::cout << "List size: " << size_ << std::endl;
  for (int i = 0; i < size_; ++i) {
    std::cout << list_[i] << " ";
  }
  std::cout << std::endl;
}

/**
* \brief 二分法搜寻位置
* \param data 寻找的对象内容
* \return 对象的位置，-1代表未找到
*/
template <class T>
int sequential_list<T>::search(const T data) {
  int left = 0, right = size_ - 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (list_[mid] > data) {
      right = mid - 1;
    } else if (list_[mid] < data) {
      left = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

/**
 * \brief 寻找应该在哪里插入元素
 * \param target 打算插入的元素
 * \return 插入位置
 */
template <class T>
int sequential_list<T>::insert_place(const T target) {
  /*Find the one which is smaller than *data*.*/
  int start = 0, end = size_ - 1;
  while (start <= end) { // 二分搜索
    int mid = (start + end) / 2;
    if (target < list_[mid]) {
      end = mid - 1;
    } else if (target > list_[mid]) {
      start = mid + 1;
    } else {
      return mid; // 有相同元素，在左边插入（其实无影响
    }
  }
  /*未找到相同元素，start指针停留在更小的元素那边，向后移动直到遇到更大的 或者列表结尾*/
  while (start < size_ && list_[start] < target) start++;
  return start;
}

template <class T>
sequential_list<T>::~sequential_list() {
  delete[] list_;
}
#endif //NO1_SEQUENTIAL_LIST_H
