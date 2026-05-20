#ifndef BFS_H
#define BFS_H

#include "../structures/LinkedList.h"

class BFS {

public:

    static LinkedList<int> shortestPath(
        int** matriz,
        int totalNodos,
        int inicio,
        int destino
    );
};

#endif