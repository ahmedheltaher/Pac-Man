#ifndef GHOST_H
#define GHOST_H
#include "./Entity.h"

enum class Name {
	Horizontal,
	Virtical
};

class Ghost : public Entity {
private:
	void changeGhostDirection();
public:
	Name moveType;
	Ghost(float, float, Name);
	~Ghost();
	void update(float, std::vector<sf::RectangleShape>);
};
#endif // !GHOST