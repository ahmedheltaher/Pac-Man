#ifndef PLAYER_H
#define PLAYER_H
#include "./Entity.h"

class Player: public Entity {
private:
	int lives;
public:
	Player(float, float);
	~Player();
	void handleKeyboardEvent(sf::Event);
	int getLives();
	void decrementLives();
};

#endif // !PLAYER