#include "../headers/Tile.h"

// Constructor
Tile::Tile(float x, float y, int width = 32, int height = 32, sf::Color fill = sf::Color(0, 93, 255)) :position({ x, y }), size({width, height}) {
	sprite.setSize(sf::Vector2f(size.width, size.height));
	sprite.setPosition(sf::Vector2f(position.x, position.y));
	sprite.setFillColor(fill);
};

// Destructor
Tile::~Tile() {};

// Getter For Position
Position Tile::getPosition() const {
	return position;
};

sf::RectangleShape Tile::getSprite() const {
	return sprite;
};