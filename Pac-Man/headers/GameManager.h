#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>
#include <iostream>
#include "./Level.h"
#include "./SceneManager.h"

class GameManager {
private:
	int loadedLevels;
	int currentLevel;
	std::vector<Level> levels;
	SceneManager scenes;
public:
	GameManager(int);
	~GameManager();
	void loop();
	void runLevel(int);
	void runLevelbyIndex(int);
	void nextLevel();
};

#endif // !GAMEMANAGER


