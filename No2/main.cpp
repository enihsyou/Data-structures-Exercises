#include <iostream>
#include "stack.h"
#include "queue.h"
#include <string>
#include <regex>
#include <cassert>

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
    if (!std::regex_match(input, input_regex)) {
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
      stack.Push(stoi(input));// 字符串转整数
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
    if (!std::regex_match(input, input_regex)) {
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
      queue.Enqueue(stoi(input)); // 字符串转整数
    }
  }
  std::cout << queue;
}

namespace {
auto Precedence = [](std::string& op)-> int {
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
auto CmpOperator = [](std::string& op1, std::string& op2) -> int {
  if (op1 == op2) { return 0; }
  if (Precedence(op1) - Precedence(op2) > 0) { return 1; } else { return -1; }
};
auto Evaluate = [](std::string& op, std::string& a, std::string& b) -> std::string {
  /*使用字符串，同时储存整数和小数*/
  if (a.find('.') != std::string::npos || b.find('.') != std::string::npos) { // 有一个小数
    double val1 = stod(a), val2 = stod(b);
    if (op == "+")return std::to_string(val1 + val2);
    if (op == "-")return std::to_string(val1 - val2);
    if (op == "*")return std::to_string(val1 * val2);
    if (op == "/")return std::to_string(val1 / val2);
  } else { // 都是整数
    int val1 = stoi(a), val2 = stoi(b);
    if (op == "+")return std::to_string(val1 + val2);
    if (op == "-")return std::to_string(val1 - val2);
    if (op == "*")return std::to_string(val1 * val2);
    if (op == "/")return std::to_string(val1 / val2);
  }
  throw std::invalid_argument("不支持的操作符");
};
}

void caculator() {
  std::string input;
  g_Clean_input();
  std::cout << "输入四则运算表达式：";
  std::regex arithmetic_regex(R"((\d+(?:\.\d*)?)|([\(\)\+\-\*\/\^]))");
  while (std::getline(std::cin, input)) {
    /*Shunting Yard Algorithm*/
    Stack<std::string> result_stack; // 结果栈
    Stack<std::string> op_stack; // 操作符栈
    try {
      for (auto i = std::sregex_iterator(input.begin(), input.end(), arithmetic_regex); i != std::sregex_iterator(); ++i) {
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
          result_stack.Push(op); // 数字直接放入结果栈
        }
      }
      /*RPN Calculator*/
      while (!op_stack.EmptyQ()) result_stack.Push(Evaluate(op_stack.Pop(), result_stack.Pop(), result_stack.Pop()));
      if (!result_stack.EmptyQ()) std::cout << input << " = " << result_stack.Pop() << std::endl;
    } catch (const std::exception& error) { std::cout << "表达式 " << input << " 有误" << std::endl; }
  }

}

int main() {
  std::cin.putback('\n'); // 绕过第一个清空操作
  std::cout << "|||链栈的操作|||" << std::endl;
  Stack<int> stack = Stack<int>();
  s_func_1(stack);


  std::cout << "|||循环队列的操作|||" << std::endl;
  std::cout << "输入队列大小：";
  int queue_size;
  std::cin >> queue_size;
  Queue<int> queue = Queue<int>(queue_size);
  q_init(queue);
  std::cout << "|||逆波兰计算器|||" << std::endl;
  caculator();
  return 0;
}
