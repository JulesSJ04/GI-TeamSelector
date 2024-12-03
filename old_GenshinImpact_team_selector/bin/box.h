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
    virtual ~Box() {}

    // FILE MANIPULATION
    void writeToFile(Character c);
    void loadExistingCharacters();
    void writeMultipleCharacterToFile();
    bool resetCharacterFile();
    bool loadCharacters();
    void updateFileData();

    // DISPLAYS
    void displayBox() const;
    void displayExistingCharacters() const;
    void displayNonAddedCharacters() const;

    // BOX MANIPULATION
    void addCharacterToBox();
    void removeCharacterFromMyBox();
    void updateCharacterData(int rank);
    void resetBox();

    // GETTERS AND SETTERS
    void getCharacterDifference();
    Character getCharacterByName(std::string name);
    std::vector<std::string> getCharactersName();
    // Getter for m_characters
    const std::unordered_map<std::string, Character>& getCharacters() const {
        return m_characters;
    }
    // Getter for m_existing_characters
    const std::unordered_map<std::string, Element>& getExistingCharacters() const {
        return m_existing_characters;
    }
    // Getter for m_non_added_characters
    const std::set<std::string>& getNonAddedCharacters() const {
        return m_non_added_characters;
    }

    // DATA CHECK
    bool hasCharacter(std::string c, int build);
    bool characterExist(std::string name);

};

#endif