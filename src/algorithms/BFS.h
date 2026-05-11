#ifndef BFS_H
#define BFS_H

#include "../structures/LinkedList.h"

class BFS {

public:

    static bool esConexo(
        int** matriz,
        int totalNodos,
        int nodoInicial
    );

    static LinkedList<int> shortestPath(
        int** matriz,
        int totalNodos,
        int inicio,
        int destino
    );
};

#endif