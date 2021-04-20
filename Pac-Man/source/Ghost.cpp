#include "../headers/Ghost.h"
#include <iostream>

// Constructor
Ghost::Ghost(float x = 0, float y = 0, Name name = Name::Virtical) :Entity(x, y, "ghost"), moveType(name) {
	setSpeed(200);
	switch (moveType) {
	case Name::Virtical:
		loadTexture("yellow_ghost.png");
		setTextureRect(sf::IntRect(3, 3, 14, 14));
		break;
	case Name::Horizontal:
		setTextureRect(sf::IntRect(3, 63, 14, 14));
		loadTexture("red_ghost.png");
		break;
	}
};

// Destructor
Ghost::~Ghost() {};

void Ghost::changeGhostDirection() {
    switch (direction) {
    case Direction::UP:
        setDirection(Direction::DOWN);
		setTextureRect(sf::IntRect(3, 23, 14, 14));
        break;
    case Direction::DOWN:
        setDirection(Direction::UP);
		setTextureRect(sf::IntRect(3, 3, 14, 14));
        break;
    case Direction::LEFT:
        setDirection(Direction::RIGHT);
		setTextureRect(sf::IntRect(3, 63, 14, 14));
        break;
    case Direction::RIGHT:
        setDirection(Direction::LEFT);
		setTextureRect(sf::IntRect(3, 43, 14, 14));
        break;
    case Direction::NONE:
		switch (moveType) {
		case Name::Virtical:
			setDirection(Direction::UP);
			break;
		case Name::Horizontal:
			setDirection(Direction::RIGHT);
			break;
		}
        break;
    }
};


void Ghost::update(float deltaTime, std::vector<sf::RectangleShape> map) {
	switch (moveType) {
	case Name::Virtical:
		switch (direction) {
		case Direction::UP:
			if (!move(0.0, -speed * deltaTime, map)) changeGhostDirection();
			break;
		case Direction::DOWN:
			if (!move(0.0, speed * deltaTime, map)) changeGhostDirection();
			break;
		case Direction::NONE:
			changeGhostDirection();
			break;
		}
		break;
	case Name::Horizontal:
		switch (direction) {
		case Direction::RIGHT:
			if (!move(speed * deltaTime, 0.0, map)) changeGhostDirection();
			break;
		case Direction::LEFT:
			if (!move(-speed * deltaTime, 0.0, map)) changeGhostDirection();
			break;
		case Direction::NONE:
			changeGhostDirection();
			break;
		}
		break;
	}
};

