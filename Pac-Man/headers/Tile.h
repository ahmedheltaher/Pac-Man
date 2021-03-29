#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
private:
	sf::RectangleShape sprite;
public:
	Tile(float, float, float, float, sf::Color);
	~Tile();
	sf::RectangleShape getSprite() const;
};

#endif // !TILE
