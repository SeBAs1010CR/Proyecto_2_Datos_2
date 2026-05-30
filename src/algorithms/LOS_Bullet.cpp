#include "LOS_Bullet.h"
#include <SFML/Graphics.hpp>
#include "../Tank/tank.h"
using namespace sf;

LinkedList<int> LOS_Bullet::Path(double angle, Map& battleField, int Start_x, int Start_y, LinkedList<Tank*>& tanks_list, LinkedList<double>& route_x, LinkedList<double>& route_y) {

	double angle_radians = angle * 3.14159265 / 180.0;
	double curr_x = Start_x;
	double curr_y = Start_y;
	int curr_row = int(curr_x) / 50;
	int curr_column = int(curr_y) / 50;
	int origin_id = battleField.getId(curr_row, curr_column);

	LinkedList<int> Path;
	int last_id = battleField.getId(curr_row, curr_column);
	Path.insert(last_id);
	int failsafe = 0;

	while (failsafe < 1600) {
		failsafe++;

		double old_x = curr_x;
		double old_y = curr_y;

		curr_x += 5.0 * cos(angle_radians);
		curr_y += 5.0 * sin(angle_radians);
		curr_row = int(curr_x) / 50;
		curr_column = int(curr_y) / 50;

		if (curr_row < 0 or curr_row >= battleField.getRows() or curr_column < 0 or curr_column >= battleField.getColumns()) {
			break;
		}

		int curr_id = battleField.getId(curr_row, curr_column);

		if (curr_id != origin_id) {
			origin_id = -1;

			if (Colision(battleField, tanks_list, curr_row, curr_column)) {
				Path.insert(battleField.getId(curr_row, curr_column));
				route_x.insert(curr_x);
				route_y.insert(curr_y);
				break;
			}

			if (battleField.getMatrixSquare(curr_row, curr_column) != 0) {
				int corner_x = curr_row * 50;
				int corner_y = curr_column * 50;

				angle = Rebound(curr_x, curr_y, corner_x, corner_y, angle, angle_radians);
				curr_x = old_x + 5.0 * cos(angle_radians);
				curr_y = old_y + 5.0 * sin(angle_radians);
			}
			else {
				if (curr_id != last_id) {
					Path.insert(curr_id);
					last_id = curr_id;
				}
			}
		}

		route_x.insert(curr_x);
		route_y.insert(curr_y);
	}
	return Path;
}

double LOS_Bullet::Rebound(double curr_x, double curr_y, int corner_x, int corner_y, double angle, double& angle_radians) {
	double cx = corner_x + 25.0;
	double cy = corner_y + 25.0;

	double dx = curr_x - cx;
	double dy = curr_y - cy;

	if (abs(dx) > abs(dy)) {
		angle = 180.0 - angle;

	}
	else {
		angle = -angle;

	}

	if (angle > 180.0) angle -= 360.0;
	if (angle <= -180.0) angle += 360.0;
	angle_radians = angle * 3.14159265 / 180.0;

	return angle;
}

bool LOS_Bullet::Colision(Map& battleField, LinkedList<Tank*>& tanks_list, int curr_row, int curr_column) {
	Node<Tank*>* curr_tank = tanks_list.getHead();
	while (curr_tank != nullptr) {
		Tank* t = curr_tank->data;
		if (t->isAlive) {
			int curr_tank_row = t->getPos() / battleField.getColumns();
			int curr_tank_column = t->getPos() % battleField.getColumns();

			if (curr_tank_row == curr_row and curr_tank_column == curr_column) {
				return true;
			}
		}
		curr_tank = curr_tank->next;
	}
	return false;
}