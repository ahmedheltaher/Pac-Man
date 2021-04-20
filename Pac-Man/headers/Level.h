#ifndef LEVEL_H
#define LEVEL_H
#include "./Map.h"
#include "./Ghost.h"
#include "./Player.h"
#include "./SoundManager.h"
#include <string>

class Level {
private:
	Map map;
	int score;
	std::vector<Ghost> ghosts = map.getGhosts();;
	std::vector<sf::RectangleShape> readyMap = map.getRendrableTilemap();
	std::vector<sf::RectangleShape> readyCoins = map.getRendrableCoinsLayout();
	std::map<std::string, std::vector<sf::RectangleShape>> readyGridMap = map.getRendrableGridMap();
	std::vector<Tile> coins = map.getCoins();
public:
	Level(int);
	~Level();
	void handleEvents(sf::Event);
	void update(float);
	void draw(sf::RenderWindow*);
	bool chekCollisionWithEnemies();
	int chekCollisionWithCoins();
	SoundManager soundManager;
	Player pacman;
	int getScore();
	void pause();
	bool gotAllCoins();
	bool pacmanDied();
};
#endif // !LEVEL
