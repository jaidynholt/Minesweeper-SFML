#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <SFML/Graphics.hpp>
using namespace std;

#pragma once

class Welcome {
public:
	Welcome();
	void setInput(char inputLetter);
	void drawText();
	//getter
	string getName();
	sf::RenderWindow welcomeWindow;
	int columnNum = 0;
	int rowNum = 0;
	int mineNum = 0;
private:
	unsigned int width = 0;
	unsigned int height = 0;
	sf::Font font;
	sf::Text welcomeText;
	sf::Text inputPromptText;
	sf::Text inputText;
	string input = "";
};