#include "statistics.h"

Statistics::Statistics(Team_list * tl, Box * b) 
    : m_team_list(tl), m_box(b)
{}

void Statistics::displayStatistics() {

}

template <class T>
void Statistics::displayF(Mode display_m, std::set<std::pair<std::string, int>, T> sortedSet) {
    int cpt = 0;
    clear_console();
    printTitle<std::string>("----- Sorted characters : -----");
    if (display_m != Mode::ALL) {
        // Iterate over the sorted set
        for (const auto& pair : sortedSet) {
            std::cout << PURPLE << pair.second << " times " << RESET << " :      ";
            printMessage<std::string>(pair.first + " ");
            cpt ++;
            if (cpt == 3) break;
        }
    } else {
        for(const auto& pair: sortedSet) {
            std::cout << PURPLE << pair.second << " times " << RESET << ": \t";
            printMessage<std::string>(pair.first + " ");
        }
    }
}

void Statistics::displayCharacterFrequency(Mode display_m) {
    // Mise à jour des équipes
    this->m_team_list->computePossibleTeams();
    this->m_character_frequency.clear();
    // Mettre à jour la map de fréquences
    std::unordered_map<int, Team>& teams = this->m_team_list->getTeams();
    int cpt = 0;
    for (const auto &elem: teams) {
        std::vector<std::string> team_names = teams.at(cpt).getNames();
        cpt++;
        for(unsigned int i = 0; i < TEAM_SIZE; i++) {
            this->m_character_frequency[team_names[i]]++;
        }
    }

    // Afficher les 3 personnages plus présent    
    if ((display_m == Mode::MOST) || (display_m == Mode::ALL)) {
        std::set<std::pair<std::string, int>, GreaterValue> sortedSet(
            m_character_frequency.begin(), m_character_frequency.end());
        this->displayF<GreaterValue>(display_m, sortedSet);
    } else {
        std::set<std::pair<std::string, int>, LesserValue> sortedSet(
            m_character_frequency.begin(), m_character_frequency.end());
        this->displayF<LesserValue>(display_m, sortedSet);
    }
}

