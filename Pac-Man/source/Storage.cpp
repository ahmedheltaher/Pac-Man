#include "../headers/Storage.h"
#include <fstream>
#include <sstream>
#include <algorithm>

// Constructor
Storage::Storage() {
	std::ifstream dataBaseFile("./storage/data.txt");
	if (dataBaseFile.is_open()) {
		std::string line, key, value;
		while (std::getline(dataBaseFile, line)) {
			std::istringstream in(line);
			in >> key >> value;
			leaderBoard.push_back(std::make_pair(key, std::stoi(value)));
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

bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
	return (a.second > b.second);
}

std::string Storage::getStringLeaderBoard() {
	std::string data = "";
	int dataEnterd = 0;
	std::sort(leaderBoard.begin(), leaderBoard.end(), sortbysec);
	for (int i = 0; i < leaderBoard.size(); i++) {
		if (dataEnterd > 10) break;
		data += leaderBoard[i].first + " - " + std::to_string(leaderBoard[i].second) + "\n";
		dataEnterd++;
	}
	return data;
};