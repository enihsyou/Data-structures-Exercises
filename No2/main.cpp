#include <iostream>
#include "stack.h"
#include "queue.h"
#include <string>
#include <regex>

void g_Clean_input() {
  std::cin.clear();
  std::cin.putback('\n');
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void s_func_1(Stack<int>& stack) {
  // int specificed
  std::string input;
  g_Clean_input();
  std::cout << "��������ѹջ������'#'��ջ������'@'�鿴ջ��������'%'�鿴��ջԪ�أ��ո�ָ�������EOF��������\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!regex_match(input, input_regex)) {
      std::cout << input << "�޷�ʶ������" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "������" << stack.Pop() << std::endl;
      } catch (std::underflow_error& error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << stack;
    } else if (input == "@") {
      try {
        std::cout << "ջ��Ԫ�أ�" << stack.Peek() << std::endl;
      } catch (std::underflow_error& error) { std::cout << error.what() << std::endl; }
    } else {
      stack.Push(stoi(input));
    }
  }
  std::cout << stack;
}


void q_init(Queue<int>& queue) {
  // int specificed
  std::string input;
  g_Clean_input();
  std::cout << "����������ӣ�����'#'���ӣ�����'@'�鿴���ף�����'%'�鿴����Ԫ�أ��ո�ָ�������EOF��������\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!regex_match(input, input_regex)) {
      std::cout << input << "�޷�ʶ������" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "���ӣ�" << queue.Dequeue() << std::endl;
      } catch (std::underflow_error& error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << queue;
    } else if (input == "@") {
      try {
        std::cout << "����Ԫ�أ�" << queue.Peek() << std::endl;
      } catch (std::underflow_error& error) { std::cout << error.what() << std::endl; }
    } else {
      queue.Enqueue(stoi(input));
    }
  }
  std::cout << queue;
}


int main() {
//    std::cin.putback('\n'); // �ƹ���һ����ղ���
    std::cout << "|||��ջ�Ĳ���|||" << std::endl;
    Stack<int> stack = Stack<int>();
    s_func_1(stack);


  std::cout << "|||ѭ�����еĲ���|||" << std::endl;
  std::cout << "������д�С��";
  int queue_size;
  std::cin >> queue_size;
  Queue<int> queue = Queue<int>(queue_size);
  q_init(queue);

  return 0;
}
