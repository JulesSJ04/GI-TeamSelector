#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "general.h"

/*
* Class describing a single character
*/
class Character {
private:
    std::string m_name;
    Character_role m_role;
    Element m_element;
    bool m_has_build;

public:
    Character(){}
    Character(std::string n, Character_role r, Element e, bool b);
    virtual ~Character() {std::cout << "Destroy character " << m_name << std::endl; }

    void displayCharacter() const;
    std::string displayBool() const;

    // Getter and Setter for m_name
    std::string getName() { return m_name; }
    void setName(const std::string& name) { m_name = name; }
    // Getter and Setter for m_role
    const Character_role& getRole() const { return m_role; }
    void setRole(const Character_role& role) { m_role = role; }
    // Getter and Setter for m_element
    const Element& getElement() const { return m_element; }
    void setElement(const Element& element) { m_element = element; }
    // Getter and Setter for m_has_build
    bool hasBuild() const { return m_has_build; }
    void setHasBuild(bool hasBuild) { m_has_build = hasBuild; }
};

#endif