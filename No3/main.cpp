#include "BinaryTree.h"
#include <iostream>
#include <regex>
#include <limits>


namespace {
auto print = [](const TreeNode &node) -> void { std::cout << node.key_ << " "; };

void g_Clean_input() {
    std::cin.clear();
    std::cin.putback('\n');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void tree_init(BinaryTree &tree) {
    std::string input;
    g_Clean_input();
    std::cout << "������� \'����:����\' ��������ֵ�Զ��������Էָ�������\n����'#'��ӡ��������EOF��ǻ���'END'������\n";
    std::regex delimiter_regex(R"([\s\|\\\/,;_]+)");
    std::regex token_regex(R"(END|#|(-?\d+)\:(-?\d+))");
    const std::string MAX_INT(std::to_string(std::numeric_limits<int>::max()));
    const std::string MIN_INT(std::to_string(std::numeric_limits<int>::min()));
    while (getline(std::cin, input)) {
        auto token_iterator =
            std::sregex_token_iterator(input.begin(), input.end(), delimiter_regex, -1);
        while (token_iterator != std::sregex_token_iterator()) {
            std::string split_string = token_iterator->str();
            ++token_iterator;
            if (split_string.empty()) continue;
            std::smatch token_match;
            if (regex_search(split_string, token_match, token_regex)) {
                if (token_match.str(2).empty()) {
                    tree.print();
                    if (token_match.str() == "END") { return; }
                    continue;
                }
                std::string first = token_match.str(1);
                std::string second = token_match.str(2);
                auto compare = [](const std::string &a) -> bool {
                    if (a.length() > 11) return false;
                    long long tmp = std::stoll(a);
                    if (tmp > 0
                        && tmp / (static_cast<long long>(std::numeric_limits<int>::max()) + 1) >= 1)
                        return false;
                    else if (tmp < 0
                        && tmp / (static_cast<long long>(std::numeric_limits<int>::min()) - 1) >= 1)
                        return false;
                    return true;
                };

                if (compare(first) && compare(second)) { tree.put(std::stoi(first), std::stoi(second)); }
                else {
                    std::cerr << split_string << "������ʾ��Χ������" << std::endl;
                }
                continue;
            }
            std::cerr << split_string << "δ��ʶ�𣬺���" << std::endl;
        }
    }
}

void tree_func_1(BinaryTree &tree) {
    std::cout << "���ĵ�ǰ״̬��\n";
    tree.print();
    std::cout << "����ǰ�������ӡ���ǵݹ飩��\n";
    tree.preOrderIterativeTraverse(print);
    std::cout << std::endl;
    std::cout << "��������ǰ�������ӡ���ݹ飩��\n";
    tree.preOrderRecursiveTraverse(print);
    std::cout << std::endl;
    std::cout << "�����������������ӡ���ǵݹ飩��\n";
    tree.inOrderIterativeTraverse(print);
    std::cout << std::endl;
    std::cout << "�����������������ӡ���ݹ飩��\n";
    tree.inOrderRecursiveTraverse(print);
    std::cout << std::endl;
    std::cout << "�������ĺ��������ӡ���ǵݹ飩��\n";
    tree.postOrderIterativeTraverse(print);
    std::cout << std::endl;
    std::cout << "�������ĺ��������ӡ���ݹ飩��\n";
    tree.postOrderRecursiveTraverse(print);
    std::cout << std::endl;
}

void tree_func_2(BinaryTree &tree) {
    std::cout << "�������������н������������໥������\n";
    tree.swapChildren();
    tree.print();
    std::cout << std::endl;
}

void tree_func_3(BinaryTree &tree) { std::cout << "�������е�Ҷ�������" << tree.leavesCount() << std::endl; }

void tree_func_4(BinaryTree &tree) {
    std::cout << "�����˳�������������\n";
    tree.levelOrderBFSTraverse(print);
    std::cout << std::endl;
}
}

int main() {
    BinaryTree tree = BinaryTree();
    tree_init(tree);
    tree.put(10, 12);
    tree.put(5, 10);
    tree.put(15, 15);
    tree.put(9, 14);
    tree.put(13, 15);
    tree.put(2, 13);
    tree.put(6, 13);
    tree.put(12, 13);
    tree.put(14, 13);
    tree_func_1(tree);
    tree_func_2(tree);
    tree_func_3(tree);
    tree_func_4(tree);
    return 0;
}
