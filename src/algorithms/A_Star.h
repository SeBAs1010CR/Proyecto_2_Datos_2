#ifndef A_STAR_H
#define A_STAR_H

#include "../Structures/LinkedList.h"

class Tank;

class A_Star {

public:
    static int heuristic(int node, int destination, int columns);
    static LinkedList<int> shortestPath(
        int** graph,
        int totalNodes,
        int startNode,
        int destination,
        int columns,
        LinkedList<Tank*>& tanks_list
    );
};

#endif