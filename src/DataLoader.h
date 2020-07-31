#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <filesystem>


class DataLoader {
private:
	//static bool file_exists(const char* str);

public:
	static std::map<std::string, std::vector<std::vector<int>>> LoadMap(const std::string path);
};
