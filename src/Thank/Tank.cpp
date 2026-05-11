#include "Tank.h"
#include "../map/Map.h"
#include "../algorithms/BFS.h"
#include "../algorithms/Dijkstra.h"

#include <cstdlib>
#include <ctime>

using namespace std;




// CONSTRUCTOR


Tank::Tank(int x, int y, string c){

    posX = x;
    posY = y;

    color = c;

    life = 100;

    movement = 5;

    powerUps = 0;

    // Daño según color
    if(color == "blue" ||
       color == "cyan"){

        damage = 25;
    }

    else{

        damage = 50;
    }
}


// MOVER TANQUE


void Tank::move(int newX, int newY){

    posX = newX;
    posY = newY;

    cout << "Tank movido a: "
         << posX
         << ", "
         << posY
         << endl;
}


// CALCULAR RUTA //////


void Tank::calculateRoute(Map& map){

    int probability =
        rand() % 100;

    // ---------------------
    // TANQUES AZUL/CELESTE
    // ---------------------

    if(color == "blue" ||
       color == "cyan"){

        // 50% BFS
        if(probability < 50){

            cout << "Usando BFS"
                 << endl;

            // Nodo inicial
            int inicio =
                map.encontrarNodoInicial();

            // Destino de prueba
            int destino =
                map.getTotalNodes() - 1;

            // Calcular ruta
            LinkedList<int> ruta =
                BFS::shortestPath(
                    map.getAdjacencyMatrix(),
                    map.getTotalNodes(),
                    inicio,
                    destino
                );

            cout << "Ruta BFS:"
                 << endl;

            ruta.print();
        }

        // 50% RANDOM
        else{

            cout << "Movimiento Random"
                 << endl;

            randomMovement(map);
        }
    }

    // ---------------------
    // TANQUES ROJO/AMARILLO
    // ---------------------

    else{

        // 80% DIJKSTRA
        if(probability < 80){

            cout << "Usando Dijkstra"
                 << endl;

            int inicio =
                map.encontrarNodoInicial();

            int destino =
                map.getTotalNodes() - 1;

            LinkedList<int> ruta =
                Dijkstra::shortestPath(
                    map.getAdjacencyMatrix(),
                    map.getTotalNodes(),
                    inicio,
                    destino
                    );

            cout << "Ruta Dijkstra:"
            << endl;

            ruta.print();

        }

        // 20% RANDOM
        else{

            cout << "Movimiento Random"
                 << endl;

            randomMovement(map);
        }
    }
}


// MOVIMIENTO RANDOM ////////////


void Tank::randomMovement(Map& map){

    int randomX =
        posX + (rand() % 5 - 2);

    int randomY =
        posY + (rand() % 5 - 2);


    // PRIMER INTENTO ///////////
  

    if(map.lineOfSight(
        posX,
        posY,
        randomX,
        randomY
    )){

        move(randomX, randomY);

        cout << "Movimiento directo"
             << endl;
    }

   
    // SEGUNDO INTENTO /////////////
   

    else{

        cout << "Obstaculo detectado"
             << endl;

        int secondX =
            posX + (rand() % 5 - 2);

        int secondY =
            posY + (rand() % 5 - 2);

        if(map.lineOfSight(
            posX,
            posY,
            secondX,
            secondY
        )){

            move(secondX, secondY);

            cout << "Segundo intento exitoso"
                 << endl;
        }

        else{

            cout << "Avanzando lo mas posible"
                 << endl;

            // Movimiento parcial simple
            move(
                posX + 1,
                posY
            );
        }
    }
}


// DISPARAR


void Tank::shoot(){ // No implementada aun

    cout << "Tank fired!"
         << endl;
}


// RECIBIR DAÑO


void Tank::takeDamage(int amount){

    life -= amount;

    if(life < 0){

        life = 0;
    }

    cout << "Vida restante: "
         << life
         << endl;
}

 
// POWER UPS // No implementada aun


void Tank::applyPowerUp(){

    powerUps++;

    cout << "PowerUp aplicado!"
         << endl;
}


// MOSTRAR INFO ///////////


void Tank::showInfo(){

    cout << "Color: "
         << color
         << endl;

    cout << "Vida: "
         << life
         << endl;

    cout << "Posicion: "
         << posX
         << ", "
         << posY
         << endl;
}