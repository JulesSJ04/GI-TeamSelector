#include "menu.h"

/*
* @brief Link to the different options of the menu
*/
void menuModify(Box * box) {
    std::vector<std::string> menu_options = {
        "Quit                                         ",
        "Remove a character                           ",
        "Update role                                  ",
        "Update build state                           ",
        "Reset box                                    "
    };
    for (unsigned int i = 0; i < menu_options.size(); i++) {
        printMessage<std::string>(std::to_string(i) + ". " + menu_options.at(i));
    }
    int choice = 0;
    do {
        choice = inputUser<std::string, int>("Pick an option from the displayed one");
    } while(((choice < 0) || (choice > menu_options.size())));
    switch (choice)
    {
    case 0:
        return;
    case 1:
        box->updateCharacterData(0);
        break;
    case 2:
        box->updateCharacterData(1);
        break;
    case 3:
        box->updateCharacterData(3);
        break;
    case 4:
        box->resetBox();
        break;
    default:
        break;
    }
}

/*
* @brief Team finding options
*/
void menuTeams(Team_list * teams) {
    std::vector<std::string> menu_options = {
        "Quit                                         ",
        "Name : 1 team                                ",
        "Name : 2 teams                               ",
        "Element : 1 team                             ",
        "Element : 2 teams                            ",
        "Random : 1 team                              ",
        "Random : 2 teams                             ",
        "Display all teams                            "
    };
    for (unsigned int i = 0; i < menu_options.size(); i++) {
        printMessage<std::string>(std::to_string(i) + ". " + menu_options.at(i));
    }
    int choice = 0;
    do {
        choice = inputUser<std::string, int>("Pick an option from the displayed one");
    } while(((choice < 0) || (choice > menu_options.size())));
    switch (choice)
    {
    case 0:
        return;
    case 1:
        teams->displayTeamsByName();
        break;
    case 2:
        teams->displayTeamsByName(true);
        break;
    case 3:
        teams->displayTeamsByElement();
        break;
    case 4:
        teams->displayTeamsByElement(true);
        break;
    case 5:
        teams->displayRandomTeams();
        break;
    case 6:
        //printRestriction("FUNCTIONNALITY UNDER MAINTENANCE");
        teams->displayRandomTeams(true);
        break;
    case 7:
        teams->displayTeams();;
        break;
    default:
        break;
    } 
}

/*
* @brief Link to the different statistics display
*/
void menuStatistics(Statistics * stats) {
    std::vector<std::string> menu_options = {
        "Quit                                           ",
        "3 Most used characters over my teams           ",
        "3 Less used characters over my teams           ",
        "Characters frequency characters over my teams  ",
        "Characters frequency over all teams            "
    };
    for (unsigned int i = 0; i < menu_options.size(); i++) {
        printMessage<std::string>(std::to_string(i) + ". " + menu_options.at(i));
    }
    int choice = 0;
    do {
        choice = inputUser<std::string, int>("Pick an option from the displayed one");
    } while(((choice < 0) || (choice > menu_options.size())));
    switch (choice) {
    case 0:
        return;
    case 1:
        stats->computeCharacterFrequency(static_cast<Mode>(1), true);
        break;
    case 2:
        stats->computeCharacterFrequency(static_cast<Mode>(2), true);
        break;
    case 3:
        stats->computeCharacterFrequency(static_cast<Mode>(0), true);
        break;
    case 4:
        stats->computeNonAddedCharacterFrequency();
        break;
    default:
        break;    
    }

}

/*
* @brief Link to the different options of the menu
*/
void menuSwitch(int choice, Box * box, Team_list * teams, Statistics * stats)
{
    switch (choice)
    {
    case 0: //Quit
        break;
    case 1: // Display characters from my box
        box->displayBox();
        break;
    case 2: // Add character in my box
        box->addCharacterToBox(); 
        break;
    case 3: // Modify box
        menuModify(box); 
        break;
    case 4:
        menuTeams(teams);
        break;
    case 5: // Add a team to the list
        teams->addTeam();
        break;
    case 6: // Add a team to the list
        menuStatistics(stats);
        break;
    default:
        printRestriction<std::string>("Not implemented yet");
        break;
    }
}

