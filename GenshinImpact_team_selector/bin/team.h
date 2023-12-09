#ifndef TEAM_H_
#define TEAM_H_

#include "general.h"
#include "character.h"

class Team {
private:
    std::string m_team_name;
    Character m_team[TEAM_SIZE];
    int m_note;

public :
    Team() {} //NEEDED FOR UNORDERED MAP
    Team(std::string na, Character c1, Character c2, Character c3, Character c4, int n);
    virtual ~Team() {}

    // Getters and setters
    const Character * getTeam() const { return m_team; }
    int getNote() const { return m_note; }
    void setNote(int note) { m_note = note; }
    std::vector<std::string> getNames() {
        std::vector<std::string> m_names;
        m_names.push_back(m_team[0].getName());
        m_names.push_back(m_team[1].getName());
        m_names.push_back(m_team[2].getName());
        m_names.push_back(m_team[3].getName());
        return m_names;
    }
    
    // CHECK
    bool isCharacterInTeam(std::string character_name);

    // DISPLAYS
    void displayTeam() const;
    

};

#endif