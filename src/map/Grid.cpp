#include "Map.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Map::Map(int x, int y){
    this -> filas = x; 
    this -> columnas = y;
    this -> totalNodos = x * y; // Nodos de la matriz
    probObstaculo = 0.2;
    


    grid = new int*[filas];
    for(int i = 0; i < filas; i++){
        grid[i] = new int[columnas];

        for(int j = 0; j < columnas; j++){
            grid[i][j] = 0;
        }

    }
    MatrizAdyacencia = new int*[totalNodos];

    for(int i = 0; i < totalNodos; i++){
        MatrizAdyacencia[i] = new int[totalNodos];
        for(int j = 0; j < totalNodos; j++){
            MatrizAdyacencia[i][j] = 0;
        }
    }
}
void Map::ConstruirAdyacencia(){
    for(int i = 0; i < totalNodos; i++){
        for(int j = 0; j < totalNodos; j++){
        MatrizAdyacencia[i][j] = 0;
        }
    }
    
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(grid[i][j] == 1){
                continue;
            }
            int NodoActual = i * columnas + j; //---> convierte (x,y) en un solo numero o nodo
            //Derecha
            if(j + 1 < columnas && grid[i][j + 1] == 0){
                    int NodoDerecha = i * columnas + (j + 1);
                    MatrizAdyacencia[NodoActual][NodoDerecha] = 1; // Grafo no dirijido de A -> B y B -> A
                    MatrizAdyacencia[NodoDerecha][NodoActual] = 1;               
            }
            //Izquierda
            if(j - 1 >= 0 && grid[i][j - 1] == 0){
                    int NodoIzquierda = i * columnas + (j - 1);
                    MatrizAdyacencia[NodoActual][NodoIzquierda] = 1; 
                    MatrizAdyacencia[NodoIzquierda][NodoActual] = 1;
            }
            //Abajo
            if(i + 1 < filas && grid[i + 1][j] == 0){
                    int NodoAbajo = (i + 1) * columnas + j;
                    MatrizAdyacencia[NodoActual][NodoAbajo] = 1; 
                    MatrizAdyacencia[NodoAbajo][NodoActual] = 1;
            }
            //Arriba
            if(i - 1 >= 0 && grid[i - 1][j] == 0){
                    int NodoArriba = (i - 1) * columnas + j;
                    MatrizAdyacencia[NodoActual][NodoArriba] = 1; 
                    MatrizAdyacencia[NodoArriba][NodoActual] = 1;
            }
        }
    }
}
int Map::encontrarNodoInicial(){ //-> para el BFS
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(grid[i][j] == 0){
                return i * columnas + j;
            }
            
        }
    }
    return -1;
}
int Map::contarCeldasLibres(){
    int CeldasLibres = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(grid[i][j] == 0){
                CeldasLibres += 1;
            }
            
        }
    }
    return CeldasLibres;
}
void Map::GenerarObstaculo(){ // srand(time(0)); poner en main si no aparece siempre el mismo mapa

    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){

            float r = (float) rand() / RAND_MAX;

            if(r < probObstaculo){
                grid[i][j] = 1; // obstáculo
            }
            else{
                grid[i][j] = 0; // libre
            }

        }
    }
    grid[0][0] = 0; // Que al menos una celda este libre para que no se caiga el bfs
}

//Destructor
Map::~Map(){
    for(int i = 0; i < filas; i++){
        delete[] grid[i];
    }
    delete[] grid;

    for(int i = 0; i < totalNodos; i++){
        delete[] MatrizAdyacencia[i];
    }
    delete[] MatrizAdyacencia;
}

int** Map::getAdjacencyMatrix(){

    return MatrizAdyacencia;
}

int Map::getTotalNodes(){

    return totalNodos;
}

int** Map::getGrid(){

    return grid;
}

bool Map::lineOfSight(
    int x1,
    int y1,
    int x2,
    int y2
){

    int dx = x2 - x1;

    int dy = y2 - y1;

    int steps =
        std::max(abs(dx), abs(dy));

    float xIncrement =
        dx / (float)steps;

    float yIncrement =
        dy / (float)steps;

    float x = x1;

    float y = y1;

    for(int i = 0; i <= steps; i++){

        int gridX = (int)x;

        int gridY = (int)y;

        // Obstáculo
        if(grid[gridY][gridX] == 1){

            return false;
        }

        x += xIncrement;

        y += yIncrement;
    }

    return true;
}