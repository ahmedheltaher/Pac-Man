#include "../headers/Ghost.h"
#include "../headers/Map.h"
#include <iostream>

// Constructor
Ghost::Ghost(Name name, float x = 0, float y = 0) :Entity(x, y, "ghost"), moveType(name) {
	setSpeed(100);
};

// Destructor
Ghost::~Ghost() {};

Direction generateRandom() {
	Direction randomNumber = static_cast<Direction>(std::rand() % 4);
	return randomNumber;
}

void Ghost::changeGhostDirection() {
    switch (direction) {
    case Direction::UP:
        setDirection(Direction::DOWN);
        break;
    case Direction::DOWN:
        setDirection(Direction::UP);
        break;
    case Direction::LEFT:
        setDirection(Direction::RIGHT);
        break;
    case Direction::RIGHT:
        setDirection(Direction::LEFT);
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


void Ghost::update(float deltaTime,std::vector<sf::RectangleShape> map) {
	switch (direction) {
	case Direction::UP:
		if (!move(0.0, -speed * deltaTime, map)) changeGhostDirection();
		break;
	case Direction::RIGHT:
		if (!move(speed * deltaTime, 0.0, map)) changeGhostDirection();
		break;
	case Direction::DOWN:
		if (!move(0.0, speed * deltaTime, map)) changeGhostDirection();
		break;
	case Direction::LEFT:
		if (!move(-speed * deltaTime, 0.0, map)) changeGhostDirection();
		break;
	case Direction::NONE:
		changeGhostDirection();
		break;
	default:
		break;
	}
	switch (moveType) {
	case Name::Virtical:
		switch (direction) {
		case Direction::UP:
			if (!move(0.0, -speed * deltaTime, map)) changeGhostDirection();
			break;
		case Direction::DOWN:
			if (!move(0.0, speed * deltaTime, map)) changeGhostDirection();
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
		}
		break;
	}
};

