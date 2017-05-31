#include <iostream>
#include <limits>
#include <regex>
#include <random>
#include "LinkedList.h"


namespace {
auto Is_number_in_limits = [](const std::string &a) -> bool {
    if (a.length() > 11) return false;
    long long tmp = std::stoll(a);
    if (tmp > 0
        && tmp / (static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) + 1) >= 1)
        return false;
    else if (tmp < 0
        && tmp / (static_cast<unsigned long long>(std::numeric_limits<unsigned int>::min()) - 1) >= 1)
        return false;
    return true;
};
}

void g_Clean_input() {
    std::cin.clear();
    std::cin.putback('\n');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void insert_func() {
    LinkedList<int> linkedList{ };
    std::string input;
    g_Clean_input();
    std::cout << "输入多个 '整数' 来指定要排序的列表，以分隔符分离\n"
        "输入'R\\d+'代表随机生成，最后用'I'指定插入排序，'S'指定选择排序\n"
        "EOF标记或者'END'结束并输出排序结果，例如'R20 IEND'：\n";
    std::regex delimiter_regex(R"([\s\|\\\/,;_]+)");
    std::regex token_regex(R"(((I|S)END)|R(\d+)|(\d+))");
    while (getline(std::cin, input)) {
        auto token_iterator = std::sregex_token_iterator(input.begin(), input.end(), delimiter_regex, -1);
        while (token_iterator != std::sregex_token_iterator()) {
            std::string split_string = token_iterator->str();
            ++token_iterator;
            if (split_string.empty()) continue;
            std::smatch token_match;
            if (regex_search(split_string, token_match, token_regex)) {
                if (token_match[1].length()) {
                    std::string string = token_match.str(2);

                    linkedList.print();
                    std::cout << std::endl;
                    if (string == "I") linkedList.insert_sort();
                    else linkedList.select_sort();
                    std::cout << std::endl;
                    linkedList.print();
                    return;
                } else if (token_match[3].length()) {
                    std::string string_size = token_match.str(3);
                    if (Is_number_in_limits(string_size)) {
                        const int size = stoi(string_size);
                        std::random_device device;
                        std::uniform_int_distribution<int> distribution(0, 2 * size);
                        for (int i = 0; i < size; ++i) {
                            linkedList.insert(distribution(device));
                        }
                    } else { std::cerr << split_string << "超出表示范围，忽略" << std::endl; }
                } else if (token_match[4].length()) {
                    std::string first = token_match.str(4);
                    if (Is_number_in_limits(first)) {
                        linkedList.insert(stoi(first));
                    } else { std::cerr << split_string << "超出表示范围，忽略" << std::endl; }
                } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
            } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
        }
    }
}

//7 3 4 5 6 2 3 8 END
int main() {
    insert_func();
    return 0;
}
