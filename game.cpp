#include "game.h"
using namespace std;

Game::Game(int columnNum, int rowNum, int mineNum) : Board(columnNum, rowNum, mineNum), Leaderboard(columnNum, rowNum){
	
	// set width and height (32 pixels per tile, +100 for buttons)
	this->width = columnNum * 32;
	this->height = rowNum * 32 + 100;

	// set mines left to be mine count to start
	minesLeft = mineNum;

	// create window with correct width and height
	gameWindow.create(sf::VideoMode(width, height), "Minesweeper");
	Board::CreateBoard();

	// set position of UI buttons
	debugButton.setPosition((Board::getColumnNum() * 32) - 304, (Board::getRowNum() + 0.5f) * 32);
	leaderboardButton.setPosition((Board::getColumnNum() * 32) - 176, 32 * (Board::getRowNum() + 0.5f));
	pauseButton.setPosition((Board::getColumnNum() * 32) - 240, 32 * (Board::getRowNum() + 0.5f));
	faceButton.setPosition(((Board::getColumnNum() / 2.0) * 32) - 32, 32 * (Board::getRowNum() + 0.5f));

	// create and set position of mine count sprites
	sf::Sprite mineCountNegative;
	mineCountNegative.setPosition(12, 32 * (Board::getRowNum() + 0.5f) + 16);
	mineCountSprites.push_back(mineCountNegative);
	sf::Sprite mineCount1;
	mineCount1.setPosition(33, 32 * (Board::getRowNum() + 0.5f) + 16);
	mineCountSprites.push_back(mineCount1);
	sf::Sprite mineCount2;
	mineCount2.setPosition(54, 32 * (Board::getRowNum() + 0.5f) + 16);
	mineCountSprites.push_back(mineCount2);
	sf::Sprite mineCount3;
	mineCount3.setPosition(75, 32 * (Board::getRowNum() + 0.5f) + 16);
	mineCountSprites.push_back(mineCount3);

	// create and set position of timer sprites
	sf::Sprite timerMinute1;
	timerMinute1.setPosition((Board::getColumnNum() * 32) - 97, 32 * (Board::getRowNum() + 0.5f) + 16);
	timerSprites.push_back(timerMinute1);
	sf::Sprite timerMinute2;
	timerMinute2.setPosition((Board::getColumnNum() * 32) - 97 + 21, 32 * (Board::getRowNum() + 0.5f) + 16);
	timerSprites.push_back(timerMinute2);
	sf::Sprite timerSecond1;
	timerSecond1.setPosition((Board::getColumnNum() * 32) - 54, 32 * (Board::getRowNum() + 0.5f) + 16);
	timerSprites.push_back(timerSecond1);
	sf::Sprite timerSecond2;
	timerSecond2.setPosition((Board::getColumnNum() * 32) - 54 + 21, 32 * (Board::getRowNum() + 0.5f) + 16);
	timerSprites.push_back(timerSecond2);

	// start the timer (initialize the start time and first break point to be when the game is constructed)
	startTime = chrono::steady_clock::now();
	breakPointTime = chrono::steady_clock::now();
	elapsedTimeUntilBreakpoint = breakPointTime - startTime;
	elapsedTimeSinceBreakpoint = chrono::steady_clock::now() - breakPointTime;
	totalTimeDuration = elapsedTimeUntilBreakpoint + elapsedTimeSinceBreakpoint;
}

float Game::getTotalTime() {
	return totalTimeDuration.count();
}

void Game::setTimer() {
	// update the timer (if not paused or game over)
	if (!isGameOver && !isPaused) {
		elapsedTimeSinceBreakpoint = chrono::steady_clock::now() - breakPointTime;
		totalTimeDuration = elapsedTimeUntilBreakpoint + elapsedTimeSinceBreakpoint;
	}
}

void Game::pausePlayTimer(int option) {
	// stop timer (set new breakpoint time)
	breakPointTime = chrono::steady_clock::now();
	// if pressed pause, set new elapsedTimeUntilBreakpoint
	if (!isPaused) {
		elapsedTimeUntilBreakpoint = elapsedTimeUntilBreakpoint + elapsedTimeSinceBreakpoint;
	}
	if (option == 0) {
		// if this argument is not given, default switches pause mode on/off
		isPaused = !isPaused;
	}
	else {
		// if this argument is given not zero, pauses game regardless of isPaused status
		isPaused = true;
	}
}

void Game::resetTimer() {
	// reset timer
	startTime = chrono::steady_clock::now();
	breakPointTime = chrono::steady_clock::now();
	elapsedTimeUntilBreakpoint = breakPointTime - startTime;
	elapsedTimeSinceBreakpoint = chrono::steady_clock::now() - breakPointTime;
	totalTimeDuration = elapsedTimeUntilBreakpoint + elapsedTimeSinceBreakpoint;
	isPaused = false;
}

bool Game::isDebugButtonPressed(sf::Vector2i coordinate) {
	// if the game is not over (can't do anything but reset and leaderboard if game is over)
	if (!isGameOver) {
		// if coordinate within the debug button bounds
		if (debugButton.getGlobalBounds().contains(sf::Vector2f(coordinate))) { return true; }
	}
	return false;
}

bool Game::isPauseButtonPressed(sf::Vector2i coordinate) {
	// if the game is not over (can't do anything but reset and leaderboard if game is over)
	if (!isGameOver) {
		// if coordinate within the pause button bounds
		if (pauseButton.getGlobalBounds().contains(sf::Vector2f(coordinate))) { return true; }
	}
	return false;
}

bool Game::isFaceButtonPressed(sf::Vector2i coordinate) {
	// if coordinate within the face button bounds
	if (faceButton.getGlobalBounds().contains(sf::Vector2f(coordinate))) {return true;}
	return false;
}

bool Game::isLeaderboadButtonPressed(sf::Vector2i coordinate) {
	// if coordinate within the leaderboard button bounds
	// if coordinate within the face button bounds
	if (leaderboardButton.getGlobalBounds().contains(sf::Vector2f(coordinate))) {return true;}
	return false;
}

void Game::buttonPressed(sf::Vector2i coordinate) {
	if (isDebugButtonPressed(coordinate)) {
		setDebugMode();
	}
	if (isPauseButtonPressed(coordinate)) {
		pausePlayTimer();
		setPauseMode();
	}
	if (isFaceButtonPressed(coordinate)) {
		resetBoard();
	}
}

void Game::setPauseMode() {
	// makes board in pause mode
	Board::PauseMode();
}

void Game::setDebugMode() {
		// change debug mode on/off
		Board::DebugMode();
}

void Game::resetBoard() {
	// recreate board
	Board::RestartBoard();
	// reset GameOver bool
	isGameOver = false;
	// reset gameWon bool
	isLost = true;
	// reset minesLeft to original mineNum
	minesLeft = Board::getMineNum();
	// reset timer
	resetTimer();
}

void Game::setWinMode() {
	isGameOver = true;
	isLost = false;
	pausePlayTimer(1);
	Board::WinMode();
	minesLeft = 0;
}

void Game::revealTile(sf::Vector2i coordinate) {
	// if the game is not over and not paused
	if (!isPaused && !isGameOver) {
		// get tile position in vector (divide by 32 pixels)
		// flip that tile
		int column = coordinate.x / 32.0f;
		int row = coordinate.y / 32.0f;
		// reveal this tile if the coordinates are valid and the tile is not flagged
		if ((column < Board::getColumnNum()) && (row < Board::getRowNum()) && !Board::getTile(column, row)->IsFlag()) {
			Board::getTile(column, row)->Reveal();
			// if mine is revealed, trigger game end
			if (Board::getTile(column, row)->IsMine()) {
				// set last breakpoint (for the end of the game)
				breakPointTime = chrono::steady_clock::now();
				elapsedTimeUntilBreakpoint = elapsedTimeUntilBreakpoint + elapsedTimeSinceBreakpoint;
				// reveal all mines
				Board::LoseMode();
				isGameOver = true;
				isLost = true;
			}
		}
	}
}

void Game::placeFlag(sf::Vector2i coordinate) {
	// if the game is not over and not paused
	if (!isPaused && !isGameOver) {
		// get tile position in vector (divide by 32 pixels)
		int column = coordinate.x / 32.0f;
		int row = coordinate.y / 32.0f;
		if ((column < Board::getColumnNum()) && (row < Board::getRowNum())) {
			// place flag on/off this tile
			Board::getTile(column, row)->PlaceFlag();
			if (Board::getTile(column, row)->IsFlag()) { minesLeft--; }
			else { minesLeft++; }
		}
	}
}

void Game::drawBoard() {
	for (int i = 0; i < Board::getRowNum(); i++) {
		for (int j = 0; j < Board::getColumnNum(); j++) {
			// set tile's sprite's texture, and draw it to the window
			Board::getTile(j, i)->spriteBG.setTexture(*(TextureManager::getTexture(Board::getTile(j, i)->getTextureName().at(0))));
			gameWindow.draw(Board::getTile(j, i)->spriteBG);
			// if this tile has more than one texture, set it and draw it
			if (Board::getTile(j, i)->getTextureName().size() > 1) {
				Board::getTile(j, i)->spriteTopImage.setTexture(*(TextureManager::getTexture(Board::getTile(j, i)->getTextureName().at(1))));
				gameWindow.draw(Board::getTile(j, i)->spriteTopImage);
			}	
		}
	}
}

void Game::drawUI() {
	// set button texture
	debugButton.setTexture(*(TextureManager::getTexture("debug")));
	leaderboardButton.setTexture(*(TextureManager::getTexture("leaderboard")));
	if (isPaused) { pauseButton.setTexture(*(TextureManager::getTexture("play"))); }
	else { pauseButton.setTexture(*(TextureManager::getTexture("pause"))); }
	if (!isGameOver) { faceButton.setTexture(*(TextureManager::getTexture("faceHappy"))); }
	else {
		if (isLost) { faceButton.setTexture(*(TextureManager::getTexture("faceLose"))); }
		else { faceButton.setTexture(*(TextureManager::getTexture("faceWin"))); }
	}

	// draw buttons
	gameWindow.draw(debugButton);
	gameWindow.draw(leaderboardButton);
	gameWindow.draw(pauseButton);
	gameWindow.draw(faceButton);
}

void Game::drawMineCount() {
	// create temporary variable equal to absolute value of minesLeft (positive)
	int minesLeftTemp = abs(minesLeft);
	// for sprites in mineCount, assign textures depending on minesLeft number
	int count = 3;
	while (count > 0){
		mineCountSprites.at(count).setTextureRect(sf::IntRect((minesLeftTemp % 10) * 21, 0, 21, 32));
		mineCountSprites.at(count).setTexture(*(TextureManager::getTexture("digits")));
		minesLeftTemp /= 10;
		count--;
	}
	// add negative sprite if minesLeft is negative
	if (minesLeft < 0) {
		mineCountSprites.at(0).setTextureRect(sf::IntRect(210, 0, 21, 32));
		mineCountSprites.at(0).setTexture(*(TextureManager::getTexture("digits")));
		gameWindow.draw(mineCountSprites.at(0));
	}
	// draw the mine counts
	gameWindow.draw(mineCountSprites.at(1));
	gameWindow.draw(mineCountSprites.at(2));
	gameWindow.draw(mineCountSprites.at(3));
}

void Game::drawTimer() {
	// calculate minutes vs seconds
	int minutes = totalTimeDuration.count() / 60;
	int seconds = totalTimeDuration.count() - (minutes * 60);

	// for sprites in timerSprites, assign textures depending on minutes and seconds
	timerSprites.at(0).setTextureRect(sf::IntRect((minutes / 10) * 21, 0, 21, 32));
	timerSprites.at(0).setTexture(*(TextureManager::getTexture("digits")));

	timerSprites.at(1).setTextureRect(sf::IntRect((minutes % 10) * 21, 0, 21, 32));
	timerSprites.at(1).setTexture(*(TextureManager::getTexture("digits")));

	timerSprites.at(2).setTextureRect(sf::IntRect((seconds / 10) * 21, 0, 21, 32));
	timerSprites.at(2).setTexture(*(TextureManager::getTexture("digits")));

	timerSprites.at(3).setTextureRect(sf::IntRect((seconds % 10) * 21, 0, 21, 32));
	timerSprites.at(3).setTexture(*(TextureManager::getTexture("digits")));

	// draw the mine counts
	gameWindow.draw(timerSprites.at(0));
	gameWindow.draw(timerSprites.at(1));
	gameWindow.draw(timerSprites.at(2));
	gameWindow.draw(timerSprites.at(3));
}

bool Game::checkWin() {
	// check each tile
	for (int i = 0; i < Board::getRowNum(); i++) {
		for (int j = 0; j < Board::getColumnNum(); j++) {
			if (!(Board::getTile(j, i)->IsMine()) && (Board::getTile(j, i)->IsHidden())) {
				// if the tile is not a mine and is still hidden
				return false;
			}
		}
	}
	return true;
}

bool Game::IsGameOver() {
	return isGameOver;
}

bool Game::IsLost() {
	return isLost;
}

void Game::createLeaderboardWindow() {
	// separate function to create the window and display it the first time
	Leaderboard::createWindow();
}

void Game::leaderboardWindowEventLoop() {
	// draw and display window once (since it doesn't need to be updated)
	Leaderboard::drawText();
	Leaderboard::leaderboardWindow.display();
	// handles events while game window is open
	while (Leaderboard::leaderboardWindow.isOpen()) {
		sf::Event event;
		while (Leaderboard::leaderboardWindow.pollEvent(event))
		{
			// close button event
			if (event.type == sf::Event::Closed) {
				// close leaderboardWindow and resume game
				Leaderboard::leaderboardWindow.close();
				if (!isGameOver) {
					pausePlayTimer();
					setPauseMode();
				}
			}
		}
	}
}

void Game::updateLeaderboard(string name, double time) {
	Leaderboard::addScore(name, time);
	Leaderboard::writeToFile();
}