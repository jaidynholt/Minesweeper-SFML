#include "texture.h"
using namespace std;

TextureManager::TextureManager(){
    flagTexture.loadFromFile("files/images/flag.png");
    addTexture("flag", &flagTexture);

    mineTexture.loadFromFile("files/images/mine.png");
    addTexture("mine", &mineTexture);

    oneTexture.loadFromFile("files/images/number_1.png");
    addTexture("1", &oneTexture);

    twoTexture.loadFromFile("files/images/number_2.png");
    addTexture("2", &twoTexture);

    threeTexture.loadFromFile("files/images/number_3.png");
    addTexture("3", &threeTexture);

    fourTexture.loadFromFile("files/images/number_4.png");
    addTexture("4", &threeTexture);

    fiveTexture.loadFromFile("files/images/number_5.png");
    addTexture("5", &fiveTexture);

    sixTexture.loadFromFile("files/images/number_6.png");
    addTexture("6", &sixTexture);

    sevenTexture.loadFromFile("files/images/number_7.png");
    addTexture("7", &sevenTexture);

    eightTexture.loadFromFile("files/images/number_8.png");
    addTexture("8", &eightTexture);

    hiddenTexture.loadFromFile("files/images/tile_hidden.png");
    addTexture("tileHidden", &hiddenTexture);

    revealedTexture.loadFromFile("files/images/tile_revealed.png");
    addTexture("tileRevealed", &revealedTexture);

    debugTexture.loadFromFile("files/images/debug.png");
    addTexture("debug", &debugTexture);

    digitsTexture.loadFromFile("files/images/digits.png");
    addTexture("digits", &digitsTexture);

    faceHappyTexture.loadFromFile("files/images/face_happy.png");
    addTexture("faceHappy", &faceHappyTexture);

    faceLoseTexture.loadFromFile("files/images/face_lose.png");
    addTexture("faceLose", &faceLoseTexture);

    faceWinTexture.loadFromFile("files/images/face_win.png");
    addTexture("faceWin", &faceWinTexture);

    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    addTexture("leaderboard", &leaderboardTexture);

    pauseTexture.loadFromFile("files/images/pause.png");
    addTexture("pause", &pauseTexture);

    playTexture.loadFromFile("files/images/play.png");
    addTexture("play", &playTexture);
}

void TextureManager::addTexture(string name, sf::Texture* texturePtr) {
    textures.emplace(name, texturePtr);
}

sf::Texture* TextureManager::getTexture(string name) {
    return textures.at(name);
}