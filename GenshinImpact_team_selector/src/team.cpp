#include "team.h"

Team::Team(std::string na, Character c1, Character c2, Character c3, Character c4, int n):
    m_team_name(na), m_team{c1, c2, c3, c4}, m_note(n) 
{
    std::cout << m_team_name << " added with : " << c1.getName() 
    << " / " << c2.getName() << " / " << c3.getName() << " / " << c4.getName() 
    << std::endl;
}

void Team::displayTeam() const {
    std::cout << "---------------------------------------------------------" << std::endl;
    std::cout << "Team " << this->m_team_name << " has been ranked " << std::to_string(this->m_note) << " : " << std::endl;
    for (unsigned int i = 0; i < 4; i++) {
        this->m_team[i].displayCharacter();
    }
}

bool Team::isCharacterInTeam(std::string character_name) {
    bool has_character = false;
    for (unsigned int i = 0; i < TEAM_SIZE ; i++) {
        if (character_name.compare(this->m_team[i].getName()) == 0)
            return true;
    }
    return false;
}

