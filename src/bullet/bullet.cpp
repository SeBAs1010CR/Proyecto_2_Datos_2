#include "bullet.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include "../map/map.h"
#include "../algorithms/LOS_Bullet.h"
#include "../algorithms/A_Star.h"
#include "../Tank/tank.h"
#include "../Structures/Queue.h"


using namespace std;

void Bullet::animateMovement(float f_pos, Map& battleField, RenderWindow& window, LinkedList<int>& path) {
	savedPath = path;
	current = savedPath.getHead();
	isShowingPath = true;
	isMoving = false;
	waitClock.restart();
}

void Bullet::updateAnimationAStar(Map& battleField, RenderWindow& window) {
	if (isShowingPath == false and isMoving == false) {
		return;
	}

	if (isShowingPath == true) {
		if (waitClock.getElapsedTime().asSeconds() < 0.1) {
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
			if (current != nullptr) current = current->next;
			isShowingPath = false;
			isMoving = true;
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
			isActive = false;
			return;
		}

		if (abs(bullet_row - target_row) < 0.05 and abs(bullet_column - target_column) < 0.05) {
			bullet_row = target_row;
			bullet_column = target_column;
			current = current->next;
			if (current != nullptr) {
				int idSquare = current->data;
				target_row = idSquare / battleField.getColumns();
				target_column = idSquare % battleField.getColumns();
			}
			else {
				int final_id = battleField.getId((int)bullet_row, (int)bullet_column);
				Node<Tank*>* curr_tank = tanks_list.getHead();
				while (curr_tank != nullptr) {
					Tank* t = curr_tank->data;
					if (t->isAlive and t->getPos() == final_id) {
						if (t->color == "blue" or t->color == "sky_blue") t->setHealth(25);
						else t->setHealth(50);
						break;
					}
					curr_tank = curr_tank->next;
				}
				isMoving = false;
				isActive = false;
			}
			return;
		}

		if (waitClock.getElapsedTime().asSeconds() < 0.01) {
			return;
		}
		waitClock.restart();

		if (bullet_row < target_row) bullet_row += 0.05;
		else if (bullet_row > target_row) bullet_row -= 0.05;
		else if (bullet_column < target_column) bullet_column += 0.05;
		else if (bullet_column > target_column) bullet_column -= 0.05;
	}
}

void Bullet::updateAnimationLOS(Map& battleField, RenderWindow& window, Queue<int>& powerups) {
	if (isShowingPath == false and isMoving == false) {
		return;
	}

	if (isShowingPath == true) {
		if (waitClock.getElapsedTime().asSeconds() < 0.1) {
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
			isShowingPath = false;
			isMoving = true;
		}
		return;
	}

	if (isMoving == true) {
		if (waitClock.getElapsedTime().asSeconds() < 0.01) {
			return;
		}
		waitClock.restart();

		if (curr_x_node != nullptr and curr_y_node != nullptr) {
			double bullet_x = curr_x_node->data;
			double bullet_y = curr_y_node->data;

			bullet_row = (bullet_x - 25.0) / 50.0;
			bullet_column = (bullet_y - 25.0) / 50.0;

			curr_x_node = curr_x_node->next;
			curr_y_node = curr_y_node->next;
		}
		else {
			if (isActive) {
				int final_row = int((bullet_row * 50.0 + 25.0) / 50.0);
				int final_column = int((bullet_column * 50.0 + 25.0) / 50.0);
				int final_id = battleField.getId(final_row, final_column);

				Node<Tank*>* curr_tank = tanks_list.getHead();
				while (curr_tank != nullptr) {
					Tank* target_tank = curr_tank->data;

					if (target_tank->isAlive and target_tank->getPos() == final_id) {
						if (target_tank->color == "blue" or target_tank->color == "sky_blue") {
							if (!powerups.isEmpty() and powerups.front() == 3) {
								target_tank->setHealth(100);
								powerups.dequeue();
							}
							else {
								target_tank->setHealth(25);
							}
							
						}
						else {
							if (!powerups.isEmpty() and powerups.front() == 3) {
								target_tank->setHealth(100);
								powerups.dequeue();
							}
							else {
								target_tank->setHealth(50);
							}
						}
						break;
					}
					curr_tank = curr_tank->next;
				}
			}
			isMoving = false;
			isActive = false;
		}
	}
}


Bullet::Bullet(int position, float angle, string color, Map& battleField, RenderWindow& window, bool powerup, LinkedList<Tank*>& tanks_list) {
	this->pos = position;
	this->angle = angle;
	this->color = color;
	this->powerup = powerup;
	this->isActive = true;
	this->origin_id = position;

	Node<Tank*>* curr_tank = tanks_list.getHead();
	while (curr_tank != nullptr) {
		this->tanks_list.insert(curr_tank->data);
		curr_tank = curr_tank->next;
	}

	bullet_row = pos / battleField.getColumns();
	bullet_column = pos % battleField.getColumns();
	bullet.loadFromFile("assets/bullet.png");
	seal_bullet = new Sprite(bullet);
	seal_bullet->setOrigin(Vector2f(25, 25));
}

void Bullet::draw(Map& battleField, RenderWindow& window) {
	if (isActive == true and isShowingPath == false) {
		seal_bullet->setPosition(Vector2f(bullet_row * 50 + 25.f, bullet_column * 50 + 25.f));
		pos = battleField.getId(bullet_row, bullet_column);
		window.draw(*seal_bullet);
	}
}

void Bullet::movement(float f_pos, Map& battleField, RenderWindow& window) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(0, 1);

	int random = distr(gen);
	yellow_ground.loadFromFile("assets/yellow_ground.png");
	battleField.erasePath();

	int start_x = (pos / battleField.getColumns()) * 50 + 25;
	int start_y = (pos % battleField.getColumns()) * 50 + 25;

	if (powerup) {
		LinkedList<int> path = A_Star::shortestPath(battleField.getAdj(), battleField.getSize(), pos, f_pos, battleField.getColumns(), tanks_list);
		animateMovement(f_pos, battleField, window, path);
	}
	else {
		LinkedList<double> r_x;
		LinkedList<double> r_y;
		LinkedList<int> path = LOS_Bullet::Path(angle, battleField, start_x, start_y, tanks_list, r_x, r_y);
		routeX = r_x;
		routeY = r_y;
		curr_x_node = routeX.getHead();
		curr_y_node = routeY.getHead();
		animateMovement(f_pos, battleField, window, path);
	}
}

