#include <iostream>

struct Node {
  int data;
  Node *next;
};

class LinkedList {
 public:
  LinkedList() : N{0}, start{nullptr} {}

  LinkedList(int size) : N{size} {}

  bool insert(int data) {
    Node *old_start = start;
    Node *new_start = new Node;
    new_start->data = data;
    new_start->next = old_start;
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
  bool insert(int data, int i) {
    if (i > N || i < 0) return false;
    if (i == 0) {
      insert(data);
      return true;
    }

    Node *next_item = start;
    int count = 1;
    while (count < i) { //&& next_item->next != nullptr) {
      next_item = next_item->next;
      count++;
    }

    Node *new_item = new Node;
    new_item->data = data;
    new_item->next = next_item->next;
    next_item->next = new_item;

    N++;
    return true;
  }

  /*
 * remove the i-th item, count start from 0
 *  |o|o|o|o|
 *   ^ ^ ^ ^
 *   0 1 2 3
 *
 * */
  bool remove(int i) {
    if (i >= N || i < 0) return false;
    if (i == 0) {
      remove();
      return true;
    }

    Node *next_item = start;
    int count = 1;
    while (count < i) { //&& next_item->next != nullptr) {
      next_item = next_item->next;
      count++;
    }
    if (i == N - 1) next_item->next = nullptr;
    else next_item->next = next_item->next->next;

    N--;
    return true;
  }

  bool remove() {
    if (N < 1 || start->next == nullptr)return false;

    Node *old_start = start;
    start = old_start->next;
    delete old_start;

    N--;
    return true;
  }

  void print() {
    Node *next = start;
    std::cout << "链表元素个数：" << N << std::endl;
    while (next != nullptr) {
      std::cout << next->data << " ";
      next = next->next;
    }
    std::cout << std::endl;
  }

  int size() { return N; }

  bool is_empty() { return N == 0; }

//  bool remove(Node node){}

  /*search for key from head to tail, return the first occurrence*/
  int where(int key) {
    Node *next = start;
    int count = 0;
    while (next != nullptr && next->data != key) {
      next = next->next;
      count++;
    }
    if (count == N - 1)return -1;
    return count;
  }

 private:
  int N;
  Node *start;
};

int main() {
  LinkedList list = LinkedList();
  list.print();
  for (int i = 0; i < 3; ++i) {
    list.insert(i);
  }
  list.print();
  list.remove(2);
  list.print();
  for (int i = 0; i < 3; ++i) {
    list.remove();
  }
  list.print();
  list.insert(99, 0);
  list.print();
  list.insert(98, 1);
  list.print();
  std::cout << list.where(98);
  return 0;
}
