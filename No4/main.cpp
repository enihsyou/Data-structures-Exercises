#include <iostream>
#include "Graph.h"


int main() {
    Graph g = Graph(13);
    g.addUndirectedEdge(0, 5);
    g.addUndirectedEdge(4, 3);
    g.addUndirectedEdge(0, 1);
    g.addUndirectedEdge(9, 12);
    g.addUndirectedEdge(6, 4);
    g.addUndirectedEdge(5, 4);
    g.addUndirectedEdge(0, 2);
    g.addUndirectedEdge(11, 12);
    g.addUndirectedEdge(9, 10);
    g.addUndirectedEdge(0, 6);
    g.addUndirectedEdge(7, 8);
    g.addUndirectedEdge(9, 11);
    g.addUndirectedEdge(5, 3);
    std::cout << g << std::endl;
    auto c = BFS(g.adjacentMatrix(), g.vertexN(), 0);
    auto d = DFS(g.adjacentMatrix(), g.vertexN(), 0);
    auto a = g.BFS(0);
    auto b = g.DFS(0);
    return 0;
}
