#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "welcome.h"
#include "leaderboard.h"
#include "game.h"
#include "board.h"
#include "tile.h"
#include "texture.h"
using namespace std;

int main()
{
    // create welcome window object
    Welcome welcome;

    // draw and display the window the first time
    welcome.drawText();
    welcome.welcomeWindow.display();

    // handles events while welcome window is open
    while (welcome.welcomeWindow.isOpen())
    {
        sf::Event event;
        while (welcome.welcomeWindow.pollEvent(event))
        {
            // close button event (if closed, do not open game window)
            if (event.type == sf::Event::Closed) {
                welcome.welcomeWindow.close();
                return 0;
            }
            // key pressed event
            if (event.type == sf::Event::KeyPressed) {
                // if enter key is pressed
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                    // if the input string is not empty
                    if (welcome.getName().size() != 0) {
                        welcome.welcomeWindow.close();
                    }
                }
            }
            // text entered event
            if (event.type == sf::Event::TextEntered) {
                // check if character is in standard ascii range
                if (event.text.unicode < 128) {
                    // cast to a char and set inputText String
                    welcome.setInput(static_cast<char>(event.text.unicode));
                }
            }
            else {
                // go back through loop without doing the 3 steps below
                break;
            }
            // three steps that follow handling of events:
            // 1) clear the window
            welcome.welcomeWindow.sf::RenderTarget::clear(sf::Color::Blue);
            // 2) draw anything inside the window
            welcome.drawText();
            // 3) display anything drawn in the window
            welcome.welcomeWindow.display();
        }
    }

    // Create game object
    Game game(welcome.columnNum, welcome.rowNum, welcome.mineNum);

    // draw and display the window the first time
    game.gameWindow.sf::RenderTarget::clear(sf::Color::White);
    game.drawBoard();
    game.drawUI();
    game.drawMineCount();
    game.gameWindow.display();

    // handles events while game window is open
    while (game.gameWindow.isOpen()) {
        sf::Event event;
        while (game.gameWindow.pollEvent(event))
        {
            // close button event
            if (event.type == sf::Event::Closed) {
                game.gameWindow.close();
            }
            // mouse button pressed event
            if (event.type == sf::Event::MouseButtonPressed) {
                // get position relative to window
                sf::Vector2i coordinate = sf::Mouse::getPosition(game.gameWindow);
                cout << coordinate.x << ", " << coordinate.y << endl;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    // check what was pressed
                    // if tile pressed, reveal it
                    game.revealTile(coordinate);
                    // if button pressed, do that functionality
                    game.buttonPressed(coordinate);
                    // if leaderboard pressed, open leaderboard window
                    if (game.isLeaderboadButtonPressed(coordinate)) {
                        // Pause game and redraw window to be paused if game is not over
                        if (!game.IsGameOver()) {
                            game.pausePlayTimer(1);
                            game.setPauseMode();
                            game.gameWindow.sf::RenderTarget::clear(sf::Color::White);
                            game.drawBoard();
                            game.drawUI();
                            game.drawMineCount();
                            game.drawTimer();
                        }
                        game.gameWindow.display();
                        // create leaderboard window
                        game.createLeaderboardWindow();
                        // draw and display it once (since it doesn't need to be updated here)
                        game.leaderboardWindowEventLoop();
                    }
                    // check if the game is won
                    if (game.checkWin() && game.IsLost()) {
                        // sets game over and game won
                        game.setWinMode();
                        game.gameWindow.sf::RenderTarget::clear(sf::Color::White);
                        game.drawBoard();
                        game.drawUI();
                        game.drawMineCount();
                        game.drawTimer();
                        game.gameWindow.display();
                        // create leaderboard window
                        game.createLeaderboardWindow();
                        // update the leaderboard to include this latest time
                        game.updateLeaderboard(welcome.getName(), game.getTotalTime());
                        // draw and display it once (since it doesn't need to be updated here)
                        game.leaderboardWindowEventLoop();
                        // do not open leaderboard window again until game is reset
                    }
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    // add/remove flag if right mouse pressed
                    game.placeFlag(coordinate);
                }
            }
        }
        // update timer
        game.setTimer();
        // three steps that follow handling of events:
        // 1) clear the window
        game.gameWindow.sf::RenderTarget::clear(sf::Color::White);
        // 2) draw anything inside the window
        game.drawBoard();
        game.drawUI();
        game.drawMineCount();
        game.drawTimer();
        // 3) display anything drawn in the window
        game.gameWindow.display();
    }

    return 0;
}