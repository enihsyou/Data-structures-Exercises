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


//namespace {
//struct Edge {
//    const unsigned int from;
//    const unsigned int to;
//
//    Edge(const unsigned int from, const unsigned int to) : from(from), to(to) { }
//};
//struct UndirectedEdge : public Edge {
//    UndirectedEdge(const unsigned int from, const unsigned int to) : Edge(from, to) { };
//};
//struct DirectedEdge : public Edge {
//    DirectedEdge(const unsigned int from, const unsigned int to) : Edge(from, to) { };
//};
//struct Path {
//    const unsigned int from;
//    const unsigned int to;
//
//    Path(const unsigned int from, const unsigned int to)
//        : from(from), to(to), marked_{new bool[from]}, edgeTo_{new unsigned int[from]} {
//    }
//
//private:
//    const bool *marked_;
//    const unsigned int *edgeTo_[];
//};
//};

class Graph {
    const unsigned int vertexN_ = 0U;
    unsigned int edgeN_ = 0U;
    std::map<unsigned int, std::set<unsigned int>> adjacent_ = { };
    std::vector<std::string> label_ = { };

    void validateVertex(const unsigned int v) const;
    class ConnectQ {
        const unsigned int from_;
    public:
        ConnectQ(const unsigned int from);
        bool marked(const unsigned int to);
        unsigned int count(const unsigned int to);
    };
    class PathQ {
        const unsigned int from_;
    public:
        PathQ(const unsigned int from);
        bool hasPathTo(const unsigned int to);
        const std::vector<unsigned int> pathTo(const unsigned int to);
    };
public:
    explicit Graph(const unsigned int vertexN);
//    void addEdge(const Edge &edge);
    void addUndirectedEdge(const unsigned int from, const unsigned int to);
    void addDirectedEdge(const unsigned int from, const unsigned int to);
    unsigned int *adjacentMatrix() const;
    const std::vector<unsigned int> BFS(const unsigned int from) const;
    const std::vector<unsigned int> DFS(const unsigned int from) const;
    const ConnectQ pathQ(const unsigned int from) const;
    const PathQ connectQ(const unsigned int from) const;
    inline const unsigned int vertexN() const {return vertexN_;};
    inline const unsigned int edgeN() const {return edgeN_;};
    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
};
const std::vector<unsigned int> BFS(const unsigned int *adjacent_matrix, const unsigned int size, const unsigned int from);
const std::vector<unsigned int> DFS(const unsigned int *adjacent_matrix, const unsigned int size, const unsigned int from);
//class UndirectedGraph : public Graph {
//public:
//    UndirectedGraph(const unsigned int vertexN);
//    virtual void addEdge(const unsigned int from, const unsigned int to) override;
//
//};
//class DirectedGraph : public Graph {
//public:
//    DirectedGraph(const unsigned int vertexN);
//    virtual void addEdge(const unsigned int from, const unsigned int to) override;
//};
#endif //NO4_GRAPH_H
