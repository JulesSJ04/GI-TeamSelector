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
        std::string team_name;
        std::string names[TEAM_SIZE];
        int note;
        while (std::getline(input_file, line)) {
            std::istringstream iss(line);
            std::string data;
            // Nom
            std::getline(iss, data, ',');
            team_name = data;
            // c1 to c4
            for (unsigned int i = 0; i<TEAM_SIZE ; i++) {
                std::getline(iss, data, ',');
                names[i] = data;
            }
            // note
            std::getline(iss, data, ',');
            note = std::stoi(data);
            // Ajouter les données à la liste de structure
            String_team team = {team_name, {names[0], names[1], names[2], names[3]}, note};
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
        for (unsigned int i = 0; i < TEAM_SIZE; i++) {
            if (this->m_box->hasCharacter(elem.characters[i], 0) == false) {
                is_possible = false;
            }
        }
        // Vérifier si la team n'as pas déjà été ajoutée
        if (is_possible) {
            bool has_been_added = this->isAlreadyAdded(elem);
            // Ajouter la team si ils existent dans la box
            if (has_been_added == false) {
                this->m_teams.push_back(Team(
                    elem.name,
                    this->m_box->getCharacterByName(elem.characters[0]),
                    this->m_box->getCharacterByName(elem.characters[1]),
                    this->m_box->getCharacterByName(elem.characters[2]),
                    this->m_box->getCharacterByName(elem.characters[3]),
                    elem.note
                ));
            }
        }
        
    }
}

bool Team_list::isAlreadyAdded(const String_team &team) {
    int match_cpt = 0;
    // Pour chacunes des équipes
    for (auto existingTeam : this->m_teams) {
        int match_cpt = 0;
        // Récupérer les 4 noms de l'équipe
        std::vector<std::string> existingNames = existingTeam.getNames();
        // Pour chacuns des noms de l'équipe en cours, reagrder si identique à l'équipe en paramètre
        for (unsigned int i=0; i<TEAM_SIZE; i++) {
            for(unsigned int j=0; j<TEAM_SIZE; j++) {
                if(!existingNames[i].compare(team.characters[j])) {
                    match_cpt++;
                    // Si le compteur égale la taille de l'équipe, alors return true
                    if (match_cpt == TEAM_SIZE) return true;
                } 
            }
        }
    }
    return false; 

}

bool Team_list::checkOwnership(std::string character_name, int build) {
    if (this->m_box->hasCharacter(character_name, build) == false) {
        std::cout << "The specified character " << character_name << " is not in your box or has not a build : " <<std::endl;
        this->m_box->displayBox();
        return false;
    }
    return true;
}

void Team_list::displayTeams() const {
    for (const auto &elem: this->m_teams) {
        elem.displayTeam();
    }
}

int Team_list::buildPrompt() {
    // Récupérer le facteur de build
    int has_build;
    std::cout << "Does he need build ? 0. No 1. Yes" << std::endl;
    do {
        std::cin >> has_build;
        if ((has_build != 0) && (has_build != 1))
            std::cout << "Please pick an existing option from the list" << std::endl; 
    } while((has_build != 0) && (has_build != 1));  
    return has_build;
}

void Team_list::displayTeamsByName() {
    //Vérifier que les teams sont à jour
    this->computePossibleTeams();

    // Récupérer le nom du personnages
    std::cout << "Pick a character you want to see the teams :" << std::endl;
    std::string character_name;
    std::cin >> character_name;
    
    // Vérifier si le personnage est présent dans la box 
    if (this->checkOwnership(character_name, this->buildPrompt()) == false) {
        std::cout << "Specified character is not in your team" << std::endl;
        return;
    }
    if (this->m_teams.size() == 0) {
        std::cout << "No team matches your characters" << std::endl;
        return;
    }
    // Parcourir les équipes
    std::cout << "Acquiring possible teams" << std::endl;
    for (unsigned int i = 0; i < this->m_teams.size() ; i++) {
        // Vérifier si elles contiennent le personnage
        if (this->m_teams[i].isCharacterInTeam(character_name)) 
            this->m_teams[i].displayTeam();
    }
}

void Team_list::displaySecondTeam(std::string character1, std::string character2) {
    // Vérifier si les personnages sont présent dans la box 
    if (this->checkOwnership(character1, this->buildPrompt()) == false) {return;}
    if (this->checkOwnership(character2, this->buildPrompt()) == false) {return;}
    // Récupérer la première team choisie
    String_team picked_team = this->getFirstTeam(character1);
    
}


String_team Team_list::getFirstTeam(std::string character_name) {
    
}


