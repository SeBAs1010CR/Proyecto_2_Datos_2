#pragma once
#include <SFML/Graphics.hpp>
class Map {
private:
    int** matrix;
    int** adj;
    int rows;
    int columns;
    sf::Texture wall_up;
    sf::Texture wall_down;
    sf::Texture wall_right;
    sf::Texture wall_left;
    sf::Texture ground;
    sf::Texture shadow;
    sf::Texture up_left_corner;
    sf::Texture up_right_corner;
    sf::Texture down_left_corner;
    sf::Texture down_right_corner;
    sf::Texture obstacle;
    sf::Texture yellow_ground;

    void matrixGenerator();
    void notIsolation();

public:
    Map(int  rows, int columns);
    void DrawMap(sf::RenderWindow& window);
    int getId(int current_row, int current_column);
    int** getAdj() { return adj; };
    int getSize() { return rows * columns; };
    int getRows() { return rows; };
    int getColumns() { return columns; };
    int getMatrixSquare(int r, int c) { return matrix[r][c]; };
    void setMatrixSquare(int r, int c, int v) { matrix[r][c] = v; };
    void GraphVersion();
    void erasePath();
};