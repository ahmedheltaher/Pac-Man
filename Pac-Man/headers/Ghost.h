#ifndef GHOST_H
#define GHOST_H
#include "./Entity.h"

enum class Name {
	Horizontal,
	Virtical
};

class Ghost : public Entity {
private:
public:
	Name moveType;
	Ghost(Name, float, float);
	~Ghost();
	void changeGhostDirection();
	void update(float, std::vector<sf::RectangleShape>);
};
#endif // !GHOST