#include "board.h"
using namespace std;

Board::Board() {
    columnNum = 0;
    // num of rows
    rowNum = 0;
    // num of mines
    mineNum = 0;
    // num of tiles = columnNum * rowNum
    tileNum = 0;
}

// overloaded constructor that reads info from board_config.cfg
Board::Board(int columnNum, int rowNum, int mineNum) {
    // set columnNum and rowNum and mineNum with arguments
    this->columnNum = columnNum;
    this->rowNum = rowNum;
    this->mineNum = mineNum;

    // assign tileNum to columnNum * rowNum
    tileNum = columnNum * rowNum;

    // DEBUG: print out all variables
    cout << "columnNum: " << columnNum << endl;
    cout << "rowNum: " << rowNum << endl;
    cout << "mineNum: " << mineNum << endl;
    cout << "tileNum: " << tileNum << endl;
}

// restart board
void Board::RestartBoard() {
    // clear the vector
    boardVector.clear();
    // create the board again
    CreateBoard();
}

// Debug mode
void Board::DebugMode() {
    for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector.at(i).size(); j++) {
            boardVector.at(i).at(j).DebugMode();
        }
    }
}

// Pause mode (locks everything)
void Board::PauseMode() {
    for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector.at(i).size(); j++) {
            boardVector.at(i).at(j).Paused();
        }
    }
}

void Board::WinMode() {
    // set all mines to be flagged
    for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector.at(i).size(); j++) {
            if (boardVector.at(i).at(j).IsHidden()) { boardVector.at(i).at(j).PlaceFlag(); }
        }
    }
}

void Board::LoseMode() {
    // set all mines to be revealed
    for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector.at(i).size(); j++) {
            if (boardVector.at(i).at(j).IsMine()) { boardVector.at(i).at(j).Reveal(); }
        }
    }
}

//Getter: columnNum
int Board::getColumnNum() {
    return columnNum;
}

//Getter: rowNum
int Board::getRowNum() {
    return rowNum;
}

//Getter: mineCount
int Board::getMineNum() {
    return mineNum;
}

//Getter: get tile
Tile* Board::getTile(int column, int row) {
    return &boardVector.at(row).at(column);
}

// create board
void Board::CreateBoard() {
    // populate board 2D vector with Tile objects
    for (int i = 0; i < rowNum; i++) {
        vector<Tile> row;
        for (int j = 0; j < columnNum; j++) {
            // create new tile
            Tile newTile;
            // set position of its sprites
            newTile.spriteBG.setPosition(j * 32, i * 32);
            newTile.spriteTopImage.setPosition(j * 32, i * 32);
            row.push_back(newTile);
        }
        boardVector.push_back(row);
    }
    cout << "board created" << endl;
    // link tiles
    Tile* ptr = nullptr;
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < columnNum; j++) {
            if (j != 0 && i != 0) {
                // push back ptr to tile left above
                ptr = &(boardVector.at(i - 1).at(j - 1));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
            if (i != 0) {
                // push back ptr to tile above
                ptr = &(boardVector.at(i - 1).at(j));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
            if (j != columnNum - 1 && i != 0) {
                // push back ptr to tile right above
                ptr = &(boardVector.at(i - 1).at(j + 1));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
            if (j != 0) {
                // push back ptr to tile behind
                ptr = &(boardVector.at(i).at(j - 1));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
            if (j != columnNum - 1) {
                // push back ptr to tile in front
                ptr = &(boardVector.at(i).at(j + 1));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
            if (i != rowNum - 1 && j != 0) {
                // push back ptr to tile left bellow
                ptr = &(boardVector.at(i + 1).at(j - 1));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
            if (!(i == rowNum - 1)) {
                // push back ptr to tile bellow
                ptr = &(boardVector.at(i + 1).at(j));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
            if (i != rowNum - 1 && j != columnNum - 1) {
                // push back ptr to tile right bellow
                ptr = &(boardVector.at(i + 1).at(j + 1));
                boardVector.at(i).at(j).adjacentTiles.push_back(ptr);
            }
        }
    }
    cout << "Linked" << endl;
    // Randomly assign tiles to mines
    int mineCount = mineNum;
    int randCol;
    int randRow;
    while (mineCount > 0) {
        randCol = rand() % columnNum;
        randRow = rand() % rowNum;
        if (!boardVector.at(randRow).at(randCol).IsMine()) {
            boardVector.at(randRow).at(randCol).PlaceMine();
            mineCount--;
        }
    }
    cout << "mines assigned" << endl;
}