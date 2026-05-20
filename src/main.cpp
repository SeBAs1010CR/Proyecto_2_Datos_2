#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include "map/map.h"
#include "Tank/tank.h"
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

    Tank red(battleField.getId(1, 1), 180, "red", battleField, window);
    Tank blue(battleField.getId(1, columns - 2), 0, "blue", battleField, window);
    Tank yellow(battleField.getId(rows - 2,1), 180, "yellow", battleField, window);
    Tank sky_blue(battleField.getId(rows - 2, columns - 2), 0, "sky_blue", battleField, window);
    while (window.isOpen())
    {
        window.clear();
        battleField.DrawMap(window);

        while (const optional<Event> event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
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
                                blue.movement(battleField.getId(squareRow, squareColumn), battleField, window);
                                turn = 2;
                                touch_n = 1;
                            }

                            distancex = abs(red.getPos() / columns - squareRow);
                            distancey = abs(red.getPos() % columns - squareColumn);
                            if (chosen == "red" and distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey) and battleField.getMatrixSquare(squareRow, squareColumn) == 0 and idSquare != blue.getPos() and idSquare != yellow.getPos() and idSquare != sky_blue.getPos()) {
                                red.movement(battleField.getId(squareRow, squareColumn), battleField, window);
                                turn = 2;
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
                            if (chosen == "yellow" and  distancex < 3 and distancey < 3   and (0 < distancex or 0 < distancey) and battleField.getMatrixSquare(squareRow, squareColumn) == 0 and idSquare != red.getPos() and idSquare != blue.getPos() and idSquare != sky_blue.getPos()) {
                                yellow.movement(battleField.getId(squareRow, squareColumn), battleField, window);
                                turn = 1;
                                touch_n = 1;
                                
                            }
                            distancex = abs(sky_blue.getPos() / columns - squareRow);
                            distancey = abs(sky_blue.getPos() % columns - squareColumn);
                            if (chosen == "sky_blue" and distancex < 3 and distancey < 3 and (0 < distancex or 0 < distancey) and battleField.getMatrixSquare(squareRow, squareColumn) == 0 and idSquare != red.getPos() and idSquare != yellow.getPos() and idSquare != blue.getPos()) {
                                sky_blue.movement(battleField.getId(squareRow, squareColumn), battleField, window);
                                turn = 1;
                                touch_n = 1;
                            }
                        }
                    }

                }

                if (mouseEvent->button == Mouse::Button::Right) {
                    int mouseX = mouseEvent->position.x;

                    int mouseY = mouseEvent->position.y;

                }
            }
        }

        red.updateAnimation(battleField, window);
        blue.updateAnimation(battleField, window);
        yellow.updateAnimation(battleField, window);
        sky_blue.updateAnimation(battleField, window);

        red.draw(battleField, window);
        blue.draw(battleField, window);
        yellow.draw(battleField, window);
        sky_blue.draw(battleField, window);



        window.display();
    }
    return 0;
}