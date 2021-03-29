#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include "./Ghost.h"
#include <vector>
#include <map>
#include <string>
#include "./Tile.h"

struct Position {
	float x;
	float y;
};

class Map {
private:
	std::map<std::string, std::vector<Tile>> gridMap;
	std::map<std::string, std::vector<sf::RectangleShape>> readyGridMap;
	std::vector<Tile> tilemap;
	std::vector<sf::RectangleShape> rendrableTilemap;
	std::vector<Tile> coinsLayout;
	std::vector<sf::RectangleShape> rendrableCoinsLayout;
	Position playerPosition;
	std::vector<Ghost> ghosts;
public:
	Map(std::string);
	~Map();
	std::vector<Tile> getTilemap();
	std::vector<Tile> getCoins();
	std::vector<sf::RectangleShape> getRendrableTilemap();
	std::vector<sf::RectangleShape> getRendrableCoinsLayout();
	Position getPlayerPosition() const;
	void setPlayerPosition(float, float);
	std::vector<Ghost> getGhosts();
	std::map<std::string, std::vector<sf::RectangleShape>> getRendrableGridMap();
};

#endif // !MAP
