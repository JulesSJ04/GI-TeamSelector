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

    bool resetBox();
    // Displays
    void displayBox() const;
    void displayExistingCharacters() const;
    void displayNonAddedCharacters() const;
    // Containers loading
    void loadExistingCharacters();
    bool loadCharacters();
    void getCharacterDifference();
    // Used for team filling
    bool hasCharacter(std::string c, int build);
    bool characterExist(std::string name);
    Character getCharacterByName(std::string name);
    // Character adding
    void addCharacterToBox();
    void writeToFile(Character c);
    // Box modifying
    void removeCharacterFromMyBox(std::string name);

    
    
};

#endif