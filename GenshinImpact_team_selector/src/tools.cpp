#include "general.h"


/*
* @brief convert Element variable type to string
* @param: element to convert
* @return: element to string
*/
std::string elementToString(Element elem) {
    switch(elem) {
        case ANEMO: return "Anemo";
        case GEO: return "Geo";
        case ELECTRO: return "Electro";
        case DENDRO: return "Dendro";
        case HYDRO: return "Hydro";
        case PYRO: return "Pyro";
        case CRYO: return "Cryo";
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
        case MAIN_DPS: return "Main DPS";
        case SUB_DPS: return "Sub DPS";
        case DPS_SUPPORT: return "DPS Support";
        case HEAL_SUPPORT: return "Heal Support";
        default: return "Unknown Role";
    }
}