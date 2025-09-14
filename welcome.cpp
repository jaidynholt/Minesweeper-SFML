#include "welcome.h"
using namespace std;

Welcome::Welcome() {
	//create fstream object to read board_config.cfg file; print error message if not opened
	fstream boardConfigIn("files/board_config.cfg", ios_base::in);
	if (!boardConfigIn.is_open()) { cout << "File \"board_config.cfg\" not opened!" << endl; }

	// read columnNum:
	// create a temp string variable; read in line from file; convert to int and store in columnNum
	string temp;
	getline(boardConfigIn, temp);
	columnNum = stoi(temp);

	// read rowNum:
	// create a temp string variable; read in line from file; convert to int and store in columnNum
	getline(boardConfigIn, temp);
	rowNum = stoi(temp);

	// read mineNum:
	getline(boardConfigIn, temp);
	mineNum = stoi(temp);
	
	// set width and height (32 pixels per tile, +100 for buttons)
	this->width = columnNum * 32;
	this->height = rowNum * 32 + 100;

	// create window with correct width and height
	welcomeWindow.create(sf::VideoMode(width, height), "Minesweeper");
	// change color of background
	welcomeWindow.sf::RenderTarget::clear(sf::Color::Blue);

	// load font from file
	if (!font.loadFromFile("files/font.ttf")) { cout << "Unable to load font.ttf" << endl; }

	// set welcome text
	welcomeText.setFont(font);
	welcomeText.setString("WELCOME TO MINESWEEPER!");
	welcomeText.setCharacterSize(24);
	welcomeText.setFillColor(sf::Color::White);
	welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	// set origin in the center
	sf::FloatRect textBoundRect = welcomeText.getLocalBounds();
	welcomeText.setOrigin(textBoundRect.width / 2.0f, textBoundRect.height / 2.0f);
	// set position to center of window
	welcomeText.setPosition(width / 2.0f, height / 2.0f - 150);

	// set input prompt text
	inputPromptText.setFont(font);
	inputPromptText.setString("Enter your name:");
	inputPromptText.setCharacterSize(20);
	inputPromptText.setFillColor(sf::Color::White);
	inputPromptText.setStyle(sf::Text::Bold);
	// set origin in the center
	textBoundRect = inputPromptText.getLocalBounds();
	inputPromptText.setOrigin(textBoundRect.width / 2.0f, textBoundRect.height / 2.0f);
	// set position to center of window
	inputPromptText.setPosition(width / 2.0f, height / 2.0f - 75);

	// set input text
	inputText.setFont(font);
	inputText.setString("|");
	inputText.setCharacterSize(18);
	inputText.setFillColor(sf::Color::Yellow);
	inputText.setStyle(sf::Text::Bold);
	// set origin in the center
	textBoundRect = inputText.getLocalBounds();
	inputText.setOrigin(textBoundRect.width / 2.0f, textBoundRect.height / 2.0f);
	// set position to center of window
	inputText.setPosition(width / 2.0f, height / 2.0f - 45);
}

void Welcome::setInput(char inputLetter) {
	// handles letters: add letter
	if (isalpha(inputLetter) || inputLetter == ' ') {
		// if string is empty: capitalize first letter
		if (input.size() == 0) {
			input += toupper(inputLetter);
		}
		// if string is not empty: lowercase letters 
		else if (input.size() <= 10) {
			input += tolower(inputLetter);
		}
	}
	// handles backspace: take away a letter from input
	else if (inputLetter == '\b' && input.size() != 0) {
		input.pop_back();
	}
	inputText.setString(input + '|');
	// set origin of inputText in the center
	sf::FloatRect textBoundRect = inputText.getLocalBounds();
	inputText.setOrigin(textBoundRect.width / 2.0f, textBoundRect.height / 2.0f);
}

void Welcome::drawText() {
	welcomeWindow.draw(welcomeText);
	welcomeWindow.draw(inputPromptText);
	welcomeWindow.draw(inputText);
}

string Welcome::getName() {
	return input;
}