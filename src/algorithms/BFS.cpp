#include "BFS.h"

bool BFS::esConexo(int** matriz, int totalNodos, int nodoInicial){

    bool* visitado = new bool[totalNodos];
    for(int i = 0; i < totalNodos; i++){
        visitado[i] = false;
    }

    int* cola = new int[totalNodos];
    int front = 0;
    int rear = 0;

    cola[rear++] = nodoInicial;
    visitado[nodoInicial] = true;

    int count = 1;

    while(front < rear){
        int actual = cola[front++];

        for(int i = 0; i < totalNodos; i++){
            if(matriz[actual][i] == 1 && !visitado[i]){
                cola[rear++] = i;
                visitado[i] = true;
                count++;
            }
        }
    }

    delete[] visitado;
    delete[] cola;

    return count == totalNodos; 
}