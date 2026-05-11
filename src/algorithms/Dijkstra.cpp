#include "Dijkstra.h"

#include "PriorityQueue.h"

#include <climits>

LinkedList<int> Dijkstra::shortestPath(
    int** graph,
    int totalNodes,
    int startNode,
    int destination
){


    // ARRAYS


    int* distance =
        new int[totalNodes];

    bool* visited =
        new bool[totalNodes];

    int* previous =
        new int[totalNodes];

    // Inicializar
    for(int i = 0; i < totalNodes; i++){

        distance[i] = INT_MAX;

        visited[i] = false;

        previous[i] = -1;
    }

    distance[startNode] = 0;


    // PRIORITY QUEUE


    PriorityQueue<int> pq;

    pq.enqueue(startNode, 0);


    // DIJKSTRA
  

    while(!pq.isEmpty()){

        int current =
            pq.front();

        pq.dequeue();

        if(visited[current]){

            continue;
        }

        visited[current] = true;

        // Llegó
        if(current == destination){

            break;
        }

        // Revisar vecinos
        for(int i = 0; i < totalNodes; i++){

            // Hay conexión
            if(graph[current][i] > 0){

                int weight =
                    graph[current][i];

                int newDistance =
                    distance[current] + weight;

                // Mejor camino
                if(newDistance < distance[i]){

                    distance[i] =
                        newDistance;

                    previous[i] =
                        current;

                    pq.enqueue(
                        i,
                        newDistance
                    );
                }
            }
        }
    }


    // RECONSTRUIR RUTA
  

    LinkedList<int> path;

    int current =
        destination;

    while(current != -1){

        path.insertFirst(current);

        current =
            previous[current];
    }


    // LIBERAR MEMORIA
  

    delete[] distance;

    delete[] visited;

    delete[] previous;

    return path;
}