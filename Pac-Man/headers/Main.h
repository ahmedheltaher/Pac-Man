#ifndef MAIN_H
#define MAIN_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./headers/Level.h"
#include "./headers/SoundManager.h"
#include "./headers/Storage.h"
#include "./headers/FPS.h"
#include "./headers/Menu.h"


#define VIDEOMODE  sf::VideoMode(1500, 1024)
std::string TITLE = "Pac-Man";

sf::Image icon;

void setupLogo(sf::RenderWindow& window) {
	icon.loadFromFile("./textures/resized_logo.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
};


void switchWindows(sf::Mutex& mutex, sf::RenderWindow& window, sf::Thread& thread) {
	mutex.lock();
	window.close();
	thread.launch();
	mutex.unlock();
};

struct PlayerName {
	std::string name;
	int length;
};

PlayerName playerName = { "", 0 };

Storage storage;
SoundManager soundManager("music", "sfx");
Level level(2);
bool gamePaused = false;

void mainMenu();
void gameLoop();
void instructions();
void leaderBoard();
void credits();
void enterYourName();
void win();
void lose();

sf::Mutex mainMenuMutex, gameMutex,
		  instructionsMutex, leaderBoardMutex,
		  creditsMutex, enterYourNameMutex, winMutex, loseMutex;

#endif // !MAIN