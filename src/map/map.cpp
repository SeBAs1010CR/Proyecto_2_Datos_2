#include "map.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "../Structures/Queue.h"
using namespace std;
using namespace sf;
void Map::matrixGenerator() {
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < columns; j++) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < rows * columns; i++) {
        for (int j = 0; j < rows * columns; j++) {
            adj[i][j] = 0;
        }
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 4);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int random = distr(gen);
            if (i == 0 and j != 0 and j != columns - 1) {
                matrix[i][j] = 2;
            }
            else if (i == 1 and j == 1 or i == rows - 2 and j == columns - 2 or i == 1 and j == columns - 2 or i == rows - 2 and j == 1) {
                matrix[i][j] = 0;
            }
            else if (i == rows - 1 and j != 0 and j != columns - 1) {
                matrix[i][j] = 3;
            }
            else if (j == 0 and i != 0 and i != rows - 1) {
                matrix[i][j] = 4;
            }
            else if (j == columns - 1 and i != 0 and i != rows - 1) {
                matrix[i][j] = 5;
            }
            else if (i == 0 and j == 0) {
                matrix[i][j] = 6;
            }
            else if (i == rows - 1 and j == 0) {
                matrix[i][j] = 7;
            }
            else if (i == 0 and j == columns - 1) {
                matrix[i][j] = 8;
            }
            else if (i == rows - 1 and j == columns - 1) {
                matrix[i][j] = 9;
            }

            else {
                if (random == 1) {
                    matrix[i][j] = 1;
                }
                else {
                    matrix[i][j] = 0;
                }
            }
        }
    }
    GraphVersion();
    notIsolation();
}
void Map::erasePath() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 10) {
                matrix[i][j] = 0;
            }
        }
    }
}
void Map::notIsolation() {
    int n = rows * columns;
    bool* visited = new bool[n]();
    Queue<int> opened;
    int startingId = getId(1, 1);
    visited[startingId] = true;
    for (int i = 0; i < n; i++) {
        if (adj[startingId][i] == 1) {
            opened.enqueue(i);
        }
    }

    while (!opened.isEmpty()){
        int curr_element = opened.front();
        visited[curr_element] = true;
        opened.dequeue();
        for (int i = 0; i < n; i++) {
            if (adj[curr_element][i] == 1 and visited[i] == false) {
                opened.enqueue(i);
            }
        }

    }

    bool* realEspaces = new bool[n]();
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            if (matrix[i][j] == 0) {
                realEspaces[getId(i, j)] = true;
            }
        }
    }
    bool istotal = true;
    for (int i = 0; i < n; i++) {
        if (visited[i] != realEspaces[i]) {
            istotal = false;
        }
    }

    delete[] visited;
    delete[] realEspaces;
    if (istotal == false) {
        matrixGenerator();
    }


}

Map::Map(int  rows, int columns) {
    matrix = new int* [rows];
    adj = new int* [rows * columns];
    this->rows = rows;
    this->columns = columns;

    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns]();
    }
    for (int i = 0; i < rows * columns; i++) {
        adj[i] = new int[rows * columns]();
    }
    matrixGenerator();
    wall_up.loadFromFile("assets/wall_up.png");
    wall_down.loadFromFile("assets/wall_down.png");
    wall_right.loadFromFile("assets/wall_right.png");
    wall_left.loadFromFile("assets/wall_left.png");
    ground.loadFromFile("assets/ground.png");
    shadow.loadFromFile("assets/shadow.png");
    up_left_corner.loadFromFile("assets/up_left_corner.png");
    up_right_corner.loadFromFile("assets/up_right_corner.png");
    down_left_corner.loadFromFile("assets/down_left_corner.png");
    down_right_corner.loadFromFile("assets/down_right_corner.png");
    obstacle.loadFromFile("assets/obstacle.png");
    yellow_ground.loadFromFile("assets/yellow_ground.png");
}
void Map::DrawMap(RenderWindow& window) {
    Sprite seal(wall_up);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 0) {
                seal.setTexture(ground);
            }
            else if (matrix[i][j] == 1) {
                seal.setTexture(obstacle);
            }
            else if (matrix[i][j] == 4) {
                seal.setTexture(wall_up);
            }
            else if (matrix[i][j] == 5) {
                seal.setTexture(wall_down);
            }
            else if (matrix[i][j] == 2) {
                seal.setTexture(wall_left);
            }
            else if (matrix[i][j] == 3) {
                seal.setTexture(wall_right);
            }
            else if (matrix[i][j] == 6) {
                seal.setTexture(up_left_corner);
            }
            else if (matrix[i][j] == 8) {
                seal.setTexture(down_left_corner);
            }
            else if (matrix[i][j] == 7) {
                seal.setTexture(up_right_corner);
            }
            else if (matrix[i][j] == 9) {
                seal.setTexture(down_right_corner);
            }
            else if (matrix[i][j] == 10) {
                seal.setTexture(yellow_ground);
            }
            seal.setPosition(Vector2f(i * 50, j * 50));
            window.draw(seal);
        }
    }
}
int Map::getId(int current_row, int current_column) {
    int Id = current_row * columns + current_column;
    return Id;
}
void Map::GraphVersion() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 0) {
                int currentNode = getId(i, j);
                if (i + 1 < rows and matrix[i + 1][j] == 0) {
                    int rightNode = getId(i + 1, j);
                    adj[currentNode][rightNode] = 1;
                    adj[rightNode][currentNode] = 1;
                }
                if (j + 1 < columns and matrix[i][j + 1] == 0) {
                    int downNode = getId(i, j + 1);
                    adj[currentNode][downNode] = 1;
                    adj[downNode][currentNode] = 1;
                }
            }
        }
    }
}