#ifndef STORAGE_H
#define STORAGE_H
#include <string>
#include <map>
#include <iostream>

class Storage {
private:
	std::map<std::string, std::string> leaderBoard;
public:
	Storage();
	~Storage();
	void addData(std::string);
	std::map<std::string, std::string> getLeaderBoard();
};
#endif // !STORAGE