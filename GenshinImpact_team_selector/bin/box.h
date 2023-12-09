#ifndef BOX_H_
#define BOX_H_

#include "general.h"
#include "character.h"

class Box{
private:
    std::unordered_map<std::string, Character> m_characters;
    std::unordered_map<std::string, Element> m_existing_characters;
    std::set<std::string> m_non_added_characters;
    bool m_got_loaded;
public:
    Box();
    virtual ~Box() {this->m_got_loaded = this->resetBox();}

    // FILE MANIPULATION
    void writeToFile(Character c);
    void loadExistingCharacters();
    bool loadCharacters();
    void removeCharacterFromMyBox(std::string name);

    // DISPLAYS
    void displayBox() const;
    void displayExistingCharacters() const;
    void displayNonAddedCharacters() const;

    // BOX MANIPULATION
    void addCharacterToBox();
    bool resetBox();

    // GETTERS AND SETTERS
    void getCharacterDifference();
    Character getCharacterByName(std::string name);

    // DATA CHECK
    bool hasCharacter(std::string c, int build);
    bool characterExist(std::string name);
    
    // Character adding
    
    
    // Box modifying
    

    
    
};

#endif