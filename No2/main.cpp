#include <iostream>
#include "stack.h"
#include "queue.h"
#include <string>
#include <regex>
#include <cmath>

void g_Clean_input() {
  std::cin.clear();
  std::cin.putback('\n');
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void s_func_1(Stack<int> &stack) {
  // int specificed
  std::string input;
  g_Clean_input();
  std::cout << "输入整数压栈，输入'#'弹栈，输入'@'查看栈顶，输入'%'查看堆栈元素，空格分隔（输入EOF结束）：\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!std::regex_match(input, input_regex)) {
      std::cout << input << "无法识别，跳过" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "弹出：" << stack.Pop() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << stack;
    } else if (input == "@") {
      try {
        std::cout << "栈顶元素：" << stack.Peek() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else {
      stack.Push(stoi(input));// 字符串转整数
    }
  }
  std::cout << stack;
}

void q_init(Queue<int> &queue) {
  // int specificed
  std::string input;
  g_Clean_input();
  std::cout << "输入整数入队，输入'#'出队，输入'@'查看队首，输入'%'查看队列元素，空格分隔（输入EOF结束）：\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!std::regex_match(input, input_regex)) {
      std::cout << input << "无法识别，跳过" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "出队：" << queue.Dequeue() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << queue;
    } else if (input == "@") {
      try {
        std::cout << "队首元素：" << queue.Peek() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else {
      try {
        queue.Enqueue(stoi(input)); // 字符串转整数
      } catch (std::overflow_error &error) { std::cout << error.what() << std::endl; }
    }
  }
  std::cout << queue;
}

namespace {
auto Precedence = [](std::string &op) -> int {
  // 都是二元算符
  if (op == "+")return 2;
  if (op == "-")return 2;
  if (op == "*")return 3;
  if (op == "/")return 3;
  if (op == "^")return 4;
  if (op == "(")return 1;
  if (op == ")")return 1;
  return 0; // 是数字
  //  throw std::invalid_argument("不支持的操作符");

};
auto Evaluate = [](std::string &op, double val1, double val2) -> double {
  if (op == "+")return val1 + val2;
  if (op == "-")return val1 - val2;
  if (op == "*")return val1 * val2;
  if (op == "/")return val1 / val2;
  if (op == "^")return pow(val1, val2);

  throw std::invalid_argument("不支持的操作符");
};
}

void calculator() {
  std::string input;
  g_Clean_input();
  std::cout << "输入四则运算表达式：";
  std::regex arithmetic_regex(R"((\d+(?:\.\d*)?)|([\(\)\+\-\*\/\^]))");
  while (std::getline(std::cin, input)) {
    /*Shunting Yard Algorithm*/
    Stack<double> result_stack; // 结果栈
    Stack<std::string> op_stack; // 操作符栈
    try {
      for (auto i = std::sregex_iterator(input.begin(), input.end(), arithmetic_regex);
           i != std::sregex_iterator(); ++i) {
        auto op = i->str(); // 输入的操作数

        if ((*i)[2].length() > 0) { // Operator
          while (true) {
            if (op_stack.EmptyQ() || op == "(" || Precedence(op) > Precedence(op_stack.Peek())) {
              // 空栈
              // 新遇到的操作符的优先级更高
              // 左括号，都直接放入操作符栈
              op_stack.Push(op);
              break;
            }
            auto stack_top = op_stack.Pop();
            if (stack_top == "(") break; // 直到遇到匹配的左括号，停下

            result_stack.Push(Evaluate(stack_top, result_stack.Pop(), result_stack.Pop()));
          }
        } else { // Number
          result_stack.Push(stod(op)); // 数字直接放入结果栈
        }
      }
      /*RPN Calculator*/
      while (!op_stack.EmptyQ())
        result_stack.Push(Evaluate(op_stack.Pop(),
                                   result_stack.Pop(),
                                   result_stack.Pop()));
      if (!result_stack.EmptyQ()) std::cout << input << " = " << result_stack.Pop() << std::endl;
    } catch (const std::exception &) { std::cout << "表达式 " << input << " 有误" << std::endl; }
  }

}

int main() {
  std::cin.putback('\n'); // 绕过第一个清空操作
  std::cout << "|||链栈的操作|||" << std::endl;
  Stack<int> stack = Stack<int>();
  s_func_1(stack);

  std::cout << "|||循环队列的操作|||" << std::endl;
  std::cout << "输入队列大小：";
  g_Clean_input();
  int queue_size;
  std::cin >> queue_size;
  Queue<int> queue = Queue<int>(queue_size);
  q_init(queue);
  std::cout << "|||逆波兰计算器|||" << std::endl;
  calculator();
  return 0;
}
