#include "general.h"
#include "character.h"

Character::Character(std::string n, Character_role r, Element e, bool b)
    : m_name(n), m_role(r), m_has_build(b), m_element(e)
{}

std::string Character::displayBool() const {
    return (m_has_build == true)? " has a build " : " has not a build ";
}

void Character::displayCharacter() const {
    std::cout << BG_WHITE << "\t" + this->m_name + "\t\t" << RESET <<" => type " << elementToString(this->m_element) 
        <<  " has role " << roleToString(this->m_role)  << " and" << this->displayBool()
        << std::endl;  
}
