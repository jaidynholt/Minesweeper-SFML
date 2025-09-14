#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#pragma once
using namespace std;

class Leaderboard {
public:
	Leaderboard(int columnNum, int rowNum);
	void createWindow();
	void addScore(string name, double time);
	void setScoreboard();
	void drawText();
	void readFromFile();
	void writeToFile();
	sf::RenderWindow leaderboardWindow;
private:
	unsigned int width = 0;
	unsigned int height = 0;
	map<string, vector<string>> scores;
	sf::Font font;
	sf::Text titleText;
	sf::Text scoresText;
	string scoreboard = "";
};