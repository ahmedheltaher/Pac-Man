#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <vector>
#include <utility>
#include <iostream>

class Storage {
private:
	std::vector<std::pair<std::string, int>> leaderBoard;
public:
	Storage();
	~Storage();
	void addData(std::string);
	std::string getStringLeaderBoard();
};
#endif // !STORAGE