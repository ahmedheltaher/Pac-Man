#include "../headers/Storage.h"
#include <fstream>
#include <sstream>

// Constructor
Storage::Storage() {
	std::ifstream dataBaseFile("./storage/data.txt");
	if (dataBaseFile.is_open()) {
		std::string line, key, value;
		int lines_read = 0;
		while ((lines_read < 10) && std::getline(dataBaseFile, line)) {
			std::istringstream in(line);
			in >> key >> value;
			leaderBoard[key] = value;
			++lines_read;
		}
	}
	dataBaseFile.close();
};

// Destructor
Storage::~Storage() {};

void Storage::addData(std::string data) {
	std::ofstream dataBaseFile("./storage/data.txt", std::ios_base::app);
	if (dataBaseFile.is_open()) dataBaseFile << data + " \n";
	dataBaseFile.close();
};

std::map<std::string, std::string> Storage::getLeaderBoard() {
	return leaderBoard;
};