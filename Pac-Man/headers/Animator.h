#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

class Animator
{
private:
	std::map<std::string, std::vector<sf::IntRect>> animations;
	std::map<std::string, float> animationDurations;
	int animationInductor;
	int FPS;
public:
	Animator(std::string);
	~Animator();
	void addKeyFrame(std::string, sf::IntRect);
	sf::IntRect runAnimation(std::string);
};

#endif // !ANIMATOR
