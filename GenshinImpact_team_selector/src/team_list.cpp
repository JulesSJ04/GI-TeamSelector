#include "team_list.h"

int Team_list::s_team_id = 0;

Team_list::Team_list(Box * b)
    : m_box(b)
{
    s_team_id = 0;
    this->loadTeams();
    this->computePossibleTeams();
}

/******************************************************************************************************************************
* FILE MANIPULATION
******************************************************************************************************************************/

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
            printSystem<std::string>("Team added to file (" + line + ")"); 
        }
    } catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unknown error occurred" << std::endl;
    }
}

/******************************************************************************************************************************
* CHECKING AND UPDATE METHODS
******************************************************************************************************************************/

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
    printMessage<std::string>(std::to_string(this->m_teams.size()) +
        " / " + std::to_string(this->m_global_teams.size()) + 
        " teams where added from your box " );
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
        printRestriction<std::string>("The specified character " + character_name + " is not in your box or has not a build : ");
        this->m_box->displayBox();
        return false;
    }
    return true;
}

/******************************************************************************************************************************
* DISPLAYS
******************************************************************************************************************************/

void Team_list::displayTeams() {
    //Vérifier que les teams sont à jour
    this->computePossibleTeams();
    for (const auto &elem: this->m_teams) {
        elem.second.displayTeam();
    }
}

void Team_list::displayTwoTeams(int team1_id, int team2_id) {
    clear_console();
    printTitle<std::string>(" ---------------------- PICKED TEAM 1 ---------------------- ");
    this->m_teams.at(team1_id).displayTeam();
    printTitle<std::string>(" ---------------------- PICKED TEAM 2 ---------------------- ");
    this->m_teams.at(team2_id).displayTeam();
    printTitle<std::string>(" ----------------------------------------------------------- ");
}

/******************************************************************************************************************************
* TEAM DISPLAY FROM NAME
******************************************************************************************************************************/

void Team_list::displayTeamsByName(bool is_double_choice) {
    //Vérifier que les teams sont à jour
    this->computePossibleTeams();
    // Vérifier que des équipes sont réalisables
    if (this->m_teams.size() == 0) {
        printRestriction<std::string>("No team matches your characters");
        return;
    }

    // Récupérer le nom du personnages
    std::string character_name = inputUser<std::string, std::string>("Pick a character you want to see the teams :");    
    // Vérifier si le personnage est présent dans la box 
    bool has_build = this->buildPrompt();
    if (this->checkOwnership(character_name, has_build) == false) {
        printRestriction<std::string>("Specified character is not in your team");
        return;
    }

    // Récupérer l'ID de la team 1 et l'afficher si mode 1 team
    int team_one_id = this->getFirstTeam<std::string>(character_name, has_build);
    if (!is_double_choice) {
        clear_console();
        printTitle<std::string>(" ---------------------- PICKED TEAM ---------------------- ");
        this->m_teams.at(team_one_id).displayTeam();
        return;
    }

    // Récupérer l'ID de la team 2
    // Récupérer le nom du personnages
    std::string second_character_name = inputUser<std::string, std::string>("Pick a character you want to see the teams :");    
    // Vérifier si le personnage est présent dans la box 
    if (this->checkOwnership(second_character_name, has_build) == false) {
        printRestriction<std::string>("Specified character is not in your team");
        return;
    }
    int team_two_id = this->getSecondTeam<std::string>(team_one_id, second_character_name, has_build);
    if (team_two_id!=-1) 
        this->displayTwoTeams(team_one_id, team_two_id);
}

/******************************************************************************************************************************
* TEAM DISPLAY FROM ELEMENT
******************************************************************************************************************************/

void Team_list::displayTeamsByElement(bool is_double_choice) {
    //Vérifier que les teams sont à jour
    this->computePossibleTeams();
    // Vérifier que des équipes sont réalisables
    if (this->m_teams.size() == 0) {
        printRestriction<std::string>("No team matches your characters");
        return;
    }
    // Acquérir l'élement voulu
    int picked_element = -1;
    printMessage<std::string>("Choose an element from the following elements :");
    displayPossibleElement();
    do {
        picked_element = inputUser<std::string, int>("Your choice :");
    } while ((picked_element < 0 ) || (picked_element > 7));

    // Récupérer l'ID de la team 1 et l'afficher si mode 1 team
    int team_one_id = this->getFirstTeam<int>(picked_element, true);
    if (!is_double_choice) {
        clear_console();
        printTitle<std::string>(" ---------------------- PICKED TEAM ---------------------- ");
        this->m_teams.at(team_one_id).displayTeam();
        return;
    }

    // Récupérer l'ID de la team 2
    printMessage<std::string>("Choose an element from the following elements :");
    displayPossibleElement();
    do {
        picked_element = inputUser<std::string, int>("Your choice :");
    } while ((picked_element < 0 ) || (picked_element > 7));

    int team_two_id = this->getSecondTeam<int>(team_one_id, picked_element, true);
    if (team_two_id!=-1) 
        this->displayTwoTeams(team_one_id, team_two_id);
}

/******************************************************************************************************************************
* GET TEAMS
******************************************************************************************************************************/

template<class T>
int Team_list::getFirstTeam(T data, bool need_build) {

    // Si selon élement, demander si main dps
    bool main_dps = false;
    if constexpr (std::is_same_v<T, int>) {
        main_dps = this->mainDpsPrompt();
    }
    std::cout << BG_WHITE << "Consider this list of teams" << RESET << std::endl;
    std::set<int> user_input_check;
    int picked_team = -1;
    
    // Parcourir les équipes
    for (auto &elem: this->m_teams) {
        // Vérifier si elles contiennent le personnage
        if (this->isCharacterInTeamCondition(elem.second, data, main_dps, need_build))  
        {
            std::cout << " " << PURPLE << elem.first << RESET << " ";
            elem.second.displayTeam();
            user_input_check.insert(elem.first);
        }
    }
    // Acquérir le choix user
    printMessage<std::string>(std::to_string(user_input_check.size()) + " teams where found according to your box");
    do {
        picked_team = inputUser<std::string, int>("Pick a team from the displayed list from his number :");
    } while(user_input_check.count(picked_team) != 1);
    return picked_team;
}

template<class T>
int Team_list::getSecondTeam(int team_one_id, T data, bool need_build) {
    // Si selon élement, demander si main dps
    bool main_dps = false;
    if constexpr (std::is_same_v<T, int>) {
        main_dps = this->mainDpsPrompt();
    }
    // Etape 1 : Récupérer les 4 noms de l'équipe choisie
    std::vector<std::string> four_picked_character = this->m_teams.at(team_one_id).getNames();
    std::set<int> user_input_check;
    // Etape 2 : parcourir les équipes
    for (auto &elem: this->m_teams) {
        // Vérifier si elles contiennent le personnage
        if (this->isCharacterInTeamCondition(elem.second, data, main_dps, need_build))  
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
        printRestriction<std::string>("You can't pick a second team from your box");
        return -1;
    }
    printMessage(std::to_string(user_input_check.size()) + " teams where found according to your box");
    // Acquérir le choix user
    int picked_team_2 = 0; 
    do {
        picked_team_2 = inputUser<std::string, int>("Pick a team from the displayed list from his number :");
    } while(user_input_check.count(picked_team_2) != 1); 
    return picked_team_2; 
}


/******************************************************************************************************************************
* USEFUL METHODS
******************************************************************************************************************************/

void Team_list::addTeam() {
    // Nom de l'équipe
    std::string team_name = inputUser<std::string, std::string>("Choose a team name");
    // Choix des 4 personnages
    std::set<std::string> new_team_characters;
    std::string tampon_character;
    int cpt = 1;
    printMessage<std::string>("Pick the four characters");
    do {
        tampon_character = inputUser<std::string, std::string>(" Character " + std::to_string(cpt) + " : ");
        if(this->m_box->characterExist(tampon_character)) {
            new_team_characters.insert(tampon_character);
            // Vérifier si pas en double dans l'équipe
            if (new_team_characters.size() == cpt) cpt++; 
        }
    } while(new_team_characters.size() != 4);
    // Acquérir la note
    int note;
    do {
        note = inputUser<std::string, int>("Give it a mark between 0 and 10");
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

int Team_list::buildPrompt() {
    // Récupérer le facteur de build
    int has_build;
    do {
        has_build = inputUser<std::string, int>("Does he need build ? 0. No 1. Yes");
        if ((has_build != 0) && (has_build != 1))
            printRestriction("Please pick an existing option from the list");
    } while((has_build != 0) && (has_build != 1));  
    return has_build;
}

bool Team_list::mainDpsPrompt() {
    int need_mainDPS;
    do {
        need_mainDPS = inputUser<std::string, int>("Does the character need to be a main DPS ? 0. No 1. Yes");
        if ((need_mainDPS != 0) && (need_mainDPS != 1))
            printRestriction("Please pick an existing option from the list");
    } while((need_mainDPS != 0) && (need_mainDPS != 1));
    if(need_mainDPS == 0) 
        return false;
    return true;
}

template<class T>
bool Team_list::isCharacterInTeamCondition(Team& team, T data, bool is_main_dps, bool need_build)
{
    if constexpr (std::is_same_v<T, int>) {
        return team.isCharacterElement(static_cast<Element>(data), is_main_dps);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return team.isCharacterInTeam(data, need_build);
    } else {
        // Handle unsupported types
        static_assert(std::is_same_v<T, int> || std::is_same_v<T, std::string>, "Unsupported type");
        return false;
    }
}


