#include "leaderboard.h"
using namespace std;

Leaderboard::Leaderboard(int columnNum, int rowNum) {
	// set width and height (32 pixels per tile, +100 for buttons, divided by 2)
	this->width = (columnNum * 16);
	this->height = (rowNum * 16) + 50;

	// load font from file
	if (!font.loadFromFile("files/font.ttf")) { cout << "Unable to load font.ttf" << endl; }

	// set title text
	titleText.setFont(font);
	titleText.setString("LEADERBOARD");
	titleText.setCharacterSize(20);
	titleText.setFillColor(sf::Color::White);
	titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	// set origin in the center
	sf::FloatRect textBoundRect = titleText.getLocalBounds();
	titleText.setOrigin(textBoundRect.width / 2.0f, textBoundRect.height / 2.0f);
	// set position to center of window
	titleText.setPosition(width / 2.0f, height / 2.0f - 120);

	// set scores text
	scoresText.setFont(font);
	scoresText.setString(scoreboard);
	scoresText.setCharacterSize(18);
	scoresText.setFillColor(sf::Color::White);
	scoresText.setStyle(sf::Text::Bold);
	// set origin in the center
	textBoundRect = scoresText.getLocalBounds();
	scoresText.setOrigin(textBoundRect.width / 2.0f, textBoundRect.height / 2.0f);
	// set position to center of window
	scoresText.setPosition(width / 2.0f, height / 2.0f + 20);

	// read scores and populate map
	readFromFile();
	//set scoreboard text
	setScoreboard();
}

void Leaderboard::createWindow() {
	// create window with correct width and height
	leaderboardWindow.create(sf::VideoMode(width, height), "Minesweeper");
	// change color of background
	leaderboardWindow.sf::RenderTarget::clear(sf::Color::Blue);
}

void Leaderboard::addScore(string name, double time) {
	// convert time (double) to string with formating
	string timeString;
	int minutes = time / 60;
	int seconds = time - (minutes * 60);
	if (minutes < 10) { timeString += '0';}
	timeString += to_string(minutes) + ':';
	if (seconds < 10) { timeString += '0'; }
	timeString += to_string(seconds);
	cout << timeString << endl;

	// pop the previous score that had an astrisk
	map<string, vector<string>>::iterator iter = scores.begin();
	for (; iter != scores.end(); iter++) {
		// iterate through the names in the vector at each map position
		for (int i = 0; i < iter->second.size(); i++) {
			// if the name has an astrisk at the end, pop it
			if (iter->second.at(i).at(iter->second.at(i).size() - 1) == '*') {
				iter->second.at(i).pop_back();
				break;
			}
		}
	}

	// add the new score to the map
	// if the time already exists, add the name to its vector
	if (scores.find(timeString) != scores.end()) {
		scores.at(timeString).push_back(name + '*');
	}
	else {
		vector <string> nameVector{ (name + '*')};
		scores.emplace(timeString, nameVector);
	}

	// map automatically sorted by time least to most
	// if more than 5 scores in map, discard last element (pop the greatest time)
	int count = 0;
	iter = scores.begin();
	for (; iter != scores.end(); iter++) {
		for (int i = 0; i < iter->second.size(); i++) {
			if (count >= 5) {
				cout << iter->second.at(i) << endl;
				// if the greatest time has only one name in it, erase that entire map entry
				if (iter->second.size() == 1) {
					scores.erase(iter);
					cout << "entire entry erased" << endl;
				}
				// else, pop the last time in the vector
				else {
					iter->second.pop_back();
					cout << "pop back" << endl;
				}
				cout << "success: pop last score" << endl;
				count++;
				break;
			}
			count++;
			cout << count << endl;
		}
		if (count > 5) { break; }
	}
	// update scoreboard text
	cout << "starting setscoreboard function " << endl;
	setScoreboard();
}

void Leaderboard::setScoreboard() {
	// create the string that will be displayed on the leaderboard (based on scores stored)
	// first clear the string
	scoreboard = "";
	// iterate through scores and add to string with formating
	int count = 1;
	map<string, vector <string>>::iterator iter = scores.begin();
	for (; iter != scores.end(); iter++) {
		for (int i = 0; i < iter->second.size(); i++) {
			// place each name and time in the string
			scoreboard += to_string(count) + ".\t";
			count++;
			scoreboard += iter->first + "\t";
			scoreboard += iter->second.at(i);
			if (count < 6) { scoreboard += "\n\n"; }
		}
	}
	cout << "Success: set scoreboard string" << endl;
	// set the text's string
	scoresText.setString(scoreboard);
	cout << scoreboard << endl;
	// set origin of scoresText in the center again
	sf::FloatRect textBoundRect = scoresText.getLocalBounds();
	scoresText.setOrigin(textBoundRect.width / 2.0f, textBoundRect.height / 2.0f);
	cout << "success: set text string" << endl;
}

void Leaderboard::drawText() {
	leaderboardWindow.draw(titleText);
	leaderboardWindow.draw(scoresText);
}

void Leaderboard::readFromFile() {
	//create fstream object to read leaderboard.txt file; print error message if not opened
	fstream leaderboardIn("files/leaderboard.txt", ios_base::in);
	if (!leaderboardIn.is_open()) { cout << "File \"leaderboard.txt\" not opened!" << endl; }
	string singleLine;
	while(getline(leaderboardIn, singleLine)) {
		// turn line into stream
		stringstream line(singleLine);
		// read time
		string time;
		getline(line, time, ',');
		// read name
		string name;
		getline(line, name);
		cout << name;
		// emplace in map
		if (scores.find(time) != scores.end()) {
			scores.at(time).push_back(name);
		}
		else {
			vector <string> names{ name };
			scores.emplace(time, names);
		}
	}
}

void Leaderboard::writeToFile() {
	//create fstream object to read board_config.cfg file; print error message if not opened
	fstream leaderboardOut("files/leaderboard.txt", ios_base::out);
	if (!leaderboardOut.is_open()) { cout << "File \"leaderboard.txt\" not opened!" << endl; }
	// iterate through scores and write each one to the file
	int count = 1;
	map<string, vector <string>>::iterator iter = scores.begin();
	for (; iter != scores.end(); iter++) {
		for (int i = 0; i < iter->second.size(); i++) {
			// write the time to the file
			leaderboardOut << (iter->first) << ',';
			// write the name to the file
			leaderboardOut << (iter->second.at(i));
			count++;
			// add a newline if it's not the last line
			if (count < 6) { leaderboardOut << '\n'; }
		}
	}
}