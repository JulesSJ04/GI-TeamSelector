#ifndef TEAM_H_
#define TEAM_H_

#include "general.h"
#include "character.h"

class Team {
private:
    Character m_team[TEAM_SIZE];
    int m_note;

public :
    Team(Character c1, Character c2, Character c3, Character c4, int n);
    virtual ~Team() {}

    // Getters and setters
    const Character * getTeam() const { return m_team; }
    int getNote() const { return m_note; }
    void setNote(int note) { m_note = note; }

    // Display
    void displayTeam() const;
    bool isCharacterInTeam(std::string character_name);

};

#endif