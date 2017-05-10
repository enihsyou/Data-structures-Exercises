//
// Created by Shane on 2017/5/9.
//

#ifndef NO4_GRAPH_H
#define NO4_GRAPH_H
#include <vector>
#include <string>
#include <map>
#include <set>
#include <ostream>


struct Edge {
    const unsigned int from;
    const unsigned int to;
    const double weight;

    Edge(const unsigned int from, const unsigned int to, const double weight = default_value)
        : from(from), to(to), weight(weight) { }

    static double default_value;

    static void setDefault(const double new_default) { Edge::default_value = new_default; };

    friend std::ostream &operator<<(std::ostream &os, const Edge &edge) {
        os << "from: " << edge.from << " to: " << edge.to << " weight: " << edge.weight;
        return os;
    }
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
    AdjacentMatrixGraph(const unsigned int vertexN) : vertexN_(vertexN), adjacent_{new bool[vertexN]} { }

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

    class Connect {
        const unsigned int from_;
    public:
        Connect(const unsigned int from);
        bool marked(const unsigned int to);
        unsigned int count(const unsigned int to);
    };

    class Path {
    protected:
        const Graph *graph;
        const unsigned int source;
        std::vector<unsigned int> edgeTo;
        std::vector<unsigned int> distTo;
        std::vector<bool> marked;
    public:
        Path(const unsigned int from, const Graph *graph) : source{from}, graph{graph},
                                                            marked{std::vector<bool>(graph->vertexN_)},
                                                            distTo{std::vector<unsigned int>(graph->vertexN_, -1)},
                                                            edgeTo{std::vector<unsigned int>(graph->vertexN_)} { };
        bool hasPathTo(const unsigned int to);
        const std::vector<unsigned int> pathTo(const unsigned int to);
        int distanceTo(const unsigned int vertex);
    };

    class DepthFirstPath : public Path {
        void dfs(const unsigned int vertex);
    public:
        DepthFirstPath(const unsigned int from, const Graph *graph) : Path{from, graph} {
            graph->validateVertex(from);
            distTo[from] = 0;
            dfs(from);
        };
    };

    class BreadthFirstPath : public Path {
        void bfs(const unsigned int vertex);
    public:
        BreadthFirstPath(const unsigned int from, const Graph *graph) : Path{from, graph} {
            graph->validateVertex(from);
            distTo[from] = 0;
            bfs(from);
        };
    };

    class ConnectedComponent { };

    class Cycle { };

    class DirectedCycle : public Cycle { };

    class TopologicalSort { };

    class DepthFirstOrder { };

    class StrongConnectedComponent : public ConnectedComponent { };

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
    void addUndirectedEdge(const unsigned int from, const unsigned int to, const double weight = Edge::default_value);
    void addDirectedEdge(const unsigned int from, const unsigned int to, const double weight = Edge::default_value);
    const std::vector<std::vector<double>> adjacentMatrix() const;
    const std::vector<unsigned int> BFS(const unsigned int source) const;
    const std::vector<unsigned int> DFS(const unsigned int source) const;
    const Connect pathQ(const unsigned int from) const;
    const DepthFirstPath depthFirstPathQ(const unsigned int from) const;
    const BreadthFirstPath breadthFirstPath(const unsigned int from) const;
    const Path* connectQ(const unsigned int from) const;

    inline const unsigned int vertexN() const { return vertexN_; };

    inline const unsigned int edgeN() const { return edgeN_; };
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
};

#endif //NO4_GRAPH_H
