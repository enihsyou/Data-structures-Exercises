//
// Created by Shane on 2017/5/9.
//

#include <queue>
#include <stack>
#include "Graph.h"


Graph::Graph(const unsigned int vertexN) : vertexN_{vertexN} { }

void Graph::validateVertex(const unsigned int v) const {
    if (v >= vertexN_) throw std::invalid_argument("Invalid");
}

void Graph::addUndirectedEdge(const unsigned int from, const unsigned int to) {
    validateVertex(from);
    validateVertex(to);
    adjacent_[from].insert(to);
    adjacent_[to].insert(from);
    edgeN_++;
}

void Graph::addDirectedEdge(const unsigned int from, const unsigned int to) {
    validateVertex(from);
    validateVertex(to);
    adjacent_[from].insert(to);
    edgeN_++;
}

unsigned int *Graph::adjacentMatrix() const {
    unsigned int *adjacent = new unsigned int[vertexN_ * vertexN_]{0};
    for (auto &&item : adjacent_) {
        for (auto &&entry : item.second) {
            adjacent[item.first * vertexN_ + entry] = 1;
        }
    }
    return adjacent;
}

std::ostream &operator<<(std::ostream &os, const Graph &graph) {
    auto matrix = graph.adjacentMatrix();
    for (int i = 0; i < graph.vertexN_; ++i) {
        for (int j = 0; j < graph.vertexN_; ++j) {
            os << matrix[i * graph.vertexN_ + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

const std::vector<unsigned int> BFS(const unsigned int *adjacent_matrix,
                                    const unsigned int size,
                                    const unsigned int from) {
    if (from >= size) throw std::invalid_argument("Invalid");
    std::vector<unsigned int> result;
    std::queue<unsigned int> stack;
    bool marked[size] = { };
    stack.push(from);
    while (!stack.empty()) {
        unsigned int entry = stack.front();
        stack.pop();
        if (marked[entry]) continue;
        marked[entry] = true;
        result.push_back(entry);
        for (unsigned int i = 0U; i < size; ++i) {
            if (marked[i]) continue;
            const unsigned int index = entry * size + i;
            if (adjacent_matrix[index])
                stack.push(i);
        }
    }

    return result;
}
const std::vector<unsigned int> DFS(const unsigned int *adjacent_matrix,
                                    const unsigned int size,
                                    const unsigned int from) {
    if (from >= size) throw std::invalid_argument("Invalid");
    std::vector<unsigned int> result;
    std::stack<unsigned int> stack;
    bool marked[size] = { };
    stack.push(from);
    while (!stack.empty()) {
        unsigned int entry = stack.top();
        stack.pop();
        if (marked[entry]) continue;
        marked[entry] = true;
        result.push_back(entry);
        for (unsigned int i = 0U; i < size; ++i) {
            if (marked[i]) continue;
            const unsigned int index = entry * size + i;
            if (adjacent_matrix[index])
                stack.push(i);
        }
    }

    return result;
}

const std::vector<unsigned int> Graph::BFS(const unsigned int from) const {
    validateVertex(from);
    std::vector<unsigned int> result;
    std::queue<unsigned int> queue;
    bool marked[vertexN_] = { };
    queue.push(from);
    while (!queue.empty()) {
        auto neighbor_p = adjacent_.find(queue.front());
        queue.pop();
        if (neighbor_p != adjacent_.end()) {
            auto &self = neighbor_p->first;
            if (marked[self]) continue;
            marked[self] = true;
            result.push_back(self);
            for (auto &&entry : neighbor_p->second) {
                if (!marked[entry]) {
                    queue.push(entry);
                }
            }
        }
    }

    return result;
}

const std::vector<unsigned int> Graph::DFS(const unsigned int from) const {
    validateVertex(from);
    std::vector<unsigned int> result;
    std::stack<unsigned int> stack;
    bool marked[vertexN_] = { };
    stack.push(from);
    while (!stack.empty()) {
        auto neighbor_p = adjacent_.find(stack.top());
        stack.pop();
        if (neighbor_p != adjacent_.end()) {
            auto &self = neighbor_p->first;
            if (marked[self]) continue;
            marked[self] = true;
            result.push_back(self);
            for (auto &&entry : neighbor_p->second) {
                if (!marked[entry]) {
                    stack.push(entry);
                }
            }
        }
    }

    return result;
}

