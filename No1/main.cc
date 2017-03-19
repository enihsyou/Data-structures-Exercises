#include <iostream>
#include <limits>
#include "sequential_list.h"
#include "linked_list.h"
using std::cout;
using std::cin;
using std::endl;

void s_func_1(sequential_list<int>& s_list) {
  int input;
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cout << "输入要插入的整数（以非数字输入结束）：" << endl;
  while (cin >> input) {
    s_list.put(input);
  }
  s_list.print();
}

void l_init(linked_list<int>& l_list) {
  int input;
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cout << "输入要插入的整数：" << endl;
  while (cin >> input) {
    l_list.insert(input);
  }
  l_list.print();
}

void l_func_1(linked_list<int>& l_list) {
  int lower_bound, upper_bound;
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cout << "输入要移除的范围下限：" << endl;
  cin >> lower_bound;
  cout << "输入要移除的范围上限：" << endl;
  cin >> upper_bound;
  l_list.remove(lower_bound, upper_bound);
  l_list.print();
}

void l_func_2(linked_list<int>& l_list) {
  cout << "对单链表就地逆置：" << endl;
  l_list.reverse();
  l_list.print();
}

void l_func_3() {
  linked_list<int> A = linked_list<int>();
  linked_list<int> B = linked_list<int>();
  cout << "输入数字 创建递增列表A：" << endl;
  l_init(A);
  cout << "输入数字 创建递增列表B：" << endl;
  l_init(B);
  cout << "合并创建递减列表C：" << endl;
  linked_list<int> C = linked_list<int>(A, B);
  C.print();
}

int main() {
  cin.putback('\n'); // 绕过第一个清空操作
  cout << "|||线性表的顺序存储结构操作|||" << endl;
  sequential_list<int> Va = sequential_list<int>();
  s_func_1(Va);
  cout << "|||线性表的链式存储结构操作|||" << endl;
  linked_list<int> Vb = linked_list<int>();
  l_init(Vb);
  l_func_1(Vb);
  l_func_2(Vb);
  l_func_3();

  return 0;
}
