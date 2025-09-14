#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "board.h"
#include "leaderboard.h"
#include "texture.h"
using namespace std;

#pragma once

class Game: private Board, private Leaderboard, private TextureManager{
public:
	Game(int columnNum, int rowNum, int mineNum);
	// set timer
	void setTimer();
	void pausePlayTimer(int option = 0);
	void resetTimer();
	// get time
	float getTotalTime();
	// press buttons
	void buttonPressed(sf::Vector2i coordinate);
	bool isDebugButtonPressed(sf::Vector2i coordinate);
	bool isPauseButtonPressed(sf::Vector2i coordinate);
	bool isFaceButtonPressed(sf::Vector2i coordinate);
	bool isLeaderboadButtonPressed(sf::Vector2i coordinate);
	// button functionality
	void setDebugMode();
	void setPauseMode();
	void resetBoard();
	void setWinMode();
	// reveal tile
	void revealTile(sf::Vector2i coordinate);
	// place flag
	void placeFlag(sf::Vector2i coordinate);
	// draw functions
	void drawBoard();
	void drawUI();
	void drawMineCount();
	void drawTimer();
	// leaderboard functionality
	void createLeaderboardWindow();
	void leaderboardWindowEventLoop();
	void updateLeaderboard(string name, double Time);
	// check if the game was won
	bool checkWin();
	bool IsGameOver();
	bool IsLost();

	sf::RenderWindow gameWindow;
private:
	// sprites for the UI buttons
	sf::Sprite debugButton;
	sf::Sprite leaderboardButton;
	sf::Sprite pauseButton;
	sf::Sprite faceButton;
	// vector of sprites for the mine count
	vector<sf::Sprite> mineCountSprites;
	// vector of sprites for the timer
	vector<sf::Sprite> timerSprites;

	// the game window width and height
	unsigned int width = 0;
	unsigned int height = 0;

	// if the game is paused
	bool isPaused = false;
	// if the game is in play or over
	bool isGameOver = false;
	// if the game is won or lost
	bool isLost = true;
	// number of mines left (mineNum - # of flags)
	int minesLeft;

	// timer:
	// the point in time when the game started
	chrono::steady_clock::time_point startTime;
	// the time elapsed from the breakpoint to the current point in time
	chrono::duration<double> elapsedTimeSinceBreakpoint;
	// the time elapsed since the last breakpoint
	chrono::duration<double> elapsedTimeUntilBreakpoint;
	// the total time the game has lasted (not counting pauses); running total
	chrono::duration<double> totalTimeDuration;
	// breakpoint (triggered by pause button)
	chrono::steady_clock::time_point breakPointTime;
};
