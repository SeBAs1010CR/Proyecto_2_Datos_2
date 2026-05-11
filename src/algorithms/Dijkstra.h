#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "LinkedList.h"

class Dijkstra {

public:

    static LinkedList<int> shortestPath(
        int** graph,
        int totalNodes,
        int startNode,
        int destination
    );
};

#endif