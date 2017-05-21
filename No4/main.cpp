#include <iostream>
#include <limits>
#include <regex>
#include "Graph.h"


namespace {
auto print_vector = [](const std::vector<unsigned int> &vector) -> void {
    std::cout << '[';
    for (auto &i: vector) {
        std::cout << i << ", ";
    }
    std::cout << "\b\b]" << std::endl;
};
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

void graph_init(AdjacentMatrixGraph &graph) {
    std::string input;
    g_Clean_input();
    std::cout << "->有向边；<->无向边；D深度优先；B广度优先\n"
        "例子：0->7 1->5 0->4 2<->3 1<->7 0->2 1->2 1->3 2<->7 6->2 3<->6 6->0 6->4 # D3 @ B4 END\n"
        "以分隔符分离，'#'打印邻接矩阵，'@'打印邻接表，EOF标记或者'END'结束：\n";
    std::regex delimiter_regex(R"([\s\|\\\/,;_]+)");
    std::regex token_regex(R"((END)|(#)|(@)|((\d+)(->|<->)(\d+))|B(\d+)|D(\d+))");
    while (getline(std::cin, input)) {
        auto token_iterator = std::sregex_token_iterator(input.begin(), input.end(), delimiter_regex, -1);
        while (token_iterator != std::sregex_token_iterator()) {
            std::string split_string = token_iterator->str();
            ++token_iterator;
            if (split_string.empty()) continue;
            std::smatch token_match;
            if (regex_search(split_string, token_match, token_regex)) {
                if (token_match[1].length()) { return; }
                else if (token_match[2].length()) { graph.prettyPrintAdjacentMatrix(std::cout); }
                else if (token_match[3].length()) { graph.prettyPrintAdjacentTable(std::cout); }
                else if (token_match[4].length()) {
                    std::string first = token_match.str(5);
                    std::string method = token_match.str(6);
                    std::string second = token_match.str(7);
                    if (Is_number_in_limits(first) && Is_number_in_limits(second)) {
                        if (method == "<->")
                            graph.addBidirectedEdge(static_cast<unsigned int>(std::stoi(first)),
                                                    static_cast<unsigned int>(std::stoi(second)));
                        else if (method == "->")
                            graph.addDirectedEdge(static_cast<unsigned int>(std::stoi(first)),
                                                  static_cast<unsigned int>(std::stoi(second)));
                    } else { std::cerr << split_string << "数字范围不正确" << std::endl; }
                } else if (token_match[8].length() && Is_number_in_limits(token_match.str(8))) {
                    print_vector(graph.BFS(static_cast<unsigned int>(std::stoi(token_match.str(8)))));
                } else if (token_match[9].length() && Is_number_in_limits(token_match.str(9))) {
                    print_vector(graph.DFS(static_cast<unsigned int>(std::stoi(token_match.str(9)))));
                } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
            } else { std::cerr << split_string << "未能识别，忽略" << std::endl; }
        }
    }
}


int main() {
    std::cout << "输入图的顶点数：";
    unsigned int vec;
    std::cin >> vec;
    AdjacentMatrixGraph graph(vec);
    graph_init(graph);
//    Graph g = Graph(8);
//    g.addDirectedEdge(4, 5, 0.35);
//    g.addDirectedEdge(5, 4, 0.35);
//    g.addDirectedEdge(4, 7, 0.37);
//    g.addDirectedEdge(5, 7, 0.28);
//    g.addDirectedEdge(7, 5, 0.28);
//    g.addDirectedEdge(5, 1, 0.32);
//    g.addDirectedEdge(0, 4, 0.38);
//    g.addDirectedEdge(0, 2, 0.26);
//    g.addDirectedEdge(7, 3, 0.39);
//    g.addDirectedEdge(1, 3, 0.29);
//    g.addDirectedEdge(2, 7, 0.34);
//    g.addDirectedEdge(6, 2, 0.40);
//    g.addDirectedEdge(3, 6, 0.52);
//    g.addDirectedEdge(6, 0, 0.58);
//    g.addDirectedEdge(6, 4, 0.93);
//    g.addDirectedEdge(4, 5, 0.35);
//    g.addDirectedEdge(4, 7, 0.37);
//    g.addDirectedEdge(5, 7, 0.28);
//    g.addDirectedEdge(0, 7, 0.16);
//    g.addDirectedEdge(1, 5, 0.32);
//    g.addDirectedEdge(0, 4, 0.38);
//    g.addDirectedEdge(2, 3, 0.17);
//    g.addDirectedEdge(1, 7, 0.19);
//    g.addDirectedEdge(0, 2, 0.26);
//    g.addDirectedEdge(1, 2, 0.36);
//    g.addDirectedEdge(1, 3, 0.29);
//    g.addDirectedEdge(2, 7, 0.34);
//    g.addDirectedEdge(6, 2, 0.40);
//    g.addDirectedEdge(3, 6, 0.52);
//    g.addDirectedEdge(6, 0, 0.58);
//    g.addDirectedEdge(6, 4, 0.93);
//    auto a  = g.depthFirstPathQ(0);
//    auto b  = g.breadthFirstPathQ(0);
//    auto c  = g.cycleQ();
//    auto d  = g.depthFirstOrderQ();
//    auto e  = g.connectedComponentQ();
//    auto f  = g.topologicalSort();
//    auto h  = g.kosarajuSharirStrongConnectedComponent();
//    auto i  = g.primMinimumSpanningTree();
//    auto j  = g.kruskalMinimumSpanningTree();
//    std::cout << g << std::endl;

    return 0;
}
