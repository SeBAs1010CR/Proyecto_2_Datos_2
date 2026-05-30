#include "Tank.h"
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

void Tank::setHealth(int damage) {
	health -= damage;
	if (health <= 0) {
		isAlive = false;
		pos = -1; 
	}
}

void Tank::animateMovement(float f_pos, Map& battleField, RenderWindow& window, LinkedList<int>& path) {
	savedPath = path;
	current = savedPath.getHead();
	isShowingPath = true;
	isMoving = false;
	isRotating = false;
	waitClock.restart();
}

void Tank::updateAnimation(Map& battleField, RenderWindow& window) {
	if (isRotatingToShoot == true) {
		rotateTankToShoot(target_shoot_angle);

		if (isRotatingToShoot == false and has_pending_shot == true) {
			if (activeBullet != nullptr) {
				delete activeBullet;
			}

			activeBullet = new Bullet(this->pos, bullet_shoot_angle, this->color, battleField, window, pending_powerUpAStar, pending_tanks_position);
			activeBullet->movement(pending_destination, battleField, window);

			has_pending_shot = false;
		}
		return;
	}

	if (isShowingPath == false and isMoving == false) {
		return;
	}

	if (isShowingPath == true) {
		if (waitClock.getElapsedTime().asSeconds() < 0.2) {
			return;
		}

		waitClock.restart();
		if (current != nullptr) {
			int idSquare = current->data;
			int c_row = idSquare / battleField.getColumns();
			int c_column = idSquare % battleField.getColumns();
			battleField.setMatrixSquare(c_row, c_column, 10);
			current = current->next;
		}
		else {
			current = savedPath.getHead();
			current = current->next;
			isShowingPath = false;
			isMoving = true;
			isRotating = true;
			if (current != nullptr) {
				int idSquare = current->data;
				target_row = idSquare / battleField.getColumns();
				target_column = idSquare % battleField.getColumns();
			}
			else {
				isMoving = false;
			}
		}
		return;
	}

	if (isMoving == true) {
		if (current == nullptr) {
			isMoving = false;
			return;
		}

		if (tank_row == target_row and tank_column == target_column) {
			current = current->next;
			if (current != nullptr) {
				int idSquare = current->data;
				target_row = idSquare / battleField.getColumns();
				target_column = idSquare % battleField.getColumns();
				isRotating = true;
			}
			else {
				isMoving = false;
			}
			return;
		}

		float c_row = target_row;
		float c_column = target_column;

		if (isRotating == true) {
			if (waitClock.getElapsedTime().asSeconds() < 0.01) {
				return;
			}
			waitClock.restart();

			if (tank_row < c_row) {
				if (abs(angle - 90) > 1) {
					if (90 < angle and angle < 270) {
						angle -= 2;
					}
					else {
						angle += 2;
					}
				}
				else {
					isRotating = false;
				}
			}
			else if (tank_row > c_row) {
				if (abs(angle - 270) > 1) {
					if (90 < angle and angle < 270) {
						angle += 2;
					}
					else {
						angle -= 2;
					}
				}
				else {
					isRotating = false;
				}
			}
			else if (tank_column < c_column) {
				if (abs(angle - 180) > 1) {
					if (angle < 180) {
						angle += 2;
					}
					else {
						angle -= 2;
					}
				}
				else {
					isRotating = false;
				}
			}
			else if (tank_column > c_column) {
				if (abs(angle - 0) > 1 && abs(angle - 360) > 1) {
					if (180 < angle and angle < 360) {
						angle += 2;
					}
					else {
						angle -= 2;
					}
				}
				else {
					if (angle >= 360) { angle = 0; }
					isRotating = false;
				}
			}
			else {
				isRotating = false;
			}

			if (angle >= 360) {
				angle -= 360;
			}
			if (angle < 0) {
				angle += 360;
			}
		}
		else {
			if (waitClock.getElapsedTime().asSeconds() < 0.01) {
				return;
			}
			waitClock.restart();

			if (tank_row < c_row) {
				tank_row += 0.01;
				if (tank_row >= c_row) { tank_row = c_row; }
			}
			else if (tank_row > c_row) {
				tank_row -= 0.01;
				if (tank_row <= c_row) { tank_row = c_row; }
			}
			else if (tank_column < c_column) {
				tank_column += 0.01;
				if (tank_column >= c_column) { tank_column = c_column; }
			}
			else if (tank_column > c_column) {
				tank_column -= 0.01;
				if (tank_column <= c_column) { tank_column = c_column; }
			}

			if (abs(tank_row - c_row) < 0.001) { tank_row = c_row; }
			if (abs(tank_column - c_column) < 0.001) { tank_column = c_column; }

			if (tank_row == c_row and tank_column == c_column) {
				current = current->next;
				if (current != nullptr) {
					int idSquare = current->data;
					target_row = idSquare / battleField.getColumns();
					target_column = idSquare % battleField.getColumns();
					isRotating = true;
				}
				else {
					isMoving = false;
				}
			}
		}
	}
}

Tank::Tank(int position, float angle, string color, Map& battleField, RenderWindow& window) {
	this->pos = position;
	this->angle = angle;
	this->color = color;
	this->health = 100;
	this->isAlive = true;

	tank_row = pos / battleField.getColumns();
	tank_column = pos % battleField.getColumns();
	blue_tank.loadFromFile("assets/blue_tank.png");
	red_tank.loadFromFile("assets/red_tank.png");
	sky_blue_tank.loadFromFile("assets/sky_blue_tank.png");
	yellow_tank.loadFromFile("assets/yellow_tank.png");
	HealthAt100.loadFromFile("assets/HealthAt100.png");
	HealthAt75.loadFromFile("assets/HealthAt75.png");
	HealthAt50.loadFromFile("assets/HealthAt50.png");
	HealthAt25.loadFromFile("assets/HealthAt25.png");
	HealthAt0.loadFromFile("assets/HealthAt0.png");



	if (color == "blue") seal_tank = new Sprite(blue_tank);
	else if (color == "sky_blue") seal_tank = new Sprite(sky_blue_tank);
	else if (color == "red") seal_tank = new Sprite(red_tank);
	else if (color == "yellow") seal_tank = new Sprite(yellow_tank);

	seal_tank->setOrigin(Vector2f(25, 25));

	seal_health = new Sprite(HealthAt100);
}

void Tank::draw(Map& battleField, RenderWindow& window) {
	seal_tank->setPosition(Vector2f(tank_row * 50 + 25, tank_column * 50 + 25));
	seal_tank->setRotation(degrees(angle));
	pos = battleField.getId(tank_row, tank_column);
	window.draw(*seal_tank);

	if (health <= 100 and health > 75) {
		seal_health->setTexture(HealthAt100);
	}
	else if (health <= 75 and health > 50) {
		seal_health->setTexture(HealthAt75);
	}
	else if (health <= 50 and health > 25) {
		seal_health->setTexture(HealthAt50);
	}
	else if (health <= 25 and health > 0) {
		seal_health->setTexture(HealthAt25);
	}
	else if (health <= 0) {
		seal_health->setTexture(HealthAt0);
	}
	seal_health->setPosition(Vector2f(tank_row * 50 -25, tank_column * 50 - 50));
	window.draw(*seal_health);
}

void Tank::movement(float f_pos, Map& battleField, RenderWindow& window, int max_random_n) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(0, max_random_n);

	int random = distr(gen);
	yellow_ground.loadFromFile("assets/yellow_ground.png");
	battleField.erasePath();

	if (color == "blue" or color == "sky_blue") {
		if (random == 1) {
			LinkedList<int> path = LOS::Path(battleField.getAdj(), battleField.getSize(), pos, f_pos, battleField.getColumns());
			animateMovement(f_pos, battleField, window, path);
		}
		else {
			LinkedList<int> path = BFS::shortestPath(battleField.getAdj(), battleField.getSize(), pos, f_pos);
			animateMovement(f_pos, battleField, window, path);
		}
	}
	else {
		if (random == 1) {
			LinkedList<int> path = LOS::Path(battleField.getAdj(), battleField.getSize(), pos, f_pos, battleField.getColumns());
			animateMovement(f_pos, battleField, window, path);
		}
		else {
			
			LinkedList<int> path = Dijkstra::shortestPath(battleField.getAdj(), battleField.getSize(), pos, f_pos);
			animateMovement(f_pos, battleField, window, path);
		}
	}
}
void Tank::rotateTankToShoot(float target_angle) {
	if (waitClock.getElapsedTime().asSeconds() < 0.01) {
		return;
	}
	waitClock.restart();

	if (abs(angle - target_angle) > 1 && abs(angle - target_angle) < 359) {
		float opposite_angle = target_angle + 180;
		if (opposite_angle >= 360) {
			opposite_angle -= 360;
		}

		if (target_angle < 180) {
			if (target_angle < angle and angle < opposite_angle) {
				angle -= 2;
			}
			else {
				angle += 2;
			}
		}
		else {
			if (opposite_angle < angle and angle < target_angle) {
				angle += 2;
			}
			else {
				angle -= 2;
			}
		}
	}
	else {
		isRotatingToShoot = false;
	}

	if (angle >= 360) {
		angle -= 360;
	}
	if (angle < 0) {
		angle += 360;
	}
}
void Tank::Shoot(int destination, Map& battleField, RenderWindow& window, Queue<int>& powerups, LinkedList<Tank*>& tanks_list) {
	Vector2i mousePos = Mouse::getPosition(window);
	float destX = mousePos.x;
	float destY = mousePos.y;
	float currX = (this->pos / battleField.getColumns()) * 50.0f + 25.0f;
	float currY = (this->pos % battleField.getColumns()) * 50.0f + 25.0f;

	float math_angle = atan2(destY - currY, destX - currX) * 180.0 / 3.14159265;

	bullet_shoot_angle = math_angle;
	if (bullet_shoot_angle < 0) {
		bullet_shoot_angle += 360;
	}

	target_shoot_angle = math_angle + 90.0;
	if (target_shoot_angle >= 360) {
		target_shoot_angle -= 360;
	}
	if (target_shoot_angle < 0) {
		target_shoot_angle += 360;
	}

	pending_powerUpAStar = false;
	if (!powerups.isEmpty() && powerups.front() == 2) {
		pending_powerUpAStar = true;
		powerups.dequeue();
	}

	pending_destination = destination;
	pending_tanks_position = tanks_list;

	isRotatingToShoot = true;
	has_pending_shot = true;
}