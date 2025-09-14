#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "tile.h"
#pragma once
using namespace std;

class Board {
public:
    // default constructor
    Board();
    Board(int columnNum, int rowNum, int mineNum);
    void CreateBoard();
    void RestartBoard();
    // turns all tiles on or off debug mode / pause mode
    void DebugMode();
    void PauseMode();
    void WinMode();
    void LoseMode();
    // getters
    int getColumnNum();
    int getRowNum();
    int getMineNum();
    Tile* getTile(int column, int row);
private:
    // num of columns
    int columnNum = 0;
    // num of rows
    int rowNum = 0;
    // num of mines
    int mineNum = 0;
    // num of tiles = columnNum * rowNum
    int tileNum = 0;
    // 2D vector for the board that contains tile objects
    vector<vector<Tile>> boardVector;
};