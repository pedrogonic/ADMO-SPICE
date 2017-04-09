
#include "Utils.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <exception>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int pos(std::vector<std::string> v,std::string s) {
    
    try{
        if (v[stoi(s)] == s)
            return stoi(s);
    }catch(std::exception& e) {}
    
    for (int i = 0; v.size(); i++){
        if (v[i] == s)
            return i;
    }
    
    return -1;
}