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
#include <cstdlib>
#include <unordered_map>
#include <map>

#define MAX_PATH_LENGTH 100
#define TEAM_SIZE 4

// ANSI escape codes for text color
#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define PURPLE      "\e[0;35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BOLD_BLACK  "\033[1m\033[30m"
#define BOLD_RED    "\033[1m\033[31m"
#define BOLD_GREEN  "\033[1m\033[32m"
#define BOLD_YELLOW "\033[1m\033[33m"
#define BOLD_BLUE   "\033[1m\033[34m"
#define BOLD_MAGENTA "\033[1m\033[35m"
#define BOLD_CYAN   "\033[1m\033[36m"
#define BOLD_WHITE  "\033[1m\033[37m"
#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m\033[30m"

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
void displayPossibleRole();
void displayPossibleElement();
void clear_console();

/* Display methods */
template<class T> 
void printRestriction(const T& data) {
    std::cout << BG_RED << data << RESET << std::endl;
} 

template<class T>
void printMessage(const T& data) {
    std::cout << BG_WHITE << " " << data << RESET << std::endl;
}

template<class T>
void printSystem(const T& data) {
    std::cout << data << std::endl;
}

template<class T>
void printTitle(const T& data) {
    std::cout << BG_BLUE << WHITE << data << RESET << std::endl;
}

template<class T, class U>
U inputUser(const T& message) {
    U user_input;
    std::cout << BG_CYAN << message << RESET << BOLD_BLUE<< std::endl;
    std::cin >> user_input;
    std::cout << RESET;
    return user_input;
}

#endif