//
// Created by Shane on 2017/5/9.
//

#include <queue>
#include <stack>
#include <iomanip>
#include "Graph.h"


double Edge::default_value = 0.0;

Graph::Graph(const unsigned int vertexN) : vertexN_{vertexN}, edgeN_{0U},
                                           inDegreeN_{std::vector<unsigned int>(vertexN)},
                                           adjacent_{std::vector<std::vector<Edge>>(vertexN)} { }

void Graph::validateVertex(const unsigned int v) const {
    if (v >= vertexN_) throw std::invalid_argument("Invalid");
}

void AdjacentMatrixGraph::validateVertex(const unsigned int v) const {
    if (v >= vertexN_) throw std::invalid_argument("Invalid");
}

void Graph::addUndirectedEdge(const unsigned int from, const unsigned int to, const double weight) {
    validateVertex(from);
    validateVertex(to);
    Edge edge = Edge(from, to, weight);
    adjacent_[from].push_back(edge);
    adjacent_[to].push_back(std::move(edge));
    inDegreeN_[from]++;
    inDegreeN_[to]++;
    edgeN_++;
}

void Graph::addDirectedEdge(const unsigned int from, const unsigned int to, const double weight) {
    validateVertex(from);
    validateVertex(to);
    Edge edge = Edge(from, to, weight);
    adjacent_[from].push_back(edge);
    inDegreeN_[from]++;
    edgeN_++;
}

std::ostream &operator<<(std::ostream &os, const Graph &graph) {
    auto matrix = graph.adjacentMatrix();
    for (auto &&item : matrix) {
        for (auto &&item2 : item) {
            os << std::setw(5) << std::setprecision(4) << item2 << " ";
        }
        os << std::endl;
    }
    return os;
}

const std::vector<std::vector<double>> Graph::adjacentMatrix() const {
    auto adjacent = std::vector<std::vector<double>>(vertexN_);
    adjacent.assign(vertexN_, std::vector<double>(vertexN_));
    for (const std::vector<std::vector<Edge>>::value_type &item : adjacent_) {
        for (const std::vector<Edge>::value_type &item2 : item) {
            adjacent[item2.from][item2.to] = item2.weight;
        }
    }
    return adjacent;
}

const Graph::DepthFirstPath Graph::depthFirstPathQ(const unsigned int from) const {
    return Graph::DepthFirstPath(0, this);
}

const Graph::Cycle Graph::cycleQ() const {
    return Graph::Cycle(this);
}

const Graph::BreadthFirstPath Graph::breadthFirstPathQ(const unsigned int from) const {
    return Graph::BreadthFirstPath(0, this);
}

const Graph::DepthFirstOrder Graph::depthFirstOrderQ() const {
    return Graph::DepthFirstOrder(this);
}

const std::vector<unsigned int> AdjacentMatrixGraph::BFS(const unsigned int from) {
    validateVertex(from);
    std::vector<unsigned int> result;
    std::queue<unsigned int> stack;
    bool marked[vertexN_] = { };
    stack.push(from);
    while (!stack.empty()) {
        unsigned int entry = stack.front();
        stack.pop();
        if (marked[entry]) continue;
        marked[entry] = true;
        result.push_back(entry);
        for (unsigned int i = 0U; i < vertexN_; ++i) {
            if (marked[i]) continue;
            const unsigned int index = entry * vertexN_ + i;
            if (adjacent_[index])
                stack.push(i);
        }
    }

    return result;
}

const std::vector<unsigned int> AdjacentMatrixGraph::DFS(const unsigned int from) {
    validateVertex(from);

    std::vector<unsigned int> result;
    std::stack<unsigned int> stack;
    bool marked[vertexN_] = { };
    stack.push(from);
    while (!stack.empty()) {
        unsigned int entry = stack.top();
        stack.pop();
        if (marked[entry]) continue;
        marked[entry] = true;
        result.push_back(entry);
        for (unsigned int i = 0U; i < vertexN_; ++i) {
            if (marked[i]) continue;
            const unsigned int index = entry * vertexN_ + i;
            if (adjacent_[index])
                stack.push(i);
        }
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const AdjacentMatrixGraph &graph) {
    bool *matrix = graph.adjacent_;
    for (int i = 0; i < graph.vertexN_; ++i) {
        for (int j = 0; j < graph.vertexN_; ++j) {
            os << matrix[i * graph.vertexN_ + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

//const std::vector<unsigned int> Graph::BFS(const unsigned int source) const {
//    validateVertex(source);
//    std::vector<unsigned int> result;
//    std::queue<unsigned int> queue;
//    bool marked[vertexN_] = { };
//    queue.push(source);
//    while (!queue.empty()) {
//        auto neighbor_p = adjacent_.find(queue.front());
//        queue.pop();
//        if (neighbor_p != adjacent_.end()) {
//            auto &self = neighbor_p->first;
//            if (marked[self]) continue;
//            marked[self] = true;
//            result.push_back(self);
//            for (auto &&entry : neighbor_p->second) {
//                if (!marked[entry]) {
//                    queue.push(entry);
//                }
//            }
//        }
//    }
//
//    return result;
//}
//
//const std::vector<unsigned int> Graph::DFS(const unsigned int source) const {
//    validateVertex(source);
//    std::vector<unsigned int> result;
//    std::stack<unsigned int> stack;
//    bool marked[vertexN_] = { };
//    stack.push(source);
//    while (!stack.empty()) {
//        auto neighbor_p = adjacent_.find(stack.top());
//        stack.pop();
//        if (neighbor_p != adjacent_.end()) {
//            auto &self = neighbor_p->first;
//            if (marked[self]) continue;
//            marked[self] = true;
//            result.push_back(self);
//            for (auto &&entry : neighbor_p->second) {
//                if (!marked[entry]) {
//                    stack.push(entry);
//                }
//            }
//        }
//    }
//
//    return result;
//}

bool Graph::Path::hasPathTo(const unsigned int to) {
    graph->validateVertex(to);
    return marked[to];
}

void Graph::DepthFirstPath::dfs(const unsigned int vertex) {
    marked[vertex] = true;
    for (auto &&item : graph->adjacent_[vertex]) {
        if (!marked[item.to]) {
            edgeTo[item.to] = vertex;
            distTo[item.to] = distTo[item.from] + 1;
            dfs(item.to);
        }
    }
}

int Graph::Path::distanceTo(const unsigned int vertex) {
    graph->validateVertex(vertex);
    return distTo[vertex];
}

const std::vector<unsigned int> Graph::Path::pathTo(const unsigned int to) {
    graph->validateVertex(to);
    if (!hasPathTo(to)) return { };
    std::stack<unsigned int> path;
    for (auto x = to; x != source; x = edgeTo[x]) {
        path.push(x);
    }
    path.push(source);
    return std::vector<unsigned int>(&path.top() + 1 - path.size(), &path.top() + 1);
}

void Graph::BreadthFirstPath::bfs(const unsigned int vertex) {
    std::queue<unsigned int> queue;
    queue.push(vertex);
    while (!queue.empty()) {
        auto q = queue.front();
        queue.pop();
        marked[q] = true;
        for (auto &&item : graph->adjacent_[q]) {
            if (!marked[item.to]) {
                edgeTo[item.to] = q;
                distTo[item.to] = distTo[item.from] + 1;
                queue.push(item.to);
            }
        }
    }
}

bool Graph::Cycle::cycleQ() const {
    return cycle.size() > 0;
}

void Graph::Cycle::dfs(const unsigned int vertex) {
    onStack[vertex] = true;
    marked[vertex] = true;
    for (auto &&item : graph->adjacent_[vertex]) {
        if (cycleQ()) return;
        if (!marked[item.to]) {
            edgeTo[item.to] = vertex;
            dfs(item.to);
        } else if (onStack[item.to]) {
            auto x = item.to;
            while (x != item.from) {
                cycle.push(x);
                x = edgeTo[x];
            }
            cycle.push(item.to);
            return;
        }
    }
    onStack[vertex] = false;
}

const std::stack<unsigned int> &Graph::Cycle::getCycle() const {
    return cycle;
}

Graph::DepthFirstOrder::DepthFirstOrder(const Graph *graph) : graph(graph),
                                                              marked{std::vector<bool>(graph->vertexN_)},
                                                              pre{std::vector<unsigned int>(graph->vertexN_)},
                                                              post{std::vector<unsigned int>(graph->vertexN_)},
                                                              preOrder{ },
                                                              postOrder{ },
                                                              preCounter{0},
                                                              postCounter{0} {
    for (unsigned int i = 0; i < graph->vertexN_; ++i) {
        if (!marked[i]) dfs(i);
    }
}

void Graph::DepthFirstOrder::dfs(const unsigned int vertex) {
    marked[vertex] = true;
    pre[vertex] = preCounter++;
    preOrder.push(vertex);
    for (auto &&item : graph->adjacent_[vertex]) {
        if (!marked[item.to]) dfs(item.to);
    }
    postOrder.push(vertex);
    post[vertex] = postCounter++;
}

const std::queue<unsigned int> &Graph::DepthFirstOrder::getPreOrder() const {
    return preOrder;
}

const std::queue<unsigned int> &Graph::DepthFirstOrder::getPostOrder() const {
    return postOrder;
}

unsigned int Graph::DepthFirstOrder::previousIndex(const unsigned int which) const {
    graph->validateVertex(which);
    return pre[which];
}

unsigned int Graph::DepthFirstOrder::postIndex(const unsigned int which) const {
    graph->validateVertex(which);
    return post[which];
}
