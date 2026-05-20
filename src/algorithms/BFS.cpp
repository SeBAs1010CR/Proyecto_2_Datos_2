#include "BFS.h"
#include "../Structures/Queue.h"

// SHORTEST PATH /////////////


LinkedList<int> BFS::shortestPath(
    int** matriz,
    int totalNodos,
    int inicio,
    int destino
){

    bool* visitado =
        new bool[totalNodos];

    int* previous =
        new int[totalNodos];

    // Inicializar
    for(int i = 0; i < totalNodos; i++){

        visitado[i] = false;

        previous[i] = -1;
    }

    Queue<int> cola;

    cola.enqueue(inicio);

    visitado[inicio] = true;


    // BFS ///////////////


    while(!cola.isEmpty()){

        int actual = cola.front();

        cola.dequeue();

        // Llegó
        if(actual == destino){

            break;
        }

        for(int i = 0; i < totalNodos; i++){

            if(matriz[actual][i] == 1 &&
               !visitado[i]){

                cola.enqueue(i);

                visitado[i] = true;

                previous[i] = actual;
            }
        }
    }


    // RECONSTRUIR RUTA /////////////////////


    LinkedList<int> path;

    int current = destino;

    while(current != -1){

        path.insertFirst(current);

        current = previous[current];
    }

    delete[] visitado;

    delete[] previous;

    return path;
}