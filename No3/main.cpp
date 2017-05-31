#include "BinaryTree.h"
#include <iostream>
#include <regex>
#include <limits>


namespace {
auto print = [](const TreeNode &node) -> void { std::cout << node.key_ << " "; };
auto Is_number_in_limits = [](const std::string &a) -> bool {
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

void g_Clean_input() {
    std::cin.clear();
    std::cin.putback('\n');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void tree_init(BinaryTree &tree) {
    std::string input;
    g_Clean_input();
    std::cout << "输入多组 \'整数:整数\' 来创建键值对二叉树，以分隔符分离\n输入'!整数'删除对应键，'#'打印树，EOF标记或者'END'结束：\n";
    std::regex delimiter_regex(R"([\s\|\\\/,;_]+)");
    std::regex token_regex(R"((END)|(#)|!(-?\d+)|((-?\d+)\:(-?\d+)))");
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
                if (token_match[1].length()) { return; }
                else if (token_match[2].length()) { tree.print(); }
                else if (token_match[3].length()) {
                    std::string first = token_match.str(3);
                    if (Is_number_in_limits(first)) { // !(-?\d+)
                        tree.remove(stoi(first));
                    } else { std::cerr << split_string << "超出表示范围，忽略" << std::endl; }
                } else if (token_match[4].length()) {
                    std::string first = token_match.str(5);
                    std::string second = token_match.str(6);
                    if (Is_number_in_limits(first) && Is_number_in_limits(second)) { // (-?\d+)\:(-?\d+))
                        tree.put(stoi(first), stoi(second));
                    } else { std::cerr << split_string << "超出表示范围，忽略" << std::endl; }
                } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
            } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
        }
    }
}

void tree_func_1(BinaryTree &tree) {
    std::cout << "二叉树的当前状态：\n";
    tree.print();
    std::cout << "二叉树的前序遍历打印（非递归）：\n";
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

void tree_func_3(BinaryTree &tree) { std::cout << "二叉树中的叶结点数：" << tree.leavesCount() << std::endl; }

void tree_func_4(BinaryTree &tree) {
    std::cout << "按层次顺序遍历二叉树：\n";
    tree.levelOrderBFSTraverse(print);
    std::cout << std::endl;
}

void tree_func_5(BinaryTree &tree) {
    std::string input;
    g_Clean_input();
    std::cout << "输入多组 '整数' 来构造键值对二叉树，以分隔符分离\n若存在相同键则删除，不存在则插入，'#'打印树，EOF标记或者'END'结束：\n";
    std::regex delimiter_regex(R"([\s\|\\\/,;_]+)");
    std::regex token_regex(R"((END)|(#)|(-?\d+))");
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
                if (token_match[1].length()) { return; }
                else if (token_match[2].length()) { tree.print(); }
                else if (token_match[3].length()) {
                    std::string first = token_match.str(3);
                    if (Is_number_in_limits(first)) {
                        int num = stoi(first);
                        if (tree.contain(num)) tree.remove(num);
                        else tree.put(num);
                    } else { std::cerr << split_string << "超出表示范围，忽略" << std::endl; }
                } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
            } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
        }
    }
}
}

//10:1;3:19 5:2 15:3 9:4,13:5|2:6 # !3 # 6:7 12:8 14:9 END
//10 ;3 5 15 9,13|2 # 3 # 6 12 14 # 10 # END
int main() {
    BinaryTree tree = BinaryTree();
//    tree_init(tree);
    //    tree.put(10, 12);
    //    tree.put(5, 10);
    //    tree.put(15, 15);
    //    tree.put(9, 14);
    //    tree.put(13, 15);
    //    tree.put(2, 13);
    //    tree.put(6, 13);
    //    tree.put(12, 13);
    //    tree.put(14, 13);
//    tree_func_1(tree);
//    tree_func_2(tree);
//    tree_func_3(tree);
//    tree_func_4(tree);
    tree_func_5(tree);
    return 0;
}
