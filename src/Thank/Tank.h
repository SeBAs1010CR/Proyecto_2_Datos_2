#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Tank {

private:

    // Posición del tanque
    int posX;
    int posY;

    // Datos del tanque
    string color;
    int life;

    // Movimiento máximo
    int movement;

    // Daño del tanque
    int damage;

    // Cantidad de powerups
    int powerUps;

public:
    //Constuctor
    
    Tank(int x, int y, string c);
    

    // MÉTODOS


    void move(int newX, int newY);
    void calculateRoute(Map& map);
    void shoot();
    void takeDamage(int amount);
    void applyPowerUp();
    void showInfo();
    void randomMovement(Map& map);


};