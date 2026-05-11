#include "BFS.h"
#include "../structures/Queue.h"


// VERIFICAR CONECTIVIDAD ////////////////


bool BFS::esConexo(
    int** matriz,
    int totalNodos,
    int nodoInicial
){

    bool* visitado =
        new bool[totalNodos];

    for(int i = 0; i < totalNodos; i++){

        visitado[i] = false;
    }

    Queue<int> cola;

    cola.enqueue(nodoInicial);

    visitado[nodoInicial] = true;

    int count = 1;

    while(!cola.isEmpty()){

        int actual = cola.front();

        cola.dequeue();

        for(int i = 0; i < totalNodos; i++){

            if(matriz[actual][i] == 1 &&
               !visitado[i]){

                cola.enqueue(i);

                visitado[i] = true;

                count++;
            }
        }
    }

    delete[] visitado;

    return count == totalNodos;
}


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