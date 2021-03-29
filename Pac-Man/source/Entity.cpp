#include "../headers/Entity.h"

// Constructor
Entity::Entity(float x = 0, float y = 0, std::string animation = "") :animator(animation), direction(Direction::NONE){
	sprite.setPosition(x, y);
	sprite.setScale(3, 3);
};

// Destructor
Entity::~Entity() {};

// Setter For Position
void Entity::setPosition(float x, float y) {
	sprite.setPosition(sf::Vector2f(x, y));
};

// Loader For Sprite Texture
void Entity::loadTexture(std::string fileName) {
	texture.loadFromFile("./textures/" + fileName);
	sprite.setTexture(texture);
};

// Getter For Sprite
sf::Sprite Entity::getSprite() const {
	return sprite;
};


// Setter For Sprite Scale
void Entity::setScale(float scaleX, float scaleY) {
	sprite.setScale(scaleX, scaleY);
};

// Setter for Sprite Texture Rect
void Entity::setTextureRect(sf::IntRect dimensions) {
	sprite.setTextureRect(dimensions);
};


// Setter for Player Direction
void Entity::setDirection(Direction dir) {
	if (direction == dir) return;
	direction = dir;
};

// Setter for Player Speed
void Entity::setSpeed(float s) {
	if (speed == s) return;
	speed = s;
};

std::string Entity::getQuarter() {
	std::string quarter = "";
	quarter += (sprite.getPosition().y > 512) ? "bottom" : "top";
	quarter += (sprite.getPosition().x > 750) ? "Left" : "Right";
	return quarter;
};


// Handle Update
void Entity::update(float deltaTime, std::vector<sf::RectangleShape> map) {
	switch (direction) {
	case Direction::UP:
		move(0.0, -speed * deltaTime, map);
		sprite.setTextureRect(animator.runAnimation("up"));
		break;
	case Direction::RIGHT:
		move(speed * deltaTime, 0.0, map);
		sprite.setTextureRect(animator.runAnimation("right"));
		break;
	case Direction::DOWN:
		move(0.0, speed * deltaTime, map);
		sprite.setTextureRect(animator.runAnimation("down"));
		break;
	case Direction::LEFT:
		move(-speed * deltaTime, 0.0, map);
		sprite.setTextureRect(animator.runAnimation("left"));
		break;
	}
};

bool Entity::move(float moveX, float moveY, std::vector<sf::RectangleShape> map) {
	for (unsigned int i = 0; i < map.size(); i++) {
		if (sprite.getPosition().x + moveX <= map[i].getPosition().x + map[i].getGlobalBounds().width &&
			sprite.getPosition().x + sprite.getGlobalBounds().width + moveX >= map[i].getPosition().x &&
			sprite.getPosition().y + moveY <= map[i].getPosition().y + map[i].getGlobalBounds().height &&
			sprite.getPosition().y + sprite.getGlobalBounds().height + moveY >= map[i].getPosition().y)
			return false;
	}
	if (moveX == 0 && moveY == 0) return false;
	sprite.move(moveX, moveY);
	return true;
};