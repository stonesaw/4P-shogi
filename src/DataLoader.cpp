#include "DataLoader.h"


std::map<std::string, std::vector<std::vector<int>>> DataLoader::LoadMap(const std::string path) {
    std::string errmsg = "DataLoader::LoadMap()\n    ";
    std::ifstream ifs(path);
    if (!ifs.is_open()) 
        throw std::invalid_argument(errmsg + "[Wrong to Path! '" + path + "' ]");
    if (std::regex_search(path, std::regex(".info$"))) 
        throw std::invalid_argument(errmsg + "[Please .info file path: '" + path + "' ]");

    std::string str;
    std::smatch match;
    std::string pieceName = "null";
    std::map<std::string, std::vector<std::vector<int>>> map;
    std::vector<int> vec;
    int line = 0;
    while (std::getline(ifs, str)) {
        line++;
        if (std::regex_search(str, std::regex("^\s*//|^\n"))) {
            continue;
        }
        else if (std::regex_match(str, match, std::regex("^# (\\w+)"))) {
            pieceName = match[1].str();
        }
        else if (std::regex_match(str, std::regex("(\d\s)+\d"))) {
            std::istringstream iss(str);
            std::string s;
            while (iss >> s) {
                int n = std::stoi(s.c_str());
                vec.push_back(n);
            }
            if (pieceName == "null")
                throw std::runtime_error(errmsg + "[Load File Error! line:" + std::to_string(line) + " Please input piece name]");
            else 
                map[pieceName].push_back(vec);
        }
        else {
            throw std::runtime_error(errmsg + "[Load File Error! line:" + std::to_string(line) + " `" + str + "` Wrong input!]");
        }
    }

    return map;
}

//bool DataLoader::file_exists(const char* str) {
//    std::ifstream fs(str);
//    return fs.is_open();
//}
