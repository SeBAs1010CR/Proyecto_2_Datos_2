#include "A_Star.h"
#include "../Structures/PriorityQueue.h"
#include "../Structures/LinkedList.h"
#include "../Tank/tank.h"
#include <climits>

int A_Star::heuristic(int node, int destination, int columns) {
    int node_row = node / columns;
    int node_col = node % columns;
    int dest_row = destination / columns;
    int dest_col = destination % columns;
    return abs(node_row - dest_row) + abs(node_col - dest_col);
}

LinkedList<int> A_Star::shortestPath(
    int** graph,
    int totalNodes,
    int startNode,
    int destination,
    int columns,
    LinkedList<Tank*>& tanks_list
) {


    // ARRAYS


    int* distance =
        new int[totalNodes];

    bool* visited =
        new bool[totalNodes];

    int* previous =
        new int[totalNodes];

    // Inicializar
    for (int i = 0; i < totalNodes; i++) {

        distance[i] = INT_MAX;

        visited[i] = false;

        previous[i] = -1;
    }

    distance[startNode] = 0;


    // PRIORITY QUEUE


    PriorityQueue<int> pq;

    pq.enqueue(startNode, heuristic(startNode, destination, columns));


    // A Star


    while (!pq.isEmpty()) {

        int current =
            pq.front();

        pq.dequeue();

        if (visited[current]) {

            continue;
        }

        visited[current] = true;

        Node<Tank*>* curr_t = tanks_list.getHead();
        bool hitTank = false;
        while (curr_t != nullptr) {
            if (curr_t->data->isAlive && curr_t->data->getPos() == current && current != startNode) {
                hitTank = true;
                break;
            }
            curr_t = curr_t->next;
        }
        if (hitTank) {
            destination = current;
            break;
        }

        // Llegó
        if (current == destination) {

            break;
        }

        // Revisar vecinos
        for (int i = 0; i < totalNodes; i++) {

            // Hay conexión
            if (graph[current][i] > 0) {

                int weight =
                    graph[current][i];

                int newDistance =
                    distance[current] + weight;

                // Mejor camino
                if (newDistance < distance[i]) {

                    distance[i] =
                        newDistance;

                    previous[i] =
                        current;

                    int priority =
                        newDistance + heuristic(i, destination, columns);

                    pq.enqueue(
                        i,
                        priority
                    );
                }
            }
        }
    }

    if (distance[destination] == INT_MAX) {
        delete[] distance;
        delete[] visited;
        delete[] previous;
        return LinkedList<int>();
    }

    // RECONSTRUIR RUTA


    LinkedList<int> path;

    int current =
        destination;

    while (current != -1) {

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