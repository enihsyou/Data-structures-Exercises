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
  std::cout << "输入整数压栈，输入'#'弹栈，输入'@'查看栈顶，输入'%'查看堆栈元素，空格分隔（输入EOF结束）：\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!regex_match(input, input_regex)) {
      std::cout << input << "无法识别，跳过" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "弹出：" << stack.Pop() << std::endl;
      } catch (std::underflow_error& error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << stack;
    } else if (input == "@") {
      try {
        std::cout << "栈顶元素：" << stack.Peek() << std::endl;
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
  std::cout << "输入整数入队，输入'#'出队，输入'@'查看队首，输入'%'查看队列元素，空格分隔（输入EOF结束）：\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!regex_match(input, input_regex)) {
      std::cout << input << "无法识别，跳过" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "出队：" << queue.Dequeue() << std::endl;
      } catch (std::underflow_error& error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << queue;
    } else if (input == "@") {
      try {
        std::cout << "队首元素：" << queue.Peek() << std::endl;
      } catch (std::underflow_error& error) { std::cout << error.what() << std::endl; }
    } else {
      queue.Enqueue(stoi(input));
    }
  }
  std::cout << queue;
}


int main() {
//    std::cin.putback('\n'); // 绕过第一个清空操作
    std::cout << "|||链栈的操作|||" << std::endl;
    Stack<int> stack = Stack<int>();
    s_func_1(stack);


  std::cout << "|||循环队列的操作|||" << std::endl;
  std::cout << "输入队列大小：";
  int queue_size;
  std::cin >> queue_size;
  Queue<int> queue = Queue<int>(queue_size);
  q_init(queue);

  return 0;
}
