#include <iostream>
#include "BinaryTree.h"
#include <regex>
#include <limits>

namespace {
auto print = [](const TreeNode &node)-> void { std::cout << node.key << " "; };

void g_Clean_input() {
    std::cin.clear();
    std::cin.putback('\n');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void tree_init(BinaryTree &tree) {
    std::string input;
    g_Clean_input();
    std::cout << "输入多组 \'整数:整数\' 来创建键值对二叉树，以分隔符分离，随时输入#打印树，输入EOF结束：\n";
    std::regex delimeter_regex(R"([\s\|\\\/,;_]+)");
    std::regex token_regex(R"(#|(-?\d+)\:(-?\d+))");
    const std::string MAX_INT(std::to_string(std::numeric_limits<int>::max()));
    const std::string MIN_INT(std::to_string(std::numeric_limits<int>::min()));
    while (std::getline(std::cin, input)) {
        auto token_iterator = std::sregex_token_iterator(input.begin(), input.end(), delimeter_regex, -1);
        while (token_iterator != std::sregex_token_iterator()) {
            std::string splited_string = token_iterator->str();
            ++token_iterator;
            if (splited_string.empty()) continue;
            std::smatch token_match;
            if (std::regex_search(splited_string, token_match, token_regex)) {
                if (token_match.str(2).empty()) {
                    tree.print();
                    continue;
                }
                std::string first = token_match.str(1);
                std::string second = token_match.str(2);
                auto compare = [](const std::string &a)-> bool {
                        if (a.length() > 11) return false;
                        long long tmp = std::stoll(a);
                        if (tmp > 0 && tmp / (static_cast<long long>(std::numeric_limits<int>::max()) + 1) >= 1)return false;
                        else if (tmp < 0 && tmp / (static_cast<long long>(std::numeric_limits<int>::min()) - 1) >= 1)return false;
                        return true;
                    };

                if (compare(first) && compare(second)) {
                    tree.put(std::stoi(first), std::stoi(second));
                } else {
                    std::cerr << splited_string << "超出表示范围，忽略" << std::endl;
                }
                continue;
            }
            std::cerr << splited_string << "未能识别，忽略" << std::endl;
        }
    }
}

void tree_func_1(BinaryTree &tree) {
    std::cout << "树的当前状态：\n";
    tree.print();
    std::cout << "树的前序遍历打印（非递归）：\n";
    tree.preOrderIterativeTraverse(print);
    std::cout << std::endl;
    std::cout << "二叉树的前序遍历打印（递归）：\n";
    tree.preOrderRecursiveTraverse(print);
    std::cout << std::endl;
    std::cout << "二叉树的中序遍历打印（非递归）：\n";
    tree.inOrderIterativeTraverse(print);
    std::cout << std::endl;
    std::cout << "二叉树的中序遍历打印（递归）：\n";
    tree.inOrderRecursiveTraverse(print);
    std::cout << std::endl;
    std::cout << "二叉树的后序遍历打印（非递归）：\n";
    tree.postOrderIterativeTraverse(print);
    std::cout << std::endl;
    std::cout << "二叉树的后序遍历打印（递归）：\n";
    tree.postOrderRecursiveTraverse(print);
    std::cout << std::endl;
}

void tree_func_2(BinaryTree &tree) {
    std::cout << "将二叉树中所有结点的左右子树相互交换：\n";
    tree.swapChildren();
    tree.print();
    std::cout << std::endl;
}

void tree_func_3(BinaryTree &tree) {
    std::cout << "二叉树中的叶结点数：" << tree.leavesCount() << std::endl;
}

void tree_func_4(BinaryTree &tree) {
    std::cout << "按层次顺序遍历二叉树：\n";
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
