#include "../headers/Tile.h"

// Constructor
Tile::Tile(float x, float y, float width = 32, float height = 32, sf::Color fill = sf::Color(0, 93, 255)) {
	sprite.setSize(sf::Vector2f(width, height));
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setFillColor(fill);
};

// Destructor
Tile::~Tile() {};


sf::RectangleShape Tile::getSprite() const {
	return sprite;
};