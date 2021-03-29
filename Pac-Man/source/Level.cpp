#include "../headers/Level.h"
#include <string>
#include <iostream>
#include <dos.h>

// Constructor
Level::Level(int levelNumber) :map("level_" + std::to_string(levelNumber)), pacman(map.getPlayerPosition().x, map.getPlayerPosition().y), score(0), soundManager("music", "sfx") {
    ghosts = map.getGhosts();
    for (unsigned int i = 0; i < ghosts.size(); i++) {
        if (ghosts[i].moveType == Name::Horizontal) ghosts[i].loadTexture("red_ghost.png");
        else ghosts[i].loadTexture("yellow_ghost.png");
    }
};

// Destructor
Level::~Level() {};

void Level::update(float deltaTime) {
    Position pos = map.getPlayerPosition();
    pacman.update(deltaTime, readyGridMap[pacman.getQuarter()]);
    for (unsigned int i = 0; i < ghosts.size(); i++) ghosts[i].update(deltaTime, readyGridMap[ghosts[i].getQuarter()]);
    int coinColliedeWithIndex = chekCollisionWithCoins();
    if (coinColliedeWithIndex != -1) {
        score++;
        readyCoins.erase(readyCoins.begin() + coinColliedeWithIndex);
        coins[coinColliedeWithIndex].~Tile();
        soundManager.playSFX("eat");
    }
    if (chekCollisionWithEnemies() && pacman.getLives() > 0) {
        soundManager.playSFX("die");
        pacman.setPosition(pos.x, pos.y);
        pacman.setDirection(Direction::NONE);
        pacman.setTextureRect(sf::IntRect(3, 3, 14, 14));
        pacman.decrementLives();
    }
}

void Level::draw(sf::RenderWindow *window) {
    for (unsigned int i = 0; i < readyMap.size(); i++) window->draw(readyMap[i]);
    for (unsigned int i = 0; i < readyCoins.size(); i++) window->draw(readyCoins[i]);
    for (unsigned int i = 0; i < ghosts.size(); i++) window->draw(ghosts[i].getSprite());
    window->draw(pacman.getSprite());
};

void Level::handleEvents(sf::Event event) {
    pacman.handleKeyboardEvent(event);
};

bool Level::chekCollisionWithEnemies() {
    for (unsigned int i = 0; i < ghosts.size(); i++) if (pacman.getSprite().getGlobalBounds().intersects(ghosts[i].getSprite().getGlobalBounds())) return true;
    return false;
}

int Level::chekCollisionWithCoins() {
    for (unsigned int i = 0; i < readyCoins.size(); i++) if (pacman.getSprite().getGlobalBounds().intersects(readyCoins[i].getGlobalBounds())) return i;
    return -1;
}

int Level::getScore() {
    return score;
}

void Level::pause() {
    pacman.setDirection(Direction::NONE);
    for (unsigned int i = 0; i < ghosts.size(); i++) ghosts[i].setDirection(Direction::NONE);
}

bool Level::gotAllCoins() {
    return readyCoins.size() == 0;
};

bool Level::pacmanDied() {
    return chekCollisionWithEnemies() && !(pacman.getLives() > 0);
};