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
  std::cout << "��������ѹջ������'#'��ջ������'@'�鿴ջ��������'%'�鿴��ջԪ�أ��ո�ָ�������EOF��������\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!std::regex_match(input, input_regex)) {
      std::cout << input << "�޷�ʶ������" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "������" << stack.Pop() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << stack;
    } else if (input == "@") {
      try {
        std::cout << "ջ��Ԫ�أ�" << stack.Peek() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else {
      stack.Push(stoi(input));// �ַ���ת����
    }
  }
  std::cout << stack;
}

void q_init(Queue<int> &queue) {
  // int specificed
  std::string input;
  g_Clean_input();
  std::cout << "����������ӣ�����'#'���ӣ�����'@'�鿴���ף�����'%'�鿴����Ԫ�أ��ո�ָ�������EOF��������\n";
  std::regex input_regex(R"(^-?\d+|#|@|%$)");
  while (std::cin >> input) {
    if (!std::regex_match(input, input_regex)) {
      std::cout << input << "�޷�ʶ������" << std::endl;
      continue;
    }
    if (input == "#") {
      try {
        std::cout << "���ӣ�" << queue.Dequeue() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else if (input == "%") {
      std::cout << queue;
    } else if (input == "@") {
      try {
        std::cout << "����Ԫ�أ�" << queue.Peek() << std::endl;
      } catch (std::underflow_error &error) { std::cout << error.what() << std::endl; }
    } else {
      try {
        queue.Enqueue(stoi(input)); // �ַ���ת����
      } catch (std::overflow_error &error) { std::cout << error.what() << std::endl; }
    }
  }
  std::cout << queue;
}

namespace {
auto Precedence = [](std::string &op) -> int {
  // ���Ƕ�Ԫ���
  if (op == "+")return 2;
  if (op == "-")return 2;
  if (op == "*")return 3;
  if (op == "/")return 3;
  if (op == "^")return 4;
  if (op == "(")return 1;
  if (op == ")")return 1;
  return 0; // ������
  //  throw std::invalid_argument("��֧�ֵĲ�����");

};
auto Evaluate = [](std::string &op, double val1, double val2) -> double {
  if (op == "+")return val1 + val2;
  if (op == "-")return val1 - val2;
  if (op == "*")return val1 * val2;
  if (op == "/")return val1 / val2;
  if (op == "^")return pow(val1, val2);

  throw std::invalid_argument("��֧�ֵĲ�����");
};
}

void calculator() {
  std::string input;
  g_Clean_input();
  std::cout << "��������������ʽ��";
  std::regex arithmetic_regex(R"((\d+(?:\.\d*)?)|([\(\)\+\-\*\/\^]))");
  while (std::getline(std::cin, input)) {
    /*Shunting Yard Algorithm*/
    Stack<double> result_stack; // ���ջ
    Stack<std::string> op_stack; // ������ջ
    try {
      for (auto i = std::sregex_iterator(input.begin(), input.end(), arithmetic_regex);
           i != std::sregex_iterator(); ++i) {
        auto op = i->str(); // ����Ĳ�����

        if ((*i)[2].length() > 0) { // Operator
          while (true) {
            if (op_stack.EmptyQ() || op == "(" || Precedence(op) > Precedence(op_stack.Peek())) {
              // ��ջ
              // �������Ĳ����������ȼ�����
              // �����ţ���ֱ�ӷ��������ջ
              op_stack.Push(op);
              break;
            }
            auto stack_top = op_stack.Pop();
            if (stack_top == "(") break; // ֱ������ƥ��������ţ�ͣ��

            result_stack.Push(Evaluate(stack_top, result_stack.Pop(), result_stack.Pop()));
          }
        } else { // Number
          result_stack.Push(stod(op)); // ����ֱ�ӷ�����ջ
        }
      }
      /*RPN Calculator*/
      while (!op_stack.EmptyQ())
        result_stack.Push(Evaluate(op_stack.Pop(),
                                   result_stack.Pop(),
                                   result_stack.Pop()));
      if (!result_stack.EmptyQ()) std::cout << input << " = " << result_stack.Pop() << std::endl;
    } catch (const std::exception &) { std::cout << "���ʽ " << input << " ����" << std::endl; }
  }

}

int main() {
  std::cin.putback('\n'); // �ƹ���һ����ղ���
  std::cout << "|||��ջ�Ĳ���|||" << std::endl;
  Stack<int> stack = Stack<int>();
  s_func_1(stack);

  std::cout << "|||ѭ�����еĲ���|||" << std::endl;
  std::cout << "������д�С��";
  g_Clean_input();
  int queue_size;
  std::cin >> queue_size;
  Queue<int> queue = Queue<int>(queue_size);
  q_init(queue);
  std::cout << "|||�沨��������|||" << std::endl;
  calculator();
  return 0;
}
