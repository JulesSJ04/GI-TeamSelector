#include "general.h"
#include "box.h"
#include "team_list.h"

/*
* @brief convert Element variable type to string
* @param: element to convert
* @return: element to string
*/
std::string elementToString(Element elem) {
    switch(elem) {
        case ANEMO: return (BOLD_GREEN+std::string("Anemo")+RESET);
        case GEO: return (YELLOW+std::string("Geo")+RESET);
        case ELECTRO: return (PURPLE+std::string("Electro")+RESET);
        case DENDRO: return (GREEN+std::string("Dendro")+RESET);
        case HYDRO: return (BLUE+std::string("Hydro")+RESET);
        case PYRO: return (RED+std::string("Pyro")+RESET);
        case CRYO: return (CYAN+std::string("Cryo")+RESET);
        case OMNI: return (BG_WHITE+std::string("Omni")+RESET);
        default: return "No-element";
    }
}

/*
* @brief convert Character_role variable type to string
* @param: role to convert
* @return: role to string
*/
std::string roleToString(Character_role role) {
    switch (role) {
        case MAIN_DPS: return (RED+std::string("Main DPS")+RESET);
        case SUB_DPS: return (BLUE+ std::string("Sub DPS") + RESET) ;
        case DPS_SUPPORT: return (YELLOW+ std::string("DPS Support") + RESET);
        case HEAL_SUPPORT: return (GREEN+ std::string("Heal Support") + RESET);
        default: return "Unknown Role";
    }
}

/*
* @brief display all the possible role a character can have
*/
void displayPossibleRole() {
    std::cout << "0. " << roleToString(static_cast<Character_role>(0)) << std::endl
        << "1. " << roleToString(static_cast<Character_role>(1)) << std::endl
        << "2. " << roleToString(static_cast<Character_role>(2)) << std::endl
        << "3. " << roleToString(static_cast<Character_role>(3)) << std::endl;
}

/*
* @brief display all the possible role a character can have
*/
void displayPossibleElement() {
    for (unsigned int i = 0; i < 8; i++) {
        std::cout << std::to_string(i) << ". " << elementToString(static_cast<Element>(i)) << std::endl; 
    }
}


