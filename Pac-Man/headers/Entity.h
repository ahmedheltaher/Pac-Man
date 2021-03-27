#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include "./Structs.h"
#include "./Animator.h"

class Entity {
	friend class Player;
	friend class Ghost;
private:
	Direction direction;
	float speed;
	Position position;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Entity(float, float, std::string);
	~Entity();
	void info() const; // For Debug
	Position getPosition() const;
	sf::Sprite getSprite() const;
	void setPosition(float, float);
	void loadTexture(std::string);
	void setDirection(Direction);
	void setSpeed(float);
	void setScale(float, float);
	void setTextureRect(sf::IntRect);
	void update(float, std::vector<sf::RectangleShape>);
	bool move(float, float, std::vector<sf::RectangleShape>);
	Animator animator;
};

#endif // !ENTITY