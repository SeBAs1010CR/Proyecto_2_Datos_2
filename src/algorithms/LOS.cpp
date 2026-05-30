#include "../Structures/LinkedList.h"
#include "../Structures/PriorityQueue.h"
#include "LOS.h"
#include <random>

LinkedList<int> LOS::Path(
    int** graph,
    int totalNodes,
    int currNode,
    int destination,
    int columns
) {

    int curr_x = currNode / columns;
    int curr_y = currNode % columns;
    int final_x = destination / columns;
    int final_y = destination % columns;
    int n_colisions = 0;
    LinkedList<int> randomPath;

    int dif_x = final_x - curr_x;
    int dif_y = final_y - curr_y;
    bool notColision;
    randomPath.insert(currNode);

    while (true) {
        notColision = true;

        while (curr_x != final_x) {
            notColision = false;
            for (int i = 0; i < totalNodes; i++) {
                if (graph[currNode][i] == 1) {
                    int next_x = i / columns;
                    if (dif_x > 0 and next_x == curr_x + 1) {
                        randomPath.insert(i);
                        currNode = i;
                        curr_x = next_x;
                        notColision = true;
                        dif_x = final_x - curr_x;
                        break;
                    }
                    else if (dif_x < 0 and next_x == curr_x - 1) {
                        randomPath.insert(i);
                        currNode = i;
                        curr_x = next_x;
                        notColision = true;
                        dif_x = final_x - curr_x;
                        break;
                    }
                }

            }
            if (!notColision) {
                break;
            }

        }

        if (!notColision) {
            n_colisions += 1;
            if (n_colisions > 1) {
                return randomPath;
            }

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, 3);
            bool pasoExitoso = false;

            while (!pasoExitoso) {
                int random = distr(gen);
                for (int i = 0; i < totalNodes; i++) {
                    if (graph[currNode][i] == 1) {
                        int next_x = i / columns;
                        int next_y = i % columns;
                        if (random == 0 and next_x == curr_x + 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                        else if (random == 1 and next_x == curr_x - 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                        else if (random == 2 and next_y == curr_y - 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                        else if (random == 3 and next_y == curr_y + 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                    }
                }
            }
            dif_x = final_x - curr_x;
            dif_y = final_y - curr_y;
        }
        notColision = true;
        while (curr_y != final_y) {
            notColision = false;
            for (int i = 0; i < totalNodes; i++) {
                if (graph[currNode][i] == 1) {
                    int next_y = i % columns;
                    if (dif_y > 0 and next_y == curr_y + 1) {
                        randomPath.insert(i);
                        currNode = i;
                        curr_y = next_y;
                        notColision = true;
                        dif_y = final_y - curr_y;
                        break;
                    }
                    else if (dif_y < 0 and next_y == curr_y - 1) {
                        randomPath.insert(i);
                        currNode = i;
                        curr_y = next_y;
                        notColision = true;
                        dif_y = final_y - curr_y;
                        break;
                    }
                }
            }
            if (!notColision) {
                break;
            }


        }

        if (!notColision) {
            n_colisions += 1;
            if (n_colisions > 1) {
                return randomPath;
            }

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(0, 3);
            bool pasoExitoso = false;

            while (!pasoExitoso) {
                int random = distr(gen);
                for (int i = 0; i < totalNodes; i++) {
                    if (graph[currNode][i] == 1) {
                        int next_x = i / columns;
                        int next_y = i % columns;
                        if (random == 0 and next_x == curr_x + 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                        else if (random == 1 and next_x == curr_x - 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                        else if (random == 2 and next_y == curr_y - 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                        else if (random == 3 and next_y == curr_y + 1) {
                            randomPath.insert(i);
                            currNode = i;
                            curr_x = next_x;
                            curr_y = next_y;
                            pasoExitoso = true;
                            break;
                        }
                    }
                }
            }
            dif_x = final_x - curr_x;
            dif_y = final_y - curr_y;
        }

        if (curr_x == final_x and curr_y == final_y) {
            return randomPath;
        }
    }
}