#include <iostream>
#include <numeric>

//struct Node {
//  int data;
//  Node *next;
//};
template<class T>
class Node {
 private:
  T data;
  Node<T> *next_node;
 public:
  Node() : next_node{nullptr} {}

  Node(T init) : data{init}, next_node{nullptr} {}

  Node(T init, Node<T> *next) : data{init}, next_node{next} {}

  T getData() const {
    return data;
  }

  void setData(T data) {
    Node<T>::data = data;
  }

  Node<T> *getNext_node() const {
    return next_node;
  }

  void setNext_node(Node<T> *next_node = nullptr) {
    Node<T>::next_node = next_node;
  }

  bool operator<(Node<T> &a) {
    return this->getData() < a.getData();
  }
};
template<class T>
class LinkedList {
 public:
  LinkedList() : LinkedList(0) {}

  LinkedList(const int size) : N{size}, start{nullptr} {}

  /*Assume a & b is in ascending order, merge a & b into this, in descending order*/
  LinkedList(const LinkedList<T> &a, const LinkedList<T> &b) : LinkedList() {
    int N1 = 0, N2 = 0;
    Node<T> *p1, *p2;
    while (N1 < a.size() && N2 < b.size()) {
      p1 = a.moveTo(N1);
      p2 = b.moveTo(N2);

      if (*p1 < *p2) {
        insert(p1->getData());
        N1++;
      } else {
        insert(p2->getData());
        N2++;
      }
    }
    while (N1 < a.size()) {
      p1 = a.moveTo(N1);
      insert(p1->getData());
      N1++;
    }
    while (N2 < b.size()) {
      p2 = b.moveTo(N2);
      insert(p2->getData());
      N2++;
    }
  }

  Node<T> *getStart() const {
    return start;
  }

  /*Deep copy*/
  LinkedList(const LinkedList<T> &a) {
    start = a.getStart();
    N = a.size();

    Node<T> *now_item = a.getStart();
    Node<T> *pointer = start;
    while (now_item->getNext_node() != nullptr) {
      auto new_node = new Node<T>(now_item->getData());
      pointer->setNext_node(new_node);
    }
  }

  bool insert(const T data) {
    Node<T> *new_start = new Node<T>(data, start);
    start = new_start;

    N++;
    return true;
  }

  /*
   * Insert item into the i-th place, start from 0
   *  |o|o|o|o|
   *  ^ ^ ^ ^ ^
   *  0 1 2 3 4
   *
   * */
  bool insert(const T data, const int i) {
    if (i > N || i < 0) return false;
    if (i == 0) {
      insert(data);
      return true;
    }

    Node<T> *next_item = start;
    auto count = 1;
    while (count < i) { //&& next_item->next != nullptr) {
      next_item = next_item->getNext_node();
      count++;
    }

    Node<T> *new_item = new Node<T>(data, next_item->getNext_node());
    next_item->setNext_node(new_item);

    N++;
    return true;
  }

  bool remove() {
    if (N < 1 || !start->getNext_node()) return false;

    Node<T> *old_start = start;
    start = old_start->getNext_node();
    delete old_start;

    N--;
    return true;
  }

  /*
 * remove the i-th item, count start from 0
 *  |o|o|o|o|
 *   ^ ^ ^ ^
 *   0 1 2 3
 *
 * */
  bool remove(const int i) {
    if (i >= N || i < 0) return false;
    if (i == 0) {
      remove();
      return true;
    }

    Node<T> *next_item = start;
    auto count = 1;
    while (count < i) { //&& next_item->next != nullptr) {
      next_item = next_item->getNext_node();
      count++;
    }
    Node<T> *deleted = next_item->getNext_node();
    if (i == N - 1) next_item->setNext_node();
    else next_item->setNext_node(next_item->getNext_node()->getNext_node());
    delete deleted;

    N--;
    return true;
  }

  void print() const {
    Node<T> *next = start;
    std::cout << N << " items in the list" << std::endl;
    while (next != nullptr) {
      std::cout << next->getData() << " ";
      next = next->getNext_node();
    }
    std::cout << std::endl;
  }

  int size() const { return N; }

  bool is_empty() const { return N == 0; }

  /*search for key from head to tail, return the first occurrence*/
  int where(const int key) {
    Node<T> *next = start;
    auto count = 0;
    while (next != nullptr && next->getData() != key) {
      next = next->getNext_node();
      count++;
    }
    if (count == N - 1)return -1;
    return count;
  }

  void reverse() {
    if (N < 2) return;
    Node<T> *new_start = moveTo(N - 1);
    Node<T> *now_item = new_start;
    for (auto i = N - 2; i >= 0; --i) {
      now_item->setNext_node(moveTo(i));
      now_item = now_item->getNext_node();
    }
    now_item->setNext_node();
    start = new_start;
  }

  ~LinkedList() {
    auto queue = start;
    Node<T> *memory;

    while (queue->getNext_node() != nullptr) {
      memory = queue;
      queue = queue->getNext_node();
      delete memory;
    }
  }

 private:
  int N;
  Node<T> *start;

  /*return a pointer, which point to the i-th item, [0, N)*/
  Node<T> *moveTo(const int index) const {
    if (index < 0 || index >= N)return nullptr;
    Node<T> *pointer = start;
    int counter = 0;
    while (counter < index) {
      pointer = pointer->getNext_node();
      counter++;
    }
    return pointer;
  }
};
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
//    list[size--] = nullptr;
    size--;
  }

  void print() const {
    std::cout << "List size: " << size << std::endl;
    for (int i = 0; i < size; ++i) {
      std::cout << list[i] << " ";
    }
    std::cout << std::endl;
  }
};

int main() {
  LinkedList<int> list = LinkedList<int>();
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
  LinkedList<int> one = LinkedList<int>();
  LinkedList<int> two = LinkedList<int>();
  for (int j = 9; j > 6; --j) {
    one.insert(j);
  }
  for (int k = 4; k > 1; --k) {
    two.insert(k);
  }
  LinkedList<int> three = LinkedList<int>(one, two);
  three.print();

  return 0;
}



