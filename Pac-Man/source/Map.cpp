#include "../headers/Map.h"
#include "../headers/Ghost.h"
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

// Constructor
Map::Map(std::string fileName) :playerPosition({0, 0}) {
	std::ifstream mapFile("./maps/" + fileName + ".txt");
	if (mapFile.is_open()) {
		std::string line, quarter = "";
		int lineCount = 0;
		while (std::getline(mapFile, line)) {
			for (unsigned int column = 0; column < line.length(); column++) {
				float x = (float) column * 32, y = (float) lineCount * 32;
				quarter += (y > 512) ? "bottom" : "top";
				quarter += (x > 750) ? "Left" : "Right";
				switch (line[column]) {
				case '1':
					tilemap.push_back(Tile(x, y, 32, 32, sf::Color(0, 93, 255)));
					gridMap[quarter].push_back(Tile(x, y, 32, 32, sf::Color(0, 93, 255)));
					break;
				case 'X':
					coinsLayout.push_back(Tile((x > 640) ? x  : x + 28, (y > 512) ? y : y + 28, 8, 8, sf::Color(255, 255, 0)));
					break;
				case 'P':
					setPlayerPosition(x + 12, y);
					break;
				case 'H':
					ghosts.push_back(Ghost(Name::Horizontal, x + 16, (y > 500) ? y + 16 : y - 16));
					break;
				case 'V':
					ghosts.push_back(Ghost(Name::Virtical, (x > 500) ? x + 16 : x - 16, y + 16));
					break;
				default:
					break;
				}
				quarter = "";
			}
			lineCount++;
		}
	}
	mapFile.close();
	for (Tile tile : tilemap) rendrableTilemap.push_back(tile.getSprite());
	for (Tile tile : coinsLayout) rendrableCoinsLayout.push_back(tile.getSprite());
	for (auto& i : gridMap) for (Tile tile : i.second) readyGridMap[i.first].push_back(tile.getSprite());
};

// Destructor
Map::~Map() {};

// Getter For Tilemap
std::vector<Tile> Map::getTilemap()  {
	return tilemap;
};


std::vector<sf::RectangleShape> Map::getRendrableTilemap() {
	return rendrableTilemap;
};

std::vector<sf::RectangleShape> Map::getRendrableCoinsLayout() {
	return rendrableCoinsLayout;
};

// Getter For Coins
std::vector<Tile> Map::getCoins() {
	return coinsLayout;
};

// Getter for Player Position 
Position Map::getPlayerPosition() const {
	return playerPosition;
};

void Map::setPlayerPosition(float x, float y) {
	playerPosition = { x, y };
};

std::vector<Ghost> Map::getGhosts() {
	return ghosts;
};

std::map<std::string, std::vector<sf::RectangleShape>> Map::getRendrableGridMap() {
	return readyGridMap;
};
