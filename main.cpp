#include <iostream>

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
  Node() {}

  Node(T init) : data{init} {}

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
};
template<class T>
class LinkedList {
 public:
  LinkedList() : LinkedList(0) {}

  LinkedList(const int size) : N{size}, start{nullptr} {}

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
    int count = 1;
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
    if (N < 1 || start->getNext_node() == nullptr) return false;

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
    int count = 1;
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
    std::cout << "链表元素个数：" << N << std::endl;
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
    int count = 0;
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
    for (int i = N - 2; i > 0; ++i) {
      now_item->setNext_node(moveTo(i));
    }

    start = new_start;
  }

  ~LinkedList() {

  }

 private:
  int N;
  Node<T> *start;

  /*return a pointer, which point to the i-th item, including 0*/
  Node<T> *moveTo(const int index) {
    if (index < 0 || index >= N)return nullptr;
    Node<T> *pointer = start;
    int counter = 0;
    while (counter < index && pointer->getNext_node() != nullptr) {
      pointer = pointer->getNext_node();
    }
    return pointer;
  }
};

int main() {
  LinkedList<int> list = LinkedList<int>();
  /*Empty test*/
  list.print();

  /*Insert 9 range integeres*/
  for (int i = 0; i < 9; ++i) {
    list.insert(i);
  }
  list.print();

  /*Remove the second item*/
  list.remove(2 - 1);
  list.print();

  /*Insert 99 to the head*/
  list.insert(99);
  list.print();

  /*Remove 3 items from head*/
  for (int i = 0; i < 3; ++i) {
    list.remove();
  }
  list.print();

  /*Insert number 98 2 items away from tail*/
  list.insert(98, list.size() - 2);
  list.print();

  /*Search for number 98*/
  std::cout << list.where(98) << std::endl;

  return 0;
}
