#include <queue>
#include <stack>
#include <iomanip>
#include <algorithm>
#include "Graph.h"


double Edge::default_value = 0.0;

Edge::Edge(const unsigned int from, const unsigned int to, const double weight)
    : from(from),
      to(to),
      weight(weight) { }

std::ostream &operator<<(std::ostream &os, const Edge &edge) {
    os << "from: " << edge.from << " to: " << edge.to << " weight: " << edge.weight;
    return os;
}

unsigned int Edge::other(const unsigned int v) const {
    if (v == from) return to;
    if (v == to) return from;
    throw std::runtime_error("not consistence");
}

bool Edge::operator<(const Edge &rhs) const {
    return weight < rhs.weight;
}

bool Edge::operator>(const Edge &rhs) const {
    return rhs < *this;
}

bool Edge::operator<=(const Edge &rhs) const {
    return !(rhs < *this);
}

bool Edge::operator>=(const Edge &rhs) const {
    return !(*this < rhs);
}

bool Edge::operator==(const Edge &rhs) const {
    return std::tie(from, to, weight) == std::tie(rhs.from, rhs.to, rhs.weight);
}

bool Edge::operator!=(const Edge &rhs) const {
    return !(rhs == *this);
}


const std::vector<unsigned int> AdjacentMatrixGraph::BFS(const unsigned int from) const {
    validateVertex(from);

    std::vector<unsigned int> result;
    std::queue<unsigned int> queue;
    bool marked[vertexN_] = { };
    queue.push(from);
    while (!queue.empty()) {
        unsigned int entry = queue.front();
        queue.pop();
        if (marked[entry]) continue;

        marked[entry] = true;
        result.push_back(entry);
        for (unsigned int i = 0U; i < vertexN_; ++i) {
            if (marked[i]) continue;
            const unsigned int index = entry * vertexN_ + i;
            if (adjacent_[index])
                queue.push(i);
        }
    }

    return result;
}

const std::vector<unsigned int> AdjacentMatrixGraph::DFS(const unsigned int from) const {
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
        for (int i = vertexN_ - 1; i >= 0; --i) {
            if (marked[i]) continue;
            const unsigned int index = entry * vertexN_ + i;
            if (adjacent_[index])
                stack.push(static_cast<unsigned int>(i));
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

AdjacentMatrixGraph::AdjacentMatrixGraph(const unsigned int vertexN)
    : vertexN_(vertexN),
      adjacent_{new bool[vertexN * vertexN]{ }} { }

AdjacentMatrixGraph::~AdjacentMatrixGraph() {
    delete[](adjacent_);
}

void AdjacentMatrixGraph::validateVertex(const unsigned int v) const {
    if (v >= vertexN_) throw std::invalid_argument("Invalid");
}

void AdjacentMatrixGraph::addBidirectedEdge(const unsigned int v, const unsigned int w) {
    validateVertex(v);
    validateVertex(w);
    adjacent_[v * vertexN_ + w] = true;
    adjacent_[w * vertexN_ + v] = true;
}

void AdjacentMatrixGraph::addDirectedEdge(const unsigned int from, const unsigned int to) {
    validateVertex(from);
    validateVertex(to);
    adjacent_[from * vertexN_ + to] = true;
}

const std::vector<std::vector<bool>> AdjacentMatrixGraph::adjacentMatrix() const {
    std::vector<std::vector<bool>> result;
    for (int i = 0; i < vertexN_; ++i) {
        result.push_back(std::vector<bool>(adjacent_ + i * vertexN_, adjacent_ + (i + 1) * vertexN_));
    }
    return result;
}

void AdjacentMatrixGraph::prettyPrintAdjacentMatrix(std::ostream &os) const {
    if (vertexN_ > PRINT_LENGTH_LIMIT) {
        os << vertexN_ << " too huge" << std::endl;
        return;
    }

    int number_length = std::max(2, static_cast<int>(std::to_string(vertexN_).length()));
    os << std::setw(number_length) << "╲";
    for (int i = 0; i < vertexN_; i++) {
        os << std::setw(number_length) << i;
    }
    os << std::endl;

    for (int i = 0; i < vertexN_; ++i) {
        os << std::setw(number_length) << i;
        for (int j = 0; j < vertexN_; ++j) {
            os << std::setw(number_length) << adjacent_[i * vertexN_ + j];
        }
        os << std::endl;
    }
}

void AdjacentMatrixGraph::prettyPrintAdjacentTable(std::ostream &os) const {
    int number_length = std::max(2, static_cast<int>(std::to_string(vertexN_).length()));

    for (int i = 0; i < vertexN_; ++i) {
        os << std::setw(number_length) << i << "-->";
        for (int j = 0; j < vertexN_; ++j) {
            if (adjacent_[i * vertexN_ + j]) os << std::setw(number_length) << j;
        }
        os << std::endl;
    }
}


//const std::vector<unsigned int> Graph::BFS(const unsigned int source_) const {
//    validateVertex(source_);
//    std::vector<unsigned int> result;
//    std::queue<unsigned int> queue;
//    bool marked_[vertexN_] = { };
//    queue.push(source_);
//    while (!queue.empty()) {
//        auto neighbor_p = adjacent_.find(queue.front());
//        queue.pop();
//        if (neighbor_p != adjacent_.end()) {
//            auto &self = neighbor_p->first;
//            if (marked_[self]) continue;
//            marked_[self] = true;
//            result.push_back(self);
//            for (auto &&entry : neighbor_p->second) {
//                if (!marked_[entry]) {
//                    queue.push(entry);
//                }
//            }
//        }
//    }
//
//    return result;
//}
//
//const std::vector<unsigned int> Graph::DFS(const unsigned int source_) const {
//    validateVertex(source_);
//    std::vector<unsigned int> result;
//    std::stack<unsigned int> stack;
//    bool marked_[vertexN_] = { };
//    stack.push(source_);
//    while (!stack.empty()) {
//        auto neighbor_p = adjacent_.find(stack.top());
//        stack.pop();
//        if (neighbor_p != adjacent_.end()) {
//            auto &self = neighbor_p->first;
//            if (marked_[self]) continue;
//            marked_[self] = true;
//            result.push_back(self);
//            for (auto &&entry : neighbor_p->second) {
//                if (!marked_[entry]) {
//                    stack.push(entry);
//                }
//            }
//        }
//    }
//
//    return result;
//}

Graph::Graph(const unsigned int vertexN) : vertexN_{vertexN},
                                           edgeN_{0U},
                                           inDegreeN_{std::vector<unsigned int>(vertexN)},
                                           adjacent_{std::vector<std::vector<Edge>>(vertexN)} { }

void Graph::validateVertex(const unsigned int v) const {
    if (v >= vertexN_) throw std::invalid_argument("Invalid");
}

void Graph::addBidirectedEdge(const unsigned int from, const unsigned int to, const double weight) {
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

const Graph::BreadthFirstPath Graph::breadthFirstPathQ(const unsigned int from) const {
    return Graph::BreadthFirstPath(0, this);
}

const Graph::Cycle Graph::cycleQ() const {
    return Graph::Cycle(this);
}

const Graph::DepthFirstOrder Graph::depthFirstOrderQ() const {
    return Graph::DepthFirstOrder(this);
}

const Graph::ConnectedComponent Graph::connectedComponentQ() const {
    return Graph::ConnectedComponent(this);
}

const Graph::TopologicalSort Graph::topologicalSort() const {
    return Graph::TopologicalSort(this);
}

Graph Graph::reverse() const {
    Graph graph = Graph(vertexN_);
    for (auto &&item : adjacent_) {
        for (auto &&item2 : item) {
            graph.addBidirectedEdge(item2.to, item2.from);
        }
    }
    return graph;
}

const Graph::KosarajuSharirStrongConnectedComponent Graph::kosarajuSharirStrongConnectedComponent() const {
    return Graph::KosarajuSharirStrongConnectedComponent(this);
}

const Graph::PrimMinimumSpanningTree Graph::primMinimumSpanningTree() const {
    return Graph::PrimMinimumSpanningTree(this);
}

const Graph::KruskalMinimumSpanningTree Graph::kruskalMinimumSpanningTree() const {
    return Graph::KruskalMinimumSpanningTree(this);
}

void Graph::DepthFirstPath::dfs(const unsigned int vertex) {
    marked_[vertex] = true;
    for (auto &&item : graph_->adjacent_[vertex]) {
        if (!marked_[item.to]) {
            edgeTo_[item.to] = vertex;
            distTo_[item.to] = distTo_[item.from] + 1;
            dfs(item.to);
        }
    }
}

Graph::DepthFirstPath::DepthFirstPath(const unsigned int source, const Graph *graph) : Path{source, graph} {
    graph->validateVertex(source);
    distTo_[source] = 0;
    dfs(source);
}

Graph::Path::Path(const unsigned int source, const Graph *graph) : source_{source},
                                                                   graph_{graph},
                                                                   marked_{std::vector<bool>(graph->vertexN_)},
                                                                   distTo_{
                                                                       std::vector<unsigned int>(graph->vertexN_, -1)},
                                                                   edgeTo_{
                                                                       std::vector<unsigned int>(graph->vertexN_)} { }

bool Graph::Path::hasPathTo(const unsigned int to) {
    graph_->validateVertex(to);
    return marked_[to];
}

int Graph::Path::distanceTo(const unsigned int vertex) {
    graph_->validateVertex(vertex);
    return distTo_[vertex];
}

const std::vector<unsigned int> Graph::Path::pathTo(const unsigned int to) {
    graph_->validateVertex(to);
    if (!hasPathTo(to)) return { };
    std::stack<unsigned int> path;
    for (auto x = to; x != source_; x = edgeTo_[x]) {
        path.push(x);
    }
    path.push(source_);
    return std::vector<unsigned int>(&path.top() + 1 - path.size(), &path.top() + 1);
}

void Graph::BreadthFirstPath::bfs(const unsigned int vertex) {
    std::queue<unsigned int> queue;
    queue.push(vertex);
    while (!queue.empty()) {
        auto q = queue.front();
        queue.pop();
        marked_[q] = true;
        for (auto &&item : graph_->adjacent_[q]) {
            if (!marked_[item.to]) {
                edgeTo_[item.to] = q;
                distTo_[item.to] = distTo_[item.from] + 1;
                queue.push(item.to);
            }
        }
    }
}

Graph::BreadthFirstPath::BreadthFirstPath(const unsigned int source, const Graph *graph) : Path{source, graph} {
    graph->validateVertex(source);
    distTo_[source] = 0;
    bfs(source);
}

bool Graph::Cycle::cycleQ() const {
    return cycle_.size() > 0;
}

void Graph::Cycle::dfs(const unsigned int vertex) {
    onStack_[vertex] = true;
    marked_[vertex] = true;
    for (auto &&item : graph_->adjacent_[vertex]) {
        if (cycleQ()) return;
        if (!marked_[item.to]) {
            edgeTo_[item.to] = vertex;
            dfs(item.to);
        } else if (onStack_[item.to]) {
            auto x = item.to;
            while (x != item.from) {
                cycle_.push(x);
                x = edgeTo_[x];
            }
            cycle_.push(item.to);
            return;
        }
    }
    onStack_[vertex] = false;
}

const std::stack<unsigned int> &Graph::Cycle::getCycle() const {
    return cycle_;
}

Graph::Cycle::Cycle(const Graph *graph) : graph_{graph},
                                          cycle_{ },
                                          onStack_{std::vector<bool>(graph->vertexN_)},
                                          edgeTo_{std::vector<unsigned int>(graph->vertexN_)},
                                          marked_{std::vector<bool>(graph->vertexN_)} { }

Graph::DepthFirstOrder::DepthFirstOrder(const Graph *graph) : graph_(graph),
                                                              marked_{std::vector<bool>(graph->vertexN_)},
                                                              preList_{std::vector<unsigned int>(graph->vertexN_)},
                                                              postList_{std::vector<unsigned int>(graph->vertexN_)},
                                                              preOrder_{ },
                                                              postOrder_{ },
                                                              preCounter_{0},
                                                              postCounter_{0} {
    for (unsigned int i = 0; i < graph->vertexN_; ++i) {
        if (!marked_[i]) dfs(i);
    }
}

void Graph::DepthFirstOrder::dfs(const unsigned int vertex) {
    marked_[vertex] = true;
    preList_[vertex] = preCounter_++;
    preOrder_.push(vertex);
    for (auto &&item : graph_->adjacent_[vertex]) {
        if (!marked_[item.to]) dfs(item.to);
    }
    postOrder_.push(vertex);
    postList_[vertex] = postCounter_++;
}

const std::queue<unsigned int> &Graph::DepthFirstOrder::getPreOrder() const {
    return preOrder_;
}

const std::queue<unsigned int> &Graph::DepthFirstOrder::getPostOrder() const {
    return postOrder_;
}

unsigned int Graph::DepthFirstOrder::previousIndex(const unsigned int which) const {
    graph_->validateVertex(which);
    return preList_[which];
}

unsigned int Graph::DepthFirstOrder::postIndex(const unsigned int which) const {
    graph_->validateVertex(which);
    return postList_[which];
}

const std::vector<unsigned int> Graph::DepthFirstOrder::reversePostOrder() const {
    std::vector<unsigned int> reversed_vector;
    std::queue<unsigned int> temp_queue = postOrder_;
    while (!temp_queue.empty()) {
        reversed_vector.push_back(temp_queue.front());
        temp_queue.pop();
    }
    std::reverse(reversed_vector.begin(), reversed_vector.end());
    return reversed_vector;
}


Graph::ConnectedComponent::ConnectedComponent(const Graph *graph)
    : graph_(graph),
      marked_(std::vector<bool>(graph->vertexN_)),
      componentId_(std::vector<unsigned int>(graph->vertexN_)),
      idSize_(std::vector<unsigned int>(graph->vertexN_)),
      componentN_(0U) {
    for (unsigned int i = 0; i < graph->vertexN_; ++i) {
        if (!marked_[i]) {
            dfs(i);
            componentN_++;
        }
    }
}

void Graph::ConnectedComponent::dfs(const unsigned int vertex) {
    marked_[vertex] = true;
    componentId_[vertex] = componentN_;
    idSize_[componentN_]++;
    for (auto &&item : graph_->adjacent_[vertex]) {
        if (!marked_[item.to]) dfs(item.to);
    }
}

unsigned int Graph::ConnectedComponent::componentId(const unsigned int which) const {
    graph_->validateVertex(which);
    return componentId_[which];
}

unsigned int Graph::ConnectedComponent::componentSize(const unsigned int which) const {
    graph_->validateVertex(which);
    return idSize_[componentId_[which]];
}

unsigned int Graph::ConnectedComponent::count() const {
    return componentN_;
}

void Graph::ConnectedComponent::makeUnion(const unsigned int first, const unsigned int second) {
    auto id1 = componentId(first), id2 = componentId(second);
    if (id1 == id2) return;
    for (auto &&item : componentId_) {
        if (item == id2) item = id1;
    }
    idSize_[id1] += idSize_[id2];
    idSize_[id2] = 0;
    componentN_--;
}

bool Graph::ConnectedComponent::isConnected(const unsigned int first, const unsigned int second) {
    graph_->validateVertex(first);
    graph_->validateVertex(second);
    return componentId_[first] == componentId_[second];
}

Graph::TopologicalSort::TopologicalSort(const Graph *graph)
    : graph_(graph), rank_(std::vector<unsigned int>(graph->vertexN_)) {
    Cycle finder = Cycle(graph);
    if (!finder.cycleQ()) {
        DepthFirstOrder depthFirstOrder = DepthFirstOrder(graph);
        order_ = depthFirstOrder.reversePostOrder();
        unsigned int i = 0;
        for (auto &&item : order_) {
            rank_[item] = i++;
        }
    }
}

bool Graph::TopologicalSort::hasOrder() const {
    return !order_.empty();
}

unsigned int Graph::TopologicalSort::rank(const unsigned int which) {
    graph_->validateVertex(which);
    if (hasOrder()) return rank_[which];
    throw std::runtime_error("cycle");
}

Graph::KosarajuSharirStrongConnectedComponent::KosarajuSharirStrongConnectedComponent(const Graph *graph)
    : ConnectedComponent(graph) {
    const Graph &graph1 = graph->reverse();
    DepthFirstOrder depthFirstOrder = DepthFirstOrder(&graph1);
    for (auto &&v : depthFirstOrder.reversePostOrder()) {
        if (!marked_[v]) {
            dfs(v);
            componentN_++;
        }
    }
}

Graph::PrimMinimumSpanningTree::PrimMinimumSpanningTree(const Graph *graph)
    : graph_(graph),
      edgeTo_(std::vector<unsigned int>(graph->vertexN_)),
      marked_(std::vector<bool>(graph->vertexN_)),
      priorityQueue_(std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>()) {
    for (unsigned int i = 0; i < graph->vertexN_; ++i) {
        if (!marked_[i]) prim(i);
    }
}

void Graph::PrimMinimumSpanningTree::prim(unsigned int vertex) {
    scan(vertex);
    while (!priorityQueue_.empty()) {
        auto e = priorityQueue_.top();
        priorityQueue_.pop();
        auto v = e.from, w = e.other(v);
        if (marked_[v] && marked_[w]) continue;
        mst_.push(e);
        weight_ += e.weight;
        if (!marked_[v]) scan(v);
        if (!marked_[w]) scan(w);
    }
}

void Graph::PrimMinimumSpanningTree::scan(unsigned int vertex) {
    marked_[vertex] = true;
    for (auto &&item : graph_->adjacent_[vertex]) {
        if (!marked_[item.other(vertex)]) priorityQueue_.push(item);
    }
}

double Graph::PrimMinimumSpanningTree::weight() const {
    return weight_;
}

const std::queue<Edge> &Graph::PrimMinimumSpanningTree::mst() const {
    return mst_;
}

Graph::KruskalMinimumSpanningTree::KruskalMinimumSpanningTree(const Graph *graph) : graph_(graph) {
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> priority_queue;
    for (auto &&item : graph->adjacent_) {
        for (auto &&item2 : item) {
            priority_queue.push(item2);
        }
    }

    ConnectedComponent cc = ConnectedComponent(graph_);
    while (!priority_queue.empty() && mst_.size() < graph_->vertexN_ - 1) {
        auto e = priority_queue.top();
        auto v = e.from, w = e.other(v);
        priority_queue.pop();
        if (!cc.isConnected(v, w)) {
            cc.makeUnion(v, w);
            mst_.push(e);
            weight_ += e.weight;
        }
    }
}
