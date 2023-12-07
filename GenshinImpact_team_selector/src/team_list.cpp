#include "team_list.h"

int Team_list::s_team_id = 0;

Team_list::Team_list(Box * b)
    : m_box(b)
{
    s_team_id = 0;
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
    int doublon_cpt = 0;
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
                this->m_teams[this->s_team_id] = 
                    Team(
                    elem.name,
                    this->m_box->getCharacterByName(elem.characters[0]),
                    this->m_box->getCharacterByName(elem.characters[1]),
                    this->m_box->getCharacterByName(elem.characters[2]),
                    this->m_box->getCharacterByName(elem.characters[3]),
                    elem.note);
                this->s_team_id++;
            }
        }
    }
    std::cout << BG_WHITE << this->m_teams.size() << " / " << this->m_global_teams.size() 
        << " teams where added from your box" << RESET <<std::endl; 
}

bool Team_list::isAlreadyAdded(const String_team &team) {
    int match_cpt = 0;
    // Pour chacunes des équipes
    for (auto existingTeam : this->m_teams) {
        int match_cpt = 0;
        // Récupérer les 4 noms de l'équipe
        std::vector<std::string> existingNames = existingTeam.second.getNames();
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

bool Team_list::isAlreadyUsed(int team_id, std::vector<std::string> picked_character_names) {
    std::vector<std::string> four_characters_names = this->m_teams.at(team_id).getNames();
    for(const auto &elem: four_characters_names) {
        for (const auto &elem2: picked_character_names) {
            if(elem.compare(elem2) == 0)
                return true;
        }
    }
    return false;
}

bool Team_list::checkOwnership(std::string character_name, int build) {
    if (this->m_box->hasCharacter(character_name, build) == false) {
        std::cout << BG_RED << "The specified character " << character_name << " is not in your box or has not a build : " 
        << RESET << std::endl;
        this->m_box->displayBox();
        return false;
    }
    return true;
}

void Team_list::displayTeams() {
    //Vérifier que les teams sont à jour
    this->computePossibleTeams();
    for (const auto &elem: this->m_teams) {
        elem.second.displayTeam();
    }
}

int Team_list::buildPrompt() {
    // Récupérer le facteur de build
    int has_build;
    std::cout << BG_YELLOW <<"Does he need build ? 0. No 1. Yes" << RESET << std::endl;
    do {
        std::cin >> has_build;
        if ((has_build != 0) && (has_build != 1))
            std::cout << BG_RED <<"Please pick an existing option from the list" << RESET <<std::endl; 
    } while((has_build != 0) && (has_build != 1));  
    return has_build;
}

void Team_list::displayTeamsByName() {
    //Vérifier que les teams sont à jour
    this->computePossibleTeams();

    // Récupérer le nom du personnages
    std::cout << BG_YELLOW <<"Pick a character you want to see the teams :" << RESET << std::endl;
    std::string character_name;
    std::cin >> character_name;
    
    // Vérifier si le personnage est présent dans la box 
    if (this->checkOwnership(character_name, this->buildPrompt()) == false) {
        std::cout << BG_RED <<"Specified character is not in your team" << RESET <<std::endl;
        return;
    }
    if (this->m_teams.size() == 0) {
        std::cout << BG_RED << "No team matches your characters" << RESET <<std::endl;
        return;
    }
    // Parcourir les équipes
    int team_cpt = 0;
    std::cout << "Acquiring possible teams" << std::endl;
    for (auto &elem: this->m_teams) {
        // Vérifier si elles contiennent le personnage
        if (elem.second.isCharacterInTeam(character_name)) {
            elem.second.displayTeam();
            team_cpt++;
        }
    }
    std::cout << BG_WHITE << team_cpt << " teams where found according to your box" << RESET << std::endl;

}

void Team_list::displayTwoTeam() {
    //Vérifier que les teams sont à jour
    this->computePossibleTeams();

    if (this->m_teams.size() == 0) {
        std::cout << BG_RED <<"No team matches your characters" << RESET << std::endl;
        return;
    }

    // Récupérer le nom du personnages
    std::cout << BG_YELLOW << "Pick a character you want to see the teams :" << RESET <<std::endl;
    std::string character1;
    std::cin >> character1;

    // Vérifier si le personnages est présent dans la box 
    if (this->checkOwnership(character1, this->buildPrompt()) == false) {return;}
    
    // Récupérer la première team choisie
    int picked_team_1 = this->getFirstTeam(character1);

    // Récupérer le nom du personnages
    std::cout << BG_YELLOW << "Pick a character you want to see in the second team :" << RESET <<std::endl;
    std::string character2;
    std::cin >> character2;
    if (this->checkOwnership(character2, this->buildPrompt()) == false) {return;}
    // Etape 1 : Récupérer les 4 noms de l'équipe choisie
    std::vector<std::string> four_picked_character = this->m_teams.at(picked_team_1).getNames();
    std::set<int> user_input_check;
    // Etape 2 : parcourir les équipes
    for (auto &elem: this->m_teams) {
        // Vérifier si elles contiennent le personnage
        if (elem.second.isCharacterInTeam(character2))  
        {
            // Vérifier si l'un des 4 personnages n'est pas déjà dans une équipe 
            if (!this->isAlreadyUsed(elem.first, four_picked_character)) {
                std::cout << " " << PURPLE << elem.first << RESET << " ";
                elem.second.displayTeam();
                user_input_check.insert(elem.first);
            }
            
        }
    }
    if (user_input_check.size() == 0) {
        std::cout << BG_RED << "You can't pick a second team from your box ..." << RESET <<std::endl;
        return;
    }
    // Acquérir le choix user
    std::cout << BG_WHITE << user_input_check.size() << " teams where found according to your box" << RESET << std::endl;
    int picked_team_2 = -1;
    do {
        std::cout << BG_YELLOW << "Pick a team from the displayed list from his number :" << RESET << std::endl;
        std::cin >> picked_team_2;
    } while(user_input_check.count(picked_team_2) != 1);
    this->displayTwoTeams(picked_team_1, picked_team_2);
}


int Team_list::getFirstTeam(std::string character_name) {
    std::cout << BG_WHITE << "Consider this list of teams" << RESET << std::endl;
    std::set<int> user_input_check;
    int picked_team = -1;
    // Parcourir les équipes
    for (auto &elem: this->m_teams) {
        // Vérifier si elles contiennent le personnage
        if (elem.second.isCharacterInTeam(character_name))  
        {
            std::cout << " " << PURPLE << elem.first << RESET << " ";
            elem.second.displayTeam();
            user_input_check.insert(elem.first);
        }
    }
    // Acquérir le choix user
    std::cout << BG_WHITE << user_input_check.size() << " teams where found according to your box" << RESET << std::endl;
    do {
        std::cout << BG_YELLOW << "Pick a team from the displayed list from his number :" << RESET << std::endl;
        std::cin >> picked_team;
    } while(user_input_check.count(picked_team) != 1);
    return picked_team;
}

void Team_list::displayTwoTeams(int team1_id, int team2_id) {
    std::cout << "\t\t" << BG_YELLOW << " - PICKED TEAM 1 - " << RESET << "\t\t" << std::endl;
    this->m_teams.at(team1_id).displayTeam();
    std::cout << "\t\t" << BG_YELLOW << " - PICKED TEAM 2 - " << RESET << "\t\t" << std::endl;
    this->m_teams.at(team2_id).displayTeam();
    std::cout << "\t\t" << BG_YELLOW << " - ############# - " << RESET << "\t\t" << std::endl;
}

void Team_list::addTeam() {
    // Nom de l'équipe
    std::cout << BG_YELLOW << "Choose a team name" << RESET << std::endl;
    std::string team_name;
    std::cin >> team_name;
    // Choix des 4 personnages
    std::set<std::string> new_team_characters;
    std::string tampon_character;
    int cpt = 1;
    std::cout << BG_YELLOW << "Pick the four characters" << RESET << std::endl;
    do {
        std::cout << BG_WHITE << "Character " << cpt << RESET << std::endl;
        std::cin >> tampon_character;
        if(this->m_box->characterExist(tampon_character)) {
            new_team_characters.insert(tampon_character);
            // Vérifier si pas en double dans l'équipe
            if (new_team_characters.size() == cpt) cpt++; 
        }
    } while(new_team_characters.size() != 4);
    // Acquérir la note
    int note;
    do {
        std::cout << BG_YELLOW << "Give it a mark between 0 and 10" << RESET << std::endl;
        std::cin >> note;
    } while((note < 0) || (note > 10));

    // Ajout de la nouvelle team au vector de classe
    String_team new_team;
    new_team.name = team_name;
    new_team.note = note;
    cpt = 0;
    for (const auto &elem: new_team_characters) {
        new_team.characters[cpt] = elem;
        cpt++;
    }
    this->m_global_teams.push_back(new_team);

    // Ajout de la nouvelle team au file
    this->addTeamToFile(new_team);
}

void Team_list::addTeamToFile(String_team new_team) {
    std::string file_path = "./datas/global_teams.txt";
    try {
        std::ofstream outputFile(file_path, std::ios::app);
        if(!outputFile.is_open()) {
            throw std::runtime_error("Unable to open file.");
        }
        else {
            std::string line = new_team.name + "," + 
                new_team.characters[0] + "," + new_team.characters[1] + "," +
                new_team.characters[2] + "," + new_team.characters[3] + "," +
                std::to_string(new_team.note);
            outputFile << line << std::endl;
            outputFile.close();
            std::cout << "Team added to file (" << line << ")" << std::endl; 
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }
}