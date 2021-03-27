#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "./Structs.h"

class Tile
{
private:
	Position position;
	Size size;
	sf::RectangleShape sprite;
public:
	Tile(float x, float y, int width, int height, sf::Color);
	~Tile();
	Position getPosition() const;
	sf::RectangleShape getSprite() const;
};

#endif // !TILE
