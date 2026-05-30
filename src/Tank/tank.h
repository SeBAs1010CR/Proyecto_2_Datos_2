#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include "../map/map.h"
#include "../algorithms/BFS.h"
#include "../algorithms/Dijkstra.h"
#include "../algorithms/LOS.h"
#include "../Structures/LinkedList.h"
#include "../Structures/Queue.h"
#include "../bullet/bullet.h"

using namespace std;
using namespace sf;

class Tank {
private:
	int health;
	
	int pos;
	float angle;
	float tank_row;
	

	float tank_column;

	Texture yellow_ground;
	Texture blue_tank;
	Texture red_tank;
	Texture sky_blue_tank;
	Texture yellow_tank;
	Texture HealthAt100;
	Texture HealthAt75;
	Texture HealthAt50;
	Texture HealthAt25;
	Texture HealthAt0;

	Sprite* seal_tank;
	Sprite* seal_health;

	bool isShowingPath;
	bool isMoving;
	bool isRotating;
	LinkedList<int> savedPath;
	Node<int>* current;
	Clock waitClock;
	float target_row;
	float target_column;
	bool isRotatingToShoot = false;
	float target_shoot_angle;
	float bullet_shoot_angle;
	int pending_destination;
	bool pending_powerUpAStar;
	bool has_pending_shot = false;
	LinkedList<Tank*> pending_tanks_position;

	void animateMovement(float f_pos, Map& battleField, RenderWindow& window, LinkedList<int>& path);
public:
	bool isAlive = true;
	string color;
	Bullet* activeBullet = nullptr;
	Tank(int position, float angle, string color, Map& battleField, RenderWindow& window);
	void setHealth(int damage);
	int getHealth() { return health; };
	void updateAnimation(Map& battleField, RenderWindow& window);
	void draw(Map& battleField, RenderWindow& window);
	void movement(float f_pos, Map& battleField, RenderWindow& window, int max_random_n);
	void rotateTankToShoot(float target_angle);
	void Shoot(int destination, Map& battleField, RenderWindow& window, Queue<int>& powerups, LinkedList<Tank*>& tanks_list);
	int getPos() { return pos; };
};