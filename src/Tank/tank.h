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

using namespace std;
using namespace sf;

class Tank {
private:
	int health;
	int pos;
	float angle;
	float tank_row;

	float tank_column;
	string color;
	Texture yellow_ground;
	Texture blue_tank;
	Texture red_tank;
	Texture sky_blue_tank;
	Texture yellow_tank;
	Sprite* seal_tank;
	void animateMovement(float f_pos, Map& battleField, RenderWindow& window, LinkedList<int>& path);

	enum AnimState { IDLE, SHOWING_PATH, MOVING };
	AnimState animState = IDLE;
	Node<int>* current = nullptr;
	Clock animTimer;
	float targetRow = 0;
	float targetCol = 0;
	bool isRotating = true;
	int destPos = 0;
	LinkedList<int> savedPath;

public:
	Tank(int position, float angle, string color, Map& battleField, RenderWindow& window);
	void movement(float f_pos, Map& battleField, RenderWindow& window);
	void draw(Map& battleField, RenderWindow& window);
	void updateAnimation(Map& battleField, RenderWindow& window);
	int getPos() { return pos; }
};