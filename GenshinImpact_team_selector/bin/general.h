#ifndef GENERAL_H_
#define GENERAL_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unordered_map>

#define MAX_PATH_LENGTH 100
#define TEAM_SIZE 4

inline bool ToF(int value) {
    return value == 1;
}

/* Character role */
enum Character_role{
    MAIN_DPS = 0,
    SUB_DPS = 1,
    DPS_SUPPORT = 2,
    HEAL_SUPPORT = 3
};

/* Character elements */
enum Element{
    ANEMO = 0,
    GEO = 1,
    ELECTRO = 2,
    DENDRO = 3,
    HYDRO = 4,
    PYRO = 5,
    CRYO = 6,
    OMNI = 7
};

std::string elementToString(Element elem);
std::string roleToString(Character_role role);

#endif