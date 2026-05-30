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

using namespace std;
using namespace sf;

class Tank;

class Bullet {
private:
	int health;
	int pos;
	int origin_id;
	float angle;
	float bullet_row;
	LinkedList<double> routeX;
	LinkedList<double> routeY;
	Node<double>* curr_x_node;
	Node<double>* curr_y_node;
	LinkedList<Tank*> tanks_list;
	float bullet_column;
	string color;
	Texture yellow_ground;
	Texture bullet;

	Sprite* seal_bullet;
	bool isShowingPath;
	bool isMoving;
	bool isRotating;
	bool powerup;
	bool isActive;
	LinkedList<int> savedPath;
	Node<int>* current;
	Clock waitClock;
	float target_row;
	float target_column;

	void animateMovement(float f_pos, Map& battleField, RenderWindow& window, LinkedList<int>& path);
public:
	bool getActivityState() { return isActive; };
	bool getPoweupState() { return powerup; };
	Bullet(int position, float angle, string color, Map& battleField, RenderWindow& window, bool powerup, LinkedList<Tank*>& tanks_list);
	void updateAnimationAStar(Map& battleField, RenderWindow& window);
	void updateAnimationLOS(Map& battleField, RenderWindow& window, Queue<int>& powerups);
	void draw(Map& battleField, RenderWindow& window);
	void movement(float f_pos, Map& battleField, RenderWindow& window);
	int getPos() { return pos; }
};