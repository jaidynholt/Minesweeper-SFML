#include "tile.h"
using namespace std;

// make this tile a mine if it is not already one
void Tile::PlaceMine() {
	isMine = true;
}

// reveal this tile, and recursively reveal others (if not paused and game still going)
void Tile::Reveal() {
	if (!isPaused) {
		if (isMine) {
			// if it is a mine, reveal it (don't do recursive part)
			isHidden = false;
		}
		else {
			// recursive revealing
			if (countNeighbors() != 0) {
				// base case: if there are mines touching this tile, reveal this tile and stop
				isHidden = false;
			}
			else {
				// if there are no mines touching this tile, reveal this tile and then reveal all its neighbors
				isHidden = false;
				for (int i = 0; i < adjacentTiles.size(); i++) {
					// if the adjacent tile is hidden and is not a flag, reveal it and then call reveal function on it
					if (adjacentTiles.at(i)->IsHidden() && !adjacentTiles.at(i)->IsFlag()) {
						adjacentTiles.at(i)->isHidden = false;
						adjacentTiles.at(i)->Reveal();
					}
				}
			}
		}
	}
}

// place or remove flag (if not paused and game still going)
void Tile::PlaceFlag() {
	if (!isPaused) { isFlag = !isFlag; }
}

// activate or deactivate debug mode (if not paused and game still going)
void Tile::DebugMode() {
	if (!isPaused) { isDebug = !isDebug; }
}

// pause / play mode
void Tile::Paused() {
	isPaused = !isPaused;
}

// getter: is mine
bool Tile::IsMine() {
	return isMine;
}

// getter: is hidden
bool Tile::IsHidden() {
	return isHidden;
}

//getter: is flag
bool Tile::IsFlag() {
	return isFlag;
}

// check neighboring tiles
int Tile::countNeighbors() {
	int count = 0;
	for (int i = 0; i < adjacentTiles.size(); i++) {
		if (adjacentTiles.at(i)->isMine) { count++; }
	}
	return count;
}

// get texture depending on board
vector<string> Tile::getTextureName() {
	vector<string> textureNames;
	if (isPaused) {
		// if game is paused, all tiles just display the revealed texture
		textureNames.push_back("tileRevealed");
		return textureNames;
	}
	if (isHidden) {
		textureNames.push_back("tileHidden");
		// if in debug mode, tiles with mines display mines over
		if (isMine && isDebug) { textureNames.push_back("mine"); }
		// if there is a flag, display it over
		else if (isFlag) { textureNames.push_back("flag"); }
	}
	else {
		textureNames.push_back("tileRevealed");
		// if it is a mine, display mine over
		if (isMine) { textureNames.push_back("mine"); }
		// if there are neighboring mines, display number over
		else if (countNeighbors() == 1) { textureNames.push_back("1"); }
		else if (countNeighbors() == 2) { textureNames.push_back("2"); }
		else if (countNeighbors() == 3) { textureNames.push_back("3"); }
		else if (countNeighbors() == 4) { textureNames.push_back("4"); }
		else if (countNeighbors() == 5) { textureNames.push_back("5"); }
		else if (countNeighbors() == 6) { textureNames.push_back("6"); }
		else if (countNeighbors() == 7) { textureNames.push_back("7"); }
		else if (countNeighbors() == 8) { textureNames.push_back("8"); }
	}
	return textureNames;
}