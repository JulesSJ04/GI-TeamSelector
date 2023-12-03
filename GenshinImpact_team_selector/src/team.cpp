#include "team.h"

Team::Team(Character c1, Character c2, Character c3, Character c4, int n):
    m_team{c1, c2, c3, c4}, m_note(n) 
{}

void Team::displayTeam() const {
    std::cout << " Team has been ranked " << std::to_string(this->m_note) << " : " << std::endl;
    for (unsigned int i = 0; i < 4; i++) {
        this->m_team[i].displayCharacter();
    }
}

bool Team::isCharacterInTeam(std::string character_name) {
    bool has_character = false;
    for (auto &elem: this->m_team) {
        if (character_name.compare(elem.getName()) == 0)
            return true;
    }
    return false;
}

