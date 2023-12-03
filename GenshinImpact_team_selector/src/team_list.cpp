#include "team_list.h"

Team_list::Team_list(Box * b)
    : m_box(b)
{
    this->loadTeams();
    this->computePossibleTeams();
}

void Team_list::loadTeams() {
    std::string file_path = "./datas/global_teams.txt";
    // Ouvrir le fichier
    try {
        std::ifstream input_file;
        input_file.open(file_path);
        if (!input_file.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
        // Variables à récupérer
        std::string line;
        std::string names[TEAM_SIZE];
        int note;
        while (std::getline(input_file, line)) {
            std::istringstream iss(line);
            std::string data;
            // c1 to c4
            for (unsigned int i = 0; i<TEAM_SIZE ; i++) {
                std::getline(iss, data, ',');
                names[i] = data;
            }
            // note
            std::getline(iss, data, ',');
            note = std::stoi(data);
            // Ajouter les données à la liste de structure
            String_team team = {{names[0], names[1], names[2], names[3]}, note};
            m_global_teams.push_back(team);   
        }
        input_file.close();
        
        std::cout << std::to_string(this->m_global_teams.size()) 
            <<" teams successfully loaded into database" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }
}

void Team_list::computePossibleTeams() {
    for (const auto &elem : this->m_global_teams) {
        bool is_possible = true;
        // Parcourir les 4 noms et vérifier si ils existent
        for (unsigned int i; i < TEAM_SIZE; i++) {
            if (this->m_box->hasCharacter(elem.characters[i]) == false) {
                is_possible = false;
            }
        }
        // Ajouter la team si ils existent dans la box
        if (is_possible == true) {
            this->m_teams.push_back(Team(
                this->m_box->getCharacterByName(elem.characters[0]),
                this->m_box->getCharacterByName(elem.characters[1]),
                this->m_box->getCharacterByName(elem.characters[2]),
                this->m_box->getCharacterByName(elem.characters[3]),
                elem.note
            ));
        }
    }
}

void Team_list::displayTeams() const {
    for (const auto &elem: this->m_teams) {
        elem.displayTeam();
    }
}

void Team_list::displayTeamsByName(std::string character_name) {
    // Vérifier si le charactère est présent dans le box 
    if (this->m_box->hasCharacter(character_name) == false) {
        std::cout << "The specified character " << character_name << " is not in your box " <<std::endl;
        return;
    }
    // Parcourir les équipes
    for (auto &elem: this->m_teams) {
        // Vérifier si elles contiennent le personnage
        if (elem.isCharacterInTeam(character_name)) 
            elem.displayTeam();
    }
}


