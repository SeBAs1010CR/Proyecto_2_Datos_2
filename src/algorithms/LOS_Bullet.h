#ifndef LOS_BULLET_H
#define LOS_BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Structures/LinkedList.h"
#include "../map/map.h"
#include "../Tank/tank.h"
#include <string>
#include <cmath>

using namespace sf;
using namespace std;

class LOS_Bullet {
private:
	static Clock waitClock;
public:
	static LinkedList<int> Path(double angle, Map& battleField, int Start_x, int Start_y, LinkedList<Tank*>& tanks_list, LinkedList<double>& route_x, LinkedList<double>& route_y);
	static bool Colision(Map& battleField, LinkedList<Tank*>& tanks_list, int curr_row, int curr_column);
	static double Rebound(double curr_x, double curr_y, int corner_x, int corner_y, double angle, double& angle_radians);
};
#endif