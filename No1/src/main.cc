#include <iostream>
#include "../include/linked_list.h"

template<class T>
class SequentialList {
 private:
  int size;
  int capacity;
  T *list;

  void resize(int new_size) {
    T *new_location = new T[new_size];
    T *pointer = list;
    for (int i = 0; i < size; ++i) {
      *new_location = *list;
    }
    delete list;
    list = pointer;
    capacity = new_size;
  }

  void offset(int start, int end, int offset = 1) {
    if (size + offset > capacity)resize(2 * capacity);
    for (int i = end; i > start; --i) {
      list[i] = list[i - 1];
    }
  }

  int search(T data, int lo, int hi) {
    if (lo > hi) return -1;
    int mid = (lo + hi) / 2;
    if (list[mid] > data) search(data, lo, mid - 1);
    else if (list[mid] < data) search(data, mid + 1, hi);
    else return mid;
  }

 public:
  SequentialList() : size{0}, capacity{0}, list{nullptr} {}

  SequentialList(const int capacity) : size{0}, capacity(capacity) {}

  SequentialList(const int size, const int capacity, T *list)
      : size(size), capacity(capacity), list(list) {}

  bool put(const T data) {
    if (size >= capacity) resize(2 * capacity);
    int place = search(data, 0, size);
    list[size++] = data;
    return true;
  }

  bool del(const int index) {
    if (index < 0 || index > size)return false;
//    list[size_--] = nullptr;
    size--;
  }

  void print() const {
    std::cout << "List size_: " << size << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << list[i] << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  auto list = linked_list<int>();
  /*Empty test*/
  list.print();

  /*Insert 9 range integers*/
  int items_limit;
  std::cout << "Generate number range from 0 to ";
  std::cin >> items_limit;
  for (int i = 0; i < items_limit; ++i) {
    list.insert(i);
  }
  list.print();

  /*Remove the specified item*/
  int index;
  std::cout << "Item place to remove: ";
  std::cin >> index;
  list.remove(index);
  list.print();

  /*Insert number to the head*/
  int number_to_insert;
  std::cout << "Number inserted to head: ";
  std::cin >> number_to_insert;
  list.insert(number_to_insert);
  list.print();

  /*Remove 3 items from head*/
  int num;
  std::cout << "How many items should be removed: ";
  std::cin >> num;
  for (auto i = 0; i < num; ++i) {
    list.remove();
  }
  list.print();

  /*Insert number 98 2 items away from tail*/
  int new_num, offset;
  std::cout << "Input a number and offset away from tail: ";
  std::cin >> new_num >> offset;
  list.insert(new_num, list.size() - offset);
  list.print();

  /*Search for number 98*/
  int search_for;
  std::cout << "Search for number: ";
  std::cin >> search_for;
  std::cout << "number " << search_for << " is on " << list.where(search_for) << std::endl;

  /*Inplace reverse*/
  std::cout << "Inplace reverse list" << std::endl;
  list.reverse();
  list.print();

  /*merge to list*/
  std::cout << "Merge two list" << std::endl;
  linked_list<int> one = linked_list<int>();
  linked_list<int> two = linked_list<int>();
  for (int j = 9; j > 6; --j) {
    one.insert(j);
  }
  for (int k = 4; k > 1; --k) {
    two.insert(k);
  }
  linked_list<int> three = linked_list<int>(one, two);
  three.print();
  three.reverse();
  three.print();

  return 0;
}



