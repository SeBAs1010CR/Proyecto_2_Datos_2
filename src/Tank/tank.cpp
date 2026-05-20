#include "Tank.h"

void Tank::animateMovement(float f_pos, Map& battleField, RenderWindow& window, LinkedList<int>& path) {
	savedPath = path;
	destPos = int(f_pos);
	animState = SHOWING_PATH;
	current = savedPath.getHead();
	animTimer.restart();
}

void Tank::updateAnimation(Map& battleField, RenderWindow& window) {
	if (animState == IDLE) return;

	if (animState == SHOWING_PATH) {
		if (animTimer.getElapsedTime().asSeconds() < 0.2) return;

		animTimer.restart();
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
			animState = MOVING;
			isRotating = true;
			if (current != nullptr) {
				int id = current->data;
				targetRow = id / battleField.getColumns();
				targetCol = id % battleField.getColumns();
			}
			else {
				animState = IDLE;
			}
		}
		return;
	}

	if (animState == MOVING) {
		if (current == nullptr) {
			animState = IDLE;
			return;
		}

		if (tank_row == targetRow && tank_column == targetCol) {
			current = current->next;
			if (current != nullptr) {
				int id = current->data;
				targetRow = id / battleField.getColumns();
				targetCol = id % battleField.getColumns();
				isRotating = true;
			}
			else {
				animState = IDLE;
			}
			return;
		}

		float c_row = targetRow;
		float c_column = targetCol;

		if (isRotating) {
			if (animTimer.getElapsedTime().asSeconds() < 0.01) return;
			animTimer.restart();

			float targetAngle;
			if (tank_row < c_row) targetAngle = 90;
			else if (tank_row > c_row) targetAngle = 270;
			else if (tank_column < c_column) targetAngle = 180;
			else if (tank_column > c_column) targetAngle = 0;
			else {
				isRotating = false;
				return;
			}

			float diff = targetAngle - angle;
			while (diff > 180) diff -= 360;
			while (diff < -180) diff += 360;

			if (abs(diff) <= 2) {
				angle = targetAngle;
				isRotating = false;
			}
			else {
				if (diff > 0) angle += 2;
				else angle -= 2;
				if (angle >= 360) angle -= 360;
				if (angle < 0) angle += 360;
			}
		}
		else {
			if (animTimer.getElapsedTime().asSeconds() < 0.01) return;
			animTimer.restart();

			if (tank_row < c_row) {
				tank_row += 0.01f;
				if (tank_row >= c_row) tank_row = c_row;
			}
			else if (tank_row > c_row) {
				tank_row -= 0.01f;
				if (tank_row <= c_row) tank_row = c_row;
			}
			else if (tank_column < c_column) {
				tank_column += 0.01f;
				if (tank_column >= c_column) tank_column = c_column;
			}
			else if (tank_column > c_column) {
				tank_column -= 0.01f;
				if (tank_column <= c_column) tank_column = c_column;
			}

			if (abs(tank_row - c_row) < 0.001f) tank_row = c_row;
			if (abs(tank_column - c_column) < 0.001f) tank_column = c_column;

			if (tank_row == c_row && tank_column == c_column) {
				current = current->next;
				if (current != nullptr) {
					int id = current->data;
					targetRow = id / battleField.getColumns();
					targetCol = id % battleField.getColumns();
					isRotating = true;
				}
				else {
					animState = IDLE;
				}
			}
		}
	}
}

Tank::Tank(int position, float angle, string color, Map& battleField, RenderWindow& window) {
	this->pos = position;
	this->angle = angle;
	this->color = color;

	tank_row = pos / battleField.getColumns();
	tank_column = pos % battleField.getColumns();
	blue_tank.loadFromFile("assets/blue_tank.png");
	red_tank.loadFromFile("assets/red_tank.png");
	sky_blue_tank.loadFromFile("assets/sky_blue_tank.png");
	yellow_tank.loadFromFile("assets/yellow_tank.png");
	;

	if (color == "blue") seal_tank = new Sprite(blue_tank);
	else if (color == "sky_blue") seal_tank = new Sprite(sky_blue_tank);
	else if (color == "red") seal_tank = new Sprite(red_tank);
	else if (color == "yellow") seal_tank = new Sprite(yellow_tank);

	seal_tank->setOrigin(Vector2f(25, 25));
}
void Tank::draw(Map& battleField, RenderWindow& window) {
	seal_tank->setPosition(Vector2f(tank_row * 50 + 25.f, tank_column * 50 + 25.f));
	seal_tank->setRotation(degrees(angle));
	pos = battleField.getId(tank_row, tank_column);
	window.draw(*seal_tank);
}

void Tank::movement(float f_pos, Map& battleField, RenderWindow& window) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(0, 1);

	int random = distr(gen);
	yellow_ground.loadFromFile("assets/yellow_ground.png");
	battleField.erasePath();

	if (color == "blue" or color == "sky_blue") {
		if (random == 1) {
			LinkedList<int> path = BFS::shortestPath(battleField.getAdj(), battleField.getSize(), pos, f_pos);
			animateMovement(f_pos, battleField, window, path);

		}
		else {
			LinkedList<int> path = LOS::Path(battleField.getAdj(), battleField.getSize(), pos, f_pos, battleField.getColumns());
			animateMovement(f_pos, battleField, window, path);

		}
	}
	else {
		if (random == 1) {
			LinkedList<int> path = Dijkstra::shortestPath(battleField.getAdj(), battleField.getSize(), pos, f_pos);
			animateMovement(f_pos, battleField, window, path);

		}
		else {
			LinkedList<int> path = LOS::Path(battleField.getAdj(), battleField.getSize(), pos, f_pos, battleField.getColumns());
			animateMovement(f_pos, battleField, window, path);
		}

	}
}