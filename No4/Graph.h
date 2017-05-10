#ifndef NO4_GRAPH_H
#define NO4_GRAPH_H
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <ostream>


struct Edge {
    const unsigned int from;
    const unsigned int to;
    const double weight;

    Edge(const unsigned int from, const unsigned int to, const double weight = default_value);

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
    const unsigned int vertexN_ = 0U;
    unsigned int edgeN_ = 0U;
    bool *adjacent_;

    void validateVertex(const unsigned int v) const;
public:
    AdjacentMatrixGraph(const unsigned int vertexN);

    const std::vector<unsigned int> BFS(const unsigned int from);
    const std::vector<unsigned int> DFS(const unsigned int from);
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

    class Connect {
        const unsigned int from_;
    public:
        Connect(const unsigned int from);
        bool marked(const unsigned int to);
        unsigned int count(const unsigned int to);
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
        bool isConnected(const unsigned int first, const unsigned int second);
    };

    class StrongConnectedComponent : public ConnectedComponent {
    public:
        StrongConnectedComponent(const Graph *graph);

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

    class KosarajuStrongConnectedComponent : public StrongConnectedComponent { };

    class MinimumSpanningTree { };

    class PrimMinimumSpanningTree : public MinimumSpanningTree { };

    class KruskalMinimumSpanningTree : public MinimumSpanningTree { };

    class BoruvkaMinimumSpanningTree : public MinimumSpanningTree { };

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
    const std::vector<unsigned int> BFS(const unsigned int source) const;
    const std::vector<unsigned int> DFS(const unsigned int source) const;
//    const Graph::Connect pathQ(const unsigned int from) const;
    const Graph::DepthFirstPath depthFirstPathQ(const unsigned int from) const;
    const Graph::BreadthFirstPath breadthFirstPathQ(const unsigned int from) const;
    const Graph::Cycle cycleQ() const;
    const Graph::DepthFirstOrder depthFirstOrderQ() const;
    const Graph::ConnectedComponent connectedComponentQ() const;
    const Graph::TopologicalSort topologicalSort() const;
//    const Path *connectQ(const unsigned int from) const;

    inline const unsigned int vertexN() const { return vertexN_; };

    inline const unsigned int edgeN() const { return edgeN_; };
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
};

#endif //NO4_GRAPH_H
