#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#pragma once
using namespace std;

class Tile {
public:
	// setters
	void PlaceMine();
	void Reveal();
	void PlaceFlag();
	void DebugMode();
	void Paused();
	// getters
	bool IsMine();
	bool IsHidden();
	bool IsFlag();
	vector<string> getTextureName();
	// count neightboring tiles
	int countNeighbors();
	vector<Tile*> adjacentTiles;
	sf::Sprite spriteBG;
	sf::Sprite spriteTopImage;
private:
	bool isHidden = true;
	bool isMine = false;
	bool isFlag = false;
	bool isDebug = false;
	bool isPaused = false;
};