#include "../headers/Animator.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
Animator::Animator(std::string fileName) :animationInductor(0) {
	std::ifstream mainAnimationsFile("./textures/animations/" + fileName + "/main.txt");
	std::vector<std::string> keyframesFiles;
	if (mainAnimationsFile.is_open()) {
		std::string keyframesRaw;
		mainAnimationsFile >> keyframesRaw;
		std::stringstream ss(keyframesRaw);
		while (ss.good()) {
			std::string substr;
			std::getline(ss, substr, ',');
			keyframesFiles.push_back(substr);
		}
	}
	mainAnimationsFile.close();
	for (unsigned int i = 0; i < keyframesFiles.size(); i++) {
		std::map<std::string, std::vector<sf::IntRect>> preAnimations;
		std::string line;
		int l, t, w, h, frames = 0;
		std::ifstream keyframesFile("./textures/animations/" + fileName + "/" + keyframesFiles[i] + ".txt");
		if (keyframesFile.is_open()) {
			while (std::getline(keyframesFile, line)) {
				std::istringstream in(line);
				in >> l >> t >> w >> h;
				preAnimations[keyframesFiles[i]].push_back(sf::IntRect(l, t, w, h));
				frames++;
			}
		}
		for (int f = 0; f < frames; f++) {
			for (int t = 0; t < 24 / frames; t++) {
				animations[keyframesFiles[i]].push_back(preAnimations[keyframesFiles[i]][f]);
			}
		}
		frames = 0;
		keyframesFile.close();
	}
};

// Destructor
Animator::~Animator() {};

// Push new Scene To Scenes Map
void Animator::addKeyFrame(std::string animationName, sf::IntRect keyFrame) {
	animations[animationName].push_back(keyFrame);
};

// Run Animation
sf::IntRect Animator::runAnimation(std::string animationName) {
	sf::IntRect currentFrame = animations[animationName][animationInductor];
	animationInductor++;
	animationInductor %= animations[animationName].size();
	return currentFrame;
};
