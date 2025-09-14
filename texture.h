#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#pragma once
using namespace std;

class TextureManager {
public:
    TextureManager();
    void addTexture(string name, sf::Texture* texturePtr);
	sf::Texture* getTexture(string name);
	map<string, sf::Texture*> textures;
private:
    sf::Texture flagTexture;
    sf::Texture mineTexture;
    sf::Texture oneTexture;
    sf::Texture twoTexture;
    sf::Texture threeTexture;
    sf::Texture fourTexture;
    sf::Texture fiveTexture;
    sf::Texture sixTexture;
    sf::Texture sevenTexture;
    sf::Texture eightTexture;
    sf::Texture hiddenTexture;
    sf::Texture revealedTexture;
    sf::Texture debugTexture;
    sf::Texture digitsTexture;
    sf::Texture faceHappyTexture;
    sf::Texture faceLoseTexture;
    sf::Texture faceWinTexture;
    sf::Texture leaderboardTexture;
    sf::Texture pauseTexture;
    sf::Texture playTexture;
};