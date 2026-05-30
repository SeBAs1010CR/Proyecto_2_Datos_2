#ifndef A_STAR_H
#define A_STAR_H

#include "../Structures/LinkedList.h"

class A_Star {
private:
    heuristic(int node, int destination, int columns);

public:

    static LinkedList<int> shortestPath(
        int** graph,
        int totalNodes,
        int startNode,
        int destination,
        int columns
    );
};

#endif