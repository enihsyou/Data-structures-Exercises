#ifndef NO4_GRAPH_H
#define NO4_GRAPH_H
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <ostream>


struct Edge {
    unsigned int from = 0U;
    unsigned int to = 0U;
    double weight = 0.0;
    Edge() {};
    Edge(const unsigned int from, const unsigned int to, const double weight = default_value);

//    Edge(const Edge & edge);
    unsigned int other(const unsigned int v) const;
    bool operator<(const Edge &rhs) const;
    bool operator>(const Edge &rhs) const;
    bool operator<=(const Edge &rhs) const;
    bool operator>=(const Edge &rhs) const;
    bool operator==(const Edge &rhs) const;
    bool operator!=(const Edge &rhs) const;
    static double default_value;

    static void setDefault(const double new_default) { Edge::default_value = new_default; };

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge);
};


//struct UndirectedEdge : public Edge {
//    UndirectedEdge(const unsigned int from, const unsigned int to, const double weight = default_value)
//        : Edge(from, to, weight) { };
//};
//
//struct DirectedEdge : public Edge {
//    DirectedEdge(const unsigned int from, const unsigned int to, const double weight = default_value)
//        : Edge(from, to, weight) { };
//};

class AdjacentMatrixGraph {
    static const unsigned int PRINT_LENGTH_LIMIT = 78;

    const unsigned int vertexN_ = 0U;
    bool *adjacentMatrix_;
    std::vector<std::set<unsigned int>> adjacentTable_;

    void validateVertex(const unsigned int v) const;
public:
    AdjacentMatrixGraph(const unsigned int vertexN);
    ~AdjacentMatrixGraph();
    void addBidirectedEdge(const unsigned int v, const unsigned int w);
    void addDirectedEdge(const unsigned int from, const unsigned int to);
    const std::vector<std::vector<bool>>adjacentMatrix() const;
    const std::vector<std::set<unsigned int>> adjacentTable() const;
    void prettyPrintAdjacentMatrix(std::ostream &os) const;
    void prettyPrintAdjacentTable(std::ostream &os) const;
    const std::vector<unsigned int> BFS(const unsigned int from) const;
    const std::vector<unsigned int> DFS(const unsigned int from) const;
    friend std::ostream &operator<<(std::ostream &os, const AdjacentMatrixGraph &graph);
};

/*EdgeWeightedDigraph*/
class Graph {
    const unsigned int vertexN_;
    unsigned int edgeN_;
    std::vector<unsigned int> inDegreeN_;
    std::vector<std::vector<Edge>> adjacent_;
    //    std::vector<std::string> label_;

    void validateVertex(const unsigned int v) const;

    enum STATUS {
        OK,
        READY,
        FAIL
    };

    class Path {
    protected:
        const Graph *graph_;
        const unsigned int source_;
        std::vector<unsigned int> edgeTo_;
        std::vector<unsigned int> distTo_;
        std::vector<bool> marked_;
    public:
        Path(const unsigned int source, const Graph *graph);;
        bool hasPathTo(const unsigned int to);
        const std::vector<unsigned int> pathTo(const unsigned int to);
        int distanceTo(const unsigned int vertex);
    };

    class DepthFirstPath : public Path {
        void dfs(const unsigned int vertex);
    public:
        DepthFirstPath(const unsigned int source, const Graph *graph);
    };

    class BreadthFirstPath : public Path {
        void bfs(const unsigned int vertex);
    public:
        BreadthFirstPath(const unsigned int source, const Graph *graph);
    };

    class ConnectedComponent {
    protected:
        const Graph *graph_;
        std::vector<bool> marked_;
        std::vector<unsigned int> componentId_;
        std::vector<unsigned int> idSize_;
        unsigned int componentN_;
        void dfs(const unsigned int vertex);
    public:
        ConnectedComponent(const Graph *graph);
        unsigned int componentId(const unsigned int which) const;
        unsigned int componentSize(const unsigned int which) const;
        unsigned int count() const;
        void makeUnion(const unsigned int first, const unsigned int second);
        bool isConnected(const unsigned int first, const unsigned int second);
    };

    class Cycle {
    protected:
        const Graph *graph_;
        std::vector<bool> onStack_;
        std::vector<unsigned int> edgeTo_;
        std::stack<unsigned int> cycle_;
        std::vector<bool> marked_;

        void dfs(const unsigned int vertex);
    public:
        Cycle(const Graph *graph);

        bool cycleQ() const;
        const std::stack<unsigned int> &getCycle() const;
    };

    class DepthFirstOrder {
    protected:
        const Graph *graph_;
        std::vector<bool> marked_;
        std::vector<unsigned int> preList_;
        std::vector<unsigned int> postList_;
        std::queue<unsigned int> preOrder_;
        std::queue<unsigned int> postOrder_;
        unsigned int preCounter_;
        unsigned int postCounter_;

        void dfs(const unsigned int vertex);
    public:
        DepthFirstOrder(const Graph *graph);
        unsigned int previousIndex(const unsigned int which) const;
        unsigned int postIndex(const unsigned int which) const;
        const std::vector<unsigned int> reversePostOrder() const;
        const std::queue<unsigned int> &getPreOrder() const;
        const std::queue<unsigned int> &getPostOrder() const;
    };

    class TopologicalSort {
    protected:
        const Graph *graph_;
        std::vector<unsigned int> rank_;
        std::vector<unsigned int> order_;
    public:
        TopologicalSort(const Graph *graph);
        bool hasOrder()const;
        unsigned int rank(const unsigned int which);
    };

    class KosarajuSharirStrongConnectedComponent : public ConnectedComponent {
    public:
        KosarajuSharirStrongConnectedComponent(const Graph *graph);
    };

    class PrimMinimumSpanningTree {
        const Graph *graph_;
        double weight_;
        std::vector<unsigned int> edgeTo_;
        std::queue<Edge> mst_;
        std::vector<bool> marked_;
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> priorityQueue_;
    public:
        PrimMinimumSpanningTree(const Graph *graph);
        void prim(unsigned int vertex);
        void scan(unsigned int vertex);
        double weight() const;
        const std::queue<Edge> &mst() const;
    };

    class KruskalMinimumSpanningTree {
        const Graph *graph_;
        double weight_;
        std::queue<Edge> mst_;
    public:
        KruskalMinimumSpanningTree(const Graph *graph);
    };

    class BoruvkaMinimumSpanningTree { };

    class ShortestPath { };

    class BellmanFordSortestPath : public ShortestPath { };

    class DijkstraSortestPath : public ShortestPath { };

    class AcyclicSortestPath : public ShortestPath { };

public:
    explicit Graph(const unsigned int vertexN);
    void addEdge(const Edge &edge);
    void addBidirectedEdge(const unsigned int from, const unsigned int to, const double weight = Edge::default_value);
    void addDirectedEdge(const unsigned int from, const unsigned int to, const double weight = Edge::default_value);
    const std::vector<std::vector<double>> adjacentMatrix() const;
    Graph reverse() const;
    const std::vector<unsigned int> BFS(const unsigned int source) const;
    const std::vector<unsigned int> DFS(const unsigned int source) const;
//    const Graph::Connect pathQ(const unsigned int from) const;
    const Graph::DepthFirstPath depthFirstPathQ(const unsigned int from) const;
    const Graph::BreadthFirstPath breadthFirstPathQ(const unsigned int from) const;
    const Graph::Cycle cycleQ() const;
    const Graph::DepthFirstOrder depthFirstOrderQ() const;
    const Graph::ConnectedComponent connectedComponentQ() const;
    const Graph::TopologicalSort topologicalSort() const;
    const Graph::KosarajuSharirStrongConnectedComponent kosarajuSharirStrongConnectedComponent() const;
    const Graph::PrimMinimumSpanningTree primMinimumSpanningTree() const;
    const Graph::KruskalMinimumSpanningTree kruskalMinimumSpanningTree() const;
//    const Path *connectQ(const unsigned int from) const;

    inline const unsigned int vertexN() const { return vertexN_; };

    inline const unsigned int edgeN() const { return edgeN_; };
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
};

#endif //NO4_GRAPH_H
