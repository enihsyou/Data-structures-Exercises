#include <iostream>
#include "Graph.h"


int main() {
    Graph g = Graph(8);
    g.addDirectedEdge(4, 5, 0.35);
    g.addDirectedEdge(5, 4, 0.35);
    g.addDirectedEdge(4, 7, 0.37);
    g.addDirectedEdge(5, 7, 0.28);
    g.addDirectedEdge(7, 5, 0.28);
    g.addDirectedEdge(5, 1, 0.32);
    g.addDirectedEdge(0, 4, 0.38);
    g.addDirectedEdge(0, 2, 0.26);
    g.addDirectedEdge(7, 3, 0.39);
    g.addDirectedEdge(1, 3, 0.29);
    g.addDirectedEdge(2, 7, 0.34);
    g.addDirectedEdge(6, 2, 0.40);
    g.addDirectedEdge(3, 6, 0.52);
    g.addDirectedEdge(6, 0, 0.58);
    g.addDirectedEdge(6, 4, 0.93);
    auto a  = g.depthFirstPathQ(0);
    auto b  = g.breadthFirstPathQ(0);
    auto c  = g.cycleQ().cycleQ();
    auto d  = g.depthFirstOrderQ();
    std::cout << g << std::endl;

    return 0;
}
