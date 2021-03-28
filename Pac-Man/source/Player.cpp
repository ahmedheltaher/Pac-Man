#include "../headers/Player.h"

// Constructor
Player::Player(float x = 0, float y = 0) :Entity(x, y, "pacman"), lives(3) {
	setSpeed(300);
	loadTexture("pacman.png");
	setTextureRect(sf::IntRect(3, 3, 14, 14));
};

// Destructor
Player::~Player() {};

// Player Event Hndler
void Player::handleKeyboardEvent(sf::Event event) {
	switch (event.key.code) {
	case sf::Keyboard::W:
		setDirection(Direction::UP);
		break;
	case sf::Keyboard::D:
		setDirection(Direction::RIGHT);
		break;
	case sf::Keyboard::S:
		setDirection(Direction::DOWN);
		break;
	case sf::Keyboard::A:
		setDirection(Direction::LEFT);
		break;
	}
};

int Player::getLives() {
	return lives;
};

void Player::decrementLives() {
	lives--;
};