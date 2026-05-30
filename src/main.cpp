#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include "map/map.h"
#include "Tank/tank.h"
#include "Structures/Queue.h"
#include "bullet/bullet.h"
using namespace std;
using namespace sf;
const int SQUARE_SIZE = 50;

int main()
{
    RenderWindow window(VideoMode({ 800, 600 }), "SFML Release Test");
    int rows = 16;
    int columns = 12;
    Map battleField(rows, columns);
    battleField.GraphVersion();
    int touch_n = 1;
    int turn = 1;
    string chosen;
    LinkedList<Tank*> tanks_list;

    Tank red(battleField.getId(1, 1), 180, "red", battleField, window);
    Tank blue(battleField.getId(1, columns - 2), 0, "blue", battleField, window);
    Tank yellow(battleField.getId(rows - 2, 1), 180, "yellow", battleField, window);
    Tank sky_blue(battleField.getId(rows - 2, columns - 2), 0, "sky_blue", battleField, window);

    Queue<int> powerups_1;
    Queue<int> powerups_2;

    Font font;
    font.openFromFile("assets/arial.ttf");
    Text powerupText(font);
    powerupText.setCharacterSize(30);
    powerupText.setFillColor(Color::White);
    bool showPowerupText = false;
    Clock textClock;

    bool gameOver = false;
    int winner = 0;
    Text winText(font);
    winText.setCharacterSize(50);
    winText.setFillColor(Color::White);
    winText.setPosition(Vector2f(250, 250));
    Text escText(font);
    escText.setString("Press Escape to quit");
    escText.setCharacterSize(30);
    escText.setFillColor(Color::White);
    escText.setPosition(Vector2f(270, 350));

    tanks_list.insert(&blue);
    tanks_list.insert(&red);
    tanks_list.insert(&yellow);
    tanks_list.insert(&sky_blue);

    while (window.isOpen())
    {
        window.clear();

        while (const optional<Event> event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            if (const auto* keyEvent = event->getIf<Event::KeyPressed>()) {
                if (gameOver && keyEvent->code == Keyboard::Key::Escape) {
                    window.close();
                }
                if (!gameOver && (keyEvent->code == Keyboard::Key::LShift || keyEvent->code == Keyboard::Key::RShift)) {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distr(0, 3);

                    int random = distr(gen);
                    string p_name;

                    if (random == 0) {
                        p_name = "Movimiento";
                    }
                    else if (random == 1) {
                        p_name = "Doble Turno";
                    }
                    else if (random == 2) {
                        p_name = "Bala Teledirigida";
                    }
                    else if (random == 3) {
                        p_name = "Poder de Ataque";
                    }

                    powerupText.setString("+" + p_name);

                    if (turn == 1) {
                        powerups_1.enqueue(random);
                        powerupText.setPosition(Vector2f(10, 550));
                        turn = 2;
                    }
                    else {
                        powerups_2.enqueue(random);
                        powerupText.setPosition(Vector2f(550, 550));
                        turn = 1;
                    }

                    showPowerupText = true;
                    textClock.restart();
                }
            }
            if (!gameOver) {
                if (const auto* mouseEvent = event->getIf<Event::MouseButtonPressed>()) {
                    if (mouseEvent->button == Mouse::Button::Left) {
                        int mouseX = mouseEvent->position.x;

                        int mouseY = mouseEvent->position.y;
                        int squareRow = mouseX / 50;
                        int squareColumn = mouseY / 50;
                        int idSquare = battleField.getId(squareRow, squareColumn);
                        if (turn == 1) {
                            if (touch_n == 1) {
                                if (battleField.getId(squareRow, squareColumn) == blue.getPos()) {
                                    chosen = "blue";
                                    touch_n = 2;
                                }
                                else if (battleField.getId(squareRow, squareColumn) == red.getPos()) {
                                    chosen = "red";
                                    touch_n = 2;
                                }
                            }
                            else {
                                int distancex = abs(blue.getPos() / columns - squareRow);
                                int distancey = abs(blue.getPos() % columns - squareColumn);
                                if (chosen == "blue" and distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey) and battleField.getMatrixSquare(squareRow, squareColumn) == 0 and idSquare != red.getPos() and idSquare != yellow.getPos() and idSquare != sky_blue.getPos()) {
                                    if (!powerups_1.isEmpty() and powerups_1.front() == 0) {
                                        blue.movement(battleField.getId(squareRow, squareColumn), battleField, window, 9);
                                        powerups_1.dequeue();
                                    }
                                    else {
                                        blue.movement(battleField.getId(squareRow, squareColumn), battleField, window, 1);
                                    }

                                    if (!powerups_1.isEmpty() and powerups_1.front() == 1) {
                                        powerups_1.dequeue();
                                    }
                                    else {
                                        turn = 2;
                                    }
                                    touch_n = 1;
                                }

                                distancex = abs(red.getPos() / columns - squareRow);
                                distancey = abs(red.getPos() % columns - squareColumn);
                                if (chosen == "red" and distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey) and battleField.getMatrixSquare(squareRow, squareColumn) == 0 and idSquare != blue.getPos() and idSquare != yellow.getPos() and idSquare != sky_blue.getPos()) {
                                    if (!powerups_1.isEmpty() and powerups_1.front() == 0) {
                                        red.movement(battleField.getId(squareRow, squareColumn), battleField, window, 9);
                                        powerups_1.dequeue();
                                    }
                                    else {
                                        red.movement(battleField.getId(squareRow, squareColumn), battleField, window, 1);
                                    }
                                    if (!powerups_1.isEmpty() and powerups_1.front() == 1) {
                                        powerups_1.dequeue();
                                    }
                                    else {
                                        turn = 2;
                                    }
                                    touch_n = 1;
                                }
                            }

                        }
                        else {
                            if (touch_n == 1) {
                                if (battleField.getId(squareRow, squareColumn) == yellow.getPos()) {
                                    chosen = "yellow";
                                    touch_n = 2;
                                }
                                else if (battleField.getId(squareRow, squareColumn) == sky_blue.getPos()) {
                                    chosen = "sky_blue";
                                    touch_n = 2;
                                }
                            }
                            else {
                                int distancex = abs(yellow.getPos() / columns - squareRow);
                                int distancey = abs(yellow.getPos() % columns - squareColumn);
                                if (chosen == "yellow" and distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey) and battleField.getMatrixSquare(squareRow, squareColumn) == 0 and idSquare != red.getPos() and idSquare != blue.getPos() and idSquare != sky_blue.getPos()) {
                                    if (!powerups_2.isEmpty() and powerups_2.front() == 0) {
                                        yellow.movement(battleField.getId(squareRow, squareColumn), battleField, window, 9);
                                        powerups_2.dequeue();
                                    }
                                    else {
                                        yellow.movement(battleField.getId(squareRow, squareColumn), battleField, window, 1);
                                    }
                                    if (!powerups_2.isEmpty() and powerups_2.front() == 1) {
                                        powerups_2.dequeue();
                                    }
                                    else {
                                        turn = 1;
                                    }
                                    touch_n = 1;
                                }
                                distancex = abs(sky_blue.getPos() / columns - squareRow);
                                distancey = abs(sky_blue.getPos() % columns - squareColumn);
                                if (chosen == "sky_blue" and distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey) and battleField.getMatrixSquare(squareRow, squareColumn) == 0 and idSquare != red.getPos() and idSquare != yellow.getPos() and idSquare != blue.getPos()) {
                                    if (!powerups_2.isEmpty() and powerups_2.front() == 0) {
                                        sky_blue.movement(battleField.getId(squareRow, squareColumn), battleField, window, 9);
                                        powerups_2.dequeue();
                                    }
                                    else {
                                        sky_blue.movement(battleField.getId(squareRow, squareColumn), battleField, window, 1);
                                    }
                                    if (!powerups_2.isEmpty() and powerups_2.front() == 1) {
                                        powerups_2.dequeue();
                                    }
                                    else {
                                        turn = 1;
                                    }
                                    touch_n = 1;
                                }
                            }
                        }
                    }

                    if (mouseEvent->button == Mouse::Button::Right) {
                        int mouseX = mouseEvent->position.x;
                        int mouseY = mouseEvent->position.y;
                        int squareRow = mouseX / 50;
                        int squareColumn = mouseY / 50;
                        int idSquare = battleField.getId(squareRow, squareColumn);

                        if (touch_n == 2) {
                            if (turn == 1) {
                                if (chosen == "blue") {
                                    int distancex = abs(blue.getPos() / columns - squareRow);
                                    int distancey = abs(blue.getPos() % columns - squareColumn);
                                    if (!powerups_1.isEmpty() and powerups_1.front() == 2) {
                                        if (0 < distancex or 0 < distancey) {
                                            blue.Shoot(idSquare, battleField, window, powerups_1, tanks_list);

                                            if (!powerups_1.isEmpty() and powerups_1.front() == 1) {
                                                powerups_1.dequeue();
                                            }
                                            else {
                                                turn = 2;
                                            }
                                            touch_n = 1;
                                        }
                                    }
                                    if (distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey)) {
                                        blue.Shoot(idSquare, battleField, window, powerups_1, tanks_list);

                                        if (!powerups_1.isEmpty() and powerups_1.front() == 1) {
                                            powerups_1.dequeue();
                                        }
                                        else {
                                            turn = 2;
                                        }
                                        touch_n = 1;
                                    }
                                }
                                else  if (chosen == "red") {
                                    int distancex = abs(red.getPos() / columns - squareRow);
                                    int distancey = abs(red.getPos() % columns - squareColumn);
                                    if (!powerups_1.isEmpty() and powerups_1.front() == 2) {
                                        if (0 < distancex or 0 < distancey) {
                                            red.Shoot(idSquare, battleField, window, powerups_1, tanks_list);

                                            if (!powerups_1.isEmpty() and powerups_1.front() == 1) {
                                                powerups_1.dequeue();
                                            }
                                            else {
                                                turn = 2;
                                            }
                                            touch_n = 1;
                                        }
                                    }
                                    if (distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey)) {
                                        red.Shoot(idSquare, battleField, window, powerups_1, tanks_list);

                                        if (!powerups_1.isEmpty() and powerups_1.front() == 1) {
                                            powerups_1.dequeue();
                                        }
                                        else {
                                            turn = 2;
                                        }
                                        touch_n = 1;
                                    }
                                }
                            }
                            else {
                                if (chosen == "yellow") {
                                    int distancex = abs(yellow.getPos() / columns - squareRow);
                                    int distancey = abs(yellow.getPos() % columns - squareColumn);
                                    if (!powerups_2.isEmpty() and powerups_2.front() == 2) {
                                        if (0 < distancex or 0 < distancey) {
                                            yellow.Shoot(idSquare, battleField, window, powerups_2, tanks_list);
                                            if (!powerups_2.isEmpty() and powerups_2.front() == 1) {
                                                powerups_2.dequeue();
                                            }
                                            else {
                                                turn = 1;
                                            }
                                            touch_n = 1;
                                        }
                                    }
                                    if (distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey)) {
                                        yellow.Shoot(idSquare, battleField, window, powerups_2, tanks_list);
                                        if (!powerups_2.isEmpty() and powerups_2.front() == 1) {
                                            powerups_2.dequeue();
                                        }
                                        else {
                                            turn = 1;
                                        }
                                        touch_n = 1;
                                    }
                                }
                                else  if (chosen == "sky_blue") {
                                    int distancex = abs(sky_blue.getPos() / columns - squareRow);
                                    int distancey = abs(sky_blue.getPos() % columns - squareColumn);
                                    if (!powerups_2.isEmpty() and powerups_2.front() == 2) {
                                        if (0 < distancex or 0 < distancey) {
                                            sky_blue.Shoot(idSquare, battleField, window, powerups_2, tanks_list);
                                            if (!powerups_2.isEmpty() and powerups_2.front() == 1) {
                                                powerups_2.dequeue();
                                            }
                                            else {
                                                turn = 1;
                                            }
                                            touch_n = 1;
                                        }
                                    }
                                    if (distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey)) {
                                        sky_blue.Shoot(idSquare, battleField, window, powerups_2, tanks_list);
                                        if (!powerups_2.isEmpty() and powerups_2.front() == 1) {
                                            powerups_2.dequeue();
                                        }
                                        else {
                                            turn = 1;
                                        }
                                        touch_n = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (gameOver) {
            if (winner == 1) winText.setString("Player #1 won!");
            else winText.setString("Player #2 won!");
            window.draw(winText);
            window.draw(escText);
        }
        else {
            battleField.DrawMap(window);
            red.updateAnimation(battleField, window);
            blue.updateAnimation(battleField, window);
            yellow.updateAnimation(battleField, window);
            sky_blue.updateAnimation(battleField, window);

            if (red.isAlive) red.draw(battleField, window);
            if (blue.isAlive) blue.draw(battleField, window);
            if (yellow.isAlive) yellow.draw(battleField, window);
            if (sky_blue.isAlive) sky_blue.draw(battleField, window);

            if (red.activeBullet != nullptr) {
                if (red.activeBullet->getPoweupState()) {
                    red.activeBullet->updateAnimationAStar(battleField, window);
                }
                else {
                    red.activeBullet->updateAnimationLOS(battleField, window, powerups_1);
                }
                red.activeBullet->draw(battleField, window);
                if (!red.activeBullet->getActivityState()) {
                    delete red.activeBullet;
                    red.activeBullet = nullptr;
                }
            }

            if (blue.activeBullet != nullptr) {
                if (blue.activeBullet->getPoweupState()) {
                    blue.activeBullet->updateAnimationAStar(battleField, window);
                }
                else {
                    blue.activeBullet->updateAnimationLOS(battleField, window, powerups_1);
                }
                blue.activeBullet->draw(battleField, window);
                if (!blue.activeBullet->getActivityState()) {
                    delete blue.activeBullet;
                    blue.activeBullet = nullptr;
                }
            }

            if (yellow.activeBullet != nullptr) {
                if (yellow.activeBullet->getPoweupState()) {
                    yellow.activeBullet->updateAnimationAStar(battleField, window);
                }
                else {
                    yellow.activeBullet->updateAnimationLOS(battleField, window, powerups_2);
                }
                yellow.activeBullet->draw(battleField, window);
                if (!yellow.activeBullet->getActivityState()) {
                    delete yellow.activeBullet;
                    yellow.activeBullet = nullptr;
                }
            }

            if (sky_blue.activeBullet != nullptr) {
                if (sky_blue.activeBullet->getPoweupState()) {
                    sky_blue.activeBullet->updateAnimationAStar(battleField, window);
                }
                else {
                    sky_blue.activeBullet->updateAnimationLOS(battleField, window, powerups_2);
                }
                sky_blue.activeBullet->draw(battleField, window);
                if (!sky_blue.activeBullet->getActivityState()) {
                    delete sky_blue.activeBullet;
                    sky_blue.activeBullet = nullptr;
                }
            }

            if (showPowerupText == true) {
                if (textClock.getElapsedTime().asSeconds() < 2.0) {
                    window.draw(powerupText);
                }
                else {
                    showPowerupText = false;
                }
            }

            if (!yellow.isAlive && !sky_blue.isAlive) {
                gameOver = true;
                winner = 1;
            }
            else if (!red.isAlive && !blue.isAlive) {
                gameOver = true;
                winner = 2;
            }
        }
        window.display();
    }
    return 0;
}